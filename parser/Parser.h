/*!
 * @file	Parser.h
 * @class   Parser
 * @brief  Синтаксический анализатор
 * @details В данном синтаксическом анализаторе, используется метод рекурсивного спуска.
 *  Работает анализатор до обнаружения первой ошибки, затем бросает исключение либо @ref ParseError,
 *  в случае синтаксической ошибки, либо std::invalid_argument, когда вставка элемента в @ref table, заканчивается неудачно.
 * @author	Namat
 * @date	2 дек. 2016 г.
 *
 *
 * @defgroup parser
 * @{
 */

#ifndef PARSER_H_
#define PARSER_H_

#include <unordered_map>
#include <cmath>
#include "Lexer.h"
#include "ParseError.h"

typedef std::unordered_map<ptrWord, double> hashTable;

template<class InputIterator>
class Parser {
    ///Лексический анализатор
    Lexer<InputIterator> lexer;

    ///Очередной токен
    ptrToken token;

    ///Связывает значения переменных с токеном
    hashTable table;

    ///Счетчик глубины вложенности
    int n;

public:
    Parser(InputIterator beg, InputIterator end)
            : lexer(beg, end), n(0) {
    }

    virtual ~Parser() = default;

    ///Анализ грамматики
    void parse() {
        while ( !lexer.eof()) {
            language();
        }
    }

    ///Возвращает @ref table
    hashTable getTable() const {
        return table;
    }

protected:
    ///Разбор нетерминала 'Язык'
    void language() {
        nextToken();
        if (token->tag == EoF) return;
        if (token->tag != BEGIN)
            throw ParseError(lexer.getPosition(), token->toString(),
                "Пропущено ключевое слово \"Begin\"");
        nextToken();
        if (token->tag != REAL && token->tag != INTEGER)
            throw ParseError(lexer.getPosition(), token->toString(),
                "Пропущено ключевое слово \"Real\" или \"Integer\"");
        while (token->tag == REAL || token->tag == INTEGER) {
            definition();
        }
        if (token->tag != LABEL && token->tag != VARIABLE)
            throw ParseError(lexer.getPosition(), token->toString(),
                "Пропущена метка или переменная");
        while (token->tag == LABEL || token->tag == VARIABLE) {
            operation();
        }
        if (token->tag != END)
            throw ParseError(lexer.getPosition(), token->toString(),
                "Пропущено ключевое слово \"End\"");
    }

    ///Разбор нетерминала 'Определение'
    void definition() {
        switch (token->tag) {
            case REAL: {
                nextToken();
                if (token->tag != VARIABLE)
                    throw ParseError(lexer.getPosition(), token->toString(),
                        "Пропущена переменная");
                do {
                    id();
                    nextToken();
                }
                while (token->tag == VARIABLE && !lexer.match((Tag) '='));
                break;
            }
            case INTEGER: {
                nextToken();
                if (token->tag != INT_NUM)
                    throw ParseError(lexer.getPosition(), token->toString(),
                        "Пропущено целое число");
                do {
                    nextToken();
                }
                while (token->tag == INT_NUM);
                break;
            }
            default:
                throw ParseError(lexer.getPosition(), token->toString(),
                    "Синтаксическая ошибка");
        }
    }

    ///Разбор нетерминала 'Опер'
    void operation() {
        if (token->tag == LABEL) nextToken();
        if (token->tag != VARIABLE)
            throw ParseError(lexer.getPosition(), token->toString(),
                "Пропущена переменная");
        auto it = id();
        nextToken();
        if (token->tag != '=')
            throw ParseError(lexer.getPosition(), token->toString(),
                "Пропущено '='");
        nextToken();
        additive(it->second);
    }

    ///Разбор аддитивных операций
    void additive(double& result) {
        double tmp = 0;
        multiplicative(result);
        while (token->tag == '+' || token->tag == '-') {
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

    ///Разбор мультипликативных операций
    void multiplicative(double& result) {
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
                    if ( !tmp)
                        throw ParseError(lexer.getPosition(), token->toString(),
                            "Деление на ноль");
                    result /= tmp;
                    break;
            }
        }
    }

    ///Разбор степенных операций
    void exponential(double& result) {
        double tmp = 0;
        unarySign(result);
        if (token->tag == '^') {
            nextToken();
            expression(tmp);
            result = std::pow(result, tmp);
        }
    }

    ///Разбор унарных знаков
    void unarySign(double& result) {
        int tag;
        if (token->tag == '+' || token->tag == '-') {
            tag = token->tag;
            nextToken();
        }
        expression(result);
        if (tag == '-') result = -result;
    }

    ///Разбор скобок
    void expression(double& result) {
        switch (token->tag) {
        case '(':
            nextToken();
            additive(result);
            if (token->tag != ')')
                throw ParseError(lexer.getPosition(), token->toString(),
                                 "Пропущена ')'");
            break;
        case '[': {
            ++n;
            if (n > 2)
                throw ParseError(lexer.getPosition(), token->toString(),
                                 "Превышена глубина вложенности квадратных скобок");
            nextToken();
            additive(result);
            if (token->tag != ']')
                throw ParseError(lexer.getPosition(), token->toString(),
                                 "Пропущена ']'");
            --n;
            break;
        }
        case REAL_NUM:
            result = std::static_pointer_cast<RealNumber>(token)->value;
            break;
        case INT_NUM:
            result = std::static_pointer_cast<IntegerNumber>(token)->value;
            break;
        default:
            throw ParseError(lexer.getPosition(), token->toString(),
                             "Пропущено число  или скобка");
        }
        nextToken();
    }

private:
    ///Записывает в @ref token очередной токен
    void nextToken() {
        token = lexer.token();
        if(token->tag == Tag::ERROR) throw ParseError(lexer.getPosition(), token->toString(),
                                                      "Лексическая ошибка");
    }

    ///Добавляет в @ref table новую переменную
    hashTable::iterator id() {
        auto it = table.find(std::static_pointer_cast<Word>(token));
        if (it == table.end()){
            auto i = table.emplace(std::make_pair(std::static_pointer_cast<Word>(token), 0));
            if(!i.second) throw std::invalid_argument("Parser::table.emplace() fail");
            it = i.first;
        }
        return it;
    }
};

#endif /* PARSER_H_ */
/*! @} */
