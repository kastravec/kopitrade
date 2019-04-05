##################################################################################
#    Copyright (C) 2019 Petref Saraci
#    psaraci@gmail.com
#
#    This program is free software: you can redistribute it and/or modify
#    it under the terms of the GNU General Public License as published by
#    the Free Software Foundation, either version 3 of the License, or
#    (at your option) any later version.
#
#    This program is distributed in the hope that it will be useful,
#    but WITHOUT ANY WARRANTY; without even the implied warranty of
#    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#    GNU General Public License for more details.
#
#    You have received a copy of the GNU General Public License
#    along with this program. See LICENSE.GPLv3
#    A copy of the license can be found also here <http://www.gnu.org/licenses/>.
#
###################################################################################

include(core/core.pri)
include(iexdata/iexdata.pri)
include(utils/utils.pri)
include(SortFilterProxyModel/SortFilterProxyModel.pri)
include(tradingview/tradingview.pri)
include(kopirestless/kopirestless.pri)

TEMPLATE = app
TARGET = KopiTrade
DESTDIR = $$PWD/bin

QT = qml \
     quick \
     quickcontrols2 \
     core \
     network

QT -= widgets

QT += webengine
#QT += webview


macx-ios-clang {
QT +=  webview

QMAKE_IOS_DEPLOYMENT_TARGET = 12.1
}

INCLUDEPATH += $$PWD/kopiapp/src \
               $$PWD/kopiapp/ui/widgets \
               $$PWD/core/src \
               $$PWD/utils/src \
               $$PWD/iexdata \
               $$PWD/kopirestless \
               $$PWD/tradingview

CONFIG += c++11
CONFIG += app_bundle

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    kopiapp/src/main.cpp \
    kopiapp/src/kopi.cpp \
    kopiapp/src/kstyle.cpp \
    kopiapp/src/kopiappsettings.cpp

HEADERS += \
    kopiapp/src/kopi.h \
    kopiapp/src/kstyle.h \
    kopiapp/src/kopiappsettings.h

RESOURCES += \
    kopiresources.qrc

DISTFILES +=

