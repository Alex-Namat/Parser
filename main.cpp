///@copyright
/*!
 * @mainpage    Синтаксический анализатор
 * @author      Namat
 * @date        19 нояб. 2016 г.
 * @details     @b Задание:
 *      @n Разработать синтаксический анализатор по заданному языку:
 *
 */
/*!
 * @defgroup lexer Лексический анализатор
 * @brief Реализовывает лексический анализатор.
 */

#include "Lexer.h"
#include <iostream>
#include <fstream>

int main(int argc, char *argv[]){
    std::ifstream file("test.tmp");
    Lexer lexer(file);
    if(file.is_open())
    while(!lexer.eof()){
       std::cout << lexer.token()->toString() << " ";
    }
    return 0;
}
