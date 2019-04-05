import QtQuick 2.12
import QtQuick.Controls 2.5

import "../basickontrols"

Item {
    id: root

    width: 400
    height: 400
    property alias listView: listView

    ListView {
        id: listView
        spacing: 5
        snapMode: ListView.NoSnap
        highlightRangeMode: ListView.NoHighlightRange
        clip: true
        anchors.fill: parent
    }

}
