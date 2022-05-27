cmake_minimum_required(VERSION 3.20)
project(client_lib)

set(INCLUDES
        ${CMAKE_CURRENT_SOURCE_DIR}/headers/
        #${CMAKE_CURRENT_SOURCE_DIR}/client_net_module_lib/
        ${CMAKE_CURRENT_SOURCE_DIR}/parser_lib/
        ${CMAKE_CURRENT_SOURCE_DIR}/session_lib/
        ${CMAKE_CURRENT_SOURCE_DIR}/json_actions/
        ${CMAKE_CURRENT_SOURCE_DIR}/request_lib/
        ${CMAKE_CURRENT_SOURCE_DIR}/builder/
        )
#set(CMAKE_AUTOUIC ON)
#set(CMAKE_AUTOMOC ON)
#set(CMAKE_AUTOUIC_SEARCH_PATHS ${INCLUDES})

#find_package(Qt6 REQUIRED COMPONENTS Widgets)


add_library(${PROJECT_NAME} STATIC
    ${CMAKE_CURRENT_SOURCE_DIR}/headers/client.h
    ${CMAKE_CURRENT_SOURCE_DIR}/headers/structures.h
    ${CMAKE_CURRENT_SOURCE_DIR}/headers/httpClient.h
    ${CMAKE_CURRENT_SOURCE_DIR}/headers/Response.h
    ${CMAKE_CURRENT_SOURCE_DIR}/sources/client.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/parser_lib/parser.h
    ${CMAKE_CURRENT_SOURCE_DIR}/parser_lib/parser.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/request_lib/request.h
    ${CMAKE_CURRENT_SOURCE_DIR}/session_lib/session.h
    ${CMAKE_CURRENT_SOURCE_DIR}/builder/targetBuilder.h
    ${CMAKE_CURRENT_SOURCE_DIR}/builder/targetBuilder.cpp
)

target_include_directories(client_lib PRIVATE ${INCLUDES})
target_include_directories(client_lib INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})


set(CLIENT_LIB_LIBRARIES client_lib PARENT_SCOPE)
set(CLIENT_LIB_INCLUDE_DIRS ${INCLUDES} PARENT_SCOPE)
