import QtQuick 2.12
import QtQuick.Controls 2.5

MenuItem {
    id: menuItem

    contentItem: Text {
        leftPadding: menuItem.indicator.width
        rightPadding: menuItem.arrow.width
        text: menuItem.text
        font: menuItem.font
        opacity: enabled ? 1.0 : 0.3
        color: menuItem.highlighted ? "#ffffff" : "#21be2b"
        horizontalAlignment: Text.AlignLeft
        verticalAlignment: Text.AlignVCenter
        elide: Text.ElideRight
    }

    background: Rectangle {
        implicitWidth: 200
        implicitHeight: 40
        opacity: enabled ? 1 : 0.3
        color: menuItem.highlighted ? "#21be2b" : "transparent"
    }
}
