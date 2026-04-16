cmake_minimum_required(VERSION 3.10)
project(KrakenPool LANGUAGES CXX)

file(GLOB_RECURSE SRC_FILES "src/*.cpp")
add_library(KrakenPool STATIC ${SRC_FILES})

# 暴露头文件
target_include_directories(KrakenPool PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

# 共享全局唯一的 ArgusLog 实例
target_link_libraries(KrakenPool PUBLIC
        ArgusLog
        Threads::Threads
)

target_compile_features(KrakenPool PUBLIC cxx_std_11)