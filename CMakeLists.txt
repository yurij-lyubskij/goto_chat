cmake_minimum_required(VERSION 3.21)
project(goto_chat)

set(CMAKE_CXX_STANDARD 14)

file(GLOB SOURCES *.cpp server/*.cpp)
file(GLOB_RECURSE SOURCES ${SOURCES}  ./internal/*.cpp )

file(GLOB_RECURSE TEST_SOURCES internal/AuthDb/*.cpp internal/MessageQueue/*.cpp)

file(GLOB INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR} internal/MessageQueue internal/AuthDb internal/UserRepo server internal/User internal/UserSession internal/Request internal/Response internal/Handlers internal/Router internal/Middleware )

add_executable(${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC ${INCLUDE_DIRS})

find_package(GTest REQUIRED)
add_executable(tests ${TEST_SOURCES})
#set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -coverage -lgcov")
target_include_directories(tests PUBLIC ${INCLUDE_DIRS})
target_link_libraries(tests GTest::GTest gtest_main)