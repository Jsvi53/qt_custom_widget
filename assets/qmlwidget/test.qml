import QtQuick 2.12
import QtQuick.Controls 2.5
import QtGraphicalEffects 1.12


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
            anchors.margins: 10
            onClicked: Qt.quit() // 现在可以正常工作
        }

        Button {
            id: menuTrigger
            text: "☰"
            anchors {
                left: parent.left
                top: parent.top
                margins: 10
            }
            onClicked: isMenuVisible = !isMenuVisible
        }

        Rectangle {
            id: sideMenu
            width: 200
            height: parent.height
            color: "#f0f0f0"
            anchors.right: parent.left
            
            layer.enabled: true
            layer.effect: DropShadow {
                radius: 5
                samples: 16
                color: "#80000000"
            }

            Behavior on anchors.rightMargin {
                NumberAnimation {
                    duration: 300
                    easing.type: Easing.OutCubic
                }
            }

            Button {
                text: "❯"
                anchors {
                    top: parent.top
                    right: parent.right
                    margins: 10
                }
                onClicked: isMenuVisible = false
                rotation: isMenuVisible ? 0 : 180
                Behavior on rotation {
                    NumberAnimation { duration: 300 }
                }
            }

            Column {
                anchors {
                    top: parent.top
                    topMargin: 50
                    left: parent.left
                    right: parent.right
                }
                spacing: 10

                Button {
                    text: "选项一"
                    width: parent.width
                    onClicked: console.log("选项一被点击")
                }
                Button {
                    text: "选项二" 
                    width: parent.width
                    onClicked: console.log("选项二被点击")
                }
                Button {
                    text: "选项三"
                    width: parent.width
                    onClicked: console.log("选项三被点击")
                }
            }

            states: State {
                name: "visible"
                when: isMenuVisible
                PropertyChanges {
                    target: sideMenu
                    anchors.right: parent.right
                }
            }
        }
    }

    property bool isMenuVisible: false
}