import QtQuick 2.12
import QtQuick.Controls 2.12

import Kopi 1.0

ToolTip {
    id: root
    text: qsTr("A descriptive tool tip of what the button does")

    contentItem: Text {
        text: root.text
        font: root.font
        color: "#21be2b"
    }

    background: KRectangle {
        border.color: "#21be2b"
        color: KStyle.styleDefinition.kspecs.mainMenu.mainBox.background.color
    }
}
