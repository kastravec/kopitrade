import QtQuick 2.12
import QtQuick.Controls 2.12

import Kopi 1.0

GroupBox {
    id: root
    padding: 1

    property alias backgroundItem: backgroundItem

    background: KRectangle {
        id: backgroundItem
        height: root.height
        width: root.width

        border.color: KStyle.styleDefinition.kpalette.borderBaseColor
    }
}
