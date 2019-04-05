import QtQuick 2.12
import QtQuick.Controls 2.5

import Kopi 1.0

TextField {
    id: root

    placeholderText: "type something.."

    property int backgroundBorderWidth: 2
    property string backgroundBorderColor: KStyle.styleDefinition.kpalette.borderBaseColor
    property int backgroundBorderRadius: 25

    selectByMouse: true
    persistentSelection: true
    activeFocusOnPress: true

    cursorDelegate: kcursorDelegate
    color: KStyle.styleDefinition.kpalette.text
    placeholderTextColor: KStyle.styleDefinition.kpalette.text
    selectionColor: "steelblue"

    background: Rectangle {
        id: backgroundItem
        color: root.enabled ? "transparent" : "#353637"
        width: root.width
        height: root.height
        border.color: root.enabled ? KStyle.styleDefinition.kpalette.light : root.backgroundBorderColor
        border.width: root.backgroundBorderWidth

        radius: root.backgroundBorderRadius

        KRoundButton {
            id: clearButton
            text: "x"
            font.bold: true
            width: 20
            height: 20
            clip: true
            backgroundColor: KStyle.styleDefinition.kspecs.mainMenu.mainBox.background.color //KStyle.styleDefinition.kpalette.borderBaseColor
            checkable: false
            autoExclusive: false
            anchors.right: backgroundItem.right
            anchors.rightMargin: 4
            anchors.verticalCenter: backgroundItem.verticalCenter
            visible: root.length > 0
            onClicked: root.clear()
            toolTipText: qsTr("Clear")
        }
    }

    Component {
        id: kcursorDelegate
        Rectangle {
            id: cursorRect
            visible: root.activeFocus
            width: 1
            height: 10
            color: "white"
        }
    }
}
