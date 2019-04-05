import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3

import Kopi 1.0

import "../basickontrols"

Item {
    id: root
    width: 600
    height: 800

    property alias currentWatchlistCombo: currentWatchlistCombo
    property alias editWatchlistListButton: editWatchlistListButton
    property alias editListButton: addtolistlabel
    property alias symbolListBox: symbolListBox
    property alias watchlistViewPopup: watchlistViewPopup
    property alias symbolsearch: symbolsearch
    property alias nameInput: nameInput
    property alias mainWatchlistsView: mainWatchlistsView
    property alias symbolListView: symbolListView

    ColumnLayout {
        spacing: 10
        anchors.fill: parent

        KLabel {
            id: lbl1
            text: qsTr("Manage your watchlists")
            color: KStyle.styleDefinition.kpalette.baseText
            Layout.fillWidth: true
            font.italic: true
            font.pointSize: 12
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            Layout.minimumHeight: 30
        }

        RowLayout {
            spacing: 8
            Layout.fillWidth: true

            KComboBox {
                id: currentWatchlistCombo
                Layout.fillWidth: true
                height: 40
                delegate: KItemDelegate {
                    width: currentWatchlistCombo.width
                    text: model.WatchListNameRole
                    highlighted: currentWatchlistCombo.highlightedIndex === model.index
                }
            }

            KButton {
                id: editWatchlistListButton
                text: editWatchlistListButton.checked ? qsTr("Done") : qsTr(
                                                            "Edit")
                font.pointSize: 13
                font.bold: true
                backgroundBorderWidth: 0
                backgroundBorderHighlightWidth: 1
                checkable: true
                autoExclusive: false
            }
        }

        Item {
            id: symbolListBox
            Layout.minimumWidth: root.width
            Layout.fillHeight: true
            Layout.fillWidth: true

            ColumnLayout {
                spacing: 8
                anchors.fill: parent

                RowLayout {
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    spacing: 4

                    KLabel {
                        id: addtolistlabel
                        text: "Add to the list:"
                        font.pointSize: 12
                        font.bold: true
                        color: KStyle.styleDefinition.kpalette.baseText
                    }

                    SymbolSearchView {
                        id: symbolsearch
                        popupList.width: symbolListBox.width -10
                        xmargin: -addtolistlabel.width
                        searchInputLabel.placeholderText: qsTr("<i>search for a symbol/name</i>")
                        searchInputLabel.backgroundBorderRadius: 6
                        Layout.maximumHeight: 34
                        Layout.minimumHeight: 26
                        Layout.fillWidth: true
                        Layout.fillHeight: true
                    }
                }

                SymbolListView {
                    id: symbolListView
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                }

            } //end of colum layout
        }
    }

    Popup {
        id: watchlistViewPopup
        closePolicy: Popup.NoAutoClose
        width: currentWatchlistCombo.width
        visible: editWatchlistListButton.checked
        x: currentWatchlistCombo.x
        y: currentWatchlistCombo.y + 40

        background: KRectangle {
            color: KStyle.styleDefinition.kspecs.mainMenu.mainBox.background.color
            border.color: KStyle.styleDefinition.kpalette.borderBaseColor
            radius: 10
            border.width: 1
        }

        onClosed: currentWatchlistCombo.currentIndex = mainWatchlistsView.currentIndex

        ColumnLayout {
            anchors.fill: parent

            KTextField {
                id: nameInput
                Layout.fillWidth: true
                placeholderText: "enter name for new watchlist.."
            }

            ListView {
                id: mainWatchlistsView
                spacing: 0
                Layout.minimumHeight: 150
                clip: true
                Layout.fillWidth: true
                Layout.fillHeight: true
                highlightFollowsCurrentItem: true
            }
        }
    }
}










/*##^## Designer {
    D{i:15;invisible:true}D{i:13;invisible:true}
}
 ##^##*/
