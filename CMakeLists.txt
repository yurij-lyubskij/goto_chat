cmake_minimum_required(VERSION 3.21)
project(goto_chat)

set(CMAKE_CXX_STANDARD 14)

file(GLOB SOURCES *.cpp server/*.cpp)
file(GLOB_RECURSE SOURCES ${SOURCES}  ./internal/*.cpp )

file(GLOB INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}  server internal/UserSession internal/Request internal/Response internal/Handlers internal/Router internal/Middleware )

add_executable(${PROJECT_NAME} ${SOURCES} internal/UserSession/UserSession.cpp internal/UserSession/UserSession.h)
target_include_directories(${PROJECT_NAME} PUBLIC ${INCLUDE_DIRS})