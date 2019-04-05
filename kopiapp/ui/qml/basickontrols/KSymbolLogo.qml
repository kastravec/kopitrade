import QtQuick 2.12

import Kopi 1.0

Item {
    id: root

    width: 32
    height: 28

    property string source: "qrc:/graphic-assets/icons/stock_data-512.png"
    property alias fillMode: logoImage.fillMode

    onSourceChanged: {
        if(source.length <= 0)
            root.source = "qrc:/graphic-assets/icons/stock_data-512.png"
    }

    Image {
        id: logoImage
        fillMode: Image.PreserveAspectFit
        width: root.width
        height: root.height
        source: root.source
        onStatusChanged: {
            if(status === Image.Error ||
                    status === Image.Null)
                root.source = "qrc:/graphic-assets/icons/stock_data-512.png"
        }
    }
}
