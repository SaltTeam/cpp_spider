cmake_minimum_required(VERSION 3.8)
project(cpp_spider)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
    includes/Database/IDatabase.hpp
    includes/Database/Sqlite.hpp
    includes/logger/Logger.hpp
    includes/Network/ServerNetwork.hpp
    includes/Protocol/Buffer.hpp
    includes/Protocol/ClientProtocol.hpp
    includes/Protocol/IProtocol.hpp
    includes/Protocol/Serializer.hpp
    includes/Protocol/ServerProtocol.hpp
    includes/ClientCore.hpp
    includes/dataStructure.hpp
    includes/IKeyLogger.hpp
    includes/ServerCore.hpp
    includes/SpiderException.hpp
    sources/Database/Sqlite.cpp
    sources/logger/Logger.cpp
    sources/Network/ServerNetwork.cpp
    sources/Protocol/Buffer.cpp
    sources/Protocol/Serializer.cpp
    sources/Protocol/ServerProtocol.cpp
    sources/ServerCore.cpp
    sources/ServerMain.cpp)

set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
find_package(Boost 1.63.0 COMPONENTS system thread REQUIRED)

add_executable(cpp_spider ${SOURCE_FILES})
target_link_libraries(cpp_spider boost_system boost_thread sqlite3 ssl crypto)
include_directories(includes)