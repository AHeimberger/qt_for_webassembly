include(../common.pri)
include(../protocol/protocol.pri)

TARGET = server_sensor_hub

QT = websockets

CONFIG += \
    c++11 \
    console

CONFIG -= \
    app_bundle

TEMPLATE = app

HEADERS += \
    server.h \
    sensor_data.h

SOURCES += \
    main.cpp \
    server.cpp \
    sensor_data.cpp


message("-> architecture")
message($$QMAKE_HOST.arch)
unix:contains(QMAKE_HOST.arch, aarch64):{
    INCLUDEPATH += /usr/local/include
    LIBS += -L"/usr/local/lib/" -lwiringPi
}
