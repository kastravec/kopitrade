import QtQuick 2.12
import QtQuick.Controls 2.5

import Kopi 1.0

CheckBox {
    id: root
    text: qsTr("CheckBox")

    property string indicatorColor: KStyle.styleDefinition.kpalette.highlightedText //"#21be2b" //"transparent" //KStyle.styleDefinition.kspecs.mainMenu.mainBox.background.color
    property string indicatorHighlightColor: KStyle.styleDefinition.kpalette.highlightedText //"#17a81a" //KStyle.styleDefinition.kspecs.mainMenu.mainBox.background.color
    property string indicatorBoderColor: KStyle.styleDefinition.kpalette.borderBaseColor
    property string indicatorBorderHighghtColor: KStyle.styleDefinition.kpalette.highlightedText

    indicator: KRectangle {
        implicitWidth: 12
        implicitHeight: 12
        x: root.leftPadding
        y: parent.height / 2 - height / 2
        radius: 3
        border.color: root.down ? indicatorBorderHighghtColor : indicatorBoderColor

        TapHandler {
            onTapped: root.checked = !root.checked
        }

        KRectangle {
            anchors.fill: parent
            TapHandler {
                onTapped: root.checked = !root.checked
            }

        }

        Rectangle {
            width: 6
            height: 6
            x: 4
            y: 3
            radius: 2
            color: root.down ? root.indicatorHighlightColor : root.indicatorColor
            visible: root.checked

            TapHandler {
                onTapped: root.checked = !root.checked
            }

        }
    }

    contentItem: KLabel {
        text: root.text
        font: root.font
        opacity: enabled ? 1.0 : 0.3
        color: root.down ?  KStyle.styleDefinition.kpalette.highlightedText : KStyle.styleDefinition.kpalette.text
        verticalAlignment: Text.AlignVCenter
        leftPadding: root.indicator.width + root.spacing

        TapHandler {
            onTapped: root.checked = !root.checked
        }
    }
}
