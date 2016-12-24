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

class Word : public Token {
public:
    /// Хранит строковое представление лексемы.
    const std::string lexeme;

    explicit Word(const std::string& str, const Tag& tag = Tag::VARIABLE)
            : Token(tag), lexeme(str) {
    }

    virtual ~Word() = default;

    ///Возвращает строковое значение лексемы
    std::string toString() const override {
        return lexeme;
    }
};

#endif /* WORD_H_ */
/*! @} */
