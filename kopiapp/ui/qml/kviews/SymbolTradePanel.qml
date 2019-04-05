import QtQuick 2.12

import Kopi 1.0

SymbolTradePanelForm {
    id: root

    property KSymbol iexsymbol

    stockpanelBar.hoverEnabled: false
    stockpanelBar.backgroundItem.border.color: KStyle.styleDefinition.kpalette.borderBaseColor
    stockpanelBar.backgroundItem.border.width: 2
    stockpanelBar.backgroundItem.radius: 10
}
