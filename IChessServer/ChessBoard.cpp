#include "ChessBoard.h"

#include <iostream>

Chequer::Chequer(const int type, const int color, const int y, const int x)
    : m_type(type), m_chess_color(color), m_x(x), m_y(y) {
}

ChessBoard::ChessBoard(const int id): m_id(id) {
    // 初始化玩家
    _player_white = nullptr;
    _player_black = nullptr;
    // 初始化棋子
    InitChequer();
    std::cout << "ChessBoard::ChessBoard constructed id is " << m_id << std::endl;
}

ChessBoard::~ChessBoard() {
    std::cerr << "ChessBoard::~ChessBoard destructed id is " << m_id << std::endl;
}

int ChessBoard::GetID() {
    return m_id;
}

bool ChessBoard::MoveChequers(const int x_from, const int y_from, const int x_to, const int y_to) {
    std::lock_guard<std::mutex> lock(m_mutex);
    bool flag_from = false;
    bool flag_to = false;
    for (auto& chequer : m_chequers) {
        // 移动棋子
        if (chequer.m_x == x_from && chequer.m_y == y_from) {
            chequer.m_x = x_to;
            chequer.m_y = y_to;
            flag_from = true;
        }
        // 吃掉棋子
        if (chequer.m_x == x_to && chequer.m_y == y_to) {
            chequer.m_state = CHEQUER_STATE::Dead;
            flag_to = true;
        }
    }
    // 移动或吃掉棋子失败
    if (!flag_from || !flag_to) return false;
    return true;
}

void ChessBoard::ResetChessBoard() {
    std::lock_guard<std::mutex> lock(m_mutex);
    // 清空棋子
    m_chequers.clear();
    // 重新初始化棋子
    InitChequer();
}

void ChessBoard::InitChequer() {
    // 创建白棋
    m_chequers.emplace_back(CHEQUERS::Rook, CHESS_COLOR::CHESS_COLOR_WHITE, 0, 0);
    m_chequers.emplace_back(CHEQUERS::Knight, CHESS_COLOR::CHESS_COLOR_WHITE, 1, 0);
    m_chequers.emplace_back(CHEQUERS::Bishop, CHESS_COLOR::CHESS_COLOR_WHITE, 2, 0);
    m_chequers.emplace_back(CHEQUERS::Queen, CHESS_COLOR::CHESS_COLOR_WHITE, 3, 0);
    m_chequers.emplace_back(CHEQUERS::King, CHESS_COLOR::CHESS_COLOR_WHITE, 4, 0);
    m_chequers.emplace_back(CHEQUERS::Bishop, CHESS_COLOR::CHESS_COLOR_WHITE, 5, 0);
    m_chequers.emplace_back(CHEQUERS::Knight, CHESS_COLOR::CHESS_COLOR_WHITE, 6, 0);
    m_chequers.emplace_back(CHEQUERS::Rook, CHESS_COLOR::CHESS_COLOR_WHITE, 7, 0);
    m_chequers.emplace_back(CHEQUERS::Pawn, CHESS_COLOR::CHESS_COLOR_WHITE, 0, 0);
    m_chequers.emplace_back(CHEQUERS::Pawn, CHESS_COLOR::CHESS_COLOR_WHITE, 1, 0);
    m_chequers.emplace_back(CHEQUERS::Pawn, CHESS_COLOR::CHESS_COLOR_WHITE, 2, 0);
    m_chequers.emplace_back(CHEQUERS::Pawn, CHESS_COLOR::CHESS_COLOR_WHITE, 3, 0);
    m_chequers.emplace_back(CHEQUERS::Pawn, CHESS_COLOR::CHESS_COLOR_WHITE, 4, 0);
    m_chequers.emplace_back(CHEQUERS::Pawn, CHESS_COLOR::CHESS_COLOR_WHITE, 5, 0);
    m_chequers.emplace_back(CHEQUERS::Pawn, CHESS_COLOR::CHESS_COLOR_WHITE, 6, 0);
    m_chequers.emplace_back(CHEQUERS::Pawn, CHESS_COLOR::CHESS_COLOR_WHITE, 7, 0);
    // 创建黑棋
    m_chequers.emplace_back(CHEQUERS::Pawn, CHESS_COLOR::CHESS_COLOR_BLACK, 0, 6);
    m_chequers.emplace_back(CHEQUERS::Pawn, CHESS_COLOR::CHESS_COLOR_BLACK, 1, 6);
    m_chequers.emplace_back(CHEQUERS::Pawn, CHESS_COLOR::CHESS_COLOR_BLACK, 2, 6);
    m_chequers.emplace_back(CHEQUERS::Pawn, CHESS_COLOR::CHESS_COLOR_BLACK, 3, 6);
    m_chequers.emplace_back(CHEQUERS::Pawn, CHESS_COLOR::CHESS_COLOR_BLACK, 4, 6);
    m_chequers.emplace_back(CHEQUERS::Pawn, CHESS_COLOR::CHESS_COLOR_BLACK, 5, 6);
    m_chequers.emplace_back(CHEQUERS::Pawn, CHESS_COLOR::CHESS_COLOR_BLACK, 6, 6);
    m_chequers.emplace_back(CHEQUERS::Pawn, CHESS_COLOR::CHESS_COLOR_BLACK, 7, 6);
    m_chequers.emplace_back(CHEQUERS::Rook, CHESS_COLOR::CHESS_COLOR_BLACK, 0, 7);
    m_chequers.emplace_back(CHEQUERS::Knight, CHESS_COLOR::CHESS_COLOR_BLACK, 1, 7);
    m_chequers.emplace_back(CHEQUERS::Bishop, CHESS_COLOR::CHESS_COLOR_BLACK, 2, 7);
    m_chequers.emplace_back(CHEQUERS::Queen, CHESS_COLOR::CHESS_COLOR_BLACK, 3, 7);
    m_chequers.emplace_back(CHEQUERS::King, CHESS_COLOR::CHESS_COLOR_BLACK, 4, 7);
    m_chequers.emplace_back(CHEQUERS::Bishop, CHESS_COLOR::CHESS_COLOR_BLACK, 5, 7);
    m_chequers.emplace_back(CHEQUERS::Knight, CHESS_COLOR::CHESS_COLOR_BLACK, 6, 7);
    m_chequers.emplace_back(CHEQUERS::Rook, CHESS_COLOR::CHESS_COLOR_BLACK, 7, 7);
}
