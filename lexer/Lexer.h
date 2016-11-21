/*!
 * @file    Lexer.h
 * @class   Lexer
 * @brief   Лексический анализатор.
 * @author  Namat
 * @date    19 нояб. 2016 г.
 *
 * @defgroup lexer
 * @{
 */

#ifndef LEXER_H_
#define LEXER_H_

#include <istream>
#include <unordered_map>
#include <memory>
#include "Token.h"
#include "Word.h"

typedef std::shared_ptr<Token> ptrToken;
typedef std::shared_ptr<Word> ptrWord;

class Lexer {
public:
    static int line;
    Lexer(std::istream& in);
    virtual ~Lexer();
    ptrToken token();                                   ///<Возвращает очередной токен их потока.
    bool eof();                                         ///<Проверяет конец файла.
private:
    void reserve(ptrWord w);                            ///<Резервирует ключевые слова.
    void readch();                                      ///<Считывает очередной символ
    ptrToken errorToken(std::string str);               ///<Формирует токен лексической ошибки.
    void skip();                                        ///<Пропуск пробелов.
    ptrToken doubleToken(int i);                        ///<Формирует токен вещественного числа @param i Целая часть числа
    std::istream& stream;                               ///<Поток для чтения входной последовательности
    char peek;                                          ///<Хранит очередной входной символ
    std::unordered_map<std::string,ptrWord> keyWords;   ///<Хранит строковое представление  и указатель на лексему
    /*! @var keyWords
     *  @details Используется для резервирования и сопоставления ключевых слов и переменных
     */
};

#endif /* LEXER_H_ */
/*! @} */
