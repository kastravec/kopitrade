import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.4

import SortFilterProxyModel 0.2
import Kopi 1.0

import "../basickontrols"

WatchlistViewForm {
    id: root

    property WatchListSymbolModel currentWatchlist

    mainWatchlistsView.model: WatchListsModel
    mainWatchlistsView.delegate: watchlistsdelegate
    symbolListView.symbolModel: WatchListsModel.activeWatchlist
    currentWatchlistCombo.model: WatchListsModel
    symbolListView.hideBars: false

    Component.onCompleted: {
        WatchListsModel.checkDefaultWatchlist()
        currentWatchlistCombo.displayText = WatchListsModel.activeWatchlist.watchlistName
    }

    //adding symbol to the active watchlist when selected from search view
    symbolsearch.onLastSelectedIexDataSymbolChanged: {
        WatchListsModel.activeWatchlist.addSymbol(
                    symbolsearch.lastSelectedIexDataSymbol)
    }

    KScheduler {
        id: scheduler
        interval: 5000
        repeat: true
        from: 8
        to: 21
        runOnWeekends: false

        onTriggered: WatchListsModel.activeWatchlist.refresh()
        Component.onCompleted: scheduler.start()
    }

    //    //! sort filters for the watchlists model to filter the favorite ones only
    SortFilterProxyModel {
        id: favoriteWatchListProxyModel
        sourceModel: WatchListsModel

        filters: ValueFilter {
            enabled: true
            roleName: "WatchListFavoriteRole"
            value: true
        }
    }

    nameInput.onAccepted: createWatchlistItem(nameInput.text)
    currentWatchlistCombo.onActivated: {
        WatchListsModel.setActiveWatchlist(index)
        if (WatchListsModel.activeWatchlist) {
            currentWatchlistCombo.currentIndex = index
            currentWatchlistCombo.displayText = WatchListsModel.activeWatchlist.watchlistName
        }
    }

    Component {
        id: watchlistsdelegate
        WatchListsViewDelegate {
            id: delegateitem
            width: mainWatchlistsView.width
            editMode: true
            nameLabel.text: model.WatchListNameRole

            removeButton.onClicked: {
                WatchListsModel.removeWatchList(model.WatchListNameRole)
            }

            nameLabel.onClicked: {
                WatchListsModel.setActiveWatchlist(model.WatchListNameRole)
                currentWatchlistCombo.currentIndex = mainWatchlistsView.currentIndex
                currentWatchlistCombo.displayText = WatchListsModel.activeWatchlist.watchlistName
            }
        }
    }

    Connections {
        target: WatchListsModel
        onActiveWatchlistChanged: {
            currentWatchlistCombo.displayText = WatchListsModel.activeWatchlist.watchlistName
        }
    }

    function createWatchlistItem(name) {
        root.currentWatchlist = WatchListsModel.createWatchlist(name)
        mainWatchlistsView.currentIndex = WatchListsModel.rowCount()
    }

    function launchWatchlistPopup() {
        if (!watchlistViewPopup.opened) {
            var pos = root.mapFromItem(currentWatchlistCombo,
                                       currentWatchlistCombo.x,
                                       currentWatchlistCombo.y)
            watchlistViewPopup.x = pos.x - 20
            watchlistViewPopup.y = pos.y + 20
            watchlistViewPopup.open()
        }
    }
}
