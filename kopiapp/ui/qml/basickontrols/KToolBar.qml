import QtQuick 2.12
import QtQuick.Controls 2.5

ToolBar {
    id: control
    property string backgroundColor: "transparent"
    property alias border: backgrounditem.border

    background: KRectangle {
        id: backgrounditem
        color: backgroundColor
    }
}
