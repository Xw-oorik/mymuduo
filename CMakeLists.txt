cmake_minimum_required(VERSION 3.0)
project(mymuduo)

#mymuduo最终编译成so动态库，设置动态库路径，放在根目录的lib文件夹下
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

#设置调试信息 启动c11
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -std=c++11 -fPIC")
# 配置头文件信息
include_directories(${PROJECT_SOURCE_DIR}/include)

# 加载子目录
add_subdirectory(src)