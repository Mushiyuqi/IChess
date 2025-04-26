//教程页面，记录了游戏规则相关内容
import QtQuick
import QtQuick.Controls

Item {
    id: help
    Page {
        width: app.width
        height: app.height
        background: Image {
            source: "qrc:/img/start.png"
            fillMode: Image.Stretch
            anchors.fill: parent
            opacity: 0.5
        }
        Column {
            spacing: 40
            Button {
                id: back
                text: "Back"
                onClicked: manage.goBack() // 返回上一页
            }
            Text {
                text: qsTr("国际象棋介绍：")
                font.pixelSize: 20
                anchors.left: parent.left; anchors.leftMargin: 20
            }
            Rectangle {
                id: intro
                width: parent.parent.width * 0.9
                height: parent.parent.height * 0.7
                border.color: "black"
                color: "transparent"
                anchors.left: parent.left; anchors.leftMargin: 20
                anchors.rightMargin: 20
                SwipeView{
                    id:view
                    anchors.fill: parent
                    Rectangle {
                        color: "transparent"
// <<<<<<< HEAD

//                         Text {
//                             text: qsTr("游戏规则

// 棋盘：国际象棋的棋盘是一个8x8的方格棋盘，由64个交替的黑色和白色方格组成。
// 棋子：每方有16枚棋子，包括1个国王、1个皇后、2个车、2个马、2个象和8个兵。

// 棋子的移动规则

// 国王（K）：可以移动到相邻的方格，包括斜向移动。
// 皇后（Q）：可以横向、纵向或斜向移动，没有距离限制。
// 车（R）：可以横向或纵向移动，没有距离限制。
// 马（N）：走“日”字形，即先横向或纵向移动2格，再斜向移动1格。
// 象（B）：走斜线，没有距离限制，但不能越子。
// 兵（P）：初次移动可以向前走1格或2格，之后只能向前走1格。吃子时，兵走斜线。

// 游戏目标

// 将军（Check）：一方的国王被对方威胁，即处于将军状态。
// 将死（Checkmate）：一方的国王被将军，且无法通过任何合法移动来解除将军状态，此时游戏结束，对方获胜。

// 游戏流程

// 开局：双方玩家从标准开局开始。
// 中局：玩家交替移动棋子，尝试控制棋盘、攻击对方国王并保护自己的国王。
// 残局：棋子数量减少，通常进入决定性的阶段。
// 结束：直到出现将死、和棋或双方同意和棋。")
// =======
                        Column {
//>>>>>>> fe452fd81b2a8d03ac89a60688ef5102e8dc9dce
                            anchors.fill: parent
                            spacing: 20
                            anchors.leftMargin: 25
                            Text {
                                id: title1
                                text: qsTr("认识棋子")
                                color: "white"
                                wrapMode: Text.Wrap
                                font.pointSize: 20
                            }
                            Grid {
                                columns: 1
                                spacing: 10
                                anchors.topMargin: 10
                                height: parent.height - title1.height - parent.spacing
                                Repeater {
                                    model: [
                                        { source: "qrc:/img/king-white.svg", text: "王（K） King 头顶十字架的“短腿王子”，全局重点保护对象" },
                                        { source: "qrc:/img/queen-white.svg", text: "后（Q） Queen 头戴皇冠的“最强能力者”，威力最大的棋子" },
                                        { source: "qrc:/img/rook-white.svg", text: "车（R） Rook 城堡观状的棋子，横竖通行不受限" },
                                        { source: "qrc:/img/bishop-white.svg", text: "象（B） Bishop 戴着高帽子，斜线霸主" },
                                        { source: "qrc:/img/knight-white.svg", text: "马（N） Knight 马上的骑士，跳过棋子不受限" },
                                        { source: "qrc:/img/pawn-white.svg", text: "兵（P） Pawn “攻防小能手”，直走斜吃，只进不退" }
                                    ]
                                    Row {
                                        spacing: 10
                                        Image {
                                            source: modelData.source
                                            width: 60
                                            height: (intro.height - 120) / 6
                                        }
                                        Text {
                                            text: modelData.text
                                            width: intro.width - 110
                                            height: (intro.height-120)/6
                                            wrapMode: Text.Wrap
                                            verticalAlignment: Text.AlignVCenter
                                            color: "white"
                                        }
                                    }
                                }
                            }
                        }
                    }
                    Rectangle {
                        color: "transparent"
// <<<<<<< HEAD
//                         Text {
//                             text: qsTr("特殊规则

// 吃过路兵（En passant）：当一方的兵在其初始移动后，横向经过对方的兵旁边时，对方的兵可以立即吃掉它。
// 王车易位（Castling）：在特定条件下，国王和车可以同时移动，进行王车易位。
// 升变（Promotion）：当兵到达对方底线时，可以升变为皇后、车、马或象。

// 策略和技巧

// 国际象棋是一种需要深度思考和策略规划的游戏。玩家需要考虑棋子的位置、可能的威胁、未来的移动和对手的策略。游戏中有许多著名的开局、中局和残局策略，玩家需要不断学习和实践以提高自己的水平。

// 国际象棋组织

// 国际象棋有多个国际和国家级的组织，其中最著名的是国际象棋联合会（FIDE）。FIDE负责组织国际象棋的世界锦标赛和其他重要赛事，并负责制定和更新国际象棋的规则。

// 文化影响

// 国际象棋不仅是一种游戏，也是一种文化现象。它出现在文学、电影、艺术和音乐中，被视为智力训练和策略思维的象征。许多国家和地区都有自己的国际象棋传统和历史。

// 国际象棋是一种深受人们喜爱的游戏，它不仅提供了娱乐，还有助于培养逻辑思维、决策能力和耐心。无论是作为业余爱好还是竞技运动，国际象棋都有着丰富的内涵和无限的魅力。")
// =======
                        Column {
//>>>>>>> fe452fd81b2a8d03ac89a60688ef5102e8dc9dce
                            anchors.fill: parent
                            spacing: 20
                            anchors.leftMargin: 25
                            Text {
                                id: title2
                                text: qsTr("棋子走法")
                                color: "white"
                                wrapMode: Text.Wrap
                                font.pointSize: 20
                            }
                            Grid {
                                columns: 1
                                spacing: 10
                                anchors.topMargin: 10
                                height: parent.height - title2.height - parent.spacing
                                Repeater {
                                    model: [
                                        { source: "qrc:/img/king-white.svg", text: "王一次只能行走一步，但所有方向（横、斜、直）都可以走。王被吃或者被将死意味着输棋" },
                                        { source: "qrc:/img/queen-white.svg", text: "皇后每步不限制格数，也不限制方向" },
                                        { source: "qrc:/img/rook-white.svg", text: "车横、竖直线都可以走，不可以斜线走棋。不限格数走棋，同样不能越子走棋。" },
                                        { source: "qrc:/img/knight-white.svg", text: "骑士可以竖走2格再向左或向右1格，也可以横走2格再向上或向下1格，形成一个字母L的形状，也可以无限制越过任何棋子" },
                                        { source: "qrc:/img/bishop-white.svg", text: "主教（象）只能沿着斜线走棋，不限格数，但不能越子" },
                                        { source: "qrc:/img/pawn-white.svg", text: "兵只能向前、不能后退，每次只能走1格。但兵走棋第一步时可以向前走1格或2格，之后每次只能1格。不能越子走棋" }
                                    ]
                                    Row {
                                        spacing: 10
                                        Image {
                                            source: modelData.source
                                            width: 60
                                            height: (intro.height - 120) / 6
                                        }
                                        Text {
                                            text: modelData.text
                                            width: intro.width - 110
                                            height: (intro.height-120)/6
                                            wrapMode: Text.Wrap
                                            verticalAlignment: Text.AlignVCenter
                                            color: "white"
                                        }
                                    }
                                }
                            }
                        }
                    }
                    Rectangle {
                        color: "transparent"
// <<<<<<< HEAD
//                         Text {
//                             text: qsTr("竞技国际象棋

// 国际象棋是一种竞技运动，拥有自己的等级分系统。顶尖的国际象棋选手会参加各种国际比赛，争夺世界冠军头衔。国际象棋比赛通常采用时间控制，以确保游戏的公平性和效率。

// 联机说明

// 联机需双方手机在同一个局域网下

// 双方需互相输入对方的ip地址后方可进行游戏
//     ")
// =======
                        Column {
//>>>>>>> fe452fd81b2a8d03ac89a60688ef5102e8dc9dce
                            anchors.fill: parent
                            spacing: 20
                            anchors.leftMargin: 25
                            Text {
                                id: title3
                                text: qsTr("特殊规则")
                                color: "white"
                                wrapMode: Text.Wrap
                                font.pointSize: 20
                                anchors.margins: 10 // 设置文字和边框的距离
                            }
                            Grid {
                                columns: 1
                                spacing: 10
                                anchors.topMargin: 10
                                height: parent.height - title3.height - parent.spacing
                                Repeater {
                                    model: [
                                        { text: "1.王车易位\n把王向车的方向横向移动两格，再把车直接移到王的另一侧，放在王的相邻一格。" },
                                        { text: "2.底线升变\n当已方兵到达对方底线的时候，兵需要升变为除了王之外的任何棋子。并且后面以升变后的棋子走棋规则走棋。这里需要注意，兵的升变是必须的，只能升变一次，且不可逆向降回为兵，不能变成王，也不能不变。" },
                                        { text: "3.吃过路兵\n当对方兵第一步走两格，我方兵与之并排时，则可以吃它，并且放置其前一格。" }
                                    ]
                                    Text {
                                        text: modelData.text
                                        width: intro.width - 50
                                        height: (intro.height - 120) / 3
                                        wrapMode: Text.Wrap
                                        verticalAlignment: Text.AlignVCenter
                                        color: "white"
                                    }
                                }
                            }
                        }
                    }
                    Rectangle{
                        color: "transparent"
                        Column {
                            anchors.fill: parent
                            spacing: 20
                            anchors.leftMargin: 25
                            Text {
                                id: title4
                                text: qsTr("联机注意事项")
                                color: "white"
                                wrapMode: Text.Wrap
                                font.pointSize: 20
                                anchors.margins: 10 // 设置文字和边框的距离
                            }
                            Grid {
                                columns: 1
                                spacing: 10
                                anchors.topMargin: 10
                                height: parent.height - title4.height - parent.spacing
                                Repeater {
                                    model: [
                                        { text: "1.确保双方都处于同一个局域网，且输入的ip地址正确。" },
                                        { text: "2.双方需同时点击联机，不可一方已经输入ip点击确定后，另一方还未点击联机界面选择颜色，这样做会使连接失败。" },
                                        { text: "3.双方选择相同颜色棋子会导致直接退出。" },
                                        { text: "4.在小兵升变时，请耐心等待对方选择升变后的形态。" }
                                    ]
                                    Text {
                                        text: modelData.text
                                        width: intro.width - 50
                                        height: (intro.height - 120) / 4
                                        wrapMode: Text.Wrap
                                        verticalAlignment: Text.AlignVCenter
                                        color: "white"
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}
