CONFIG += exceptions c++11

DEFINES += KOPI_CORE

INCLUDEPATH +=$$PWD/src

HEADERS += $$PWD/src/portfolio.h \
    $$PWD/src/asset.h \
    $$PWD/src/trade.h \
    $$PWD/src/assetlistmodel.h \
    $$PWD/src/tradelistmodel.h \
    $$PWD/src/portfoliolistmodel.h \
    $$PWD/src/ksymbol.h \
    $$PWD/src/ksymbolmodel.h \
    $$PWD/src/kaccount.h \
    $$PWD/src/kaccountlistmodel.h \
    $$PWD/src/watchlistsmodel.h \
    $$PWD/src/watchlistsymbolmodel.h

SOURCES += $$PWD/src/portfolio.cpp \
    $$PWD/src/asset.cpp \
    $$PWD/src/trade.cpp \
    $$PWD/src/assetlistmodel.cpp \
    $$PWD/src/tradelistmodel.cpp \
    $$PWD/src/portfoliolistmodel.cpp \
    $$PWD/src/ksymbol.cpp \
    $$PWD/src/ksymbolmodel.cpp \
    $$PWD/src/kaccount.cpp \
    $$PWD/src/kaccountlistmodel.cpp \
    $$PWD/src/watchlistsmodel.cpp \
    $$PWD/src/watchlistsymbolmodel.cpp

