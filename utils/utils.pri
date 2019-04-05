CONFIG += exceptions c++11

DEFINES += KOPI_UTILS

HEADERS += \
    $$PWD/src/httprest.h \
    $$PWD/src/kscheduler.h \
    $$PWD/src/jsonobjectlist.h

SOURCES +=    \
    $$PWD/src/httprest.cpp \
    $$PWD/src/kscheduler.cpp \
    $$PWD/src/jsonobjectlist.cpp
