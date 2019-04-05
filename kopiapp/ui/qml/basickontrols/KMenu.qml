import QtQuick 2.12
import QtQuick.Controls 2.4

import Kopi 1.0
import "../basickontrols"

Menu {
    id: menu
    topPadding: 2
    bottomPadding: 2

    property alias menuWidth: backgroundItem.implicitWidth
    property alias menuHeight: backgroundItem.implicitHeight

    background: KFrame {
        id: backgroundItem
        backgroundColor: KStyle.styleDefinition.kpalette.window
    }
}
