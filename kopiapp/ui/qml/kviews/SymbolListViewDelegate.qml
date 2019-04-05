import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.4

import Kopi 1.0
import "../basickontrols"

KFrame {
    id: root
    height: 60
    width: 300
    hoverEnabled: true
    borderRadius: 10
    padding: 4

    // applying different background colors when item is highlighted or not
    backgroundColor: (root.highlighted
                      || root.hovered) ? KStyle.styleDefinition.kpalette.light : root.backgroundBaseColor

    property string backgroundBaseColor: "transparent"
    property bool highlighted: false
    property bool editMode: false

    property string clickedIexDataSymbol
    property int priceIncreased
    property string logoURL: ""

    property alias showLogo: logoImage.enabled
    property alias showChange: changeLabel.enabled

    property alias nameLabel: nameLabel
    property alias symbolLabel: symbolLabel
    property alias removeButton: removeButton
    property alias priceLabel: priceLabel
    property alias changeLabel: changeLabel
    property alias coverPriceFrame: coverPriceFrame

    signal symbolTickerLeftClicked
    signal symbolTickerRightClicked
    signal symbolNameLeftClicked
    signal symbolNameRightClicked
    signal removeButtonClicked

    Item {
        id: rootContentBox
        anchors.fill: parent

        RowLayout {
            id: rowlayout
            anchors.fill: parent
            spacing: 4

            KSymbolLogo {
                id: logoImage
                fillMode: Image.PreserveAspectFit
                source: enabled ? root.logoURL: logoImage.source = ""

                Layout.fillHeight: true
                Layout.fillWidth: true
                Layout.maximumWidth: root.width *0.06
                Layout.maximumHeight: 32
            }

            KButton {
                id: nameLabel
                text: qsTr("name")
                backgroundBorderWidth: 0
                backgroundBorderHighlightWidth: 0
                checkable: false
                font.pointSize: 13

                Layout.fillHeight: true
                Layout.fillWidth: true
                Layout.maximumWidth: root.width * 0.55

                onClicked: {
                    root.clickedIexDataSymbol = symbolLabel.text
                    root.symbolNameLeftClicked()
                }
            }

            KButton {
                id: symbolLabel
                text: qsTr("symbol")
                backgroundBorderHighlightWidth: 0
                backgroundBorderWidth: 0
                font.pointSize: 13
                checkable: false

                Layout.fillHeight: true
                Layout.fillWidth: true
                Layout.minimumWidth: root.width * 0.13
                Layout.maximumWidth: root.width * 0.13
                Layout.maximumHeight: root.height

                onClicked: {
                    root.clickedIexDataSymbol = symbolLabel.text
                    symbolTickerLeftClicked()
                }
            }

            KButton {
                id: priceLabel
                backgroundBorderHighlightWidth: 0
                backgroundBorderWidth: 0
                font.pointSize: 13
                checkable: false

                Layout.fillHeight: true
                Layout.fillWidth: true
                Layout.minimumWidth: root.width * 0.14
                Layout.maximumWidth: root.width * 0.14
                Layout.maximumHeight: root.height

                onClicked: {
                    root.clickedIexDataSymbol = symbolLabel.text
                    symbolTickerLeftClicked()
                }

                onTextChanged: widthAnimationExpand.restart()

                KRectangle {
                    id: coverPriceFrame
                    anchors.fill: parent
                    anchors.margins: 1
                    border.width: 0
                    opacity: 0
                    radius: 5
                }

                NumberAnimation {
                    id: widthAnimationExpand
                    target: coverPriceFrame
                    property: "opacity"
                    duration: 1000
                    from: 0.5
                    to: 0
                    easing.type: Easing.Linear
                }
            }

            KButton {
                id: changeLabel
                visible: enabled
                backgroundBorderHighlightWidth: 0
                backgroundBorderWidth: 0
                font.pointSize: 12
                checkable: false
                autoExclusive: false

                Layout.fillHeight: true
                Layout.fillWidth: true
                Layout.minimumWidth: root.width * 0.12
                Layout.maximumWidth: root.width * 0.12
                Layout.maximumHeight: root.height

                onClicked: {
                    root.clickedIexDataSymbol = symbolLabel.text
                    symbolTickerLeftClicked()
                }
            }

            Item {
                Layout.maximumWidth: 16
                Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
                Layout.minimumWidth: 16
                Layout.minimumHeight: 18
                Layout.maximumHeight: 16

                KRoundButton {
                    id: removeButton
                    checkable: false
                    autoExclusive: false
                    visible: root.hovered
                    text: "-"
                    toolTipText: qsTr("Remove item from list")
                    font.pointSize: 13
                    font.bold: true
                    backgroundBoderColor: "#ae0000"
                    backgroundColor: "#ae0000"
                    backgroundBorderHighlightColor: KStyle.styleDefinition.kpalette.highlight
                    backgroundBorderWidth: 0

                    anchors.fill: parent
                    onClicked: {
                        root.clickedIexDataSymbol = symbolLabel.text
                        root.removeButtonClicked()
                    }
                }
            }
        }
    }
}
