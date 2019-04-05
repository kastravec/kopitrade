QT += quick
CONFIG += c++11

TARGET = SortFilterProxyModel
TEMPLATE = lib
VERSION = 0.2.0

include(SortFilterProxyModel.pri)

CONFIG += create_pc create_prl no_install_prl

INCLUDEPATH += $$PWD

unix:!mac:isEmpty(PREFIX) {
    message("Install PREFIX not set; using /usr/local. You can change this with 'qmake PREFIX=...'")
    PREFIX = /usr/local
}

headers.path = $${PREFIX}/include/SortFilterProxyModel
headers.files = $$PWD/qqmlsortfilterproxymodel.h

filter_headers.path = $${PREFIX}/include/SortFilterProxyModel/filters
filter_headers.files = $$PWD/filters/filter.h \
    $$PWD/filters/filtercontainer.h \
    $$PWD/filters/rolefilter.h \
    $$PWD/filters/valuefilter.h \
    $$PWD/filters/indexfilter.h \
    $$PWD/filters/regexpfilter.h \
    $$PWD/filters/rangefilter.h \
    $$PWD/filters/expressionfilter.h \
    $$PWD/filters/filtercontainerfilter.h \
    $$PWD/filters/anyoffilter.h \
    $$PWD/filters/alloffilter.h

sorter_headers.path = $${PREFIX}/include/SortFilterProxyModel/sorters
sorter_headers.files = $$PWD/sorters/sorter.h \
    $$PWD/sorters/sortercontainer.h \
    $$PWD/sorters/rolesorter.h \
    $$PWD/sorters/stringsorter.h \
    $$PWD/sorters/expressionsorter.h \
    $$PWD/sorters/filtersorter.h

proxyrole_headers.path = $${PREFIX}/include/SortFilterProxyModel/proxyroles
proxyrole_headers.files = $$PWD/proxyroles/proxyrole.h \
    $$PWD/proxyroles/proxyrolecontainer.h \
    $$PWD/proxyroles/joinrole.h \
    $$PWD/proxyroles/switchrole.h \
    $$PWD/proxyroles/expressionrole.h \
    $$PWD/proxyroles/singlerole.h \
    $$PWD/proxyroles/regexprole.h \
    $$PWD/proxyroles/filterrole.h

target.path = $${PREFIX}/lib

QMAKE_PKGCONFIG_NAME = SortFilterProxyModel
QMAKE_PKGCONFIG_DESCRIPTION = A nicely exposed QSortFilterProxyModel for QML
QMAKE_PKGCONFIG_LIBS = -L$$target.path -lSortFilterProxyModel
QMAKE_PKGCONFIG_CFLAGS = -I$$headers.path

# This is our libdir
QMAKE_PKGCONFIG_LIBDIR = $$target.path

# This is where our API specific headers are
QMAKE_PKGCONFIG_INCDIR = $$headers.path
QMAKE_PKGCONFIG_DESTDIR = pkgconfig
QMAKE_PKGCONFIG_PREFIX = $${PREFIX}
QMAKE_PKGCONFIG_VERSION = $$VERSION

INSTALLS += headers filter_headers sorter_headers proxyrole_headers target
