CONFIG += exceptions c++11

DEFINES += KOPI_IEXDATA

HEADERS += \
    $$PWD/iexdataendpoint.h \
    $$PWD/iexsymbolsmodel.h \
    $$PWD/iexchartsmodel.h \
    $$PWD/iexcloudglobals.h


SOURCES += \
    $$PWD/iexdataendpoint.cpp \
    $$PWD/iexsymbolsmodel.cpp \
    $$PWD/iexchartsmodel.cpp \
    $$PWD/iexcloudglobals.cpp
