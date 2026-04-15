cmake_minimum_required(VERSION 3.10)
project(Mnsx-HermesRPC LANGUAGES CXX)

# ==========================================
# 全局设置
# ==========================================
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ==========================================
# 依赖决议 (菱形依赖防御网)
# ==========================================

# 第一层防御：最底层的 ArgusLog
if(NOT TARGET ArgusLog)
    if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/third_party/argus_log/CMakeLists.txt")
        add_subdirectory(third_party/argus_log)
    else()
        message(STATUS "[Hermes] ArgusLog not found locally. Relying on AchillesLink to provide it.")
    endif()
endif()

# 第二层防御：中间网络层 AchillesLink
if(NOT TARGET AchillesLink)
    if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/third_party/achilles_link/CMakeLists.txt")
        add_subdirectory(third_party/achilles_link)
    else()
        message(FATAL_ERROR "[Hermes] AchillesLink dependency missing!")
    endif()
endif()

# ==========================================
# 定义核心库 (HermesRPC)
# ==========================================
file(GLOB_RECURSE LIB_SRC_FILES "src/*.cpp")
add_library(HermesRPC STATIC ${LIB_SRC_FILES})

# 暴露 Hermes 自己的头文件
target_include_directories(HermesRPC PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(HermesRPC PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    target_compile_options(HermesRPC PRIVATE -fexec-charset=UTF-8)
endif()

# ==========================================
# 链接组装 (极简纯净版)
# ==========================================
target_link_libraries(HermesRPC PUBLIC
        achilles_link
        argus_log
)

# ==========================================
# 示例程序 (Demo)
# ==========================================
if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/examples/BasicUsage.cpp")
    add_executable(HermesDemo examples/BasicUsage.cpp)
    target_link_libraries(HermesDemo PRIVATE HermesRPC)
endif()