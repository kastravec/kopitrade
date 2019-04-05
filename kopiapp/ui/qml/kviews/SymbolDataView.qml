import QtQuick 2.12
import QtQuick.Layouts 1.4

import Kopi 1.0

import "../basickontrols"

Item {
    id: root

    property string currentSymbol
    property alias chartView: chartView

    property int chartViewMaxHeight: root.height * 0.45
    property int symbolDetailsBoxHeight: root.height * 0.55

    ColumnLayout {
        id: mainColumnLayout
        spacing: 0
        anchors.fill: parent
        anchors.margins: 0

        ChartView {
            id: chartView
            Layout.alignment: Qt.AlignLeft | Qt.AlignTop
            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.maximumWidth: root.width
            Layout.maximumHeight: root.chartViewMaxHeight
            currentSymbol: root.currentSymbol
        }

        SymbolDetailslView {
            id: symbolDetailsView
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.maximumWidth: root.width
            Layout.maximumHeight: root.symbolDetailsBoxHeight
            currentSymbol: root.currentSymbol
        }
    }
}

/*##^## Designer {
    D{i:0;height:700;width:800}
}
 ##^##*/

