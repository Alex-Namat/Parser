/*
 *	Parser.cpp
 *
 *  Created on 	:   2 дек. 2016 г.
 *  Author      :   Namat
 */

#include <cmath>
#include "Parser.h"
#include "RealNumber.h"
#include "IntegerNumber.h"
#include "Word.h"
#include "ParseError.h"

Parser::Parser(std::istream& in) :
    lexer(in)
{}

void Parser::parse() {
    while(!lexer.eof()){
        language();
    }
    for(auto& i : table){
        std::cout << i.first->lexeme << ": " << i.second << std::endl;
    }
}

hashTable Parser::variables() const{
    return table;
}

void Parser::language() {
    nextToken();
    if(token->tag == EoF) return;
    if(token->tag != BEGIN) throw ParseError(lexer.position,token->toString(),"Пропущено ключевое слово <Begin>");
    nextToken();
    while(token->tag == REAL || token->tag == INTEGER){
        definition();
    }
    while(token->tag == LABEL || token->tag == VARIABLE){
        operation();
    }
    if(token->tag != END) throw ParseError(lexer.position,token->toString(),"Пропущено ключевое слово <End>");
}

void Parser::definition() {
    switch(token->tag){
        case REAL :{
            nextToken();
            do {
                if(token->tag != VARIABLE) throw ParseError(lexer.position,token->toString(),"Пропущена переменная");
                table.insert(decltype(table)::value_type(std::dynamic_pointer_cast<Word>(token),0));
                nextToken();
            } while (token->tag == VARIABLE && !lexer.match((Tag)'='));
            break;
        }
        case INTEGER :{
            nextToken();
            do {
                if(token->tag != INT_NUM) throw ParseError(lexer.position,token->toString(),"Пропущено целое число");
                nextToken();
            } while (token->tag == INT_NUM);
            break;
        }
        default:
            throw ParseError(lexer.position,token->toString(),"Синтаксическая ошибка");
    }
}

void Parser::operation() {
    if(token->tag == LABEL) nextToken();
    if(token->tag != VARIABLE) throw ParseError(lexer.position,token->toString(),"Пропущена переменная");
    auto it = table.find(std::dynamic_pointer_cast<Word>(token));
    if(it == table.end()) it = table.insert(decltype(table)::value_type(std::dynamic_pointer_cast<Word>(token),0)).first;
    nextToken();
    if(token->tag != '=') throw ParseError(lexer.position,token->toString(),"Пропущено '='");
    nextToken();
    additive(it->second);
}

void Parser::additive(double& result) {
    double tmp = 0;
    multiplicative(result);
    while (token->tag == '+' || token->tag == '-'){
        int tag = token->tag;
        nextToken();
        multiplicative(tmp);
        switch (tag) {
            case '+':
                result += tmp;
                break;
            case '-':
                result -= tmp;
                break;
        }
    }
}

void Parser::multiplicative(double& result) {
    double tmp = 0;
    exponential(result);
    while (token->tag == '*' || token->tag == '/') {
        int tag = token->tag;
        nextToken();
        exponential(tmp);
        switch (tag) {
            case '*':
                result *= tmp;
                break;
            case '/':
                if(!tmp) throw ParseError(lexer.position,token->toString(),"Деление на ноль");
                result /= tmp;
                break;
        }
    }
}

void Parser::exponential(double& result) {
    double tmp = 0;
    unarySign(result);
    if (token->tag == '^') {
        nextToken();
        expression(tmp);
        result = std::pow(result,tmp);
    }
}

void Parser::unarySign(double& result) {
    int tag;
    if(token->tag == '+' || token->tag == '-'){
        tag = token->tag;
        nextToken();
    }
    expression(result);
    if(tag == '-') result = -result;
}

void Parser::expression(double& result) {
    switch (token->tag) {
        case '(':
            nextToken();
            additive(result);
            if (token->tag != ')') throw ParseError(lexer.position,token->toString(),"Пропущена ')'");
            break;
        case '[':
            static int n = 0;
            ++n;
            if(n > 2) throw ParseError(lexer.position,token->toString(),"Глубина вложености квадратных скобок равна 2");
            nextToken();
            additive(result);
            if (token->tag != ']') throw ParseError(lexer.position,token->toString(),"Пропущена ']'");
            --n;
            break;
        case REAL_NUM:
            result = std::dynamic_pointer_cast<RealNumber>(token)->value;
            break;
        case INT_NUM:
            result = std::dynamic_pointer_cast<IntegerNumber>(token)->value;
            break;
        case VARIABLE:
            result = table.find(std::dynamic_pointer_cast<Word>(token))->second;
            break;
    }
    nextToken();
}

void Parser::nextToken() {
    token = lexer.token();
}
