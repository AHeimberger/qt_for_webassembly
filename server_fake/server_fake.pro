include(../common.pri)
include(../protocol/protocol.pri)

TARGET = server_fake

QT = websockets

CONFIG += \
    c++11 \
    console

CONFIG -= \
    app_bundle

TEMPLATE = app

HEADERS += \
    server.h

SOURCES += \
    main.cpp \
    server.cpp
