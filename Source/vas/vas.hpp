#pragma once
#ifndef VAS_HEADER
#define VAS_HEADER

#include "vaspch.hpp"

#ifdef VAS_SHARED_LIBRARY
    #ifdef VAS_SHARED_BUILD
        #ifdef _MSC_VER
            #define VAS_API __declspec(dllexport)
        #else
            #define VAS_API __attribute__((visibility("default")))
        #endif
    #else
        #ifdef _MSC_VER
            #define VAS_API __declspec(dllimport)
        #else
            #define VAS_API __attribute__((visibility("hidden")))
        #endif
    #endif
#else
    #define VAS_API
#endif

#include <vulkan/vulkan.h>

#define VAS_BYTE(x) (1 << x)

#ifdef VAS_DEBUG
    #define VAS_LOG(x) { std::cout << "[vas] [log] " << x << '\n'; }
    #define VAS_ERROR(x) { std::cerr << "[vas] [error] " << x << '\n'; }
    #define VAS_FATAL(x) { std::cerr << "[vas] [fatal] " << x << '\n'; std::cin.get(); }
    #define VAS_ASSERT(x) { if(x != VK_SUCCESS) { VAS_FATAL(std::string(__FILE__) + " " + std::to_string(__LINE__)); } }
    #define VAS_STRINGIFY(x) #x
#else
    #define VAS_LOG(x)
    #define VAS_ERROR(x)
    #define VAS_FATAL(x)
    #define VAS_ASSERT(x)
    #define VAS_STRINGIFY(x)
#endif

#include "Instance.hpp"
#include "PhysicalDevice.hpp"

#endif