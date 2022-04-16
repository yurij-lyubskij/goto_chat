cmake_minimum_required(VERSION 3.0.0)
project(checker_lib)

set(INCLUDES
        ${CMAKE_CURRENT_SOURCE_DIR}/headers
        )



add_library(checker_lib STATIC
    ${CMAKE_CURRENT_SOURCE_DIR}/sources/checker.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/headers/checker.h
)

target_include_directories(checker_lib PRIVATE ${INCLUDES})

set(CHECKER_LIB_LIBRARIES checker_lib PARENT_SCOPE)
set(CHECKER_LIB_INCLUDE_DIRS ${INCLUDES} PARENT_SCOPE)
