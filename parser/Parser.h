/*!
 * @file	Parser.h
 * @class   Parser
 * @brief  Синтаксический анализатор
 * @details В данном синтаксическом анализаторе, используется метод рекурсивного спуска.
 *  Работает анализатор до обнаружения первой ошибки, затем бросает исключение @ref ParseError.
 * @author	Namat
 * @date	2 дек. 2016 г.
 *
 *
 * @defgroup parser
 * @{
 */

#ifndef PARSER_H_
#define PARSER_H_

#include <iostream>
#include <unordered_map>
#include "Lexer.h"

typedef std::unordered_map<ptrWord,double> hashTable;

class Parser {
    Lexer lexer;                            ///<Лексический анализатор
    ptrToken token;                         ///<Очередной токен
    hashTable table;                        ///<Хранит значения переменных
public:
    Parser(std::istream& in);
    virtual ~Parser() = default;
    void parse();                           ///<Анализ грамматики
    hashTable variables() const;            ///<Возвращает @ref table
protected:
    void language();                        ///<Разбор нетерминала 'Язык'
    void definition();                      ///<Разбор нетерминала 'Определение'
    void operation();                       ///<Разбор нетерминала 'Опер'
    void additive(double& result);          ///<Разбор аддитивных операций
    void multiplicative(double& result);    ///<Разбор мультипликативных операций
    void exponential(double& result);       ///<Разбор степенных операций
    void unarySign(double& result);         ///<Разбор унарных знаков
    void expression(double& result);        ///<Разбор скобок
private:
    void nextToken();                       ///<Записывает в @ref token очередной токен
};

#endif /* PARSER_H_ */
/*! @} */
