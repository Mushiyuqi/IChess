cmake_minimum_required(VERSION 3.28)
project(IChessServer)

set(CMAKE_CXX_STANDARD 20)

add_executable(IChessServer main.cpp
        MsgNode.h
        MsgNode.cpp
        const.h
        AsioIOContextPool.cpp
        AsioIOContextPool.h
        CServer.h
        CServer.cpp
        CSession.h
        CSession.cpp
        LogicSystem.h
        LogicSystem.cpp
        ChessBoard.h
        ChessBoard.cpp
        ChessManager.h
        ChessManager.cpp
)

# 设置find package策略
cmake_policy(SET CMP0167 NEW)

# 添加Boost库的依赖
find_package(Boost REQUIRED COMPONENTS system filesystem thread)
target_link_directories(IChessServer PRIVATE
        Boost::filesystem
        Boost::system
        Boost::thread
        Boost::boost
)

# 添加Abseil库的依赖
find_package(absl REQUIRED)
target_link_libraries(IChessServer PRIVATE
        absl::log_internal_check_op
        absl::cord
        absl::strings
        absl::base
        absl::synchronization
)

# 添加Protobuf库的依赖
find_package(Protobuf REQUIRED)
target_link_libraries(IChessServer PRIVATE
        protobuf::libprotobuf
        protobuf::libprotoc
        protobuf::libprotobuf-lite
)

# 添加grpc库的依赖
target_link_libraries(IChessServer PRIVATE
        libgpr.so
        libgrpc.so
        libgrpc++.so
        libgrpc++_reflection.so
        libaddress_sorting.so
)

# 添加JSONCPP库的依赖
target_link_libraries(IChessServer PRIVATE jsoncpp.so)