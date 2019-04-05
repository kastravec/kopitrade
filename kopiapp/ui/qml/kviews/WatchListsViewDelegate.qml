import QtQuick 2.12
import QtQuick.Controls 2.5

import "../basickontrols"
import QtQuick.Layouts 1.0

import Kopi 1.0

KFrame {
    id: root
    height: 50

    property alias removeButton: removeButton
    property alias nameLabel: nameLabel
    property bool editMode: false

    hoverEnabled: true
    borderWidth: 1

    RowLayout {
        anchors.fill: parent
        spacing: 2

        KButton {
            id: nameLabel
            Layout.fillHeight: true
            Layout.fillWidth: true
            backgroundBorderWidth: 0
            backgroundBorderHighlightWidth: 1
            autoExclusive: false
            checkable: false
            textHorizontalAlignment: Text.AlignLeft
        }

        KRoundButton {
            id: removeButton
            checkable: false
            autoExclusive: false
            text: "-"
            font.pointSize: 14
            font.bold: true
            Layout.maximumWidth: 20
            Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
            Layout.minimumWidth: 20
            Layout.minimumHeight: 18
            Layout.maximumHeight: 18
            backgroundBorderWidth: 0
            backgroundBoderColor: "#ae0000"
            backgroundColor: "#ae0000"
            backgroundBorderHighlightColor: KStyle.styleDefinition.kpalette.highlight
            visible: root.editMode
        }
    }
}

/*##^## Designer {
    D{i:5;anchors_x:0;anchors_y:0}
}
 ##^##*/

