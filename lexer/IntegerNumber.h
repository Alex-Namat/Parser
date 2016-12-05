/*!
 * @file    IntegerNumber.h
 * @class   IntegerNumber
 * @brief   Класс для целых чисел.
 * @author  Namat
 * @date    19 нояб. 2016 г.
 *
 * @defgroup lexer
 * @{
 */

#ifndef INTEGERNUMBER_H_
#define INTEGERNUMBER_H_

#include "Token.h"

class IntegerNumber : public Token{
public:
    const int value;    ///< Хранит значение числа.
    IntegerNumber(const int& v) : Token(Tag::INT_NUM), value(v){}
    virtual ~IntegerNumber() = default;
    ///Формирует строку по шаблону: [INT_NUM ; Значение]
    std::string toString() const override{
        std::string str("[INT_NUM ; ");
        str += std::to_string(value) + "]";
        return str;
    }
};

#endif /* INTEGERNUMBER_H_ */
/*! @} */
