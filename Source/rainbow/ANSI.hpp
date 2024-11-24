#pragma once
#ifndef RAINBOW_COLOR_HEADER
#define RAINBOW_COLOR_HEADER

#include "rbwpch.hpp"
#include "Platform.hpp"

namespace rbw {
    inline constexpr std::string_view Default = "\x1b[0m";
    inline constexpr std::string_view Bold = "\x1b[1m";
    inline constexpr std::string_view Underline = "\x1b[4m";
    inline constexpr std::string_view Reverse = "\x1b[7m";
    inline constexpr std::string_view Normal = "\x1b[24m\x1b[27m";

    namespace foreground {
        inline constexpr std::string_view Black = "\x1b[30m";
        inline constexpr std::string_view DarkRed = "\x1b[31m";
        inline constexpr std::string_view DarkGreen = "\x1b[32m";
        inline constexpr std::string_view DarkYellow = "\x1b[33m";
        inline constexpr std::string_view DarkBlue = "\x1b[34m";
        inline constexpr std::string_view DarkMagenta = "\x1b[35m";
        inline constexpr std::string_view DarkCyan = "\x1b[36m";
        inline constexpr std::string_view DarkWhite = "\x1b[37m";
        inline constexpr std::string_view BrightBlack = "\x1b[90m";
        inline constexpr std::string_view BrightRed = "\x1b[91m";
        inline constexpr std::string_view BrightGreen = "\x1b[92m";
        inline constexpr std::string_view BrightYellow = "\x1b[93m";
        inline constexpr std::string_view BrightBlue = "\x1b[94m";
        inline constexpr std::string_view BrightMagenta = "\x1b[95m";
        inline constexpr std::string_view BrightCyan = "\x1b[96m";
        inline constexpr std::string_view White = "\x1b[97m";
    };

    namespace background {
        inline constexpr std::string_view Black = "\x1b[40m";
        inline constexpr std::string_view DarkRed = "\x1b[41m";
        inline constexpr std::string_view DarkGreen = "\x1b[42m";
        inline constexpr std::string_view DarkYellow = "\x1b[43m";
        inline constexpr std::string_view DarkBlue = "\x1b[44m";
        inline constexpr std::string_view DarkMagenta = "\x1b[45m";
        inline constexpr std::string_view DarkCyan = "\x1b[46m";
        inline constexpr std::string_view DarkWhite = "\x1b[47m";
        inline constexpr std::string_view BrightBlack = "\x1b[100m";
        inline constexpr std::string_view BrightRed = "\x1b[101m";
        inline constexpr std::string_view BrightGreen = "\x1b[102m";
        inline constexpr std::string_view BrightYellow = "\x1b[103m";
        inline constexpr std::string_view BrightBlue = "\x1b[104m";
        inline constexpr std::string_view BrightMagenta = "\x1b[105m";
        inline constexpr std::string_view BrightCyan = "\x1b[106m";
        inline constexpr std::string_view White = "\x1b[107m";
    };
};

#endif