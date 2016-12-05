/*!
 * @file    Lexer.h
 * @class   Lexer
 * @brief   Лексический анализатор.
 * @details Формирует лексемы.
 *  Выбрасывает исключение std::invalid_argument,
 *  когда проваливается попытка зарегистрировать ключевое слово в @ref keyWords
 * @author  Namat
 * @date    19 нояб. 2016 г.
 *
 * @defgroup lexer
 * @{
 */


#ifndef LEXER_H_
#define LEXER_H_

#include <memory>
#include <istream>
#include <unordered_map>
#include <queue>
#include "Token.h"
#include "Word.h"

typedef std::shared_ptr<Token> ptrToken;
typedef std::shared_ptr<Word> ptrWord;
typedef std::pair<int,int> Position;

class Lexer {
    std::istreambuf_iterator<char> pos;                 ///<Указывает на абсолютную позицию в потоке
    std::istreambuf_iterator<char> end;                 ///<Признак конца файла
    char c;                                             ///<Хранит очередной символ
    /*!
     * Используется для резервирования и сопоставления ключевых слов и переменных
     */
    std::unordered_map<std::string,ptrWord> keyWords;   ///<Хранит строковое представление  и указатель на лексему
    std::queue<ptrToken> queue;                         ///<Сохраняет результаты @ref match
public:
    /*!
     * @param first Номер строки. Начинается с  0
     * @param second Номер символа в строке. Начинается с  0
     */
    Position position;                                  ///<Хранит относительную позицию в потоке
    Lexer(std::istream& in);
    virtual ~Lexer() = default;
    ptrToken token();                                   ///<Возвращает очередной токен их потока
    bool eof() const;                                   ///<Проверяет конец файла
    /*!
     * @param t Тип токена
     * @details Проверяет следуюший токен с переданным типом и возвращает результат.@n
     * Сохраняет токен в @ref queue, впоследствии токен выбирается с помощью @ref token и удаляется из @ref queue.
     */
    bool match(Tag t);                                  ///<Проверяет тип следующего токена
private:
    void reserve(ptrWord w);                            ///<Резервирует ключевые слова
    void readch();                                      ///<Считывает очередной символ
    void skip();                                        ///<Пропуск пробелов
    ptrToken doubleToken(int i);                        ///<Формирует токен вещественного числа @param i Целая часть числа
    ptrToken tok();                                     ///<Формирует токен
};

/*! @fn bool match(Tag t)
 *  @param t Тип токена
 *  @details Проверяет следующий токен с переданным типом и возвращает результат.@n
 *  Сохраняет токен в queue, впоследствии токен выбирается с помощью token() и удаляется из queue.
 */
#endif /* LEXER_H_ */
/*! @} */
