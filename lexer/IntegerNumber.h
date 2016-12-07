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

class IntegerNumber : public Token {
public:
    /// Хранит значение числа.
    const int value;

    IntegerNumber(const int& v)
            : Token(Tag::INT_NUM), value(v) {
    }

    virtual ~IntegerNumber() = default;

    ///Возвращает строковое значение числа
    std::string toString() const override {
        return std::to_string(value);
    }
};

#endif /* INTEGERNUMBER_H_ */
/*! @} */
