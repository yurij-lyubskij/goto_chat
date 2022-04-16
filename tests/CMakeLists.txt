cmake_minimum_required(VERSION 3.22.3)
project(tests)

set(CMAKE_CXX_STANDARD 17)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTest gtest_main)

file(GLOB SOURCES ../client_net_module_lib/*.cpp ../message_lib/*.cpp)
add_executable(${PROJECT_NAME} tests.cpp ${SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC ../client_net_module_lib ../message_lib ${GTest_INCLUDE_DIRECTORIES})
target_link_libraries(${PROJECT_NAME} ${GTest_LIBRARIES})