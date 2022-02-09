cmake_minimum_required(VERSION 3.17)
project(concurrence_practices)

set(CMAKE_CXX_STANDARD 11)

# 收集源代码
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/src SRC_LIST)

# 添加可执行程序
add_executable(concurrence ${SRC_LIST})

# 给目标链接库
target_link_libraries(concurrence pthread)
