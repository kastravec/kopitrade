import QtQuick 2.12
import QtQuick.Layouts 1.0

Item {
    id: root
    property alias chartView1: chartView1
    property alias chartView2: chartView2
    property alias chartView3: chartView3
    property alias chartView4: chartView4

    GridLayout {
        anchors.fill: parent
        rows: 2
        columns: 2

        KWebView {
            id: chartView1
            toolBar.visible: false
            statusBar.visible: false
            Layout.fillHeight: true
            Layout.fillWidth: true
        }

        KWebView {
            id: chartView2
            toolBar.visible: false
            statusBar.visible: false
            Layout.fillHeight: true
            Layout.fillWidth: true
        }

        KWebView {
            id: chartView3
            toolBar.visible: false
            statusBar.visible: false
            Layout.fillWidth: true
            Layout.fillHeight: true
        }

        KWebView {
            id: chartView4
            toolBar.visible: false
            statusBar.visible: false
            Layout.fillWidth: true
            Layout.fillHeight: true
        }
    }
}



/*##^## Designer {
    D{i:0;autoSize:true;height:480;width:640}D{i:1;anchors_x:61;anchors_y:79}
}
 ##^##*/
