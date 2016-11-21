/*!
 * @file    Token.h
 * @class   Token
 * @brief   Класс для токенов.
 * @author  Namat
 * @date    19 нояб. 2016 г.
 *
 * @defgroup lexer
 * @{
 */

#ifndef TOKEN_H_
#define TOKEN_H_

#include <string>
#include "Tag.h"

class Token{
public:
    const int tag;  ///<Содержит тип лексемы @ref Tag
    Token(int t) : tag(t) {}
    virtual ~Token(){}
    ///Выводит строку по шаблону: [Тип лексемы]
    virtual std::string toString(){
        std::string str("[");
        str += (char)tag + "]";
        return str;
    }
};

#endif /* TOKEN_H_ */
/*! @} */
