import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.4

import "../basickontrols"

import Kopi 1.0

Item {
    id: root

    property string currentSymbol
    property KSymbol iexsymbol
    property alias stockDataBar: stockDataBar
    property alias newsButton: newsButton
    property alias taButton: taButton
    property alias finButton: finButton
    property alias highlightsButton: highlightsButton

    onCurrentSymbolChanged: {
        root.iexsymbol = IEXSymbolsModel.symbol(root.currentSymbol)
        symbolFinancialsView.iexsymbol = root.iexsymbol
        symbolHighlightsView.iexsymbol = root.iexsymbol
    }

    ColumnLayout {
        id: mainlayout
        anchors.fill: parent
        anchors.margins: 10

        KTabBar {
            id: stockDataBar
            currentIndex: 0

            hoverEnabled: false
            backgroundItem.border.color: KStyle.styleDefinition.kpalette.borderBaseColor
            backgroundItem.border.width: 2
            backgroundItem.radius: 10
            Layout.alignment: Qt.AlignLeft | Qt.AlignTop
            Layout.maximumHeight: 45
            Layout.minimumHeight: 30
            Layout.fillWidth: true
            Layout.fillHeight: false

            KTabButton {
                id: highlightsButton
                text: qsTr("Highlights")
                backgroundBorderWidth: 0
                width: stockDataBar.tabWidth
                isCurrent: stockDataBar.currentIndex === KTabBar.index
            }

            KTabButton {
                id: finButton
                text: qsTr("Financials")
                backgroundBorderWidth: 0
                width: stockDataBar.tabWidth
                isCurrent: stockDataBar.currentIndex === KTabBar.index
            }

            KTabButton {
                id: taButton
                text: qsTr("Analysist's Insights")
                backgroundBorderWidth: 0
                width: stockDataBar.tabWidth
                isCurrent: stockDataBar.currentIndex === KTabBar.index
            }

            KTabButton {
                id: newsButton
                text: qsTr("Technicals")
                backgroundBorderWidth: 0
                width: stockDataBar.tabWidth
                isCurrent: stockDataBar.currentIndex === KTabBar.index
            }
        }

        StackLayout {
            id: stacklayout
            Layout.fillWidth: true
            Layout.fillHeight: true
            currentIndex: stockDataBar.currentIndex

            SymbolHighlightsDataView {
                id: symbolHighlightsView
                Layout.fillHeight: true
                Layout.fillWidth: true
            }

            SymbolFinancialsView {
                id: symbolFinancialsView
                Layout.fillHeight: true
                Layout.fillWidth: true
            }

            SymbolAnalysisView {
                Layout.fillHeight: true
                Layout.fillWidth: true
                iexsymbol: root.iexsymbol
            }

            SymbolTechnicalsView {
                Layout.fillHeight: true
                Layout.fillWidth: true
                iexsymbol: root.iexsymbol
            }
        }
    }
}

/*##^## Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
 ##^##*/

