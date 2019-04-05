import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.4

import "../basickontrols"

Item {
    id: root
    width: 1000
    height: 900

    property alias busyIndicator: busyIndicator
    property alias statusLabel: statusLabel
    property alias demoAccountButton: demoAccountButton
    property alias registerBox: registerBox
    property alias loginBox: loginBox
    property alias registerButton: registerButton
    property alias loginButton: loginButton
    property alias passwordInput: passwordInput
    property alias usernameInput: usernameInput

    KBusyIndicator {
        id: busyIndicator
        z: 1
        running: false
        anchors.centerIn: root
    }

    ColumnLayout {
        anchors.verticalCenterOffset: -50
        spacing: 20
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter

        KFrame {
            id: loginBox
            Layout.minimumWidth: 400
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

                KSpacerItem {
                    id: spacer1
                    Layout.fillHeight: true
                    Layout.maximumHeight: 20
                    Layout.fillWidth: true
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

                ColumnLayout {
                    Layout.maximumWidth: 400
                    Layout.minimumWidth: 250
                    Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                    Layout.fillWidth: true
                    spacing: 15

                    KTextField {
                        id: usernameInput
                        horizontalAlignment: Text.AlignHCenter
                        Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                        Layout.fillWidth: true
                        Layout.maximumWidth: 350
                        Layout.minimumWidth: 250
                        placeholderText: "email"
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
                }

                KButton {
                    id: loginButton
                    text: qsTr("Sign in")
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

        Item {
            id: registerBox
            Layout.minimumHeight: 200
            Layout.minimumWidth: 400

            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            Layout.maximumWidth: 600
            Layout.fillHeight: true
            Layout.fillWidth: true

            ColumnLayout {
                spacing: 5
                anchors.fill: parent

                RowLayout {
                    spacing: 15
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    KButton {
                        id: registerButton
                        text: qsTr("Create account")
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

                KLabel {
                    id: label
                    text: qsTr("Register for a  free account and start planning your future investments with a few clicks in KopiTrade platform.")
                    font.italic: true
                    Layout.fillWidth: true
                    textFormat: Text.RichText
                    wrapMode: Text.WordWrap
                }
            }
        }
    }
}
