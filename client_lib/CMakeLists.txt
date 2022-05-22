set(INCLUDES
        ${CMAKE_CURRENT_SOURCE_DIR}/headers/
        )
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC_SEARCH_PATHS ${INCLUDES})

find_package(Qt6 REQUIRED COMPONENTS Widgets)

add_subdirectory(client_net_module_lib)
add_subdirectory(message_lib)

add_library(client_lib STATIC
    ${CMAKE_CURRENT_SOURCE_DIR}/headers/client.h
    ${CMAKE_CURRENT_SOURCE_DIR}/sources/client.cpp
)
target_link_libraries(client_lib PRIVATE Qt6::Widgets)
target_include_directories(client_lib PRIVATE ${INCLUDES})
target_include_directories(client_lib INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})


set(CLIENT_LIB_LIBRARIES client_lib PARENT_SCOPE)
set(CLIENT_LIB_INCLUDE_DIRS ${INCLUDES} PARENT_SCOPE)
