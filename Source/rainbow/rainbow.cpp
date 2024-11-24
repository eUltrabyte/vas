#include "rainbow.hpp"

namespace rbw {
    Console::Console() 
    : m_size({ std::numeric_limits<uint16_t>::max(), std::numeric_limits<uint16_t>::max() }) { }

    bool Console::Init() {
        #if defined(RAINBOW_WIN32)
            void* handle = GetStdHandle(STD_OUTPUT_HANDLE);
            unsigned long mode = 0;
            GetConsoleMode(handle, &mode);
            mode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
            SetConsoleMode(handle, mode);

            CONSOLE_SCREEN_BUFFER_INFO screenBufferInfo { };
            GetConsoleScreenBufferInfo(handle, &screenBufferInfo);
            m_size = { screenBufferInfo.srWindow.Right - screenBufferInfo.srWindow.Left + 1, screenBufferInfo.srWindow.Bottom - screenBufferInfo.srWindow.Top + 1 };
        #elif defined(RAINBOW_UNIX)
            #ifdef TIOCGSIZE
                struct ttysize size;
                ioctl(STDOUT_FILENO, TIOCGSIZE, &size);
                m_size = { size.ts_cols, size.ts_lines };
            #else
                struct winsize size;
                ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
                m_size = { size.ws_col, size.ws_row };
            #endif
        #endif

        RBW_LOG("console size - " + std::to_string(m_size.first) + "/" + std::to_string(m_size.second));

        if(m_size.first == std::numeric_limits<uint16_t>::max() || m_size.second == std::numeric_limits<uint16_t>::max()) {
            RBW_ASSERT(RBW_FAILURE);
            return RBW_FAILURE;
        } else {
            return RBW_SUCCESS;
        }
    }

    void Console::Terminate() {
        #if defined(RAINBOW_WIN32)
            void* handle = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleMode(handle, ENABLE_PROCESSED_OUTPUT);
        #endif
    }

    void Console::Clear() {
        std::cout << rbw::Default << rbw::Normal << "\x1b[2J\x1b[3J\x1b[H";
    }

    std::pair<uint16_t, uint16_t>& Console::GetSize() {
        return m_size;
    }
};