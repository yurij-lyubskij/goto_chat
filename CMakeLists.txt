cmake_minimum_required(VERSION 3.16)
project(goto_chat VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS  ${CMAKE_CXX_FLAGS} " -pthread -lboost_thread")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS}  -pthread -lboost_thread" )



find_package(Threads)


file(GLOB SOURCES */*/*.cpp)

#one main in tests and in project
file(GLOB SOURCES ${SOURCES} main.cpp)
file(GLOB INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR} client_lib/*/ checker_lib/*/ )

message("MAIN SOURCES\n ${SOURCES}")
message("MAIN INCLUDE_DIRS\n ${INCLUDE_DIRS}")

add_executable(${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC ${INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PRIVATE  Threads::Threads pq)

