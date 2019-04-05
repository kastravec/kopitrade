import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.12

import "../basickontrols"

KRectangle {
    id: root
    property alias scheduledLabel: scheduledLabel

    ColumnLayout {
        spacing: 10
        anchors.fill: parent
        KLabel {
            text: "Coming soon"
            font.pointSize: 28
            font.bold: true
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter

        }

        ColumnLayout {
            id: rowLayout
            Layout.alignment: Qt.AlignHCenter | Qt.AlignTop
            spacing: 20
            Layout.fillHeight: true
            Layout.fillWidth: true
            KLabel {
                id: scheduledLabel
                text: "scheduled for end Q2 2019"
                font.italic: true
                font.pointSize: 18

            }

            KLabel {
                text: "Stay tuned.."
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                font.bold: true
                font.pointSize: 24
                verticalAlignment: Text.AlignVCenter
            }
        }
    }
}



























/*##^## Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
 ##^##*/
