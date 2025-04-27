#include "ChessManager.h"
#include <iostream>
#include "ChessBoard.h"
#include <random>

ChessManager::~ChessManager() {
    std::cerr << "ChessManager::~ChessManager destructed" << std::endl;
}

ChessManager::ChessManager() {
    std::cout << "ChessManager::ChessManager constructed" << std::endl;
}

int ChessManager::GenerateNumericId() {
    // 随机生成房间号
    static std::random_device rd;  // 真随机数设备
    static std::mt19937 gen(rd()); // Mersenne Twister引擎
    static std::uniform_int_distribution<> dist(100000, 999999); // 6位数字

    // 判断房间号是否重复
    int roomID = dist(gen);
    while (m_rooms.contains(roomID)) {
        roomID = dist(gen);
    }

    return roomID;
}

ChessManager& ChessManager::GetInstance() {
    static ChessManager instance;
    return instance;
}

std::shared_ptr<ChessBoard> ChessManager::operator[](const int roomID) {
    // 获取房间
    if (!m_rooms.contains(roomID)) return nullptr;
    return m_rooms[roomID];
}

int ChessManager::GetRoom(const int color) {
    std::lock_guard<std::mutex> lock(m_mutex);
    if (color == CHESS_COLOR_BLACK) {
        // 没有房间
        if (m_need_black_id_que.empty()) return ROOM_ID::NONE;
        // 有房间
        const int roomID = m_need_black_id_que.front();
        // 清空房间号
        m_need_black_id_que.pop();
        // 返回房间号
        return roomID;
    }
    if (color == CHESS_COLOR_WHITE) {
        // 没有房间
        if (m_need_white_id_que.empty()) return ROOM_ID::NONE;
        // 有房间
        const int roomID = m_need_white_id_que.front();
        // 清空房间号
        m_need_white_id_que.pop();
        // 返回房间号
        return roomID;
    }
    return ROOM_ID::NONE;
}

void ChessManager::RemoveRoom(const int roomID) {
    std::lock_guard<std::mutex> lock(m_mutex);
    if (m_rooms.contains(roomID)) {
        // 删除房间
        m_rooms.erase(roomID);
    }
}

void ChessManager::CreateRoom(std::shared_ptr<CSession> session, const int color) {
    std::lock_guard<std::mutex> lock(m_mutex);
    // 获取房间号
    int roomID = GenerateNumericId();
    // 创建棋盘
    auto chessboard = std::make_shared<ChessBoard>(roomID);
    if (color == CHESS_COLOR_BLACK) chessboard->_player_black = session;
    if (color == CHESS_COLOR_WHITE) chessboard->_player_white = session;
    // 添加房间
    m_rooms.emplace(roomID, chessboard);
    // 将房间号添加到队列中
    if (color == CHESS_COLOR_BLACK) m_need_white_id_que.push(roomID);
    if (color == CHESS_COLOR_WHITE) m_need_black_id_que.push(roomID);
}

void ChessManager::JoinRoom(const int roomID, std::shared_ptr<CSession> session, const int color) {
    std::lock_guard<std::mutex> lock(m_mutex);
    // 添加黑色玩家
    if (color == CHESS_COLOR_BLACK && m_rooms[roomID]->_player_black == nullptr)
        m_rooms[roomID]->_player_black = session;
    // 添加白色玩家
    if (color == CHESS_COLOR_WHITE && m_rooms[roomID]->_player_white == nullptr)
        m_rooms[roomID]->_player_white = session;
}


