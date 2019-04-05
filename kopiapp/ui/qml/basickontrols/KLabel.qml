import QtQuick 2.12
import QtQuick.Controls 2.5

import Kopi 1.0

Label {
    id: root

    wrapMode: Text.WrapAtWordBoundaryOrAnywhere
    elide: Text.ElideRight
    color: KStyle.styleDefinition.kpalette.text

    property string toolTipText: root.text
    property int toolTipDelay: 650
    property bool showToolTip: false

    KToolTip.visible: root.showToolTip
    KToolTip.delay: root.toolTipDelay
    KToolTip.text: root.toolTipText
}
