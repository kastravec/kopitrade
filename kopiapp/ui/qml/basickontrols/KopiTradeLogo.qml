import QtQuick 2.12

import Kopi 1.0

Item {
    id: root

    property string logoDirectory: "qrc:/graphic-assets/logos/"
    property string logoFileName: "Color logo - no background.png"

    Image {
        id: logoImage
        anchors.fill: parent
        fillMode: Image.PreserveAspectFit
        source: logoDirectory + logoFileName
    }
}
