import QtQuick 2.12
import QtQuick.Controls 2.5

Item {
    width: 640
    height: 480

    Rectangle {
        width: parent.width
        height: parent.height
        color: "lightblue"

        Text {
            text: "Hello from QML"
            anchors.centerIn: parent
            font.pixelSize: 24
        }

        Button {
            text: "Close"
            anchors.bottom: parent.bottom
            anchors.right: parent.right
            anchors.margins: 10 // 使用 anchors.margins 设置边距
            onClicked: Qt.quit()
        }
    }
}