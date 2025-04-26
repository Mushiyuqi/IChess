//Mode是一个具体的模式，代表应用中的一个页面。
import QtQuick
import QtQuick.Controls

Item {
    id: mode
    property string name: ''
    property bool when: false//用于控制mode的激活状态

    //用于存储临时数据
    QtObject {
        id: internal
        property Item backWhen//上一个mode
    }

    onWhenChanged: {
        if (when) {
            internal.backWhen = mode.parent.mode
            mode.parent.set(name)
        } else {
            mode.parent.set(internal.backWhen, name)
        }
    }

    signal enter(var previousMode)//激活
    signal leave()//停用

    function onEnterHandler(previousMode) {
        console.log("Entering " + name + " from " + previousMode.name)
    }

    function onLeaveHandler() {
        console.log("Leaving " + name)
    }

    Component.onCompleted: {
        enter.connect(onEnterHandler)
        leave.connect(onLeaveHandler)
    }
}
