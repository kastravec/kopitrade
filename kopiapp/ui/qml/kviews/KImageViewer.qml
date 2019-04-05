import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.4

import "../basickontrols"

Item {
    property alias image: image

    ColumnLayout {
        anchors.fill: parent

        KToolBar {
            id: toolbar
            Layout.minimumHeight: 38
            Layout.fillWidth: true
        }

        Image {
            id: image
            Layout.fillHeight: true
            Layout.fillWidth: true

            fillMode: Image.PreserveAspectFit
        }
    }
}
