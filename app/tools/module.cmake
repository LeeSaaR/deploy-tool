cmake_minimum_required(VERSION 3.5)

include_directories(${CMAKE_CURRENT_LIST_DIR})

set(APP_SOURCES ${APP_SOURCES}
    ${CMAKE_CURRENT_LIST_DIR}/io.h ${CMAKE_CURRENT_LIST_DIR}/io.cpp
    ${CMAKE_CURRENT_LIST_DIR}/dtdata.h ${CMAKE_CURRENT_LIST_DIR}/dtdata.cpp
    ${CMAKE_CURRENT_LIST_DIR}/dtstyle.h ${CMAKE_CURRENT_LIST_DIR}/dtstyle.cpp
    ${CMAKE_CURRENT_LIST_DIR}/json.h ${CMAKE_CURRENT_LIST_DIR}/json.cpp
    ${CMAKE_CURRENT_LIST_DIR}/threadprogram.h ${CMAKE_CURRENT_LIST_DIR}/threadprogram.cpp

)


