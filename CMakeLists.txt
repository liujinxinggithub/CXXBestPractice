cmake_minimum_required(VERSION 3.17)
project(concurrence_practices)

set(CMAKE_CXX_STANDARD 11)

# 收集源代码
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/chapter_1 SRC_LIST_1)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/design_patterns/singleton_pattern SRC_SINGLETON_LIST)

# 添加可执行程序
add_executable(chapter_1 ${SRC_LIST_1})
add_executable(chapter_2_main ${CMAKE_CURRENT_SOURCE_DIR}/chapter_2/main.cpp)
add_executable(chapter_2_5 ${CMAKE_CURRENT_SOURCE_DIR}/chapter_2/2_5.cpp)
add_executable(chapter_2_6 ${CMAKE_CURRENT_SOURCE_DIR}/chapter_2/2_6.cpp)

add_executable(singleton_pattern ${SRC_SINGLETON_LIST})
add_executable(inherit ${CMAKE_CURRENT_SOURCE_DIR}/cxx_base/inherit.cpp)
add_executable(exception ${CMAKE_CURRENT_SOURCE_DIR}/cxx_base/exception.cpp)

# 给目标链接库
target_link_libraries(chapter_1 pthread)
target_link_libraries(chapter_2_main pthread)
target_link_libraries(chapter_2_5 pthread)
target_link_libraries(chapter_2_6 pthread)
