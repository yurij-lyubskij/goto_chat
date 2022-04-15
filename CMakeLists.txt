cmake_minimum_required(VERSION 3.21)
project(goto_chat)

set(CMAKE_CXX_STANDARD 14)

file(GLOB SOURCES *.cpp server/*.cpp)
file(GLOB SOURCES ${SOURCES}   ./internal/AuthDb/*.cpp ./internal/Handlers/*.cpp)

file(GLOB SOURCES ${SOURCES}   ./internal/MessageQueue/*.cpp ./internal/Middleware/*.cpp)

file(GLOB SOURCES ${SOURCES}   ./internal/Request/*.cpp ./internal/Response/*.cpp)

file(GLOB SOURCES ${SOURCES}   ./internal/Router/*.cpp ./internal/User/*.cpp)

file(GLOB SOURCES ${SOURCES}   ./internal/UserRepo/*.cpp ./internal/UserSession/*.cpp)

file(GLOB TEST_SOURCES internal/AuthDb/*.cpp internal/AuthDb/tests/*.cpp)
file(GLOB TEST_SOURCES ${TEST_SOURCES} internal/MessageQueue/*.cpp internal/MessageQueue/tests/*.cpp)
file(GLOB TEST_SOURCES ${TEST_SOURCES} internal/Handlers/*.cpp internal/Handlers/tests/*.cpp internal/UserSession/*.cpp )
file(GLOB TEST_SOURCES ${TEST_SOURCES} internal/Middleware/*.cpp internal/Middleware/tests/*.cpp)
file(GLOB TEST_SOURCES ${TEST_SOURCES} internal/Router/*.cpp internal/Router/tests/*.cpp)
file(GLOB TEST_SOURCES ${TEST_SOURCES} internal/UserRepo/*.cpp internal/UserRepo/tests/*.cpp)

file(GLOB INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR} internal/MessageQueue internal/AuthDb internal/UserRepo server internal/User internal/UserSession internal/Request internal/Response internal/Handlers internal/Router internal/Middleware )

add_executable(${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC ${INCLUDE_DIRS})

find_package(GTest REQUIRED)
add_executable(tests ${TEST_SOURCES})
#set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -coverage -lgcov")
target_include_directories(tests PUBLIC ${INCLUDE_DIRS})
target_link_libraries(tests GTest::GTest gtest_main)