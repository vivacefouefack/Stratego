TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt
QMAKE_CXXFLAGS += -pedantic-errors -Wall

SOURCES += \
        main.cpp

HEADERS += \
    View.h
