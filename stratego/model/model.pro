TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt
QMAKE_CXXFLAGS += -pedantic-errors -Wall

SOURCES += \
        main.cpp

HEADERS += \
    Game.h \
    IObserver.h \
    Piece.h \
    Player.h \
    Position.h
