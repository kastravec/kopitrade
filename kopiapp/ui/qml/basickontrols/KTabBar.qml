import QtQuick 2.12
import QtQuick.Controls 2.5

TabBar {
    id: root
    clip: true
    property alias backgroundItem: backgroundItem
    property int tabWidthFactor: 1
    property int tabWidth: (root.width * (1/root.tabWidthFactor) - 1)

    onCountChanged: {
        root.tabWidthFactor = (root.count === 0) ? 1 : root.count
    }

    background: KRectangle {
        id: backgroundItem
    }
}
