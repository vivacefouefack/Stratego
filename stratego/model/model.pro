TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt
QMAKE_CXXFLAGS += -pedantic-errors

SOURCES += \
        main.cpp

HEADERS += \
    Board.h \
    Game.h \
    Piece.h \
    Player.h \
    Position.h
