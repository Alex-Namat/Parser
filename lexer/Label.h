/*!
 *  @file    Label.h
 *  @class   Label
 *  @brief   Класс для меток.
 *  @author  Namat
 *  @date    19 нояб. 2016 г.
 *
 *  @defgroup lexer
 * @{
 */

#ifndef LABEL_H_
#define LABEL_H_

#include "Token.h"

class Label : public Token {
public:
    /// Хранит значение метки.
    const int value;

    explicit Label(const int& v)
            : Token(Tag::LABEL), value(v) {
    }

    virtual ~Label() = default;

    ///Возвращает строковое значение метки
    std::string toString() const override {
        std::string str(std::to_string(value));
        str += ":";
        return str;
    }
};

#endif /* LABEL_H_ */
/*! @} */
