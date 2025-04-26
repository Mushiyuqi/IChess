#pragma once
#include "const.h"

class Chequer {
public:
    Chequer(int type, int color, int y, int x);
    ~Chequer() = default;

    int m_type = -1;
    int m_chess_color = -1;
    int m_state = CHEQUER_STATE::Life;
    int m_x = -1;
    int m_y = -1;
};

class CSession;
class ChessBoard {
public:
    explicit ChessBoard(int id);
    int GetID();
    bool MoveChequers(int x_from, int y_from, int x_to, int y_to);

    // 玩家
    std::shared_ptr<CSession> _player_white;
    std::shared_ptr<CSession> _player_black;
private:
    void InitChequer();

    // 棋盘
    int m_id = 0;
    std::vector<Chequer> m_chequers;
    std::mutex m_mutex;
};

