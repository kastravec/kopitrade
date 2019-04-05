import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.4

import "../basickontrols"

import Kopi 1.0

ComboBox {
    id: root

    indicator: Canvas {
        id: canvas
        x: root.width - width - root.rightPadding
        y: root.topPadding + (root.availableHeight - height) / 2
        width: 14
        height: 10
        contextType: "2d"

        Connections {
            target: root
            onPressedChanged: canvas.requestPaint()
        }

        onPaint: {
            context.reset()
            if (root.down) {
                context.moveTo(0, 0)
                context.lineTo(width, 0)
                context.lineTo(width / 2, height)
            } else {
                context.moveTo(0, height / 2)
                context.lineTo(width, 0)
                context.lineTo(width, height)
            }

            context.closePath()
            context.fillStyle = root.down ? KStyle.styleDefinition.kpalette.highlight : KStyle.styleDefinition.kspecs.mainMenu.mainBox.background.color //KStyle.styleDefinition.kpalette.borderBaseColor
            context.fill()
        }
    }

    contentItem: KLabel {
        leftPadding: 0
        rightPadding: root.indicator.width + root.spacing

        text: root.displayText
        font: root.font
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
        elide: Text.ElideRight
        showToolTip: false
    }

    background: KRectangle {
        implicitWidth: 120
        implicitHeight: 35
        border.color: root.pressed ? KStyle.styleDefinition.kpalette.highlight : KStyle.styleDefinition.kpalette.borderBaseColor
        border.width: root.visualFocus ? 1 : 1
        radius: 6
        color: KStyle.styleDefinition.kpalette.selectedTabBackgroundColor
    }

    popup: Popup {
        y: root.height - 1
        width: root.width
        implicitHeight: contentItem.implicitHeight
        padding: 1

        onAboutToHide: {
            canvas.requestPaint()
        }

        KRectangle {
            width: root.width
            height: listview.contentHeight + 10
            color: KStyle.styleDefinition.kspecs.mainMenu.mainBox.background.color
            radius: 8
            border.width: 1

            ListView {
                id: listview
                clip: true
                anchors.fill: parent

                model: root.popup.visible ? root.delegateModel : null
                currentIndex: root.highlightedIndex
            }
        }
    }
}
