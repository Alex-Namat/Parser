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
#include <exception>
#include "Token.h"
#include "IntegerNumber.h"
#include "RealNumber.h"
#include "Label.h"
#include "Error.h"

typedef std::shared_ptr<Token> ptrToken;
typedef std::shared_ptr<Word> ptrWord;

/*!
 * @brief Хранит относительную и абсолютную позицию в потоке
 * @param line Номер строки.
 * @param pos Номер символа в строке.
 * @param absPos Абсолютная позиция.
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
    std::pair<ptrToken,Position> look;

    ///Позиция в потоке
    Position position;
public:

    Lexer(InputIterator beg, InputIterator end)
        : pos(beg), end(end) {

        if(!eof()) c = *pos;
        look.first = nullptr;

        reserve(std::make_shared<Word>("Begin", Tag::BEGIN));
        reserve(std::make_shared<Word>("End", Tag::END));
        reserve(std::make_shared<Word>("Real", Tag::REAL));
        reserve(std::make_shared<Word>("Integer", Tag::INTEGER));
    }

    virtual ~Lexer() = default;

    ///Возвращает очередной токен их потока
    ptrToken token() {
        if (look.first != nullptr) {
            ptrToken tmp = look.first;
            look.first = nullptr;
            position = look.second;
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
                if(isalpha(c)) return errorToken(std::to_string(i));
                return std::make_shared<IntegerNumber>(i);
            }
            readch();

            if (!isdigit(c)) return errorToken(std::to_string(i) + ".");
            double d = i;
            double f = 10;
            do {
                d += int(c - '0') / f;
                f *= 10;
                readch();
            }
            while (isdigit(c));
            return std::make_shared<RealNumber>(d);
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
            auto i = keyWords.emplace(std::make_pair(str, w));
            if ( !i.second)
                throw std::invalid_argument("Lexer::keyWords.emplace() fail");
            return i.first->second;
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
    bool match(const Tag& t) {
        Position pos(position);
        bool f = false;
        ptrToken tmp = token();
        look = std::make_pair(tmp,position);
        if (t == look.first->tag) f = true;
        position = pos;
        return f;
    }

    ///Возвращает @ref position
    Position getPosition() const {
        return position;
    }

private:
    ///Резервирует ключевые слова
    void reserve(const ptrWord& w) {
        auto i = keyWords.emplace(std::make_pair(w->lexeme, w));
        if ( !i.second)
            throw std::invalid_argument("Lexer::keyWords.emplace() fail");
    }

    ///Считывает очередной символ
    void readch() {
        ++pos;
        if (eof()) {
            c = (char) Tag::EoF;
            return;
        }
        c = *pos;

#ifdef _MSC_VER
    if (c < -1 || c > 255)
        throw std::invalid_argument("Not ASCII-char.");
#endif

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

    ///Формирует токен лексической ошибки
    ptrToken errorToken(std::string str) {
        do {
            str += c;
            readch();
        } while (!(eof() || isspace(c)));
        return std::make_shared<Error>(str);
    }
};

#endif /* LEXER_H_ */
/*! @} */

