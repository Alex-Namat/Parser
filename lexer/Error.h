/*!
 * @file    Error.h
 * @class   Error
 * @brief   Класс для лексических ошибок.
 * @author  Namat
 * @date    20 нояб. 2016 г.
 *
 * @defgroup lexer
 * @{
 */

#ifndef ERROR_H_
#define ERROR_H_

#include "Word.h"

class Error : public Word{
public:
    explicit Error(const std::string& str) : Word(str,Tag::ERROR){}
    virtual ~Error() = default;
};

#endif /* ERROR_H_ */
/*! @} */
