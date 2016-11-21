/*
 * Lexer.cpp
 *
 *  Created on  : 19 нояб. 2016 г.
 *  Author      : Namat
 *  Description :  
 *
 */

#include <sstream>
#include "Lexer.h"
#include "IntegerNumber.h"
#include "RealNumber.h"
#include "Label.h"
#include "Error.h"

int Lexer::line = 1;

Lexer::Lexer(std::istream& in) :
    stream(in), peek(' ')
{
    reserve(std::make_shared<Word>("Begin",Tag::BEGIN));
    reserve(std::make_shared<Word>("End",Tag::END));
    reserve(std::make_shared<Word>("Real",Tag::REAL));
    reserve(std::make_shared<Word>("Integer",Tag::INTEGER));
}

Lexer::~Lexer() {
    // TODO Auto-generated destructor stub
}

ptrToken Lexer::token() {
    skip();

    if(isdigit(peek) || peek == '.'){
        if(peek == '.') return doubleToken(0);
        int i = 0;
        do {
            i = 10*i + (int)(peek - '0');
            readch();
        } while (isdigit(peek));

        if (peek != '.'){
            if (peek == ':'){
                return std::make_shared<Label>(i);
            }
            if(!isspace(peek) && !eof())
                return errorToken(std::to_string(i));
            return std::make_shared<IntegerNumber>(i);
        }

        return doubleToken(i);
    }

    if(isalpha(peek)){
        std::string str;
        do {
            str += peek;
            readch();
        } while (isalnum(peek));
        if(!(isspace(peek) || eof()))
            return errorToken(str);
        auto it = keyWords.find(str);
        if( it != keyWords.end()) return it->second;
        ptrWord w = std::make_shared<Word>(str,Tag::VARIABLE);
        auto i = keyWords.insert(decltype(keyWords)::value_type(str, w));
        //warning
        if(!i.second) throw;
        return i.first->second;
    }

    if(!isspace(peek))
        return errorToken(std::string());

    ptrToken token = std::make_shared<Token>(peek);
    return token;
}

void Lexer::reserve(ptrWord w) {
    //warning
    keyWords.insert(decltype(keyWords)::value_type(w->lexeme, w));
}

void Lexer::readch() {
    peek = stream.get();
}

ptrToken Lexer::errorToken(std::string str) {
    do{
    str += peek;
        readch();
    }while(!(eof() || isspace(peek)));

    return std::make_shared<Error>(str,Tag::ERROR);
}

bool Lexer::eof() {
    return stream.peek() == std::char_traits<char>::eof();
}

void Lexer::skip() {
    readch();
    while(isspace(peek)){
    readch();
        if (isblank(peek))
            continue;
        if (isspace(peek))
            ++line;
    };
    if(eof()) peek = ' ';
    return;
}

ptrToken Lexer::doubleToken(int i) {
    double d = i;
    double f = 10;
    if ( !eof())
        if ( ! (isdigit(stream.peek()) || isspace(stream.peek())))
            return errorToken(std::to_string(i));
    readch();
    if (isspace(peek)) return std::make_shared<RealNumber>(d);
    do {
        d += int(peek - '0') / f;
        f *= 10;
        readch();
    }
    while (isdigit(peek));
    if ( ! (isspace(peek) || eof())) {
        std::ostringstream strs;
        strs << d;
        std::string str = strs.str();
        return errorToken(str);
    }
    std::string s;
    return std::make_shared<RealNumber>(d);
}
