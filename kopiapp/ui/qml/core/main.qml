import QtQuick 2.12

import Kopi 1.0
import QtQuick.Window 2.12
import "../mainscreens"

Item {
    id: root
    width: Screen.desktopAvailableWidth
    height: Screen.desktopAvailableHeight

    property bool firstRun
    property WatchListSymbolModel firstModel

    KSplashScreen {
        id: splashscreen
        onTimeout: mainAppWindowLoader.item.visible = true
    }

    Loader {
        id: mainAppWindowLoader
        source: "MainApplicationWindow.qml"
        active: true
        anchors.fill: parent
        visible: true
    }

    Component.onCompleted: {
        KStyle.theme = "dark.json"
        IEXCloudGlobals.readLocalIEXConfig()

        if(IEXSymbolsModel.rowCount() === 0) {
            root.firstRun = true
            IEXSymbolsModel.refresh()
        } else {
            root.firstRun = false
        }
    }

    Connections {
        target: IEXSymbolsModel

        onModelStatusChanged: {
            if(IEXSymbolsModel.modelStatus === IEXSymbolsModel.Ready) {
                console.log("MODEL STATUS " + IEXSymbolsModel.modelStatus)
                console.log("MODEL ROWS " + IEXSymbolsModel.rowCount())
                createFirstRunModel();
            }
        }
    }

    Component.onDestruction: {
        Kopi.storeLocally()
        IEXCloudGlobals.storeIEXConfigLocally()
    }

    function createFirstRunModel() {
        console.log("FIRST RUN " + firstRun )
        if(firstRun
                && IEXSymbolsModel.modelStatus === IEXSymbolsModel.Ready) {
            firstModel = WatchListsModel.createWatchlist("My tech watchlist")
            if(firstModel) {
                firstModel.addSymbol("AAPL")
                firstModel.addSymbol("TSLA")
                firstModel.addSymbol("ADBE")
                firstModel.addSymbol("GOOGL")
                WatchListsModel.setActiveWatchlist(firstModel.watchlistName)
            }
        }
    }
}
