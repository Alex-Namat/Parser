
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
#include <fstream>

int main(int argc, char *argv[]){
    std::fstream file;
    file.open("test.tmp");
    Lexer lexer(file);
    if(file.is_open())
    while(!lexer.eof()){
       std::cout << lexer.token()->toString() << " ";
    }
    std::cout << std::endl;
    file.close();

    file.open("test.tmp");
    Parser parser(file);
    if (file.is_open()) {
        try {
            parser.parse();
        }
        catch (ParseError& exception) {
            std::cout << exception.what();
        }
    }
    //system("pause");
    return 0;
}
