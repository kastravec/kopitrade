import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.4

import "../basickontrols"
import Kopi 1.0

Item {
    id: root
    width: 400
    height: 400
    focus: true

    property alias listView: listView
    property alias busyindicator: busyindicator
    property alias menuPopup: menuPopup

    ColumnLayout {
        spacing: 0
        anchors.fill: parent
        anchors.leftMargin: 4

        KRectangle {
            Layout.fillWidth: true
            height: 25
            Layout.minimumWidth: root.width -9
            Layout.maximumWidth: root.width -9
            visible: listView.count > 0
            color: KStyle.styleDefinition.kspecs.mainMenu.mainBox.background.color//KStyle.styleDefinition.kpalette.selectedTabBackgroundColor //"transparent"
            radius: 6
            border.color: KStyle.styleDefinition.kpalette.borderBaseColor
            RowLayout {
                id: buttonLayout
                spacing: 1
                anchors.fill: parent

                KButton {
                    id: nameB
                    text: qsTr("Name")
                    leftPadding: 50
                    font.pointSize: 10
                    checkable: false
                    backgroundBorderWidth: 0
                    backgroundBorderHighlightWidth: 0
                    Layout.fillWidth: true
                    Layout.maximumWidth: root.width * 0.5
                    Layout.minimumWidth: root.width * 0.5

                }

                KButton {
                    id: symbolB
                    text: qsTr("Symbol")
                    font.pointSize: 10
                    checkable: false
                    backgroundBorderWidth: 0
                    backgroundBorderHighlightWidth: 0
                    Layout.fillWidth: true
                    Layout.maximumWidth: root.width * 0.14
                    Layout.minimumWidth: root.width * 0.14
                }

                KButton {
                    id: priceB
                    text: qsTr("Price")
                    leftPadding: 8
                    font.pointSize: 10
                    checkable: false
                    backgroundBorderWidth: 0
                    backgroundBorderHighlightWidth: 0
                    textHorizontalAlignment: Qt.AlignLeft
                    Layout.fillWidth: true
                    Layout.maximumWidth: root.width * 0.14
                    Layout.minimumWidth: root.width * 0.14

                }

                KButton {
                    id: changeB
                    text: qsTr("Change (%)")
                    leftPadding: -1
                    font.pointSize: 10
                    checkable: false
                    backgroundBorderWidth: 0
                    backgroundBorderHighlightWidth: 0
                    textHorizontalAlignment: Qt.AlignLeft
                    Layout.fillWidth: true
                    Layout.minimumWidth: root.width * 0.16
                    Layout.maximumWidth: root.width * 0.16
                }
            }
        }

        KLine {
            type: "horizontal"
            Layout.fillWidth: true
        }

        ListView {
            id: listView
            clip: true
            Layout.fillHeight: true
            Layout.fillWidth: true
            keyNavigationWraps: true
            keyNavigationEnabled: true
            focus: true
            snapMode: ListView.SnapOneItem
        }

        KLine {
            type: "horizontal"
            Layout.fillWidth: true
        }
    }

    KMenu {
        id: menuPopup
        menuWidth: 150
        KMenuItem {
            id: button
            text: qsTr("Add Buy Position")
        }

        KMenuItem {
            id: button1
            text: qsTr("Add Sell Position")
        }

        KMenuItem {
            id: button24
            text: qsTr("Add to Watchlist(s)")
        }

        KMenuItem {
            id: button3
            text: qsTr("Add Alert(s)")
        }
    }

    KBusyIndicator {
        id: busyindicator
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter
    }
}
