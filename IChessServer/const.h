#pragma once
#include <vector>
#include <unordered_map>
#include <mutex>
#include <memory>
#include <map>
#include <queue>

#define MAX_MSG_LENGTH (1024*2)
#define HEAD_TOTAL_LEN 4
#define HEAD_ID_LEN 2
#define HEAD_DATA_LEN 2
#define MAX_RECVQUE 10000
#define MAX_SENDQUE 1000

enum CHEQUER_STATE {
    Life = 0,
    Dead = 1,
};

enum CHEQUERS {
    Rook = 1,
    Knight = 2,
    Bishop = 3,
    Queen = 4,
    King = 5,
    Pawn = 6,
};

enum CHESS_COLOR {
    CHESS_COLOR_WHITE = 0,
    CHESS_COLOR_BLACK = 1,
};

enum ROOM_ID {
    NONE = -1,  // 无房间标识(无效ID)
};

enum MSG_IDS {
    MSG_HELLO_WORLD = 1001,     // 测试用例
    MSG_CHEQUER_MOVE = 1002,    // 棋子移动
    MSG_PLAYER_MATCH = 1003,    // 玩家匹配
    MSG_REAGAIN = 1004,         // 悔棋
    MSG_RESTART = 1005,         // 重开
    MSG_QUIT = 1006,            // 退出
    MSG_PAWN2QUEEN = 1007,      // 兵变成皇后
    MSG_PAWN2ROOK = 1008,       // 兵变成车
    MSG_PAWN2KNIGHT = 1009,     // 兵变成马
    MSG_PAWN2BISHOP = 1010,     // 兵变成象
};
