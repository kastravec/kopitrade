import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import QtQml 2.12

import Kopi 1.0

import "../basickontrols"

KRectangle {
    id: root
    width: 180
    height: 900

    color: KStyle.styleDefinition.kspecs.mainMenu.mainBox.background.color

    property alias bottomBox: bottomBox
    property alias menuBox: menuBox
    property alias kopiMenuBox: kopiMenuBox
    property alias mainHelpButton: kopiURLButton
    property alias logoImage: logoImage
    property alias portfoliosButton: portfoliosButton

    ColumnLayout {
        spacing: 2
        anchors.fill: parent

        KopiTradeLogo {
            id: logoImage
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            Layout.preferredHeight: 200
            Layout.preferredWidth: 150
        }

        KSpacerItem {
            id: spacer2
            Layout.preferredHeight: 20
            Layout.fillWidth: true
        }

        KFrame {
            id: kopiMenuBox
            Layout.fillWidth: true

            ColumnLayout {
                anchors.fill: parent

                KButton {
                    id: portfoliosButton
                    text: "Settings"
                    Layout.fillWidth: true
                    checkable: false
                }
            }
        }

        KSpacerItem {
            id: spacer3
            Layout.preferredHeight: 25
            Layout.fillWidth: true
        }

        KFrame {
            id: menuBox
            Layout.fillWidth: true
            transformOrigin: Item.Bottom

            ColumnLayout {
                spacing: 7
                anchors.fill: parent

                KButton {
                    id: manualButton
                    text: "User manual"
                    font.pointSize: 11
                    Layout.fillWidth: true
                    checkable: false
                }

                KButton {
                    id: supportButton
                    text: "Send Feedback"
                    font.pointSize: 11
                    Layout.fillWidth: true
                    checkable: false
                }
            }
        }

        KSpacerItem {
            id: spacer
            Layout.preferredHeight: 20
            Layout.fillWidth: true
        }

        KFrame {
            id: bottomBox
            Layout.fillHeight: false
            Layout.fillWidth: true

            RowLayout {
                spacing: 1
                anchors.fill: parent

                KButton {
                    id: kopiURLButton
                    text: "http://kopitrade.io"
                    highlighted: true
                    font.italic: true
                    font.pointSize: 10
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    font.bold: false
                    checkable: false

                    onClicked: Qt.openUrlExternally(kopiURLButton.text)
                }
            }
        }
    }
}
