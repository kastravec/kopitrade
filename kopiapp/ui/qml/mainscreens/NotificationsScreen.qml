import QtQuick 2.12

import "../kviews"
import "../basickontrols"

Item {
    id: root
    width: 1200
    height: 900

    KomingSoonView {
        id: komingSoonView
        anchors.fill: parent
        scheduledLabel.text: qsTr("Scheduled for end of Q2 2019")
    }
}
