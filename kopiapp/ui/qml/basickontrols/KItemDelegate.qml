import QtQuick 2.12
import QtQuick.Controls 2.12

import Kopi 1.0

ItemDelegate {
    id: root
    text: qsTr("item")

    property string backgroundBoderColor: KStyle.styleDefinition.kpalette.borderBaseColor
    property string backgroundBorderHighlightColor: KStyle.styleDefinition.kpalette.highlight

    contentItem: KLabel {
        rightPadding: root.spacing
        text: root.text
        font: root.font
        color: (root.down || hovered || highlighted
                || checked) ? root.backgroundBorderHighlightColor : KStyle.styleDefinition.kpalette.text
    }

    background: KRectangle {
        implicitWidth: 100
        implicitHeight: 40
        border.width: (root.down || hovered || highlighted || checked) ? 0 : 0
        border.color: (root.down || hovered || highlighted
                       || checked) ? root.backgroundBorderHighlightColor : root.backgroundBoderColor
    }
}
