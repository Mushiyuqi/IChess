//开发者页面
import QtQuick
import QtQuick.Controls

Item {
    id: developer

    Page {
        visible: true
        width: app.width
        height: app.height
        background: Image {
            source: "qrc:/img/start.png"
            fillMode: Image.Stretch
            anchors.fill: parent
            opacity: 0.5
            onStatusChanged: {
                if (status === Image.Error) {
                    console.log("Image load error:", source)
                }
            }
        }
        Button {
            id: back
            text: "Back"
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.topMargin: 10
            anchors.leftMargin: 10
            onClicked: manage.goBack() // 返回上一页
        }
        Rectangle {
            width: parent.width/2
            height: textContent.height + 20
            border.color: "black"
            border.width: 1
            color: "transparent"
            anchors.centerIn: parent
            Text {
                id: textContent
                color: "white"
                text: qsTr("制作人员：
重庆师范大学 - 付强
重庆师范大学 - 唐婷婷
重庆师范大学 - 陈熙蕊

指导老师：
龚伟老师

项目名称：国际象棋
版本号：1.0.0
发布日期：2024-07-09

鸣谢：
感谢所有贡献者和支持者。

祝屏幕前的您，游玩愉快。")
                anchors.centerIn: parent
                width: parent.width - 20
                wrapMode: Text.Wrap
                horizontalAlignment: Text.AlignHCenter
            }
        }
    }
}
