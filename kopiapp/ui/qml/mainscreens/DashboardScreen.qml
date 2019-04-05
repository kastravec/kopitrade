import QtQuick 2.4
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.4

Item {
    width: 1200
    height: 900

    GridLayout {
        anchors.rightMargin: 40
        anchors.leftMargin: 40
        anchors.bottomMargin: 40
        anchors.topMargin: 40
        anchors.fill: parent
        columnSpacing: 40
        rowSpacing: 40
        rows: 2
        columns: 2

        Rectangle {
            id: rectangle
            color: "#e0cdcd"
            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            Layout.preferredHeight: 274
            Layout.preferredWidth: 324
            border.color: "#f4b9b9"

            Label {
                id: label
                x: 48
                y: 57
                text: "Labelxcxcx "
            }
        }

        Rectangle {
            id: rectangle2
            color: "#e0cdcd"
            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            Layout.preferredHeight: 274
            Layout.preferredWidth: 324
            border.color: "#f4b9b9"
        }

        Rectangle {
            id: rectangle1
            color: "#e0cdcd"
            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            Layout.preferredHeight: 274
            Layout.preferredWidth: 324
            border.color: "#f4b9b9"
        }

        Rectangle {
            id: rectangle3
            color: "#e0cdcd"
            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            Layout.preferredHeight: 274
            Layout.preferredWidth: 324
            border.color: "#f4b9b9"
        }
    }
}
