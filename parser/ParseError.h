/*!
 * @file	ParseError.h
 * @class   ParseError
 * @brief   Обрабатывает ошибки синтаксического анализатора.
 * @author	Namat
 * @date	5 дек. 2016 г.
 *
 * @defgroup parser
 * @{
 */

#ifndef PARSEERROR_H_
#define PARSEERROR_H_

#include <exception>
#include "Lexer.h"

class ParseError : public std::exception {
public:
    ///Относительная позиция синтаксического анализатора
    Position pos;

    ///Информация о лексеме
    std::string tok;

    ///Сообщение ошибки
    std::string msg;

    ParseError(const Position& p, const std::string& t, const std::string& m = "")
            : pos(p), tok(t), msg(m) {
    }

    virtual ~ParseError() = default;

    /*!Формирует строку по шаблону:@n
     * @ref Position ::line : @ref Position ::pos :  '@ref tok' @ref msg \\n
     */
    const char* what() const throw () override {
        std::string str;
        str += std::to_string(pos.line);
        str += ":";
        str += std::to_string(pos.pos);
        str += ": '";
        str += tok;
        str += " '";
        str += msg;
        str += "\n\0";
        return str.c_str();
    }
};

#endif /* PARSEERROR_H_ */
/*! @} */
