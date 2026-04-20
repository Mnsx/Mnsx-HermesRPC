cmake_minimum_required(VERSION 3.10)
project(Mnsx-HermesRPC LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 强制引入系统线程库（Kraken 和 Achilles 共同需要）
find_package(Threads REQUIRED)

# ==========================================
# 1. 依赖加载顺序 (绝对不能颠倒)
# ==========================================

# 必须首先加载全局唯一的日志基石
add_subdirectory(third_party/argus_log)

# 此时 ArgusLog 目标已存在，Achilles 和 Kraken 内部的 link 命令将自动指向它
add_subdirectory(third_party/achilles_link)

# ==========================================
# 2. 构建 HermesRPC 核心库
# ==========================================
file(GLOB_RECURSE HERMES_SRC "src/*.cpp")
add_library(HermesRPC STATIC ${HERMES_SRC})

# 暴露 Hermes 自己的头文件路径
target_include_directories(HermesRPC PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

# 【视野破壁】：这里已经全部修改为 PUBLIC，让 ServerDemo 能够看到底层的 TcpServer.h
target_include_directories(HermesRPC PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/third_party/achilles_link/include)
target_include_directories(HermesRPC PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/third_party/argus_log/include)

# 链接三大基石组件
target_link_libraries(HermesRPC PUBLIC
        AchillesLink
        ArgusLog
        Threads::Threads
)

# 确保全局编码统一
if(MSVC)
    add_compile_options(/utf-8)
endif()

# ==========================================
# 3. 编译靶场测试程序
# ==========================================
add_executable(ServerDemo examples/ServerDemo.cpp)
target_link_libraries(ServerDemo PRIVATE HermesRPC)

add_executable(ClientDemo examples/ClientDemo.cpp)
target_link_libraries(ClientDemo PRIVATE HermesRPC)