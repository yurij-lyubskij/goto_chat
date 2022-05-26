set(INCLUDES
        ${CMAKE_CURRENT_SOURCE_DIR}/headers
        ${CMAKE_CURRENT_SOURCE_DIR}/graphic)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC_SEARCH_PATHS ${INCLUDES})

find_package(Qt6 COMPONENTS Multimedia REQUIRED)
find_package(Qt6 REQUIRED COMPONENTS Widgets)

add_executable(goto_chat
        ${CMAKE_CURRENT_SOURCE_DIR}/graphic/reg_window.ui
        ${CMAKE_CURRENT_SOURCE_DIR}/sources/reg_window.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/headers/reg_window.h
        ${CMAKE_CURRENT_SOURCE_DIR}/graphic/app_window.ui
        ${CMAKE_CURRENT_SOURCE_DIR}/sources/app_window.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/headers/app_window.h
        ${CMAKE_CURRENT_SOURCE_DIR}/graphic/login_window.ui
        ${CMAKE_CURRENT_SOURCE_DIR}/sources/login_window.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/headers/login_window.h
        ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/headers/recorder.h
        ${CMAKE_CURRENT_SOURCE_DIR}/sources/recorder.cpp
        )

target_link_libraries(goto_chat PRIVATE Qt6::Widgets Qt6::Multimedia ${CLIENT_LIB_LIBRARIES} ${CHECKER_LIB_LIBRARIES})
target_include_directories(goto_chat PRIVATE ${INCLUDES} ${CLIENT_LIB_INCLUDE_DIRS} ${CHECKER_LIB_INCLUDE_DIRS})
set_target_properties(goto_chat PROPERTIES
        WIN32_EXECUTABLE ON
        MACOSX_BUNDLE ON
        )
