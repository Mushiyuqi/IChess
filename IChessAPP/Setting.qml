import QtQuick
import QtQuick.Controls

Item {
    id: setting

    property color lightcolor: "#FFFFFF"
    property color darkcolor: "#808080"

    Page {
        visible: true
        width: app.width
        height: app.height
        background: Image {
            source: "qrc:/img/start.png"
            fillMode: Image.Stretch
            anchors.fill: parent
            opacity: 0.7
            onStatusChanged: {
                if (status === Image.Error) {
                    console.log("Image load error:", source)
                }
            }
        }

        Column {
            width: app.width
            height: app.height
            spacing: 40 // 设置列中各元素之间的间距

            Button {
                id: back
                text: "Back"
                onClicked: manage.goBack() // 返回上一页
            }


            Row {
                width: parent.width
                spacing: 10 // 设置行中各元素之间的间距
                padding: 20 // 设置行内部边距

                Text {
                    text: qsTr("声音：")
                    font.pixelSize: 20
                }

                Slider {
                    id: volumeSlider
                    width: app.width*0.65
                    from: 0
                    to: 1
                    value: 1
                    onValueChanged: {
                        musicPlayer.volume = value
                    }
                }
            }

            //棋盘换肤
            Text {
                text: qsTr("棋盘颜色：")
                font.pixelSize: 20
                x: 20 // 设置左边距
            }

            ButtonGroup{id:colorGroup}
            Grid{
                rows:2
                columns:2
                spacing: 30
                anchors.horizontalCenter: parent.horizontalCenter

                Column{
                    Image{
                        source: "qrc:/img/grey_white.png"
                        width: app.width/3
                        height: app.width/3
                    }
                    RadioButton {
                        text: "灰白雅局（默认）"
                        ButtonGroup.group: colorGroup
                        onCheckedChanged: {
                            if (checked) {
                                setting.lightcolor = "#F9FDFC"
                                setting.darkcolor = "#808081"
                                console.log("Button clicked!")
                            }
                        }
                    }
                }

                Column{
                    Image{
                        source: "qrc:/img/blue_white.png"
                        width: app.width/3
                        height: app.width/3
                    }
                    RadioButton  {
                        text: "蓝白瀚境"
                        ButtonGroup.group: colorGroup
                        onCheckedChanged: {
                            if (checked) {
                                setting.lightcolor = "#F9FDFC"
                                setting.darkcolor = "#6D84B6"
                                console.log("Button clicked!")
                            }
                        }
                    }
                }

                Column{
                    Image{
                        source: "qrc:/img/green_yellow.png"
                        width: app.width/3
                        height: app.width/3
                    }
                    RadioButton {
                        text: "绿茵生机"
                        ButtonGroup.group: colorGroup
                        onCheckedChanged: {
                            if (checked) {
                                setting.lightcolor = "#EFEFD3"
                                setting.darkcolor = "#779755"
                                console.log("Button clicked!")
                            }
                        }
                    }
                }

                Column{
                    Image{
                        source: "qrc:/img/brown.png"
                        width: app.width/3
                        height: app.width/3
                    }
                    RadioButton {
                        text: "褐古智韵"
                        ButtonGroup.group: colorGroup
                        onCheckedChanged: {
                            if (checked) {
                                setting.lightcolor = "#F0DAB5"
                                setting.darkcolor = "#B58765"
                                console.log("Button clicked!")
                            }
                        }
                    }
                }
            }
        }
    }
}
