cmake_minimum_required(VERSION 3.22.3)
project(client_net_module)

set(INCLUDES ${CMAKE_CURRENT_SOURCE_DIR})

add_library(${PROJECT_NAME} STATIC ./client_net_module.cpp)

target_include_directories(${PROJECT_NAME} PRIVATE ${INCLUDES})

set(CLIENT_NET_MODULE_LIB_LIBRARIES ${PROJECT_NAME} PARENT_SCOPE)
set(CLIENT_NET_MODULE_LIB_INCLUDE_DIRS ${INCLUDES} PARENT_SCOPE)
