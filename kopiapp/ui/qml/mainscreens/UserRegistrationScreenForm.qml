import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.4

import "../basickontrols"

Item {
    id: root
    width: 1000
    height: 900
    property alias registerButton: registerButton
    property alias cancelButton: cancelButton
    property alias usernameInput: usernameInput
    property alias emailInput: emailInput
    property alias busyIndicator: busyIndicator

    property alias statusLabel: statusLabel
    property alias demoAccountButton: demoAccountButton
    property alias registrationBox: registrationBox
    property alias passwordInput: passwordInput

    KBusyIndicator {
        id: busyIndicator
        z: 1
        running: false
        anchors.centerIn: root
    }

    ColumnLayout {
        spacing: 20
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter

        KFrame {
            id: registrationBox
            Layout.minimumHeight: 250
            Layout.maximumHeight: 800
            borderColor: "#131d51"
            borderRadius: 25
            borderWidth: 0
            hoverEnabled: false

            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            Layout.fillWidth: true
            Layout.maximumWidth: 600
            Layout.fillHeight: true

            ColumnLayout {
                spacing: 25
                anchors.fill: parent

                KopiTradeLogo {
                    id: logoimage
                    Layout.rowSpan: 0
                    Layout.minimumHeight: 100
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                }

                KLabel {
                    id: label
                    text: qsTr("Register for a  free account and start planning your future investments with a few clicks in KopiTrade platform.")
                    font.pointSize: 16
                    horizontalAlignment: Text.AlignHCenter
                    Layout.minimumHeight: 40
                    Layout.fillHeight: true
                    Layout.maximumHeight: 50
                    font.italic: true
                    Layout.fillWidth: true
                    textFormat: Text.RichText
                    wrapMode: Text.WordWrap
                }

                KLabel {
                    id: statusLabel
                    color: "#e04d1c"
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                    font.pointSize: 15
                    font.bold: true
                    Layout.fillHeight: true
                    Layout.maximumHeight: 34
                    Layout.fillWidth: true
                }

                KTextField {
                    id: emailInput
                    horizontalAlignment: Text.AlignHCenter
                    Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                    Layout.fillWidth: true
                    Layout.maximumWidth: 350
                    Layout.minimumWidth: 250
                    placeholderText: "email"
                }

                KTextField {
                    id: usernameInput
                    horizontalAlignment: Text.AlignHCenter
                    Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                    Layout.minimumWidth: 250
                    placeholderText: "username"
                    Layout.fillWidth: true
                    Layout.maximumWidth: 350
                }

                KTextField {
                    id: passwordInput
                    horizontalAlignment: Text.AlignHCenter
                    Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                    Layout.fillWidth: true
                    Layout.maximumWidth: 350
                    Layout.minimumWidth: 250
                    placeholderText: "password"
                    echoMode: TextInput.Password
                }

                KButton {
                    id: registerButton
                    text: qsTr("Register")
                    checkable: false
                    font.pointSize: 15
                    backgroundBorderHighlightWidth: 1
                    backgroundBorderWidth: 2
                    font.bold: true
                    Layout.maximumWidth: 350
                    Layout.minimumWidth: 250
                    Layout.fillWidth: false
                    Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                }
            }
        }

        RowLayout {
            spacing: 15
            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.maximumWidth: 500
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter

            KButton {
                id: cancelButton
                text: qsTr("Cancel")
                checkable: false
                font.pointSize: 18
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                Layout.maximumWidth: 150
                backgroundBoderColor: "#131d51"
                highlighted: false
                backgroundBorderHighlightWidth: 1
                backgroundBorderWidth: 2
                font.bold: true
                Layout.minimumWidth: 130
                Layout.fillWidth: true
            }

            KButton {
                id: demoAccountButton
                text: qsTr("Demo account")
                enabled: true
                checkable: false
                font.pointSize: 18
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                Layout.maximumWidth: 250
                backgroundBoderColor: "#131d51"
                highlighted: false
                backgroundBorderHighlightWidth: 1
                backgroundBorderWidth: 2
                font.bold: true
                Layout.minimumWidth: 130
                Layout.fillWidth: true
            }
        }
    }
}
