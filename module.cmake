cmake_minimum_required(VERSION 3.5)

include(${CMAKE_CURRENT_LIST_DIR}/app/module.cmake)

# add ${APPLICATION_SOURCES} to PROJECT_SOURCES in top level CMakeLists.txt
set(APPLICATION_SOURCES ${APP_SOURCES})
