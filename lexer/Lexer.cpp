/*
 * Lexer.cpp
 *
 *  Created on  : 19 нояб. 2016 г.
 *  Author      : Namat
 *  Description :  
 *
 */

#include "Lexer.h"
#include "IntegerNumber.h"
#include "RealNumber.h"
#include "Label.h"
#include <iostream>
#include <exception>

Lexer::Lexer(std::istream& in) :
    pos(in), c(*pos), position(0,0)
{
    reserve(std::make_shared<Word>("Begin",Tag::BEGIN));
    reserve(std::make_shared<Word>("End",Tag::END));
    reserve(std::make_shared<Word>("Real",Tag::REAL));
    reserve(std::make_shared<Word>("Integer",Tag::INTEGER));
}

ptrToken Lexer::token(){
    if(!queue.empty()) {
        ptrToken tmp = queue.front();
        queue.pop();
        return tmp;
    }
    if(isspace(c)) skip();

    if(isdigit(c)){
        int i = 0;
        do {
            i = 10*i + (int)(c - '0');
            readch();
        } while (isdigit(c));

        if (c != '.'){
            if (c == ':'){
                readch();
                return std::make_shared<Label>(i);
            }
            return std::make_shared<IntegerNumber>(i);
        }
        readch();
        return doubleToken(i);
    }

    if(isalpha(c)){
        std::string str;
        do {
            str += c;
            readch();
        } while (isalnum(c));
        auto it = keyWords.find(str);
        if( it != keyWords.end()) return it->second;
        ptrWord w = std::make_shared<Word>(str);
        auto i = keyWords.insert(decltype(keyWords)::value_type(str, w));
        if (!i.second) throw std::invalid_argument("keyWords.insert() fail");
        return i.first->second;
    }

    if (c == '.') {
        readch();
        if (isdigit(c))
            return doubleToken(0);
        else
            return std::make_shared<Token>('.');
    }

    return tok();
}

void Lexer::reserve(ptrWord w){
    auto i = keyWords.insert(decltype(keyWords)::value_type(w->lexeme, w));
    if (!i.second) throw std::invalid_argument("keyWords.insert() fail");
}

void Lexer::readch(){
    ++pos;
    c = *pos;
    ++position.second;
}

bool Lexer::eof() const{
    return pos == end;
}

bool Lexer::match(Tag t){
    /*
   std::istreambuf_iterator<char> it = pos;
   bool f = false;
   if(c == token()->tag) f = true;
   pos = it;
   return f;
   */
    bool f = false;
    queue.push(token());
    if (t == queue.front()->tag) f = true;
    return f;
}

void Lexer::skip(){
    do {
        if ( !isblank(c))
            if (isspace(c)) {
            ++position.first;
            position.second = 0;
        }
        readch();
    }
    while (isspace(c));
    if (eof()) c = (char) Tag::EoF;
    return;
}

ptrToken Lexer::doubleToken(int i){
    double d = i;
    double f = 10;
    if (!isdigit(c)) return std::make_shared<RealNumber>(d);
    do {
        d += int(c - '0') / f;
        f *= 10;
        readch();
    }
    while (isdigit(c));
    return std::make_shared<RealNumber>(d);
}

ptrToken Lexer::tok(){
    ptrToken token = std::make_shared<Token>(c);
    readch();
    return token;
}
