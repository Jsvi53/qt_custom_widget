import QtQuick 2.12
import QtQuick.Controls 2.5
import QtGraphicalEffects 1.12

Item {
    width: 640
    height: 480

    // 渐变背景
    Rectangle {
        anchors.fill: parent
        gradient: Gradient {
            GradientStop { position: 0.0; color: "#8E2DE2" }
            GradientStop { position: 1.0; color: "#4A00E0" }
        }
    }

    // 主内容区域
    Rectangle {
        id: mainContent
        anchors.fill: parent
        color: "transparent"

        // 浮动卡片
        Rectangle {
            id: contentCard
            width: 400
            height: 300
            radius: 20
            color: "#FFFFFF"
            anchors.centerIn: parent
            opacity: 0.9

            // 卡片阴影
            layer.enabled: true
            layer.effect: DropShadow {
                transparentBorder: true
                horizontalOffset: 0
                verticalOffset: 10
                radius: 20
                samples: 41
                color: "#80000000"
            }

            // 光泽效果
            Rectangle {
                width: parent.width
                height: parent.height/2
                radius: parent.radius
                color: "#40FFFFFF"
                border.color: "#20FFFFFF"
            }

            // 动态文本
            Text {
                id: contentCardText
                width: parent.width - 40
                text: "Hello from QML"
                anchors.centerIn: parent
                wrapMode: Text.Wrap
                horizontalAlignment: Text.AlignHCenter
                font {
                    pixelSize: 36
                    family: "Arial"
                    weight: Font.DemiBold
                }
                color: "#333333"

                // 文字阴影
                layer.enabled: true
                layer.effect: DropShadow {
                    transparentBorder: true
                    horizontalOffset: 2
                    verticalOffset: 2
                    radius: 2
                    samples: 5
                    color: "#40000000"
                }
            }
        }

        // 关闭按钮
        Button {
            id: closeButton
            text: "✕"
            anchors {
                bottom: parent.bottom
                right: parent.right
                margins: 20
            }
            width: 50
            height: 50
            font.pixelSize: 20

            background: Rectangle {
                radius: 25
                color: closeButton.down ? "#FF4757" :
                                          closeButton.hovered ? "#FF6B81" : "#FF4757"
                opacity: closeButton.hovered ? 1 : 0.7

                Behavior on color { ColorAnimation { duration: 200 } }
                Behavior on opacity { NumberAnimation { duration: 200 } }
            }
            onClicked: Qt.quit()
        }

        // 菜单触发按钮
        Button {
            id: menuTrigger
            text: "☰"
            anchors {
                left: parent.left
                top: parent.top
                margins: 20
            }
            width: 50
            height: 50
            font.pixelSize: 20

            background: Rectangle {
                radius: 25
                color: menuTrigger.down ? "#3742FA" :
                                          menuTrigger.hovered ? "#5352ED" : "#3742FA"
                opacity: menuTrigger.hovered ? 1 : 0.7

                Behavior on color { ColorAnimation { duration: 200 } }
                Behavior on opacity { NumberAnimation { duration: 200 } }
            }
            onClicked: isMenuVisible = !isMenuVisible
        }

        // 侧边菜单
        Rectangle {
            id: sideMenu
            width: 250
            height: parent.height
            color: "#A0FFFFFF" // 半透明白色
            anchors.right: parent.left
            opacity: 0.95

            // 背景模糊层
            Rectangle {
                anchors.fill: parent
                color: "#80FFFFFF"
                layer.enabled: true
                layer.effect: FastBlur {
                    radius: 32
                    source: mainContent // 模糊主内容区域
                }
            }

            // 菜单内容容器（保持清晰）
            Item {
                id: menuContent
                anchors.fill: parent
                layer.enabled: true // 防止内容被模糊

                // 关闭菜单按钮
                Button {
                    id: closeMenuButton
                    text: "❯"
                    anchors {
                        top: parent.top
                        right: parent.right
                        margins: 20
                    }
                    width: 50
                    height: 50
                    font.pixelSize: 16

                    background: Rectangle {
                        radius: 25
                        color: closeMenuButton.down ? "#2ED573" :
                                                      closeMenuButton.hovered ? "#7BED9F" : "#2ED573"
                        opacity: closeMenuButton.hovered ? 1 : 0.7
                    }

                    onClicked: isMenuVisible = false
                    rotation: isMenuVisible ? 0 : 180
                    Behavior on rotation {
                        NumberAnimation {
                            duration: 400
                            easing.type: Easing.OutBack
                        }
                    }
                }

                // 菜单项列表
                Column {
                    anchors {
                        top: parent.top
                        topMargin: 80
                        left: parent.left
                        right: parent.right
                    }
                    spacing: 8
                    padding: 10

                    Repeater {
                        model: ["主页", "个人资料", "系统设置", "帮助中心", "关于我们"]

                        delegate: Button {
                            width: parent.width - 20
                            height: 50
                            leftPadding: 20

                            contentItem: Text {
                                text: modelData
                                width: parent.width - 40
                                elide: Text.ElideRight
                                wrapMode: Text.Wrap
                                font {
                                    pixelSize: 16
                                    family: "Arial"
                                    weight: Font.Medium
                                }
                                color: "#333333"
                                horizontalAlignment: Text.AlignLeft
                                verticalAlignment: Text.AlignVCenter
                            }

                            background: Rectangle {
                                color: parent.down ? "#F1F2F6" :
                                                     parent.hovered ? "#F8F9FA" : "transparent"
                                radius: 8

                                // 涟漪效果
                                Rectangle {
                                    anchors.fill: parent
                                    color: "#10000000"
                                    visible: parent.parent.down
                                    radius: 8
                                }
                            }

                            onClicked: {
                                console.log("已选择：" + modelData)
                                contentCardText.text = "当前选择：" + modelData
                            }
                        }
                    }
                }

                // 版本信息
                Text {
                    text: "版本 1.0.0"
                    anchors {
                        bottom: parent.bottom
                        horizontalCenter: parent.horizontalCenter
                        margins: 20
                    }
                    font {
                        pixelSize: 12
                        family: "Arial"
                    }
                    color: "#666666"
                }
            }

            // 菜单动画
            Behavior on anchors.rightMargin {
                NumberAnimation {
                    duration: 400
                    easing.type: Easing.OutBack
                }
            }

            // 菜单状态
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
