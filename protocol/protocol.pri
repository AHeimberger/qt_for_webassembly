LIB_NAME = protocol
LIB_PREFIX = lib
LIB_SUFFIX = .a

DIRECTORY = $$clean_path($${OUT_PWD}/../$${LIB_NAME}/$${DESTDIR}/)

LIBS += -L$${DIRECTORY} -l$${LIB_NAME}

INCLUDEPATH += $${PWD}/includes

DEPENDPATH += $${PWD}/includes

PRE_TARGETDEPS += $${DIRECTORY}/$${LIB_PREFIX}$${LIB_NAME}$${LIB_SUFFIX}
