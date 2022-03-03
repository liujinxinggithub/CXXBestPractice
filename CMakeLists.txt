cmake_minimum_required(VERSION 3.17)
project(concurrence_practices)

set(CMAKE_CXX_STANDARD 14)
SET(CMAKE_BUILD_TYPE "Debug")
SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g2 -ggdb")
SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")

# 包含头文件
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/3rdpart/easy_log) # 日志第三方库头文件

# 收集源代码,仅收集cpp文件，并储存在变量中
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/chapter_1 SRC_LIST_1)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/design_patterns/singleton SRC_SINGLETON_LIST)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/design_patterns/factory SRC_FACTORY_LIST)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/3rdpart/easy_log 3RD_LOG) # 日志第三方库源文件

# 添加可执行程序——并发实践
add_executable(chapter_1 ${SRC_LIST_1})
add_executable(chapter_2_main ${CMAKE_CURRENT_SOURCE_DIR}/chapter_2/main.cpp)
add_executable(chapter_2_5 ${CMAKE_CURRENT_SOURCE_DIR}/chapter_2/2_5.cpp)
add_executable(chapter_2_6 ${CMAKE_CURRENT_SOURCE_DIR}/chapter_2/2_6.cpp)
add_executable(chapter_2_7 ${CMAKE_CURRENT_SOURCE_DIR}/chapter_2/2_7.cpp)
add_executable(chapter_2_8 ${CMAKE_CURRENT_SOURCE_DIR}/chapter_2/2_8.cpp)
add_executable(chapter_2_9 ${CMAKE_CURRENT_SOURCE_DIR}/chapter_2/2_9.cpp)
add_executable(chapter_2_10 ${CMAKE_CURRENT_SOURCE_DIR}/chapter_2/2_10.cpp)
add_executable(chapter_2_11 ${CMAKE_CURRENT_SOURCE_DIR}/chapter_2/2_11.cpp)
add_executable(chapter_2_12 ${CMAKE_CURRENT_SOURCE_DIR}/chapter_2/2_12.cpp)

# 添加可执行程序——设计模式
add_executable(singleton ${SRC_SINGLETON_LIST})
add_executable(factory ${SRC_FACTORY_LIST} ${3RD_LOG})

# 添加可执行程序——语法
add_executable(inherit ${CMAKE_CURRENT_SOURCE_DIR}/cxx_base/inherit.cpp)
add_executable(exception ${CMAKE_CURRENT_SOURCE_DIR}/cxx_base/exception.cpp)
add_executable(smart_point ${CMAKE_CURRENT_SOURCE_DIR}/cxx_base/smart_point.cpp)
add_executable(move ${CMAKE_CURRENT_SOURCE_DIR}/cxx_base/move.cpp ${3RD_LOG})
add_executable(perfect_forward ${CMAKE_CURRENT_SOURCE_DIR}/cxx_base/perfect_forward.cpp)
add_executable(char_test ${CMAKE_CURRENT_SOURCE_DIR}/cxx_base/char.cpp)


# 给目标链接库
target_link_libraries(chapter_1 pthread)
target_link_libraries(chapter_2_main pthread)
target_link_libraries(chapter_2_5 pthread)
target_link_libraries(chapter_2_6 pthread)
target_link_libraries(chapter_2_7 pthread)
target_link_libraries(chapter_2_8 pthread)
target_link_libraries(chapter_2_9 pthread)
target_link_libraries(chapter_2_10 pthread)
target_link_libraries(chapter_2_11 pthread)
target_link_libraries(chapter_2_12 pthread)
