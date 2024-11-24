#pragma once
#ifndef RAINBOW_HEADER
#define RAINBOW_HEADER

#include "rbwpch.hpp"
#include "Platform.hpp"
#include "ANSI.hpp"

namespace rbw {
    class RBW_API Console {
    public:
        Console();
        virtual ~Console() = default;

        virtual bool Init();
        virtual void Terminate();

        virtual void Clear();

        virtual std::pair<uint16_t, uint16_t>& GetSize();

    private:
        std::pair<uint16_t, uint16_t> m_size;

    };
};

#endif