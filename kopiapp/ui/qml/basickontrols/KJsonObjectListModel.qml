import QtQuick 2.12
import QtQml.Models 2.12
import QtQuick.Layouts 1.4

import Kopi 1.0

KRectangle {
    id: root
    property alias jsonObject: listmodel.jsonObject
    property string title
    property alias repeater: repeater

    border.color: KStyle.styleDefinition.kpalette.borderBaseColor
    border.width: 0
    height: repeater.count *40

    onJsonObjectChanged: listmodel.jsonObject = root.jsonObject

    JsonObjectList {
        id: listmodel
    }

    Column {
        anchors.fill: parent

        KLabel {
            id: titleLabel
            text: root.title
            width: root.width
            height: 35
            font.bold: true
            font.pointSize: 16
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            visible: repeater.count > 0
        }

        Column {
            width: root.width
            Repeater {
                id: repeater
                delegate: delegateComponent
                model: listmodel
            }
        }
    }

    Component {
        id: delegateComponent

        KRectangle {
            id: delegateitem
            width: root.width -5
            height: 40
            color: KStyle.styleDefinition.kpalette.base
            border.color: KStyle.styleDefinition.kpalette.borderBaseColor
            border.width: 1
            radius: 8

            RowLayout {
                anchors.fill: parent
                spacing: 10
                KLabel {
                    id: nameLabel
                    text: model.Name
                    font.pointSize: 14
                    color: KStyle.styleDefinition.kpalette.brightText
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    Layout.maximumWidth: root.width *0.4
                    Layout.maximumHeight:50
                }

                KLabel {
                    id: valueLabel
                    text: model.Value
                    font.bold: true
                    font.pointSize: 15
                    color: KStyle.styleDefinition.kpalette.buttonText
                    toolTipText: valueLabel.text
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    Layout.maximumWidth: root.width *0.6
                    Layout.maximumHeight:50
                }
            }
        }
    }
}
