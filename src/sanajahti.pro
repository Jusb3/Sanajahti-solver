#-------------------------------------------------
#
# Project created by QtCreator 2015-11-12T00:13:26
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = sanajahti
TEMPLATE = app

QMAKE_CXXFLAGS += -std=c++11

SOURCES += main.cpp \
    window.cpp \
    solver.cpp \
    trie.cpp \
    ocr.cpp \
    console.cpp \
    ui.cpp
HEADERS  += \
    solver.hpp \
    trie.hpp \
    ocr.hpp \
    window.hpp \
    console.hpp \
    ui.hpp

