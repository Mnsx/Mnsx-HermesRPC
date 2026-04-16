cmake_minimum_required(VERSION 3.10)
project(ArgusLog LANGUAGES CXX)

file(GLOB_RECURSE SRC_FILES "src/*.cpp")
add_library(ArgusLog STATIC ${SRC_FILES})

# 【PUBLIC】: 供 Hermes, Achilles, Kraken 链接使用
# 使用者只需写: #include "handler/LogHandlerManager.h"
target_include_directories(ArgusLog PUBLIC
       ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# 【PRIVATE】: 仅供 Argus 内部编译使用
# 解决内部代码写 #include "include/handler/LogHandlerManager.h" 找不到文件的问题
target_include_directories(ArgusLog PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_compile_features(ArgusLog PUBLIC cxx_std_11)