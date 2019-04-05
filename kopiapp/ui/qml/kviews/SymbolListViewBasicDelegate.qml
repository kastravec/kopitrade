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
    padding: 0

    // applying different background colors when item is highlighted or not
    backgroundColor: (root.highlighted
                      || root.hovered) ? KStyle.styleDefinition.kpalette.light : root.backgroundBaseColor

    property string backgroundBaseColor: "transparent"
    property bool highlighted: false

    property string clickedIexDataSymbol

    property alias nameLabel: nameLabel
    property alias symbolLabel: symbolLabel

    signal itemclicked

    TapHandler {
        target: root
        onTapped: {
            root.clickedIexDataSymbol = symbolLabel.text
            itemclicked(root.clickedIexDataSymbol)
        }
    }

    RowLayout {
        id: rowlayout
        anchors.fill: parent
        spacing: 8

        KButton {
            id: symbolLabel
            text: qsTr("symbol")
            backgroundBorderHighlightWidth: 0
            backgroundBorderWidth: 0
            font.pointSize: 12
            checkable: false
            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.minimumWidth: root.width * 0.2
            Layout.maximumWidth: root.width * 0.2

            onClicked: {
                root.clickedIexDataSymbol = symbolLabel.text
                itemclicked()
            }
        }

        KButton {
            id: nameLabel
            text: qsTr("name")
            font.pointSize: 12
            backgroundBorderWidth: 0
            backgroundBorderHighlightWidth: 0
            checkable: false

            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.minimumWidth: root.width * 0.65
            Layout.maximumWidth: root.width * 0.65

            onClicked: {
                root.clickedIexDataSymbol = symbolLabel.text
                itemclicked()
            }
        }
    }
}
