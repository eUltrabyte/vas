cmake_minimum_required(VERSION 3.17)
project(rainbow)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(RAINBOW_SOURCE
    Source/rainbow/Platform.hpp
    Source/rainbow/ANSI.hpp
    Source/rainbow/rainbow.hpp
    Source/rainbow/rainbow.cpp
)

option(RAINBOW_SHARED_LIBRARY "rainbow build using shared libraries" OFF)
option(RAINBOW_SHARED_BUILD "rainbow build shared libraries files" OFF)

if(RAINBOW_SHARED_LIBRARY)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DRAINBOW_SHARED_LIBRARY")

    if(RAINBOW_SHARED_LIBRARY)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DRAINBOW_SHARED_BUILD")
    endif()

    add_library(${PROJECT_NAME} SHARED ${RAINBOW_SOURCE})
else()
    add_library(${PROJECT_NAME} STATIC ${RAINBOW_SOURCE})
endif()

target_precompile_headers(${PROJECT_NAME} PUBLIC Source/rainbow/rbwpch.hpp Source/rainbow/rbwpch.cpp)
target_compile_definitions(${PROJECT_NAME} PUBLIC $<$<CONFIG:Debug>:RAINBOW_DEBUG> $<$<CONFIG:RelWithDebInfo>:RAINBOW_DEBUG>)

add_subdirectory(App)