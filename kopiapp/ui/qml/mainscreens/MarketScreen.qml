import QtQuick 2.12
import Kopi 1.0

MarketsScreenForm {
    id: root

    property string chartMode: "sizeOne" // modes: sizeOne | sizeDouble | fullMode
    property string selectedIexSymbol: dicoverSymbolSearchView.lastSelectedIexDataSymbol

    symbolDataView.currentSymbol: root.selectedIexSymbol

    watchlisView.symbolListView.onLastSelectedIexDataSymbolChanged: {
        root.selectedIexSymbol = watchlisView.symbolListView.lastSelectedIexDataSymbol
    }

    onSelectedIexSymbolChanged: {
        console.log("SELECTED SYMBOL IN MARKET SPACE: " + root.selectedIexSymbol)
    }

    Component.onCompleted: {
        symbolDataView.chartView.sizeOneButton.checked = true
        switchChartViewModes(root.chartMode)
    }

    //adding symbol to the active watchlist when selected from search view
    dicoverSymbolSearchView.onLastSelectedIexDataSymbolChanged: {
        root.selectedIexSymbol = dicoverSymbolSearchView.lastSelectedIexDataSymbol
    }

    symbolDataView.chartView.sizeDoubleButton.onCheckedChanged: {
        if (symbolDataView.chartView.sizeDoubleButton.checked) {
            switchChartViewModes("sizeDouble")
        }
    }

    symbolDataView.chartView.sizeOneButton.onCheckedChanged: {
        if (symbolDataView.chartView.sizeOneButton.checked) {
            switchChartViewModes("sizeOne")
        }
    }

    symbolDataView.chartView.chartPopupButton.onCheckedChanged: {
        if (symbolDataView.chartView.chartPopupButton.checked) {
            switchChartViewModes("fullMode")
        }
    }

//    symbolDataView.chartView.imageSnapButton.onClicked: {
//        symbolDataView.chartView.snapDialog.width = root.width * 0.55
//        symbolDataView.chartView.snapDialog.height = root.height * 0.55
//        symbolDataView.chartView.snapDialog.x = root.x + width / 5
//        symbolDataView.chartView.snapDialog.y = root.y + height / 6
//        symbolDataView.chartView.snapDialog.open()
//    }

    //toggling the different chart modes | sizeOne | sizeDouble | fullMode
    function switchChartViewModes(modes) {
        root.chartMode = modes
        if (modes === "sizeOne") {
            marketDataBox.visible = true

//            root.symbolDataView.width = root.width * 0.64
//            root.marketDataBox.width = root.width * 0.36

            root.marketDataBoxMaxWidth = root.width * 0.36
            root.symbolDataViewMaxWidth = root.width * 0.64

            root.symbolDataView.chartViewMaxHeight = root.height * 0.45
            root.symbolDataView.symbolDetailsBoxHeight = root.height * 0.55
        } else if (modes === "sizeDouble") {
            marketDataBox.visible = true
//            root.symbolDataView.width = root.width * 0.64
//            root.marketDataBox.width = root.width * 0.36
            root.symbolDataViewMaxWidth = root.width * 0.64
            root.marketDataBoxMaxWidth = root.width * 0.36

            root.symbolDataView.chartViewMaxHeight = root.height * 0.7
            root.symbolDataView.symbolDetailsBoxHeight = root.height * 0.3
        } else if (modes === "fullMode") {
            marketDataBox.visible = false

            root.symbolDataViewMaxWidth = root.width
            root.marketDataBoxMaxWidth = 0

//            root.symbolDataView.width = root.width
//            root.marketDataBox.width = 0

            root.symbolDataView.chartViewMaxHeight = root.height
            root.symbolDataView.symbolDetailsBoxHeight = 0
        }
    } //end of function
}
