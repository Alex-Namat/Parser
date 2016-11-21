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

class Label : public Token{
public:
    const int value;    ///< Хранит значение метки.
    Label(int v) : Token(Tag::LABEL), value(v){}
    virtual ~Label(){}
    ///Выводит строку по шаблону: [LABEL ; Значение]
    std::string toString() override {
        std::string str("[LABEL ; ");
        str += std::to_string(value) + "]";
        return str;
    }
};

#endif /* LABEL_H_ */
/*! @} */