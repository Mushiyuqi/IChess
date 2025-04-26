import QtQuick
import QtQuick.Controls

//加载，启动动画
ApplicationWindow {
    property alias app: application

    id: application//2
    title: qsTr('Chess')

    visible: false

    width: 450
    height: 800

    color: "black"
    Loader {
        id: launcher
        visible: false
        anchors { fill: parent }
        sourceComponent: manageComponent
        focus: true
    }

    Component {
        id: manageComponent
        Manage {
            anchors { fill: parent }
        }
    }

    Column {
        id: back
        anchors.centerIn: parent
        spacing: 40
        opacity: 0.99
        // logo显示
        Image {
            id: logo
            anchors.horizontalCenter: parent.horizontalCenter
            source: "qrc:/img/icon.png"
            fillMode: Image.PreserveAspectFit
            sourceSize: Qt.size(250, 150)
            opacity: 0
            Behavior on opacity {
                NumberAnimation {
                    duration: 1500
                }
            }
        }

        Text {
            id: text
            text: "广告位招租"
            font.pixelSize: 20
            color: "white"
            anchors.horizontalCenter: parent.horizontalCenter
            opacity: 0
            Behavior on opacity {
                NumberAnimation {
                    duration: 1500
                }
            }
        }
    }
    Timer {
        id: launcherTimer
        running: false
        interval: 2000
        repeat: true
        onTriggered: {
            if (launcher.status === Loader.Ready) {
                launcher.visible = true
                back.opacity = 0
                running = false
            }
        }
    }
    //1
    Timer {
        id: startTimer
        interval: 2000
        onTriggered: {
            console.log("start!")
            application.visible = true//2
            back.opacity = 1
            logo.opacity = 1 // logo 显示
            text.opacity = 1 // text 显示
        }
    }
    Timer {
        id: blackGrainTimer
        running: back.opacity === 1
        interval: 3500
        onTriggered: {
            logo.opacity = 0
            text.opacity = 0
            launcherTimer.start()
        }
    }

    Component.onCompleted: {
        startTimer.start()//1
    }
}
