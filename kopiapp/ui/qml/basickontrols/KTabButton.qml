import QtQuick 2.12
import QtQuick.Controls 2.5

import Kopi 1.0
import "../core"

TabButton {
    id: root
    width: 100
    height: 25
    text: "Button"
    hoverEnabled: true
    padding: 8

    property bool isCurrent: false
    property string backgroundColor: KStyle.styleDefinition.kpalette.selectedTabBackgroundColor //"transparent"
    property string backgroundHighlightColor: "transparent" // //KStyle.styleDefinition.kpalette.button
    property int backgroundBorderWidth: 0 //KStyle.styleDefinition.kspecs.mainMenu.border.width
    property int backgroundBorderHighlightWidth: 0 //KStyle.styleDefinition.kspecs.mainMenu.border.width
    property string textColor: KStyle.styleDefinition.kpalette.buttonText
    property string textColorHightlight: KStyle.styleDefinition.kpalette.highlightedText


    contentItem: KLabel {
        text: root.text
        font: root.font
        opacity: enabled ? 1.0 : 0.3
        color: (root.down || root.isCurrent || root.hovered) ? root.textColorHightlight : root.textColor
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        wrapMode: Text.WrapAnywhere
        showToolTip: false
    }

    background: KRectangle {
        id: backgroundItem
        opacity: enabled ? 1 : 0.2
        color: root.isCurrent? root.backgroundColor: "transparent"

        border.color: (root.down || root.hovered
                       || isCurrent) ? KStyle.styleDefinition.kpalette.highlight : KStyle.styleDefinition.kpalette.button
        border.width: root.hovered ? root.backgroundBorderHighlightWidth : root.backgroundBorderWidth
        radius: 15
        implicitWidth: root.width - 20
        implicitHeight: root.height - 12


        PropertyAnimation {
            id: tabIsCurrenAnimation
            target: backgroundItem
            property: "opacity"
            easing.type: Easing.OutCubic
            duration: 300
            running: root.isCurrent
            to: "1"
        }

        PropertyAnimation {
            id: tabIsNotCurrenAnimation
            target: backgroundItem
            property: "opacity"
            easing.type: Easing.OutCubic
            duration: 300
            running: !root.isCurrent
            to: "0"
        }


    }

}
