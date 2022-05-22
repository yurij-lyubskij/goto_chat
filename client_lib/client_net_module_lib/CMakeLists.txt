cmake_minimum_required(VERSION 3.21.1)
project(client_net_module)


# set(Boost_USE_STATIC_LIBS OFF) 
# set(Boost_USE_MULTITHREADED ON)  
# set(Boost_USE_STATIC_RUNTIME OFF) 
find_package(Boost) 

if(Boost_FOUND)
    add_library(${PROJECT_NAME} STATIC ./client_net_module.cpp)
    #target_include_directories(${PROJECT_NAME} ${Boost_INCLUDE_DIRS})
    #target_include_directories(${PROJECT_NAME} PRIVATE ${INCLUDES})
    target_link_libraries(${PROJECT_NAME} Boost::headers)
endif()

set(CLIENT_NET_MODULE_LIB_LIBRARIES ${PROJECT_NAME} PARENT_SCOPE)
set(CLIENT_NET_MODULE_LIB_INCLUDE_DIRS ${INCLUDES} PARENT_SCOPE)
