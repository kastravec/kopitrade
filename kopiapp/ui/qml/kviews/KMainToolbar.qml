import QtQuick 2.12
import QtQuick.Layouts 1.4

import Kopi 1.0

import "../basickontrols"

KToolBar {
    id: root

    property alias mainMenuButton: mainMenuButton
//    property alias portfolioButton: portfolioButton
//    property alias marketButton: marketButton
//    property alias notesButton: notesButton
//    property alias notificationsButton: notificationsButton

    RowLayout {
        anchors.leftMargin: 5
        anchors.fill: parent
        spacing: 10

        KButton {
            id: mainMenuButton
            text: "Menu"
            backgroundBorderWidth: 0
            backgroundBorderHighlightWidth: 0
            backgroundColor:  KStyle.styleDefinition.kpalette.borderBaseColor
            borderRadius: 5
            checkable: false
        }

        KSpacerItem {
            Layout.minimumWidth: 40
            Layout.maximumWidth: 40
            Layout.fillHeight: true
            Layout.fillWidth: true
        }

//        KFrame {
//            id: buttonbox1
//            Layout.fillHeight: true
//            Layout.fillWidth: false

//            RowLayout {
//                spacing: 3
//                anchors.fill: parent

//                KToolButton {
//                    id: marketButton
//                    text: "Markets"
//                    Layout.fillHeight: true
//                }

//                KToolButton {
//                    id: portfolioButton
//                    text: "Portfolio"
//                    Layout.fillHeight: true
//                }

//                KToolButton {
//                    id: notesButton
//                    text: "Notes"
//                    Layout.fillHeight: true
//                }

//                KToolButton {
//                    id: notificationsButton
//                    text: "Notifications"
//                    Layout.fillHeight: true
//                }
//            }
//        }
    }
}

/*##^## Designer {
    D{i:0;height:50;width:1000}
}
 ##^##*/

