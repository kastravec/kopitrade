import QtQuick 2.12

Item {
    id: root

    default property Item contentItem

    // This item will become the parent of the dragged item during the drag operation
    property Item draggedItemParent
    property alias dropArea: dropArea
    property alias dragArea: dragArea

    signal moveItemRequested(int from, int to)

    width: contentItem.width
    height: contentItem.height

    // Make contentItem a child of contentItemWrapper
    onContentItemChanged: {
        contentItem.parent = contentItemWrapper;
    }

    KRectangle {
        id: contentItemWrapper
        width: root.width + 20
        height: root.height
        Drag.active: dragArea.drag.active
        Drag.hotSpot {
            x: contentItem.width / 2
            y: contentItem.height / 2
        }

        KLabel {
            text: "..\n.."
            anchors.right: parent.right
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            anchors.topMargin: 10

        }

        MouseArea {
            id: dragArea
            anchors.fill: parent
            drag.target: parent
            // Keep the dragged item at the same X position. Nice for lists, but not mandatory
            drag.axis: Drag.YAxis
            // Disable smoothed so that the Item pixel from where we started the drag remains under the mouse cursor
            drag.smoothed: false
            drag.maximumY: root.parent.height
            drag.minimumY: -1
            onReleased: {
                if (drag.active) {
                    emitMoveItemRequested();
                }
            }
        }
    }

    states: [
        State {
            when: dragArea.drag.active
            name: "dragging"

            ParentChange {
                target: contentItemWrapper
                parent: draggedItemParent
            }
            PropertyChanges {
                target: contentItemWrapper
                opacity: 0.9
                anchors.fill: undefined
                width: contentItem.width
                height: contentItem.height
            }
            PropertyChanges {
                target: root
                height: 0
            }
        }
    ]

    Loader {
        id: topDropAreaLoader
        active: model.index === 0
        anchors {
            left: parent.left
            right: parent.right
            bottom: root.verticalCenter
        }
        height: contentItem.height
        sourceComponent: Component {
            DraggableItemDropArea {
                dropIndex: 0
            }
        }
    }

    DraggableItemDropArea {
        id: dropArea
        anchors {
            left: parent.left
            right: parent.right
            top: root.verticalCenter
        }
        height: contentItem.height
        dropIndex: model.index + 1
    }

    function emitMoveItemRequested() {
        var dropArea = contentItemWrapper.Drag.target;
        if (!dropArea) {
            return;
        }
        var dropIndex = dropArea.dropIndex;

        // If the target item is below us, then decrement dropIndex because the target item is going to move up when
        // our item leaves its place
        if (model.index < dropIndex) {
            dropIndex--;
        }
        if (model.index === dropIndex) {
            return;
        }
        root.moveItemRequested(model.index, dropIndex);
    }
}
