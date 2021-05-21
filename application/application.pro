include(../common.pri)
include(../protocol/protocol.pri)

TARGET = application

wasm {
    # https://stackoverflow.com/questions/56878180/emsripten-compiled-qt-application-does-not-show-images
    QTPLUGIN += qsvg
}

QT += \
    core \
    gui \
    widgets \
    network \
    websockets \
    qml

CONFIG -= app_bundle

TEMPLATE = app

INCLUDEPATH += \
    includes

HEADERS += \
    includes/application.h \
    includes/applicationsettings.h \
    includes/dataprovider.h \
    includes/programinformation.h \
    includes/slidecontrol.h \
    includes/themeprovider.h \
    includes/valueslist.h

SOURCES += \
    sources/application.cpp \
    sources/applicationsettings.cpp \
    sources/dataprovider.cpp \
    sources/main.cpp \
    sources/slidecontrol.cpp \
    sources/themeprovider.cpp \
    sources/valueslist.cpp


RESOURCES += \
    qml.qrc
