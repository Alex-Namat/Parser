/*!
 * @mainpage    Синтаксический анализатор
 * @details   @b Вариант 17 @n
 *      @b Задание:
 *      @n Разработать синтаксический анализатор по заданному языку: @n
 *      Язык = <<Begin>> Определение...Определение Опер...Опер <<End>> @n
 *      Определение = <<Real>> Перем...Перем ! <<Integer>> Цел...Цел @n
 *      Опер = </ Метка <<:>> /> Перем <<=>> Прав.часть @n
 *      @n
 *      В Прав.части - переменные и вещественные числа;
 *      соединены аддитивными, мультипликативными и степенными операциями;
 *      есть круглые скобки с любой глубиной вложенности и квадратные скобки с глубиной вложенности 2. @n
 *      Переменная - набор букв и цифр с первой буквой. @n
 *      Метка целочисленная. @n
 *      Латинский алфавит, десятичная арифметика. @n
 * @author      Namat
 * @date        19 нояб. 2016 г.
 */
/*!
 * @defgroup lexer Лексический анализатор
 * @brief Реализовывает лексический анализатор.
 *
 * @defgroup parser Синтаксический анализатор
 * @brief Реализовывает синтаксический анализатор.
 */

#include "Lexer.h"
#include "Parser.h"
#include "ParseError.h"
#include <iostream>
#include <iterator>
#include <fstream>
#include <string>

int main(int argc, char *argv[]) {
    std::fstream file("test.tmp");
    file >> std::noskipws;
    using T = std::istream_iterator<char>;
    using S = std::string::iterator;

    T beg(file), end;
    Lexer<T> lexer(beg,end);
    while ( !lexer.eof()) {
        std::cout << lexer.token()->toString() << " ";
    }
    std::cout << std::endl;

    std::fstream file1("test.tmp");
    file1 >> std::noskipws;
    std::string str;
    std::copy(T(file1),T(),std::back_inserter(str));
    Parser<S> parser(str.begin(), str.end());
    try {
            parser.parse();
            auto table = parser.getTable();
            for (auto& i : table) {
                std::cout << i.first->lexeme << " = " << i.second << std::endl;
            }
    }
    catch (ParseError& exception) {
        std::cout << exception.what();
    }

//system("pause");
return 0;
}
