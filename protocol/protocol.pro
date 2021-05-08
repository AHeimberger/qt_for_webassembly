include(../common.pri)

TARGET = protocol

QT += \
    core

CONFIG += qt
CONFIG += c++11
CONFIG += staticlib

TEMPLATE = lib

INCLUDEPATH += \
    includes

HEADERS += \
    includes/protocol.h

SOURCES += \
    sources/protocol.cpp
