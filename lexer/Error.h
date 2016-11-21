/*
 * Error.h
 *
 *  Created on  : 20 нояб. 2016 г.
 *  Author      : Namat
 *  Description :  
 *
 */

#ifndef ERROR_H_
#define ERROR_H_

#include "Word.h"

class Error : public Word{
public:
    Error(std::string str, Tag tag) : Word(str,tag){}
    virtual ~Error(){}
    std::string toString() override {
        std::string str("[ERROR ; ");
        str += lexeme + "]";
        return str;
    }
};

#endif /* ERROR_H_ */
