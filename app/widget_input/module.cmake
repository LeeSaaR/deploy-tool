cmake_minimum_required(VERSION 3.5)

include_directories(${CMAKE_CURRENT_LIST_DIR})

set(APP_SOURCES ${APP_SOURCES}
    ${CMAKE_CURRENT_LIST_DIR}/widgetinput.h ${CMAKE_CURRENT_LIST_DIR}/widgetinput.cpp ${CMAKE_CURRENT_LIST_DIR}/widgetinput.ui
    ${CMAKE_CURRENT_LIST_DIR}/fileselection.h ${CMAKE_CURRENT_LIST_DIR}/fileselection.cpp ${CMAKE_CURRENT_LIST_DIR}/fileselection.ui
)


