cmake_minimum_required(VERSION 3.14)
project(goto_chat)

set(CMAKE_CXX_STANDARD 14)

file(GLOB SOURCES main.cpp)
file(GLOB SOURCES ${SOURCES} internal/*/*.cpp)
#find_package(PostgreSQL REQUIRED)

file(GLOB INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR} internal/*)

message("MAIN SOURCES\n ${SOURCES}")
add_executable(${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC ${INCLUDE_DIRS})
#target_link_libraries(${PROJECT_NAME} PRIVATE PostgreSQL::PostgreSQL pq)

find_package(GTest REQUIRED)

file(GLOB TEST_SOURCES ${SOURCES} internal/*/tests/*.cpp )
message("TEST SOURCES\n ${TEST_SOURCES}")
add_executable(tests ${TEST_SOURCES})
target_include_directories(tests PUBLIC ${INCLUDE_DIRS})
#target_link_libraries(tests GTest::GTest gtest_main gmock gmock_main PostgreSQL::PostgreSQL pq)
target_link_libraries(tests GTest::GTest gtest_main gmock gmock_main)