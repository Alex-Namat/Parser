/*!
 * @file    Lexer.h
 * @class   Lexer
 * @brief   Лексический анализатор.
 * @details Формирует лексемы.
 *  Принимает интераторы отвечающие категории InputIterator, где char_type = char.
 *  Выбрасывает исключение std::invalid_argument,
 *  когда вставка элемента в @ref keyWords, заканчивается неудачно.
 * @author  Namat
 * @date    19 нояб. 2016 г.
 *
 * @defgroup lexer
 * @{
 */

#ifndef LEXER_H_
#define LEXER_H_

#include <memory>
#include <unordered_map>
#include <queue>
#include <exception>
#include "Token.h"
#include "Word.h"
#include "Lexer.h"
#include "IntegerNumber.h"
#include "RealNumber.h"
#include "Label.h"

typedef std::shared_ptr<Token> ptrToken;
typedef std::shared_ptr<Word> ptrWord;

/*!
 * @brief Хранит относительную и абсолютную позицию в потоке
 * @param line Номер строки. Начинается с  1
 * @param pos Номер символа в строке. Начинается с  1
 * @param absPos Абсолютная позиция. Начинается с  0
 */
struct Position{
    int line = 1;
    int pos = 1;
    int absPos = 0;
};

template<class InputIterator>
class Lexer {
    ///Указывает на абсолютную позицию в потоке
    InputIterator pos;

    ///Признак конца потока
    InputIterator end;

    ///Хранит очередной символ
    char c;

    /*!
     * @brief Хранит строковое представление  и указатель на лексему
     * @details Используется для резервирования и сопоставления ключевых слов и переменных
     */
    std::unordered_map<std::string, ptrWord> keyWords;

    ///Сохраняет результат @ref match
    ptrToken look;

    ///Позиция в потоке
    Position position;
public:

    Lexer(InputIterator beg, InputIterator end)
            : pos(beg), end(end), c( *pos), look(nullptr) {
        reserve(std::make_shared<Word>("Begin", Tag::BEGIN));
        reserve(std::make_shared<Word>("End", Tag::END));
        reserve(std::make_shared<Word>("Real", Tag::REAL));
        reserve(std::make_shared<Word>("Integer", Tag::INTEGER));
    }

    virtual ~Lexer() = default;

    ///Возвращает очередной токен их потока
    ptrToken token() {
        if (look != nullptr) {
            ptrToken tmp = look;
            look = nullptr;
            return tmp;
        }
        if (isspace(c)) skip();

        if (isdigit(c)) {
            int i = 0;
            do {
                i = 10 * i + (int) (c - '0');
                readch();
            }
            while (isdigit(c));

            if (c != '.') {
                if (c == ':') {
                    readch();
                    return std::make_shared<Label>(i);
                }
                return std::make_shared<IntegerNumber>(i);
            }
            readch();
            return doubleToken(i);
        }

        if (isalpha(c)) {
            std::string str;
            do {
                str += c;
                readch();
            }
            while (isalnum(c));
            auto it = keyWords.find(str);
            if (it != keyWords.end()) return it->second;
            ptrWord w = std::make_shared<Word>(str);
            auto i = keyWords.insert(std::make_pair(str, w));
            if ( !i.second)
                throw std::invalid_argument("Lexer::keyWords.insert() fail");
            return i.first->second;
        }

        if (c == '.') {
            readch();
            if (isdigit(c))
                return doubleToken(0);
            else
                return std::make_shared<Token>('.');
        }

        ptrToken token = std::make_shared<Token>(c);
        if(!eof()) readch();
        return token;
    }

    ///Проверяет конец файла
    bool eof() const {
        return pos == end;
    }

    ///Проверяет тип следующего токена
    bool match(Tag t) {
        Position pos(position);
        bool f = false;
        look = token();
        if (t == look->tag) f = true;
        position = pos;
        return f;
    }

    ///Возвращает @ref position
    Position getPosition() const {
        return position;
    }

private:
    ///Резервирует ключевые слова
    void reserve(ptrWord w) {
        auto i = keyWords.insert(std::make_pair(w->lexeme, w));
        if ( !i.second)
            throw std::invalid_argument("Lexer::keyWords.insert() fail");
    }

    ///Считывает очередной символ
    void readch() {
        ++pos;
        if (eof()) {
            c = (char) Tag::EoF;
            return;
        }
        c = *pos;
        ++position.pos;
        ++position.absPos;
    }

    ///Пропуск пробелов
    void skip() {
        do {
            if ( !isblank(c))
                if (isspace(c)) {
                ++position.line;
                position.pos = 0;
            }
            readch();
        }
        while (isspace(c));
        return;
    }

    /*!
     * @brief Формирует токен вещественного числа
     * @param i Целая часть числа
     */
    ptrToken doubleToken(int i) {
        double d = i;
        double f = 10;
        if ( !isdigit(c)) return std::make_shared<RealNumber>(d);
        do {
            d += int(c - '0') / f;
            f *= 10;
            readch();
        }
        while (isdigit(c));
        return std::make_shared<RealNumber>(d);
    }

};

#endif /* LEXER_H_ */
/*! @} */

