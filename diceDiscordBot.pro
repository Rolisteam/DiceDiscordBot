QT += core network websockets
QT -= gui

CONFIG += c++11

TARGET = diceParserDiscordBot
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    selfbot.cpp \
    utils.cpp \
    command.cpp \
    interpreter.cpp \
    commandmanager.cpp \
    config.cpp

HEADERS += \
    selfbot.hpp \
    utils.hpp \
    command.hpp \
    interpreter.hpp \
    commandmanager.hpp \
    config.hpp

LIBS += -lQDiscord

#include(commands/commands.pri)
include(diceparser/diceparser.pri)
