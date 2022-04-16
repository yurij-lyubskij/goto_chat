cmake_minimum_required(VERSION 3.22.3)
project(goto_chat VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(message_lib)
add_subdirectory(client_net_module_lib)

set(CMAKE_C_FLAGS ${CMAKE_C_FLAGS} "-Wall -Werror -Wpedantic")

add_subdirectory(test)