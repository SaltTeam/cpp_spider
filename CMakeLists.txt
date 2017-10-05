cmake_minimum_required(VERSION 3.8)
project(cpp_spider)

set(CMAKE_CXX_STANDARD 11)

 include_directories(includes)

add_executable(cpp_spider
        includes/Database/IDatabase.hpp
        includes/Database/Sqlite.hpp
        includes/logger/Logger.hpp
        includes/Network/Buffer.hpp
        includes/Network/ClientNetwork.hpp
        includes/Network/ServerNetwork.hpp
        includes/Protocol/IProtocol.hpp
        includes/Protocol/Protocol.hpp
        includes/Protocol/Serializer.hpp
        includes/dataStructure.hpp
        includes/ServerCore.hpp
        includes/SpiderException.hpp
        sources/Database/main.cpp
        sources/Database/Sqlite.cpp
        sources/logger/Logger.cpp
        sources/Network/Buffer.cpp
        sources/Network/ClientNetwork.cpp
        sources/Network/ServerNetwork.cpp
        sources/Protocol/Protocol.cpp
        sources/Protocol/Serializer.cpp
        sources/main.cpp
        sources/ServerCore.cpp)
