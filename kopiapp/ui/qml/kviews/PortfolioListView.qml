import QtQuick 2.12
import QtQuick.Controls 2.5

import Kopi 1.0
import SortFilterProxyModel 0.2

PortfolioListViewForm {
    id: portfolioListView

    property string selectedPortfolio
    property string searchInput

    listView.delegate: listDelegate
    listView.highlightFollowsCurrentItem: false
    listView.focus: true
    listView.model: proxyModel

    SortFilterProxyModel {
        id: proxyModel
        sourceModel: PortfolioListModel
        filters: AnyOf {
            RegExpFilter {
                roleName: "Portfolio_ID"
                pattern: searchInput
                caseSensitivity: Qt.CaseInsensitive
            }
            RegExpFilter {
                roleName: "Portfolio_Name"
                pattern: searchInput
                caseSensitivity: Qt.CaseInsensitive
            }
        }
    }

    Component {
        id: listDelegate

        PortfolioListViewDelegate {
            id: control
            width: listView.width - 10
            height: 50
            nameLabel.text: model.Portfolio_ID
            dataLabel.text: model.Portfolio_Name
            highlighted: ListView.isCurrentItem

            MouseArea {
                id: mousearea
                anchors.fill: parent
                preventStealing: true
                acceptedButtons: Qt.RightButton | Qt.LeftButton
                onPressed: {
                    listView.currentIndex = index
                    portfolioListView.selectedPortfolio = model.Portfolio_Name
                }
            }
        }
    }
}
