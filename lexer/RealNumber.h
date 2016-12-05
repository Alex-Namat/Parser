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
    const double value; ///< Хранит значение числа.
    RealNumber(const double& v) : Token(Tag::REAL_NUM), value(v) {}
    virtual ~RealNumber() = default;
    ///Формирует строку по шаблону: [REAL_NUM ; Значение]
    std::string toString() const override {
        std::string str("[REAL_NUM ; ");
        str += std::to_string(value) + "]";
        return str;
    }
};

#endif /* REALNUMBER_H_ */
/*! @} */
