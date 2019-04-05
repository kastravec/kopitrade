import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.4

import "../kviews"
import "../basickontrols"

import Kopi 1.0

Item {
    id: root

    property alias watchlisView: watchlisView
    property alias marketDataBox: marketDataBox
    property alias symbolDataView: symbolDataView
    property alias dicoverSymbolSearchView: dicoverSymbolSearchView
    property int marketDataBoxMaxWidth: root.width * 0.36
    property int symbolDataViewMaxWidth: root.width * 0.64

    property alias snapDialog: snapDialog

    RowLayout {
        id: mainRowLayout
        spacing: 18
        anchors.fill: parent

        SymbolDataView {
            id: symbolDataView
            Layout.maximumWidth: root.symbolDataViewMaxWidth
            Layout.maximumHeight: root.height
            Layout.fillHeight: true
            Layout.fillWidth: true
        }

        Item {
            id: marketDataBox
            Layout.topMargin: 0
            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.maximumWidth: root.marketDataBoxMaxWidth
            Layout.maximumHeight: root.height

            ColumnLayout {
                anchors.fill: parent

                KTabBar {
                    id: marketListsTabBar
                    currentIndex: 0
                    contentHeight: 30
                    Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                    Layout.minimumHeight: 30
                    Layout.maximumHeight: 30
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    hoverEnabled: false
                    backgroundItem.border.color: KStyle.styleDefinition.kpalette.borderBaseColor
                    backgroundItem.border.width: 2
                    backgroundItem.radius: 10

                    KTabButton {
                        id: tabButton
                        width: marketListsTabBar.tabWidth
                        text: qsTr("Watchlists")

                        display: AbstractButton.TextOnly
                        isCurrent: marketListsTabBar.currentIndex === KTabBar.index
                        backgroundBorderWidth: 0
                    }

                    KTabButton {
                        id: cryptTab
                        width: marketListsTabBar.tabWidth
                        text: qsTr("Discover markets")
                        isCurrent: marketListsTabBar.currentIndex === KTabBar.index
                        backgroundBorderWidth: 0
                    }
                }

                StackLayout {
                    id: marketStackLayout
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    currentIndex: marketListsTabBar.currentIndex

                    Item {
                        id: watchlistTab
                        Layout.fillHeight: true
                        Layout.fillWidth: true

                        ColumnLayout {
                            id: listlayouts
                            anchors.fill: parent
                            Layout.alignment: Qt.AlignLeft | Qt.AlignTop

                            WatchlistView {
                                id: watchlisView
                                Layout.fillHeight: true
                                Layout.fillWidth: true
                                Layout.alignment: Qt.AlignLeft | Qt.AlignTop
                            }
                        }
                    }

                    Item {
                        id: discoverMarketsTab
                        Layout.fillHeight: true
                        Layout.fillWidth: true

                        ColumnLayout {
                            spacing: 10
                            anchors.fill: parent

                            Layout.alignment: Qt.AlignLeft | Qt.AlignTop

                            SymbolSearchView {
                                id: dicoverSymbolSearchView
                                popupList.width: discoverMarketsTab.width
                                Layout.maximumHeight: 50
                                Layout.minimumHeight: 40
                                Layout.fillWidth: true
                                Layout.minimumWidth: discoverMarketsTab.width - 10
                                Layout.maximumWidth: discoverMarketsTab.width - 10
                                Layout.alignment: Qt.AlignLeft | Qt.AlignTop
                            }

                            KSpacerItem {
                                Layout.fillWidth: true
                                Layout.fillHeight: true
                            }
                        }
                    }
                }
            }
        }
    }

    Popup {
        id: snapDialog

        background: KRectangle {
            color: KStyle.styleDefinition.kpalette.window
        }

        ColumnLayout {
            spacing: 1
            anchors.fill: parent

            KImageViewer {
                id: imageviewer
                Layout.fillHeight: true
                Layout.fillWidth: true
            }

            KFrame {
                id: kFrame
                backgroundColor: KStyle.styleDefinition.kpalette.dark
                borderWidthHighlighted: 1
                borderWidth: 1
                borderRadius: 6
                Layout.fillHeight: true
                Layout.maximumHeight: 50
                Layout.fillWidth: true
                Layout.alignment: Qt.AlignRight | Qt.AlignVCenter

                RowLayout {
                    anchors.left: parent.left
                    anchors.bottom: parent.bottom
                    anchors.top: parent.top

                    KButton {
                        id: saveSnapButton
                        text: "Save"
                        Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
                        backgroundBorderWidth: 1
                        backgroundBorderHighlightWidth: 1
                    }

                    KButton {
                        id: cancelSnapButton
                        text: "Cancel"
                        Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
                        backgroundBorderWidth: 1
                        backgroundBorderHighlightWidth: 1
                    }
                }
            }
        }
    }

}

/*##^## Designer {
    D{i:0;autoSize:true;height:980;width:1200}
}
 ##^##*/
