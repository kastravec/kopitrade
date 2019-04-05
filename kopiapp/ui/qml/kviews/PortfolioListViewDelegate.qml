import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.4

import "../basickontrols"
import Kopi 1.0

KFrame {
    id: root
    width: 350
    height: 100

    //applying different background colors when item is highlighted or not
    backgroundColor: root.highlighted ? KStyle.styleDefinition.kpalette.light : KStyle.styleDefinition.kpalette.window
//    borderColorHighlighted: root.highlighted ? KStyle.styleDefinition.kpalette.light : KStyle.styleDefinition.kpalette.window

    property bool highlighted: false
    property alias dataLabel: dataLabel
    property alias nameLabel: nameLabel

    RowLayout {
        anchors.fill: parent
        spacing: 15
        KLabel {
            id: nameLabel
            height: 21
            text: "name"
            Layout.fillHeight: true
            Layout.fillWidth: true
        }
        KLabel {
            id: dataLabel
            text: "portfolio data"
            Layout.fillHeight: true
            Layout.fillWidth: true
        }
    }
}
