#pragma once
#include "const.h"

class ChessBoard;
class LogicSystem;
class CSession;
class ChessManager {
public:
    ~ChessManager();
    ChessManager(const ChessManager&) = delete;
    ChessManager& operator=(const ChessManager&) = delete;
    static ChessManager& GetInstance();

    // 查询
    std::shared_ptr<ChessBoard> operator[](int roomID);
    // 修改
    int GetRoom(int color);
    void RemoveRoom(int roomID);
    void CreateRoom(std::shared_ptr<CSession> session, int color);
    void JoinRoom(int roomID, std::shared_ptr<CSession> session, int color);
private:
    ChessManager();
    int GenerateNumericId();

    std::queue<int> m_need_black_id_que;
    std::queue<int> m_need_white_id_que;
    std::unordered_map<int, std::shared_ptr<ChessBoard>> m_rooms;
    std::mutex m_mutex;
};

