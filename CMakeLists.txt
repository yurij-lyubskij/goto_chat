cmake_minimum_required(VERSION 3.16)
project(goto_chat)

set(CMAKE_CXX_STANDARD 14)
set (GMOCK_DIR "${GMOCK_DIR} /usr/src/gmock/include ")

#set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH} /home/yura11011/goto_chat/gmock")
#list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/gmock")
#message("${CMAKE_MODULE_PATH}")

file(GLOB SOURCES *.cpp server/*.cpp)
file(GLOB SOURCES ${SOURCES}   ./internal/AuthDb/*.cpp ./internal/Handlers/*.cpp)
file(GLOB SOURCES ${SOURCES}   ./internal/MessageQueue/*.cpp ./internal/Middleware/*.cpp)
file(GLOB SOURCES ${SOURCES}   ./internal/Request/*.cpp ./internal/Response/*.cpp)
file(GLOB SOURCES ${SOURCES}   ./internal/Router/*.cpp ./internal/User/*.cpp)
file(GLOB SOURCES ${SOURCES}   ./internal/UserRepo/*.cpp ./internal/UserSession/*.cpp)
file(GLOB SOURCES ${SOURCES} internal/ChatRoom/ChatRoom.cpp internal/ChatRoomHandler/ChatRoomHandler.cpp)
file(GLOB SOURCES ${SOURCES} internal/DBRepo/DBRepo.cpp internal/DBRepo/DBRepo.cpp internal/Response/Response.cpp)
file(GLOB SOURCES ${SOURCES} internal/Handlers/Handlers.cpp internal/Message/Message.cpp internal/Request/Request.cpp)
file(GLOB SOURCES ${SOURCES} internal/User/User.cpp internal/WebSocketServer/WebSocketServer.cpp )
file(GLOB SOURCES ${SOURCES} internal/MessageQueue/ internal/MessageQueue.cpp)
message("MAIN SOURCES\n ${SOURCES}")


file(GLOB TEST_SOURCES ${SOURCES} internal/*/tests/*.cpp )
file(GLOB TEST_SOURCES ${TEST_SOURCES} internal/*/tests/*.cpp server/tests/*.cpp)


file(GLOB INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR} internal/MessageQueue internal/AuthDb internal/UserRepo server internal/User internal/UserSession internal/Request internal/Response internal/Handlers internal/Router internal/Middleware )
file(GLOB INCLUDE_DIRS ${GMOCK_DIR} ${INCLUDE_DIRS} internal/ChatRoom internal/ChatRoomHandler internal/DBRepo internal/Response internal/Handlers internal/Message internal/Request internal/User internal/WebSocketServer internal/MessageQueue)

add_executable(${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC ${INCLUDE_DIRS})

find_package(GTest REQUIRED)
message("TEST SOURCES\n ${TEST_SOURCES}")
#find_package(GMock REQUIRED)
add_executable(tests ${TEST_SOURCES})
target_include_directories(tests PUBLIC ${INCLUDE_DIRS} ${GMOCK_DIR})
target_link_libraries(tests GTest::GTest gtest_main gmock)
