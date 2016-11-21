/*!
 * @file    Tag.h
 * @section @enum Tag
 * @brief   Типы лексем.
 * @author  Namat
 * @date    19 нояб. 2016 г.
 *
 * @defgroup lexer
 * @{
 */

#ifndef TAG_H_
#define TAG_H_
//unary minus
enum Tag{
    VARIABLE = 1000,    ///< Переменная
    REAL_NUM,           ///< Вещественное число
    INT_NUM,            ///< Целое число
    LABEL,              ///< Метка
    BEGIN,              ///< Ключевое слово "Begin"
    END,                ///< Ключевое слово "End"
    REAL,               ///< Ключевое слово "Real"
    INTEGER,            ///< Ключевое слово "Integer"
    ERROR               ///< Лексическая ошибка
};



#endif /* TAG_H_ */
/// @} /
