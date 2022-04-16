cmake_minimum_required(VERSION 3.16)
project(goto_chat VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(client_lib)
add_subdirectory(checker_lib)
add_subdirectory(ui)

set(CMAKE_C_FLAGS ${CMAKE_C_FLAGS} "-Wall -Werror -Wpedantic")

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -coverage")

set_target_properties(${PROJECT_NAME} PROPERTIES
        WIN32_EXECUTABLE ON
        MACOSX_BUNDLE ON
        )

add_subdirectory(test)
