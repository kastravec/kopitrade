import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.4

import QtWebEngine 1.8
//import QtWebView 1.1

import "../basickontrols"
import Kopi 1.0

Item {
    id: root
    width: 600
    height: 400
    property alias webview: webview
    property alias statusBar: statusBar
    property alias addressBar: addressBar
    property alias toolBar: toolBar

    Item {
        id: toolBar
        height: 35
        z: 1
        visible: true
        clip: true
        anchors.right: parent.right
        anchors.left: parent.left
        anchors.top: parent.top

        RowLayout {
            spacing: 10
            anchors.fill: parent
            Switch {
                id: onOffSwitch
                text: qsTr("On")
                Layout.preferredHeight: 32
                Layout.preferredWidth: 92
                checked: true
            }

            RoundButton {
                id: addressButton
                text: "s"
                checkable: true
                Layout.preferredHeight: 27
                Layout.preferredWidth: 29
            }
        }
    }

    WebEngineView {
        id: webview
        url: addressInput.text
        anchors.fill: parent

        backgroundColor: "transparent"

        settings.pluginsEnabled: true
        settings.accelerated2dCanvasEnabled: true
        settings.allowWindowActivationFromJavaScript: true
        settings.javascriptCanOpenWindows: true
        settings.showScrollBars: false
    }

    KRectangle {
        id: statusBar
        y: 373
        height: 12
        color: "#e7eae9"
        anchors.right: parent.right
        anchors.left: parent.left
        anchors.bottom: parent.bottom

        Label {
            id: status1Label
            width: 24
            height: 11
            text: qsTr("Ready")
            font.pointSize: 9
        }

        Label {
            id: status1Label1
            x: 298
            y: 0
            width: 24
            height: 11
            text: qsTr("...")
            font.pointSize: 9
        }
    }

    Item {
        id: addressBar
        x: 200
        width: 400
        height: 80
        visible: addressButton.checked
        anchors.top: toolBar.bottom
        anchors.right: parent.right

        ColumnLayout {
            anchors.fill: parent

            Label {
                id: label1
                color: "#6c1206"
                text: qsTr("Enter address:")
            }

            TextField {
                id: addressInput
                text: "http://google.com"
                placeholderText: "example http://google.com"
                Layout.fillWidth: true
                Layout.preferredHeight: 50
                Layout.preferredWidth: 400
            }
        }
    }
}
