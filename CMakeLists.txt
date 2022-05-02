cmake_minimum_required(VERSION 3.22)
project(server)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS  ${CMAKE_CXX_FLAGS} " -pthread -lboost_thread")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS}  -pthread -lboost_thread" )

add_executable(server
        blocking_server_ex.cpp)

add_executable(async_server
        async_server.cpp)

add_executable(client
        blocking_clientex.cpp)

add_executable(chat_client
        chat_client.cpp)

add_executable(chat_server
        chat_server.cpp)

add_executable(http_server
        http_server.cpp)

add_executable(http_client
        http_client.cpp)

add_executable(ws_server
        ws_server.cpp)

add_executable(ws_client
        ws_client.cpp)