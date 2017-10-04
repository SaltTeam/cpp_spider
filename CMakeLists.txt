cmake_minimum_required(VERSION 3.8)
project(cpp_spider)

set(CMAKE_CXX_STANDARD 11)

include_directories(includes)

add_executable(cpp_spider
        sources/Database/Sqlite.cpp
        sources/ServerCore.cpp)