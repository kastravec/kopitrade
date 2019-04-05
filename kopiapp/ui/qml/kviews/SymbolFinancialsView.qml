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

    property KSymbol iexsymbol

    focusPolicy: Qt.StrongFocus

    onIexsymbolChanged: {
        if(root.iexsymbol.symbol.length > 0 && root.iexsymbol.symbolType === KSymbol.CommonStock) {
            busyIndicator.running = true
            connections.target = root.iexsymbol
            iexsymbol.fetchFinancials()
            iexsymbol.fetchIncomeStatement()
        } else {
            logoImage.source = ""
            companyNameLabel.text = ""
            financialsJsonList.jsonObject = {}
            earningsJsonList.jsonObject = {}
        }
    }

    Connections {
        id: connections
        target: iexsymbol

        onErrorResponse: {
            busyIndicator.running = false
        }

        onNewFinancialsData: {
            financialsJsonList.jsonObject = iexsymbol.newJsonData
            busyIndicator.running = false
        }

        onNewIncomeStatementData: {
            earningsJsonList.jsonObject = iexsymbol.newJsonData
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
            spacing: 20

            KSymbolLogo {
                id: logoImage
                width: 80
                height: 80
                fillMode: Image.PreserveAspectFit
                source: root.iexsymbol.logoUrl
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
        }

        Row {
            width: root.width
            spacing: 2
            height: financialsJsonList.height > earningsJsonList.height ? financialsJsonList.height +20: earningsJsonList.height +20

            KJsonObjectListModel {
                id: financialsJsonList
                width: root.width/2 -15
                title: qsTr("Company Financials")
            }

            KJsonObjectListModel {
                id: earningsJsonList
                width: root.width/2 -15
                title: qsTr("Company income statement")
            }
        }
    }
}


/*##^## Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
 ##^##*/
