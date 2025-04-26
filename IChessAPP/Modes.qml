//用于管理和维护多个Mode实例
import QtQuick

Item {
    id: modes

    property Mode mode: Mode { name: 'none' }
    readonly property Mode noMode: Mode { name: 'none' }

    //定义缓存对象
    QtObject {
        id: manager
        property var key: 'name'//指定缓存键值
        property var m: ({})//存储缓存对象

        //添加一个mode到缓存中
        function add(mode) {
            console.log('Adding',mode.name)
            var t = m
            t[mode[key]] = mode
            m = t
        }

        //从缓存中读取一个mode
        function get(mode) {

            return m[mode]
        }

        //清除缓存
        function clear() {
            m = {}
        }
    }

    Component.onCompleted: {
        reload()
        mode.enter(noMode)
    }


    function set(mode) {
        mode = manager.get(mode)

        if(modes.mode)
            modes.mode.leave()

        if(mode) {
            mode.enter(modes.mode)
            modes.mode = mode
        } else {
            console.log('Modes','set mode',mode,'not found')
        }
    }

    function reload() {
        manager.clear()

        var first = true

        for(var m in modes.data) {
            var child = modes.data[m]
            if(child && ('name' in child)) {
                manager.add(child)

                if(first) {
                    modes.mode = child
                    first = false
                }
            }
        }
    }
}
