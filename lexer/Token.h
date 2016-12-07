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

class Token {
public:
    ///Содержит тип лексемы @ref Tag
    const int tag;

    Token(const int& t)
            : tag(t) {
    }

    virtual ~Token() = default;

    ///Возвращает строковое значение типа лексемы.
    virtual std::string toString() const {
        std::string str;
        str +=(char) tag;
        return str;
    }
};

#endif /* TOKEN_H_ */
/*! @} */
