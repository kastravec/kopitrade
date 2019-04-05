import QtQuick 2.12
import QtQuick.Controls 2.5
import QtGraphicalEffects 1.12

import Kopi 1.0

AbstractButton {
    id: root

    checkable: true
    checked: false
    hoverEnabled: true

    property alias backgroundColor: backgroundItem.color //"transparent" //KStyle.styleDefinition.kpalette.button
    property string backgroundHighlightColor: KStyle.styleDefinition.kpalette.highlight
    property int backgroundBorderWidth: 0
    property int backgroundBorderHighlightWidth: 0
    property string textColor: KStyle.styleDefinition.kpalette.buttonText
    property string textColorHightlight: KStyle.styleDefinition.kpalette.highlightedText
    property string backgroundBoderColor: KStyle.styleDefinition.kpalette.borderBaseColor
    property bool highlighted: false
    property string imageColorOverlay: "transparent"

    background: Rectangle {
        id: backgroundItem

        opacity: enabled ? 1 : 0.2
        color: "transparent"
        border.color: (root.down || hovered || highlighted
                       || checked) ? KStyle.styleDefinition.kpalette.highlight : backgroundBoderColor
        border.width: (checked
                       || hovered) ? root.backgroundBorderHighlightWidth : root.backgroundBorderWidth
        radius: 15

        Image {
            id: iconImage
            anchors.centerIn: parent
            source: root.icon.source
            width: root.width
            height: root.height
            smooth: true
            fillMode: Image.PreserveAspectFit
        }

//        ColorOverlay {
//            anchors.fill: iconImage
//            source: iconImage
//            color: (root.hovered
//                    || root.checked) ? root.backgroundHighlightColor : imageColorOverlay //KStyle.styleDefinition.kpalette.windowText
//            enabled: false
//        }
    }
}
