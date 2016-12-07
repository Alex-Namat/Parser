/*!
 * @file    RealNumber.h
 * @class   RealNumber
 * @brief   Класс для вещественных чисел.
 * @author  Namat
 * @date    19 нояб. 2016 г.
 *
 * @defgroup lexer
 * @{
 */

#ifndef REALNUMBER_H_
#define REALNUMBER_H_

#include "Token.h"

class RealNumber : public Token {
public:
    /// Хранит значение числа.
    const double value;

    RealNumber(const double& v)
            : Token(Tag::REAL_NUM), value(v) {
    }

    virtual ~RealNumber() = default;

    ///Возвращает строковое значение числа
    std::string toString() const override {
        return std::to_string(value);
    }
};

#endif /* REALNUMBER_H_ */
/*! @} */
