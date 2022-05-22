cmake_minimum_required(VERSION 3.22.3)
project(client_net_module)


# set(Boost_USE_STATIC_LIBS OFF) 
# set(Boost_USE_MULTITHREADED ON)  
# set(Boost_USE_STATIC_RUNTIME OFF) 
find_package(Boost) 

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS}) 
    add_library(${PROJECT_NAME} STATIC ./client_net_module.cpp)
    target_include_directories(${PROJECT_NAME} PRIVATE ${INCLUDES})
    target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})
endif()

set(CLIENT_NET_MODULE_LIB_LIBRARIES ${PROJECT_NAME} PARENT_SCOPE)
set(CLIENT_NET_MODULE_LIB_INCLUDE_DIRS ${INCLUDES} PARENT_SCOPE)
