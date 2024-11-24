#pragma once
#ifndef RAINBOW_PLATFORM_HEADER
#define RAINBOW_PLATFORM_HEADER

#include "rbwpch.hpp"

#if defined(RAINBOW_SHARED_LIBRARY)
    #if defined(RAINBOW_SHARED_BUILD)
        #if defined(_MSC_VER)
            #define RBW_API __declspec(dllexport)
        #else
            #define RBW_API __attribute__((visibility("default")))
        #endif
    #else
        #if defined(_MSC_VER)
            #define RBW_API __declspec(dllimport)
        #else
            #define RBW_API __attribute__((visibility("hidden")))
        #endif
    #endif
#else
    #define RBW_API
#endif

#define RBW_BYTE(x) (1 << x)
#define RBW_SUCCESS true
#define RBW_FAILURE false
#define RBW_RESULT bool

#if defined(RAINBOW_DEBUG)
    #define RBW_LOG(x) { std::cout << "[rainbow] [log] " << x << '\n'; }
    #define RBW_ERROR(x) { std::cerr << "[rainbow] [error] " << x << '\n'; }
    #define RBW_FATAL(x) { std::cerr << "[rainbow] [fatal] " << x << '\n'; std::cin.get(); }
    #define RBW_ASSERT(x) { if(x != RBW_SUCCESS) { RBW_FATAL(std::string(__FILE__) + " " + std::to_string(__LINE__)); } }
    #define RBW_STRINGIFY(x) #x
#else
    #define RBW_LOG(x)
    #define RBW_ERROR(x)
    #define RBW_FATAL(x)
    #define RBW_ASSERT(x)
    #define RBW_STRINGIFY(x)
#endif

#if defined(_WIN32)
    #define RAINBOW_WIN32

    #define NOMINMAX
    #include <windows.h>
#elif defined(__unix__)
    #define RAINBOW_UNIX

    #include <sys/ioctl.h>
    #include <unistd.h>
#else
    #error "[rainbow] [fatal] not supported platform"
#endif

#endif