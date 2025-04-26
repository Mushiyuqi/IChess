#include "LogicSystem.h"

#include "ChessBoard.h"
#include "ChessManager.h"

LogicSystem::LogicSystem(): m_is_stop(false) {
    // 注册回调函数
    RegisterCallBacks();
    // 启动工作线程
    m_worker_thread = std::thread(&LogicSystem::DealMsg, this);
}

LogicSystem::~LogicSystem() {
    m_is_stop = true;
    m_cond.notify_one();
    m_worker_thread.join();
    std::cerr << "LogicSystem::~LogicSystem()" << std::endl;
}

void LogicSystem::PostMsgToQue(std::shared_ptr<LogicNode> msg) {
    std::unique_lock<std::mutex> lock(m_mutex);
    m_msg_que.push(std::move(msg));
    if (m_msg_que.size() == 1) {
        m_cond.notify_one();
    }
}

LogicSystem& LogicSystem::GetInstance() {
    static LogicSystem instance;
    return instance;
}

void LogicSystem::DealMsg() {
    while (!m_is_stop) {
        std::unique_lock<std::mutex> lock(m_mutex);
        // ReSharper disable once CppDFAConstantConditions
        while (m_msg_que.empty() && !m_is_stop) {
            m_cond.wait(lock);
        }

        // 1.队列为空 线程停止
        // 2.队列非空 线程停止
        // ReSharper disable once CppDFAConstantConditions
        if (m_is_stop) {
            // 线程停止时，需要清空队列
            // ReSharper disable once CppDFAUnreachableCode
            while (!m_msg_que.empty()) {
                // 获取消息
                auto msg_node = m_msg_que.front();
                std::cout << "LogicSystem::DealMsg recv msg id is : " << msg_node->_recv_node->m_msg_id << std::endl;
                // 处理消息
                auto call_back_iter = m_fun_callbacks.find(msg_node->_recv_node->m_msg_id);
                if (call_back_iter == m_fun_callbacks.end()) {
                    m_msg_que.pop();
                    continue;
                }

                call_back_iter->second(msg_node->_session, msg_node->_recv_node->m_msg_id,
                                       std::string(msg_node->_recv_node->m_data, msg_node->_recv_node->m_total_len));

                m_msg_que.pop();
            }
            // 退出DealMsg()
            break;
        }

        // 3.队列非空 线程继续
        // 获取消息
        auto msg_node = m_msg_que.front();
        std::cout << "LogicSystem::DealMsg recv msg id is : " << msg_node->_recv_node->m_msg_id << std::endl;
        // 处理消息
        // 获取回调函数
        auto call_back_iter = m_fun_callbacks.find(msg_node->_recv_node->m_msg_id);
        if (call_back_iter == m_fun_callbacks.end()) {
            m_msg_que.pop();
            continue;
        }
        // 执行回调函数
        call_back_iter->second(msg_node->_session, msg_node->_recv_node->m_msg_id,
                               std::string(msg_node->_recv_node->m_data, msg_node->_recv_node->m_total_len));

        m_msg_que.pop();
    }
}

void LogicSystem::RegisterCallBacks() {
    // 注册回调函数
    m_fun_callbacks[MSG_IDS::MSG_HELLO_WORLD] =
        [this](std::shared_ptr<CSession> conn, const short& msg_id, const std::string& msg_data) {
            // 处理Json数据
            Json::Reader reader;
            Json::Value value;
            reader.parse(msg_data, value);
            std::cout << "LogicSystem::RegisterCallBacks recv msg id is : " << value["id"].asInt() << std::endl;
            std::cout << "LogicSystem::RegisterCallBacks recv msg is    : " << value["data"].asString() << std::endl;

            // 发回消息
            value["data"] = "msg has been dealed ( " + value["data"].asString() + " )";
            std::string json_str = value.toStyledString();
            conn->Send(json_str, static_cast<short>(value["id"].asInt()));
        };
    // 处理棋子移动消息
    m_fun_callbacks[MSG_IDS::MSG_CHEQUER_MOVE] =
        [this](std::shared_ptr<CSession> conn, const short& msg_id, const std::string& msg_data) {
            // 处理Json数据
            Json::Reader reader;
            Json::Value value;
            reader.parse(msg_data, value);
            std::cout << "LS::RCB MSG_CHEQUER_MOVE recv msg id is : " << value["id"].asInt() << std::endl;

            const int roomID = value["roomID"].asInt();
            const int xFrom = value["xFrom"].asInt();
            const int yFrom = value["yFrom"].asInt();
            const int xTo = value["xTo"].asInt();
            const int yTo = value["yTo"].asInt();
            const int color = value["color"].asInt();
            // 获取房间
            const auto room = ChessManager::GetInstance().m_rooms[roomID];
            // 记录操作
            room->MoveChequers(xFrom, yFrom, xTo, yTo);
            // 将Json数据转换为字符串
            const std::string json_str = value.toStyledString();
            // 向对方发送消息
            if (color == CHESS_COLOR::CHESS_COLOR_BLACK)
                room->_player_white->Send(json_str, static_cast<short>(value["id"].asInt()));
            if (color == CHESS_COLOR::CHESS_COLOR_WHITE)
                room->_player_black->Send(json_str, static_cast<short>(value["id"].asInt()));
        };
    // 处理玩家匹配
    m_fun_callbacks[MSG_IDS::MSG_PLAYER_MATCH] =
        [this](std::shared_ptr<CSession> conn, const short& msg_id, const std::string& msg_data) {
            // 处理Json数据
            Json::Reader reader;
            Json::Value value;
            reader.parse(msg_data, value);
            std::cout << "LS::RCB MSG_PLAYER_MATCH recv msg id is : " << value["id"].asInt() << std::endl;

            const int color = value["color"].asInt();
            // 获取现成房间号
            int roomID = ChessManager::GetInstance().GetRoom(color);
            if (roomID != ROOM_ID::NONE) {
                // 加入房间
                ChessManager::GetInstance().JoinRoom(roomID, conn, color);
                // 将Json数据转换为字符串
                value["roomID"] = roomID;
                const std::string json_str = value.toStyledString();
                // 给双方发送房间号
                ChessManager::GetInstance().m_rooms[roomID]->_player_white->Send(json_str, static_cast<short>(value["id"].asInt()));
                ChessManager::GetInstance().m_rooms[roomID]->_player_black->Send(json_str, static_cast<short>(value["id"].asInt()));
                return;
            }
            // 创建房间
            ChessManager::GetInstance().CreateRoom(conn, color);
        };
}


