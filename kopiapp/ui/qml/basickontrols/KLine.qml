import QtQuick 2.12

import Kopi 1.0

Rectangle {
    id: root

    property string type: "vertical"
    property int lineWidth: 2
    color: KStyle.styleDefinition.kpalette.selectedTabBackgroundColor //"transparent"

    onLineWidthChanged: switchingType(root.type)
    onTypeChanged: switchingType(root.type)

    function switchingType(newType) {
        if (newType === "vertical") {
            root.width = root.lineWidth
        } else if (newType === "horizontal") {
            root.height = root.lineWidth
        }
    }

    Component.onCompleted: switchingType(root.type)
}
