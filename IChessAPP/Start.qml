import QtQuick
import QtQuick.Controls

Item{
    id: start
    anchors.fill: parent
    Page {
        width: app.width
        height: app.height

        background: Image {
            source: "qrc:/img/start.png"
            fillMode: Image.Stretch
            anchors.fill: parent
            onStatusChanged: {
                if (status === Image.Error) {
                    console.log("Image load error:", source)
                }
            }
        }

        Button{
            width: 50
            height: 50
            background: Image {
                source: "qrc:/img/setting.png"
                fillMode: Image.Stretch
                anchors.fill: parent
                onStatusChanged: {
                    if (status === Image.Error) {
                        console.log("Image load error:", source)
                    }
                }
            }
            onClicked: manage.modes.set('setting')
        }
        Column {
            anchors.centerIn: parent
            spacing: 80

            Image {
                source: "qrc:/img/Title.png"
                fillMode: Image.PreserveAspectFit
                width: parent.width
                height: 150
            }

            Grid {
                rows: 2
                columns: 2
                spacing: 20

                Button {
                    text: "双人联机对战"
                    width: 150
                    height: 100
                    onClicked: chooseColor.open()
                    background: Rectangle {
                        anchors.fill: parent
                        color: "gray"
                        opacity: 0.5
                        radius: 5
                    }
                }

                Button {
                    text: "双人单机对战"
                    width: 150
                    height: 100
                    onClicked: manage.modes.set('board')
                    background: Rectangle {
                        anchors.fill: parent
                        color: "gray"
                        opacity: 0.5
                        radius: 5
                    }
                }

                Button {
                    text: "开发者名单"
                    width: 150
                    height: 100
                    onClicked: manage.modes.set('developer')
                    background: Rectangle {
                        anchors.fill: parent
                        color: "gray"
                        opacity: 0.5
                        radius: 5
                    }
                }

                Button {
                    text: "退出"
                    width: 150
                    height: 100
                    onClicked: manage.modes.set('quit')
                    background: Rectangle {
                        anchors.fill: parent
                        color: "gray"
                        opacity: 0.5
                        radius: 5
                    }
                }
            }
        }


        Dialog {
            id: chooseColor
            width: 300
            height: 150
            anchors.centerIn: parent

            contentItem:
                Column {
                    spacing: 20
                    Text {
                        text: "请选择成为黑方/白方（不可选择同样颜色）"
                        width: parent.width
                        wrapMode: Text.Wrap
                        color:"red"
                        horizontalAlignment: Text.AlignHCenter
                    }

                    Row {
                        spacing: 10
                        anchors.horizontalCenter: parent.horizontalCenter

                    Button {
                        text: "黑色"
                        width: 100
                        height: 50
                        onClicked: {
                            manage.modes.set('black')
                            chooseColor.close()
                        }
                    }

                    Button {
                        text: "白色"
                        width: 100
                        height: 50
                        onClicked: {
                            manage.modes.set('white')
                            chooseColor.close()
                        }
                    }
                }
            }
        }
    }
}


