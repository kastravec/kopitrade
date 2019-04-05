import QtQuick 2.12
import QtQuick.Controls 2.5

import Kopi 1.0

Frame {
    id: root
    property string backgroundColor: "transparent" //KStyle.styleDefinition.kpalette.window
    property int borderWidth: 0
    property string borderColor: "transparent"
    property string borderColorHighlighted: "transparent"
    property int borderWidthHighlighted: 0
    property int borderRadius: 0

    background: Rectangle {
        width: root.width
        height: root.height
        color: root.backgroundColor
        border.color: hovered ? root.borderColorHighlighted : root.borderColor
        border.width: hovered ? root.borderWidthHighlighted : root.borderWidth
        radius: root.borderRadius
    }
}
