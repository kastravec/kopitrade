import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.4

import "../basickontrols"

import Kopi 1.0
import SortFilterProxyModel 0.2

Item {
    id: root

    property alias popupList: symbolListPopup
    property int xmargin: 0
    property int ymargin: 0
    property alias symbolListPopup: symbolListPopup
    property alias symbolListView: symbolListView
    property alias searchInputLabel: searchInputLabel

    //user selected symbol - IEXDataSymbol object
    property string lastSelectedIexDataSymbol
    property string backgroundBaseColor: KStyle.styleDefinition.kspecs.mainMenu.mainBox.background.color

    Connections {
        target: searchInputLabel

        onFocusChanged: {
            if (!searchInputLabel.focus && !symbolListView.focus) {
                symbolListPopup.close()
            }
        }

        onLengthChanged: {
            if (searchInputLabel.length > 0) {
                mapCoordinatesForPopup()
                symbolListPopup.open()
            }
        }
    }

    KTextField {
        id: searchInputLabel
        placeholderText: "<i>search for a company or a ticker..</i>"

        width: root.width
        height: root.height
        focus: true

        Popup {
            id: symbolListPopup
            width: root.popupWidth
            height: 400

            background: KRectangle {
                color: root.backgroundBaseColor
            }

            ColumnLayout {
                anchors.fill: parent
                ButtonGroup {
                    buttons: buttonLayout.children
                }

                KGroupBox {
                    Layout.fillWidth: true
                    height: 40
                    RowLayout {
                        id: buttonLayout
                        spacing: 1
                        anchors.fill: parent

                        KCheckBox {
                            id: allCheckbox
                            text: qsTr("All")
                            font.pointSize: 10
                            autoExclusive: true
                            checked: true
                        }

                        KCheckBox {
                            id: stocksCheckbox
                            text: qsTr("Stocks")
                            font.pointSize: 10
                            autoExclusive: true
                        }

                        KCheckBox {
                            id: etfCheckbox
                            text: qsTr("ETF")
                            font.pointSize: 10
                            autoExclusive: true
                        }

                        KCheckBox {
                            id: currencyCheckbox
                            text: qsTr("Forex")
                            font.pointSize: 10
                            autoExclusive: true
                        }

//                        KCheckBox {
//                            id: commoditiesCheckbox
//                            text: qsTr("Commodities")
//                            font.pointSize: 10
//                            autoExclusive: true
//                        }

                        KCheckBox {
                            id: cryptoCheckbox
                            text: qsTr("Cryptocurrency")
                            font.pointSize: 10
                            autoExclusive: true
                        }
                    }
                }

                ListView {
                    id: symbolListView
                    clip: true
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    keyNavigationWraps: true
                    keyNavigationEnabled: true
                    focus: true
                    model: proxyModel
                    delegate: basicListDelegate
                    cacheBuffer: 100
                }
            }
        }
    }

    //! sort filters for the iex data symbol model
    SortFilterProxyModel {
        id: proxyModel
        sourceModel: IEXSymbolsModel
        filters: [ AnyOf {
                RegExpFilter {
                    roleName: "Symbol"
                    pattern: searchInputLabel.text
                    caseSensitivity: Qt.CaseInsensitive
                }

                RegExpFilter {
                    roleName: "Symbol_Name"
                    pattern: searchInputLabel.text
                    caseSensitivity: Qt.CaseInsensitive
                }
            },

            ValueFilter {
                enabled: etfCheckbox.checked
                roleName: "Type"
                value: KSymbol.ETF
            },

            ValueFilter {
                enabled: currencyCheckbox.checked
                roleName: "Type"
                value: KSymbol.Currency
            },

            ValueFilter {
                enabled: cryptoCheckbox.checked
                roleName: "Type"
                value: KSymbol.Cryptocurreny
            },

            ValueFilter {
                enabled: stocksCheckbox.checked
                roleName: "Type"
                value: KSymbol.CommonStock
            }
        ]
    }

    //basic delegate used for the search view
    Component {
        id: basicListDelegate
        SymbolListViewBasicDelegate {
            id: controlDelegate
            height: 60
            width: symbolListView.width - 10
            symbolLabel.text: model.Symbol
            nameLabel.text: model.Symbol_Name
            backgroundBaseColor: root.backgroundBaseColor
            borderRadius: 0
            focus: true

            onClickedIexDataSymbolChanged: {
                root.lastSelectedIexDataSymbol = controlDelegate.clickedIexDataSymbol
                searchInputLabel.focus = false
                symbolListPopup.close()

            }
        }
    }

    function mapCoordinatesForPopup() {
        var pos = root.mapFromItem(searchInputLabel, searchInputLabel.x,
                                   searchInputLabel.y)
        symbolListPopup.x = pos.x + root.xmargin
        symbolListPopup.y = pos.y + searchInputLabel.height + root.ymargin
    }
}
