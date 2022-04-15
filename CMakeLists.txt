cmake_minimum_required(VERSION 3.14)
project(goto_chat)

set(CMAKE_CXX_STANDARD 14)

file(GLOB SOURCES main.cpp)
file(GLOB_RECURSE SOURCES ${SOURCES} internal/ChatRoom/ChatRoom.cpp internal/ChatRoomHandler/ChatRoomHandler.cpp internal/DBRepo/DBRepo.cpp internal/DBRepo/DBRepo.cpp internal/Response/Response.cpp internal/Handlers/Handlers.cpp internal/Message/Message.cpp internal/Request/Request.cpp internal/User/User.cpp internal/WebSocketServer/WebSocketServer.cpp)

find_package(PostgreSQL REQUIRED)

file(GLOB INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR} internal/ChatRoom internal/ChatRoomHandler internal/DBRepo internal/Response internal/Handlers internal/Message internal/Request internal/User internal/WebSocketServer)

add_executable(${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC ${INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PRIVATE PostgreSQL::PostgreSQL pq)

find_package(GTest REQUIRED)

file(GLOB TEST_SOURCES ./internal/*/tests/*.cpp)
add_executable(tests ${TEST_SOURCES})

target_include_directories(tests PUBLIC ${INCLUDE_DIRS})
target_link_libraries(tests GTest::GTest gtest_main PostgreSQL::PostgreSQL pq)