#-------------------------------------------------
#
# Project created by QtCreator 2016-12-07T16:45:43
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Parser
TEMPLATE = app

CONFIG += c++11

INCLUDEPATH += "gui/" \
    "parser/" \
    "lexer/"

SOURCES += main.cpp\
    gui/codeeditor.cpp \
    gui/dialog.cpp

HEADERS  += dialog.h\
    gui/codeeditor.h \
    gui/dialog.h \
    lexer/IntegerNumber.h \
    lexer/Label.h \
    lexer/Lexer.h \
    lexer/RealNumber.h \
    lexer/Tag.h \
    lexer/Token.h \
    lexer/Word.h \
    parser/ParseError.h \
    parser/Parser.h \
    lexer/Error.h
