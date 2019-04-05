import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.4

import Kopi 1.0

import "../basickontrols"

Item {
    id: root
    width: 600
    height: 500

    property alias chartPopupButton: chartPopupButton
    property alias sizeDoubleButton: sizeDoubleButton
    property alias sizeOneButton: sizeOneButton

    property alias chartToolbarBox: chartToolbarBox
//    property alias cancelSnapButton: cancelSnapButton
//    property alias saveSnapButton: saveSnapButton
//    property alias imageViewer: imageviewer
    property alias chartGridView: chartGridView
    property alias chartTypeCombo: chartTypeCombo

    property alias priceLabel: priceLabel
    property alias coverFrame: coverFrame

    ColumnLayout {
        spacing: 1
        anchors.fill: parent

        Item {
            id: chartToolbarBox
            Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
            Layout.leftMargin: 4
            Layout.rightMargin: 10
            Layout.minimumHeight: 20
            Layout.maximumHeight: 22
            Layout.fillWidth: true

            RowLayout {
                anchors.right: parent.right
                anchors.bottom: parent.bottom
                anchors.top: parent.top
                spacing: 4

//                KImageButton {
//                    id: imageSnapButton
//                    Layout.alignment: Qt.AlignRight | Qt.AlignBottom
//                    Layout.maximumHeight: 24
//                    Layout.minimumHeight: 24
//                    Layout.minimumWidth: 30
//                }

                KButton {
                    id: chartPopupButton
                    text: "[  ]"
                    toolTipText: qsTr("Full Chart view-mode")

                    font.bold: true
                    font.pointSize: 14
                    autoExclusive: true
                    Layout.minimumHeight: 24
                    backgroundBorderHighlightWidth: 0
                    Layout.minimumWidth: 30
                    backgroundBorderWidth: 0
                    Layout.alignment: Qt.AlignRight | Qt.AlignTop
                    Layout.maximumHeight: 24
                }

                KButton {
                    id: sizeDoubleButton
                    text: "[]"
                    toolTipText: qsTr("Large Chart view-mode")
                    font.bold: true
                    font.pointSize: 14
                    autoExclusive: true
                    Layout.minimumHeight: 24
                    backgroundBorderHighlightWidth: 0
                    Layout.minimumWidth: 30
                    backgroundBorderWidth: 0
                    Layout.alignment: Qt.AlignRight | Qt.AlignTop
                    Layout.maximumHeight: 24
                }

                KButton {
                    id: sizeOneButton
                    text: "| "
                    toolTipText: qsTr("Mini Chart view-mode")
                    font.bold: true
                    font.pointSize: 14
                    autoExclusive: true
                    Layout.alignment: Qt.AlignRight | Qt.AlignTop
                    Layout.maximumHeight: 24
                    Layout.minimumHeight: 24
                    Layout.minimumWidth: 30
                    backgroundBorderHighlightWidth: 0
                    backgroundBorderWidth: 0
                    checked: true
                }

                KComboBox {
                    id: chartTypeCombo
                    model: chartTypeModel
                    Layout.alignment: Qt.AlignRight | Qt.AlignTop
                    Layout.maximumHeight: 24
                    Layout.minimumHeight: 24
                    Layout.minimumWidth: 30
                    delegate: KItemDelegate {
                              width: chartTypeCombo.width
                              text: modelData
                              highlighted: chartTypeCombo.highlightedIndex === index
                          }

                    ListModel {
                        id: chartTypeModel
                        ListElement { type: qsTr("Basic") }
                        ListElement { type: qsTr("Simple") }
                        ListElement { type: qsTr("Advanced") }
                    }
                }
            }
        }

        KWebView {
            id: chartGridView
            toolBar.visible: false
            statusBar.visible: false
            Layout.fillHeight: true
            Layout.fillWidth: true
        }
    }


    KRectangle {
        id: coverFrame
        width: 300
        height: 70
        x: chartGridView.x + 20
        y: chartGridView.y + 20
        color: KStyle.styleDefinition.kpalette.window

        KLabel {
            id: priceLabel
            font.pointSize: 24
            font.bold: true
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignLeft
            anchors.fill: parent
        }
    }
}












/*##^## Designer {
    D{i:1;anchors_x:0;anchors_y:0}D{i:9;anchors_x:0;anchors_y:0}
}
 ##^##*/
