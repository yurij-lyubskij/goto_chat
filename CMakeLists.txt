cmake_minimum_required(VERSION 3.14)
project(goto_chat)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS  ${CMAKE_CXX_FLAGS} " -pthread -lboost_thread")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS}  -pthread -lboost_thread" )

file(GLOB SOURCES internal/*/*.cpp )

file(GLOB TEST_SOURCES ${SOURCES} internal/*/tests/*.cpp)
message("TEST SOURCES\n ${TEST_SOURCES}")

#one main in tests and in project
file(GLOB SOURCES ${SOURCES} main.cpp)

file(GLOB INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR} internal/*/)

message("MAIN SOURCES\n ${SOURCES}")
message("MAIN INCLUDE_DIRS\n ${INCLUDE_DIRS}")
add_executable(${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC ${INCLUDE_DIRS})

find_package(GTest REQUIRED)


add_executable(alltests ${TEST_SOURCES})
target_include_directories(alltests PUBLIC ${INCLUDE_DIRS})
target_link_libraries(alltests GTest::GTest gtest_main gmock gmock_main)