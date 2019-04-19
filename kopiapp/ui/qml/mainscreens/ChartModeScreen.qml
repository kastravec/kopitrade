import QtQuick 2.12
import QtQuick.Layouts 1.4
import QtQuick.Controls 2.5

import "../basickontrols"
import "../kviews"

import Kopi 1.0

Item {
    id: root

    property int numberOfCharts: 2
    property int chartViewType: 2

    onNumberOfChartsChanged: chartsNumberChanged()

    Component.onCompleted: {
        chartsNumberChanged()
    }

    StackLayout {
        id: mainstackview

        anchors.fill: parent

        GridView {
            id: gridview2
            width: root.width
            height: root.height
            keyNavigationWraps: true
            cellWidth: root.width/2 - 2
            cellHeight: root.height
            model: 2
            delegate: ChartView {
                chartViewType: root.chartViewType
                width: gridview2.cellWidth
                height: gridview2.cellHeight
                chartToolbarBox.visible: false
                chartToolbarBox.enabled: false
                currentSymbol: "AAPL"
            }
        }

        GridView {
            id: gridview4
            width: root.width
            height: root.height
            keyNavigationWraps: true
            cellWidth: root.width/2 - 2
            cellHeight: root.height/2 - 2
            model: 4
            delegate: ChartView {
                chartViewType: root.chartViewType
                width: gridview4.cellWidth
                height: gridview4.cellHeight
                chartToolbarBox.visible: false
                chartToolbarBox.enabled: false
                currentSymbol: "AAPL"
            }
        }

        GridView {
            id: gridview8
            width: root.width
            height: root.height
            keyNavigationWraps: true
            cellWidth: root.width/4 - 2
            cellHeight: root.height/2 - 2
            model: 8
            delegate: ChartView {
                chartViewType: root.chartViewType
                width: gridview8.cellWidth
                height: gridview8.cellHeight
                chartToolbarBox.visible: false
                chartToolbarBox.enabled: false
                currentSymbol: "AAPL"
            }
        }
    }

    function chartsNumberChanged() {
        switch(root.numberOfCharts) {
        case 2:
            mainstackview.currentIndex = 0
            break
        case 4:
            mainstackview.currentIndex = 1
            break
        case 8:
            mainstackview.currentIndex = 2
            break
        }
    }
}



/*##^## Designer {
    D{i:0;autoSize:true;height:480;width:640}D{i:3;anchors_x:0;anchors_y:0}
}
 ##^##*/
