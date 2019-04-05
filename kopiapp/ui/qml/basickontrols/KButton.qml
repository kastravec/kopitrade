import QtQuick 2.12
import QtQuick.Controls 2.5

import Kopi 1.0

AbstractButton {
    id: root

    autoExclusive: true
    checkable: true
    checked: false
    hoverEnabled: true
    topPadding: 4
    bottomPadding: 4
    leftPadding: 4
    rightPadding: 4

    property string backgroundColor: "transparent" //KStyle.styleDefinition.kpalette.button
    property string backgroundHighlightColor: "transparent" //KStyle.styleDefinition.kpalette.highlight
    property string backgroundBorderHighlightColor: KStyle.styleDefinition.kpalette.highlight
    property int backgroundBorderWidth: 1
    property int backgroundBorderHighlightWidth: 1 //KStyle.styleDefinition.kspecs.mainMenu.border.width
    property string textColor: KStyle.styleDefinition.kpalette.buttonText
    property string textColorHightlight: KStyle.styleDefinition.kpalette.highlightedText
    property string backgroundBoderColor: KStyle.styleDefinition.kpalette.borderBaseColor
    property bool highlighted: false
    property alias borderRadius: backgroundItem.radius
    property alias textHorizontalAlignment: textItem.horizontalAlignment
    property alias textVerticalAlignment: textItem.verticalAlignment

    property string toolTipText: root.text
    property int toolTipDelay: 650
    property bool showToolTip: root.hovered

    KToolTip.visible: root.showToolTip
    KToolTip.delay: root.toolTipDelay
    KToolTip.text: root.toolTipText

    contentItem: KLabel {
        id: textItem
        text: root.text
        fontSizeMode: Text.Fit
        elide: Text.ElideRight
        font: root.font
        width: root.width
        height: root.height
        opacity: enabled ? 1.0 : 0.3
        color: (root.down || root.checked || root.hovered) ? root.textColorHightlight : root.textColor
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
    }

    background: Rectangle {
        id: backgroundItem

        opacity: enabled ? 1 : 0.2
        color: (root.down || hovered || highlighted
                || checked) ? root.backgroundHighlightColor : root.backgroundColor//"transparent"
        border.color: (root.down || hovered || highlighted
                       || checked) ? root.backgroundBorderHighlightColor : root.backgroundBoderColor
        border.width: (checked
                       || hovered) ? root.backgroundBorderHighlightWidth : root.backgroundBorderWidth
        radius: 15
    }
}

/*##^## Designer {
    D{i:0;height:20;width:64}
}
 ##^##*/
