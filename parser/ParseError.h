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

class ParseError : public std::exception {
public:
    std::pair<int,int> pos;                 ///<Относительная позиция синтаксического анализатора.
    std::string tok;                        ///<Информация о лексеме.
    std::string msg;                        ///<Сообщение ошибки
    ParseError(std::pair<int,int>& p, std::string t, std::string m  = "")
        :  pos(p), tok(t), msg(m){}
    virtual ~ParseError(){}
    /*!Формирует строку по шаблону:@n
     * @ref pos.first : @ref pos.second : @ref tok '@ref msg' \\n
     */
    const char* what() const throw() override{
        std::string str;
        str += std::to_string(pos.first);
        str += ":";
        str += std::to_string(pos.second);
        str += ": ";
        str += tok;
        str += " '";
        str += msg;
        str += "'\n";
        return str.c_str();
    }
};

#endif /* PARSEERROR_H_ */
/*! @} */
