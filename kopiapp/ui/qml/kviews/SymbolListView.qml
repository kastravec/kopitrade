import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQml.Models 2.12
import QtQml 2.3

import Kopi 1.0
import SortFilterProxyModel 0.2

import "../basickontrols"

SymbolListViewForm {
    id: root

    //use to hide the header and footer item
    //- by default hides when there are no items in the list
    property bool hideBars: true
    property bool editMode: false
    property bool showLogo: true
    property bool showChange: true

    //user selected symbol - IEXDataSymbol object
    property string lastSelectedIexDataSymbol
    property string searchInput
    property alias symbolModel: proxyModel.sourceModel

    property string backgroundBaseColor: KStyle.styleDefinition.kpalette.window
    property int borderItemRadius: 10

    listView.model: listviewDelegateModel
    listView.focus: true
    listView.keyNavigationEnabled: true
    listView.highlightFollowsCurrentItem: false

    busyindicator.running: IEXSymbolsModel.busy

    Component.onCompleted: {
        defaultSelectedSymbol()
    }

    Connections {
        target: IEXSymbolsModel

        onModelStatusChanged: {
            if(IEXSymbolsModel.modelStatus === IEXSymbolsModel.Ready)
                defaultSelectedSymbol()
        }
    }

    DelegateModel {
        id: listviewDelegateModel
        model: proxyModel
        delegate: listDelegate
    }

    //! sort filters for the iex data symbol model
    SortFilterProxyModel {
        id: proxyModel

        filters: AnyOf {
            RegExpFilter {
                roleName: "Symbol"
                pattern: searchInput
                caseSensitivity: Qt.CaseInsensitive
            }

            RegExpFilter {
                roleName: "Symbol_Name"
                pattern: searchInput
                caseSensitivity: Qt.CaseInsensitive
            }
        }

        sorters: RoleSorter {
            roleName: "OrderIndex"
            sortOrder: Qt.AscendingOrder
        }
    }

    //! list item delegate implementation
    Component {
        id: listDelegate

        DraggableItem {
            id: draggeditem
            property Item mainroot: root
            draggedItemParent: root
            onMoveItemRequested: {
                WatchListsModel.activeWatchlist.swapIndexOrder(from, to);
//                mainroot.listView.forceLayout()
            }

            SymbolListViewDelegate {
                id: controlDelegate
                width: root.width - 20
                height: 60
                coverPriceFrame.color: KStyle.styleDefinition.kpalette.highlight
                showChange: root.showChange
                showLogo: root.showLogo
                changeLabel.text: model.DailyChangePercent
                priceIncreased: model.PriceIncreased
                logoURL: model.Logo
                symbolLabel.text: model.Symbol
                nameLabel.text: model.Symbol_Name
                priceLabel.text: model.Last_Closed_Price
                highlighted: ListView.isCurrentItem
                focus: true
                backgroundBaseColor: root.backgroundBaseColor
                borderRadius: root.borderItemRadius
                editMode: root.editMode

                onSymbolNameLeftClicked: itemListDelegateLeftClicked(
                                             index, controlDelegate.clickedIexDataSymbol)
                onSymbolTickerLeftClicked: itemListDelegateLeftClicked(
                                               index, controlDelegate.clickedIexDataSymbol)

                onRemoveButtonClicked: {
                    symbolModel.removeSymbol(model.Symbol, false)
                }

                //changing the color of the price cover-frame to red or green according the price change
                onPriceIncreasedChanged: {
                    if(controlDelegate.priceIncreased === -1)
                        controlDelegate.coverPriceFrame.color = "transparent"//KStyle.styleDefinition.kpalette.highlight
                    else if(controlDelegate.priceIncreased === 1)
                        controlDelegate.coverPriceFrame.color = "#00b118"
                    else if(controlDelegate.priceIncreased === 0)
                        controlDelegate.coverPriceFrame.color = "#ae0000"
                }

                changeLabel.onTextChanged: {
                    if(changeLabel.text > 0) {
                        changeLabel.textColor = "#00b118"
                        priceLabel.textColor = "#00b118"
                    } else if(changeLabel.text < 0 ) {
                        changeLabel.textColor = "#dc423e"
                        priceLabel.textColor = "#dc423e"
                    }else
                        changeLabel.textColor = KStyle.styleDefinition.kpalette.highlight
                }
            }

        }
    }

    function itemListDelegateLeftClicked(index, iexDataSymbolObj) {
        root.listView.currentIndex = index
        root.lastSelectedIexDataSymbol = iexDataSymbolObj
    }

    function defaultSelectedSymbol() {
        if(root.symbolModel && root.symbolModel.rowCount() > 0) {
            var ksymb = root.symbolModel.symbol(symbolModel.rowCount())
            if(ksymb) {
                root.lastSelectedIexDataSymbol = ksymb.symbol
            }
        } else {
            root.lastSelectedIexDataSymbol = "TSLA"
        }
    }
}
