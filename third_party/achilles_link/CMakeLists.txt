cmake_minimum_required(VERSION 3.10)
project(AchillesLink LANGUAGES CXX)

file(GLOB_RECURSE SRC_FILES "src/*.cpp")
add_library(AchillesLink STATIC ${SRC_FILES})

# 暴露头文件给上层
target_include_directories(AchillesLink PUBLIC
       ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# 【核心逻辑】: 这里不执行 add_subdirectory(argus)
# 直接链接由顶级 CMake 提供的 ArgusLog 目标
target_link_libraries(AchillesLink PUBLIC
        ArgusLog
)

target_compile_features(AchillesLink PUBLIC cxx_std_11)