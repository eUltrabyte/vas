cmake_minimum_required(VERSION 3.17)
project(App)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(X11 REQUIRED)

add_executable(${PROJECT_NAME}
    App.cpp
)

target_include_directories(${PROJECT_NAME} PRIVATE ../Source)
target_link_libraries(${PROJECT_NAME} PRIVATE vas X11::X11 X11::xcb)