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
CONFIG += c++11

SOURCES += src/main.cpp \
    src/window.cpp \
    src/solver.cpp \
    src/trie.cpp \
    src/ocr.cpp \
    src/console.cpp \
    src/ui.cpp \
    src/to64bitchars.cpp \
    src/adb_screenshot.cpp \
    src/solver_thread.cpp
HEADERS  += \
    src/solver.hpp \
    src/trie.hpp \
    src/ocr.hpp \
    src/window.hpp \
    src/console.hpp \
    src/ui.hpp \
    src/to64bitchars.hpp \
    src/adb_screenshot.hpp \
    src/solver_thread.hpp

