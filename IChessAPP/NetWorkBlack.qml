import QtQuick
import QtQuick.Controls
import QtQuick.Dialogs
import QtQuick.Layouts
import MyNetWork 1.0

Item {

    id:board
    property color lightcolor: manage.lightcolor
    property color darkcolor: manage.darkcolor


    Page {
        id:page
        width: app.width
        height: app.height
        visible: true

        property int fromX: -1
        property int fromY: -1
        property int toX: -1
        property int toY: -1
        property int oppositeColor: 0

        Ipv4{
            id:ip
            send: _inToSend.text
            onReceiveChanged: {
                page.splitAndConvert(ip.receive)
                console.log("ip4收到了  "+ip.receive)
                if(_inToReceive.num6!==page.oppositeColor)//第一次接收,相同棋子，拒绝连接
                    { manage.goBack();netChessBoard.reset()}
                else{
                    waitLink.visible=false
                    if(_inToReceive.num5===1004)//悔棋
                        { netChessBoard.regretChess();netChessBoard.regretChess()}
                    else if(_inToReceive.num5===1005)//重开
                        {netChessBoard.reset()}
                    else if(_inToReceive.num5===1006)//退出
                        { manage.goBack();netChessBoard.reset()}
                    else{//移动
                    netChessBoard.setWhitePlayer()
                    netChessBoard.move(_inToReceive.num1,_inToReceive.num2,_inToReceive.num3,_inToReceive.num4)
                        promote.close()
                        promoteMask.visible = false
                        netChessBoard.setBlackPlayer()//正常情况移动到这里完成，下面是升变的情况

                        if(_inToReceive.num5 === 1007 || _inToReceive.num5 === 1008 || _inToReceive.num5 === 1009 || _inToReceive.num5 === 1010)//小兵晋升
                        {
                            netChessBoard.setWhitePlayer()
                            switch(_inToReceive.num5)
                            {
                            case 1007:
                                netChessBoard.setPromotion("queen")
                                 break;
                            case 1008:
                               netChessBoard.setPromotion("rook")
                                 break;
                            case 1009:
                                netChessBoard.setPromotion("knight")
                                 break;
                            case 1010:
                                netChessBoard.setPromotion("bishop")
                                 break;
                            }
                            netChessBoard.changeType(_inToReceive.num3,_inToReceive.num4)
                            promote.close();
                            promoteMask.visible = false
                            netChessBoard.setBlackPlayer()
                        }

                         turnText.text = qsTr(netChessBoard.getTurn() + " turn")
                    }
                }
            }
        }
        //等待ip连接
        Dialog{
            id:waitLink

            visible:false
            width: parent.width
            height: parent.height
            anchors.centerIn: parent
            Image {
                id: waitpic
                source: "qrc:/img/wait.png"
                anchors.fill: parent
            }
            modal: true
            Text {
                anchors.centerIn: parent
                text: qsTr("等待白方连接中...")
            }
            Button {
                id: cancelButton2
                text: "cancel"
                anchors.top:parent.top
                anchors.left:parent.left
                onClicked: {
                    manage.goBack()
                }
            }
        }
        //输入对方ip
        Dialog{
            id: importIp
            width: parent.width
            height: parent.height
            visible: true
            Image {
                id: textpoc
                source: "qrc:/img/link.webp"
                anchors.fill:parent
            }
            TextField {
                    id: _textField
                    width: 220
                    height: 50
                    z:2
                    placeholderText: "请输入对方的ipv4地址..."
                    anchors.centerIn: parent
                    Component.onCompleted: _textField.forceActiveFocus()
                    // 添加一个按钮来触发获取文本的操作
                    Button {
                        id: okButton
                        text: "OK"
                        anchors.top: _textField.bottom
                        anchors.right: _textField.right
                        onClicked: {
                            ip.myip4=_textField.text
                            console.log(ip.myip4)
                            _inToSend.num5=1003
                            ip.sendMessage()
                            netChessBoard.setWaitPlayer()
                            importIp.visible=false
                            waitLink.open()
                            if(_inToReceive.num6===page.oppositeColor)
                            waitLink.close()
                            boardchess.visible=true
                            grid.visible=true
                            netChessBoard.reset()
                            netChessBoard.setWaitPlayer()
                            turnText.text = qsTr(netChessBoard.getTurn() + " turn")
                        }
                    }
                    Button {
                        id: cancelButton
                        text: "cancel"
                        anchors.top: _textField.bottom
                        anchors.left: _textField.left
                        onClicked: {
                            console.log(ip.send+"   "+ip.receive)
                            manage.goBack()
                        }
                    }
                }

        }
        //记录发送数据
        Text{
            id:_inToSend
            visible: false
            property int num1: -1
            property int num2: -1
            property int num3: -1
            property int num4: -1
            property int num5: 1003//id
            property int num6: 1//color
            property int num7: _inToReceive.num7
            text:num1+" "+num2+" "+num3+" "+num4+" "+num5+" "+num6+" "+num7
        }
        //记录处理后的接收数据
        Text {
            id: _inToReceive
            visible: false
            property int num1: -1
            property int num2: -1
            property int num3: -1
            property int num4: -1
            property int num5: 0
            property int num6: 1
            property int num7: 1
        }
        // 棋盘
        Rectangle {
            id: boardchess
            width: parent.width
            height: parent.width
            anchors.centerIn: parent
            visible: false
            z: -1

            Grid {
                rows: 8
                columns: 8
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter

                Repeater {
                    model: 8 * 8

                    Rectangle {
                        width: boardchess.width / 8
                        height: boardchess.height / 8
                        color: {
                            var cols = index % 8 //列
                            var rows = (index - cols) / 8 //行 (减去cols再除，得到整数)
                            return ((rows + cols) % 2 === 0) ? lightcolor : darkcolor
                        }
                    }
                }
            }
        }

        // 显示可以走的位置
        function getMoves(x, y) {
            var movelist = netChessBoard.possibleMoves(x, y);

            for(var i = 0; i < movelist.length; i++) {
                console.log("可走位置：" + movelist[i]);
                if(gridRep.itemAt(movelist[i]).children.length > 0) {
                    gridRep.itemAt(movelist[i]).children[1].visible = true
                    gridRep.itemAt(movelist[i]).children[1].z = 1
                }
            }
        }
        // 清除可以走的位置
        function clearColor(x, y) {
            var movelist = netChessBoard.possibleMoves(x, y);

            for(var i = 0; i < movelist.length; i++) {
                console.log("清除color：" + movelist[i]);
                if(gridRep.itemAt(movelist[i]).children.length > 0) {
                    gridRep.itemAt(movelist[i]).children[1].visible = false
                    gridRep.itemAt(movelist[i]).children[1].z = -1
                }
            }
        }
        // 将字符串分割成单个字符的数组
        function splitAndConvert(inputString) {
            var numbers = inputString.split(" ")
            _inToReceive.num1=numbers[0];
            _inToReceive.num2=numbers[1];
            _inToReceive.num3=numbers[2];
            _inToReceive.num4=numbers[3];
            _inToReceive.num5=numbers[4];
            _inToReceive.num6=numbers[5];
            _inToReceive.num7=numbers[6];
        }

        //显示轮次
        Rectangle {
            width: app.width/3
            height: 50
            anchors.horizontalCenter: parent.horizontalCenter
            border.color: darkcolor
            border.width: 3
            radius: 25
            Text {
                id: turnText
                color: darkcolor
                anchors.centerIn: parent
                text: qsTr(chessBoard.getTurn() + " turn")
            }
        }
        // 模态遮罩层(游戏结束)
        Rectangle {
            id: gameEndMask
            anchors.fill: parent
            visible: false
            z: -2
            color: "transparent"

            TapHandler {
                onTapped: {
                    gameEnd.visible = true
                    // 跳转回主界面...
                    manage.goBack(); // 返回上一页
                    netChessBoard.reset();
                    gameEnd.visible = false
                }
            }

            // 游戏结束弹窗
            MessageDialog {
                id: gameEnd
                title: "游戏结束"
                text: ""
                onAccepted: {
                    console.log("end弹窗被接受");
                    // 跳转回主界面...
                    manage.goBack(); // 返回上一页
                    netChessBoard.reset();
                }
            }
        }
        // 模态遮罩层(兵升变提示)
        Rectangle {
            id: promoteMask
            anchors.fill: parent
            visible: false
            z: -2
            color: "transparent"

            TapHandler{
                onTapped: {
                    promote.visible = true
                }
            }

            // 晋升弹窗
            Dialog {
                id: promote
                title: "兵升变"
                width: 250
                height: 350
                modal: true
                anchors.centerIn: parent

                Text {
                    anchors.horizontalCenter: parent.horizontalCenter
                    text: qsTr("必须晋升（强制)")
                    color: "red"
                }

                spacing: 5

                GridLayout {
                    columns: 2
                    rows: 2
                    anchors.centerIn: parent
                    columnSpacing: 5
                    rowSpacing: 5

                    Button {
                        id: queen
                        text: qsTr("晋升成后")
                        onClicked: {
                            // console.log("promote queen");
                            netChessBoard.setPromotion("queen")
                            netChessBoard.changeType(page.toX, page.toY)
                            _inToSend.num5=1007
                            ip.sendMessage()
                            promote.close();
                            promoteMask.visible = false

                        }
                    }
                    Button {
                        id: rook
                        text: qsTr("晋升成车")
                        onClicked: {
                            // console.log("promote rook");
                            netChessBoard.setPromotion("rook")
                            netChessBoard.changeType(page.toX, page.toY)
                            _inToSend.num5=1008
                            ip.sendMessage()
                            promote.close();
                            promoteMask.visible = false
                        }
                    }
                    Button {
                        id: knight
                        text: qsTr("晋升成马")
                        onClicked: {
                            // console.log("promote knight");
                            netChessBoard.setPromotion("knight")
                            netChessBoard.changeType(page.toX, page.toY)
                            _inToSend.num5=1009
                            ip.sendMessage()
                            promote.close();
                            promoteMask.visible = false
                        }
                    }
                    Button {
                        id: bishop
                        text: qsTr("晋升成象")
                        onClicked: {
                            // console.log("promote bishop");
                            netChessBoard.setPromotion("bishop")
                            netChessBoard.changeType(page.toX, page.toY)
                            _inToSend.num5=1010
                            ip.sendMessage()
                            promote.close();
                            promoteMask.visible = false
                        }
                    }
                }
            }
        }

        Connections {
            target: netChessBoard
            function onWhiteWin() {
                console.log("Received signal in QML, White Win");
                gameEndMask.visible = true
                gameEndMask.z = 1
                gameEnd.text = "White Win!"
                gameEnd.visible = true
            }
            function onBlackWin() {
                console.log("Received signal in QML, Black Win");
                gameEndMask.visible = true
                gameEndMask.z = 1
                gameEnd.text = "Black Win!"
                gameEnd.visible = true
            }
            function onPromote() {
                console.log("晋升弹窗提示")
                promoteMask.visible = true
                promoteMask.z = 1
                promote.visible = true
            }
        }

        // 棋子
        Grid {
            id: grid
            rows: 8
            columns: 8
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
            visible: false
            Repeater {
                id: gridRep
                model: netChessBoard

                Image {
                    id: girdImg
                    width: boardchess.width / 8
                    height: boardchess.height / 8
                    fillMode: Image.PreserveAspectFit
                    source: model.pieceImg !== undefined ? model.pieceImg : ""

                    Text {
                        visible: false
                        z: 1
                        text: index
                    }

                    Rectangle {
                        id: rec
                        anchors.fill: parent
                        color: "lightgreen"
                        opacity: 0.8
                        visible: false
                        z: -1

                        TapHandler {
                            // target: rec
                            onTapped: {
                                page.clearColor(page.fromX, page.fromY)
                                page.toX = index % 8
                                page.toY = (index - page.toX) / 8
                                _inToSend.num3=page.toX
                                _inToSend.num4=page.toY
                                console.log("fromX:" + page.fromX + " fromY:" + page.fromY+" toX:"+page.toX+" toY:"+page.toY)
                                netChessBoard.move(page.fromX, page.fromY, page.toX, page.toY)
                                _inToSend.num5=1002
                                ip.sendMessage()
                                console.log("发送："+ip.send)
                                netChessBoard.setWaitPlayer()
                                turnText.text = qsTr(netChessBoard.getTurn() + " turn")
                                page.fromX = -1
                                page.fromY = -1
                            }
                        }
                    }

                    TapHandler {
                        // target: girdImg
                        onTapped: {
                            page.clearColor(page.fromX, page.fromY)
                            page.fromX = index % 8
                            page.fromY = (index - page.fromX) / 8
                            console.log("x:" + page.fromX + " y:" + page.fromY);
                            if(model.pieceImg !== undefined) {
                                _inToSend.num1=page.fromX
                                _inToSend.num2=page.fromY
                                page.getMoves(page.fromX, page.fromY);
                            }
                        }
                    }
                }
            }
        }
        footer:
            ToolBar {
                height: 55
                background:
                    Rectangle {
                        color: darkcolor
                    }
                    Row {
                        anchors.centerIn: parent
                        spacing: 55

                        ToolButton {
                            id:back
                            text: qsTr("退出")
                            onClicked: {
                                _inToSend.num5=1006
                                ip.sendMessage()
                                manage.goBack()
                                //netChessBoard.reset()
                            }
                        }

                        ToolButton {
                            text: qsTr("重开")
                            onClicked: {
                                netChessBoard.reset()
                                _inToSend.num5=1005
                                ip.sendMessage()
                            }
                        }

                        ToolButton {
                            id: regret
                            text: qsTr("撤回")
                            //撤回操作
                            onClicked:{
                                netChessBoard.regretChess()
                                netChessBoard.regretChess()
                                _inToSend.num5=1004
                                ip.sendMessage()
                            }
                        }
                    }
            }
    }
}
