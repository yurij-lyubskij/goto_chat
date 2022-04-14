cmake_minimum_required(VERSION 3.21)
project(goto_chat)

set(CMAKE_CXX_STANDARD 14)

file(GLOB SOURCES *.cpp  ./internal/Handlers/*.cpp ./internal/Router/*.cpp ./internal/Middleware/*.cpp)

file(GLOB INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR} ./internal/Handlers ./internal/Router ./internal/Middleware)

add_executable(${PROJECT_NAME} ${SOURCES} )
target_include_directories(${PROJECT_NAME} PUBLIC ${INCLUDE_DIRS})