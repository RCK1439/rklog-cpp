#include "../include/rklog/logger/console_logger.hpp"
#include "../include/rklog/core/platform.hpp"

#include <iostream>
#include <print>

#if defined(RKLOG_PLATFORM_WINDOWS)
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#define ENABLE_COLORED_CONSOLE() EnableColoredConsoleWindows()
#else
#define ENABLE_COLORED_CONSOLE() (void)0
#endif

namespace rklog {

    static void EnableColoredConsoleWindows() noexcept
    {
        const HANDLE hErr = GetStdHandle(STD_ERROR_HANDLE);
        DWORD dwMode = 0;
        GetConsoleMode(hErr, &dwMode);
        dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
        SetConsoleMode(hErr, dwMode);
    }

    ConsoleLogger::ConsoleLogger(std::string_view title) noexcept :
        Logger(title)
    {
        ENABLE_COLORED_CONSOLE();
    }

    ConsoleLogger::ConsoleLogger(std::string_view title, LogStyle style) noexcept :
        Logger(title, style)
    {
        ENABLE_COLORED_CONSOLE();
    }

    void ConsoleLogger::LogInternal(std::string_view msg, LogLevel lvl)
    {
        const LogConfig cfg = m_Style.GetConfig(lvl);

        const std::string label = cfg.GenerateLabel(m_Title, TimeStamp::Now());
        const std::string colorPrelude = cfg.GenerateColorPrelude();

#if defined(RKLOG_COMPILER_GCC)
        std::cerr << std::format(RKLOG_FMT_COLOR_OUTPUT, colorPrelude, label, msg) << '\n';
#else
        std::println(std::cerr, RKLOG_FMT_COLOR_OUTPUT, colorPrelude, label, msg);
#endif
    }

}