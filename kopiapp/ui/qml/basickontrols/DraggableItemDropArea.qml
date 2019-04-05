import QtQuick 2.12

DropArea {
    id: root
    property int dropIndex

    KRectangle {
        id: dropIndicator
        anchors {
            left: parent.left
            right: parent.right
            top: dropIndex === 0 ? parent.verticalCenter : undefined
            bottom: dropIndex === 0 ? undefined : parent.verticalCenter
        }
        height: 3
        opacity: root.containsDrag ? 1 : 0.0
        color: "red"
    }
}
