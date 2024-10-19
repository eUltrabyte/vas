cmake_minimum_required(VERSION 3.17)
project(vas)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(Vulkan REQUIRED)

set(VAS_SOURCE
    Source/vas/vas.hpp
    Source/vas/Instance.hpp
    Source/vas/Instance.cpp
    Source/vas/PhysicalDevice.hpp
    Source/vas/PhysicalDevice.cpp
)

option(VAS_SHARED_LIBRARY "vas build using shared libraries" OFF)
option(VAS_SHARED_BUILD "vas build shared libraries files" OFF)
option(VAS_BUILD_APP "vas build example app" ON)

if(VAS_SHARED_LIBRARY)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DVAS_SHARED_LIBRARY")

    if(VAS_SHARED_BUILD)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DVAS_SHARED_BUILD")
    endif()

    add_library(${PROJECT_NAME} SHARED ${VAS_SOURCE})
else()
    add_library(${PROJECT_NAME} STATIC ${VAS_SOURCE})
endif()

target_precompile_headers(${PROJECT_NAME} PUBLIC Source/vas/vaspch.hpp Source/vas/vaspch.cpp)
target_compile_definitions(${PROJECT_NAME} PUBLIC $<$<CONFIG:Debug>:VAS_DEBUG> $<$<CONFIG:RelWithDebInfo>:VAS_DEBUG>)
target_link_libraries(${PROJECT_NAME} PUBLIC Vulkan::Vulkan)

if(VAS_BUILD_APP)
    add_subdirectory(App)
endif()