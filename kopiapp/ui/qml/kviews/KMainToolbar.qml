import QtQuick 2.12
import QtQuick.Layouts 1.4

import Kopi 1.0

import "../basickontrols"

KToolBar {
    id: root

    property alias mainMenuButton: mainMenuButton
    property alias chartModeButton: chartModeButton
    property alias marketButton: marketButton
    property alias chartTypeCombo: chartTypeCombo

    property bool showChartsModeButtons: false
    property alias b2: b2
    property alias b4: b4
    property alias b8: b8

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

        RowLayout {
            spacing: 3

            KToolButton {
                id: marketButton
                text: "Markets"
                Layout.maximumHeight: 25
                Layout.fillHeight: true
            }

            KToolButton {
                id: chartModeButton
                text: "Full Chart Mode"
                Layout.maximumHeight: 25
                Layout.fillHeight: true
            }
        }

        RowLayout {
            id: chartModeButtonLayout
            visible: root.showChartsModeButtons

            KLabel {
                id: lb1
                text: qsTr("How many charts?  ")
                font.pointSize: 14
                font.bold: true
                font.italic: true
                color: KStyle.styleDefinition.kpalette.highlight
            }

            KButton {
                id: b2
                text: "2"
                Layout.minimumWidth: 30
                font.pointSize: 18
                font.bold: true
                checked: true
            }

            KButton {
                id: b4
                text: "4"
                Layout.minimumWidth: 30
                font.bold: true
                font.pointSize: 18
            }

            KButton {
                id: b8
                text: "8"
                font.bold: true
                Layout.minimumWidth: 30
                font.pointSize: 18
            }

            KLabel {
                id: lb2
                text: qsTr("Chart type?  ")
                font.pointSize: 14
                font.bold: true
                font.italic: true
                color: KStyle.styleDefinition.kpalette.highlight
            }

            KComboBox {
                id: chartTypeCombo
                model: chartTypeModel
                Layout.alignment: Qt.AlignRight | Qt.AlignTop
                Layout.maximumHeight: 24
                Layout.minimumHeight: 24
                Layout.minimumWidth: 30
                currentIndex: 2
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
}

/*##^## Designer {
    D{i:0;height:30;width:1000}
}
 ##^##*/
