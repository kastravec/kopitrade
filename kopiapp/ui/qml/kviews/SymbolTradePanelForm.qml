import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.4

import "../basickontrols"

Item {
    id: root

    property alias historyButton: historyButton
    property alias notesButton: notesButton
    property alias tradeButton: tradeButton
    property alias stockpanelBar: stockpanelBar

    ColumnLayout {
        anchors.fill: parent

        KTabBar {
            id: stockpanelBar
            Layout.maximumHeight: 45
            Layout.minimumHeight: 30
            Layout.fillWidth: true
            Layout.fillHeight: false

            KTabButton {
                id: tradeButton
                width: stockpanelBar.tabWidth
                text: qsTr("Trade")
                backgroundBorderWidth: 0
                backgroundBorderHighlightWidth: 1
                isCurrent: stockpanelBar.currentIndex === KTabBar.index
            }

            KTabButton {
                id: notesButton
                width: stockpanelBar.tabWidth
                text: qsTr("Notes")
                backgroundBorderWidth: 0
                isCurrent: stockpanelBar.currentIndex === KTabBar.index
            }

            KTabButton {
                id: historyButton
                width: stockpanelBar.tabWidth
                text: qsTr("History")
                backgroundBorderWidth: 0
                isCurrent: stockpanelBar.currentIndex === KTabBar.index
            }
        }

        StackLayout {
            id: stacklayout1
            Item {
                Layout.fillHeight: true
                Layout.fillWidth: true
            }

            Item {
                Layout.fillHeight: true
                Layout.fillWidth: true
            }

            Item {
                Layout.fillHeight: true
                Layout.fillWidth: true
            }
            currentIndex: stockpanelBar.currentIndex
            Layout.fillWidth: true
            Layout.fillHeight: true
        }
    }
}
