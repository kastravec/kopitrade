import QtQuick 2.12
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.5

import "../basickontrols"

import Kopi 1.0

ScrollView {
    id: root
    clip: true

    ScrollBar.horizontal.interactive: true
    ScrollBar.vertical.interactive: true

    contentWidth: mainColumnLayout.width
    contentHeight: mainColumnLayout.height + 20

    property KSymbol iexsymbol: KSymbol {symbol: "AAPL"}

    focusPolicy: Qt.StrongFocus

    onIexsymbolChanged: {
        connections.target = root.iexsymbol
        if(root.iexsymbol.symbol.length > 0 && root.iexsymbol.symbolType === KSymbol.CommonStock) {
            busyIndicator.running = true
            iexsymbol.fetchCompany()
            iexsymbol.fetchKeyStats()
        } else{
            logoImage.source = ""
            companyNameLabel.text = ""
            websiteLabel.text = ""
            jsonlist.jsonObject = {}
            jsonlist2.jsonObject = {}
        }
    }

    Connections {
        id: connections
        target: iexsymbol
        onErrorResponse: {
            busyIndicator.running = false
        }

        onNewKeyStatsData: {
            jsonlist2.jsonObject = iexsymbol.newJsonData
            busyIndicator.running = false
        }

        onNewCompanyData: {
            jsonlist.jsonObject = iexsymbol.newJsonData
            logoImage.source = iexsymbol.logoUrl
            busyIndicator.running = false
        }
    }

    KBusyIndicator {
        id: busyIndicator
        running: false
    }

    Column {
        id: mainColumnLayout
        spacing: 10
        width: root.width

        Row {
            id: row
            width: root.width
            height: 80
            spacing: 15

            KSymbolLogo {
                id: logoImage
                width: 80
                height: 80
                fillMode: Image.PreserveAspectFit
            }

            KLabel {
                id: symbolLabel
                color: "#d6d0d0"
                font.bold: true
                font.pointSize: 18
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
            }

            KLabel {
                id: companyNameLabel
                color: "#d7d1d1"
                font.bold: true
                font.pointSize: 18
                text: iexsymbol.symbolName
            }

            KLabel {
                id: websiteLabel
                color: "#d6d0d0"
                textFormat: Text.RichText
                font.bold: true
                font.pointSize: 18
            }
        }

        Row {
            width: root.width
            spacing: 2
            height: jsonlist2.height *1.05

            KJsonObjectListModel {
                id: jsonlist
                width: root.width/2 -15
                title: qsTr("Company")
            }

            KJsonObjectListModel {
                id: jsonlist2
                width: root.width/2 -15
                title: qsTr("Key Company data")
            }
        }
    }
}


/*##^## Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
 ##^##*/
