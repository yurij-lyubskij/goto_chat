cmake_minimum_required(VERSION 3.22.3)
project(message_lib)

set(INCLUDES ${CMAKE_CURRENT_SOURCE_DIR})

add_library(${PROJECT_NAME} STATIC ./message.cpp)

target_include_directories(${PROJECT_NAME} PRIVATE ${INCLUDES})

set(MESSAGE_LIB_LIBRARIES ${PROJECT_NAME} PARENT_SCOPE)
set(MESSAGE_LIB_INCLUDE_DIRS ${INCLUDES} PARENT_SCOPE)
