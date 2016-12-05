/*!
 * @file    Word.h
 * @class   Word
 * @brief   Класс для переменных и ключевых слов.
 * @author  Namat
 * @date    19 нояб. 2016 г.
 *
 * @defgroup lexer
 * @{
 */

#ifndef WORD_H_
#define WORD_H_

#include "Token.h"
#include <string>

class Word : public Token{
public:
    const std::string lexeme;   ///< Хранит строковое представление лексемы.
    Word(const std::string& str,const Tag tag = Tag::VARIABLE)
        : Token(tag), lexeme(str){}
    virtual ~Word(){}
    ///Формирует строку по шаблону: [Тип лексемы ; Значение]
    std::string toString() const override {
        std::string str("[");
        switch (tag) {
            case Tag::VARIABLE:
                str += "VARIABLE";
                break;
            case Tag::BEGIN:
                str += "BEGIN";
                break;
            case Tag::END:
                str += "END";
                break;
            case Tag::INTEGER:
                str += "INTEGER";
                break;
            case Tag::REAL:
                str += "REAL";
                break;
            default:
                str += std::to_string(tag);
                break;
        }
        str += " ; " + lexeme + "]";
        return str;
    }
};

#endif /* WORD_H_ */
/*! @} */
