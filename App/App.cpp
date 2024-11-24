#include <rainbow/rainbow.hpp>

auto main(int argc, char** argv) -> int {
    RBW_RESULT result = RBW_SUCCESS;
    std::unique_ptr<rbw::Console> console = std::make_unique<rbw::Console>();
    result = console->Init();
    
    std::cout << rbw::Default << "test\n";
    std::cout << rbw::Bold << "test\n";
    std::cout << rbw::Underline << "test\n";
    std::cout << rbw::Reverse << "test\n";
    std::cout << rbw::Normal << "test\n";

    std::cout << rbw::foreground::Black << "test\n";
    std::cout << rbw::foreground::DarkRed << "test\n";
    std::cout << rbw::foreground::DarkGreen << "test\n";
    std::cout << rbw::foreground::DarkYellow << "test\n";
    std::cout << rbw::foreground::DarkBlue << "test\n";
    std::cout << rbw::foreground::DarkMagenta << "test\n";
    std::cout << rbw::foreground::DarkCyan << "test\n";
    std::cout << rbw::foreground::DarkWhite << "test\n";

    std::cout << rbw::foreground::BrightBlack << "test\n";
    std::cout << rbw::foreground::BrightRed << "test\n";
    std::cout << rbw::foreground::BrightGreen << "test\n";
    std::cout << rbw::foreground::BrightYellow << "test\n";
    std::cout << rbw::foreground::BrightBlue << "test\n";
    std::cout << rbw::foreground::BrightMagenta << "test\n";
    std::cout << rbw::foreground::BrightCyan << "test\n";
    std::cout << rbw::foreground::White << "test\n";

    std::cout << rbw::background::Black << "test\n";
    std::cout << rbw::background::DarkRed << "test\n";
    std::cout << rbw::background::DarkGreen << "test\n";
    std::cout << rbw::background::DarkYellow << "test\n";
    std::cout << rbw::background::DarkBlue << "test\n";
    std::cout << rbw::background::DarkMagenta << "test\n";
    std::cout << rbw::background::DarkCyan << "test\n";
    std::cout << rbw::background::DarkWhite << "test\n";

    std::cout << rbw::background::BrightBlack << "test\n";
    std::cout << rbw::background::BrightRed << "test\n";
    std::cout << rbw::background::BrightGreen << "test\n";
    std::cout << rbw::background::BrightYellow << "test\n";
    std::cout << rbw::background::BrightBlue << "test\n";
    std::cout << rbw::background::BrightMagenta << "test\n";
    std::cout << rbw::background::BrightCyan << "test\n";
    std::cout << rbw::background::White << "test\n";

    console->Terminate();
    return result;
}