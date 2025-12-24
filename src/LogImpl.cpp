#pragma once

#include "rklog/Logger/BasicLogger.hpp"
#include "rklog/Logger/ColorLogger.hpp"

#include "rklog/Core/Platform.hpp"
#include "rklog/Core/Time.hpp"

#include <iostream>

#if defined(RKLOG_PLATFORM_WINDOWS)
#include <Windows.h>

static void EnableVirtualConsole()
{
    static bool enabled = false;
    if (enabled)
    {
        return;
    }

    const ::HANDLE hErr = ::GetStdHandle(STD_ERROR_HANDLE);
    ::DWORD dwMode = 0;
    ::GetConsoleMode(hErr, &dwMode);
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    ::SetConsoleMode(hErr, dwMode);

    enabled = true;
}

#endif // Windows configuration

namespace rklog {

void BasicLogger::LogInternal(std::string_view msg, LogLevel level)
{
    std::string logMessage = m_Title.has_value() ? std::format("[{}]:", m_Title.value()) : "";
    const auto cfg = m_Style.GetConfig(level);
    
    const auto tag = cfg.GetTag();
    logMessage += std::format("[{}]:", tag);

    const auto timeStamp = TimeStamp::Now();
    logMessage += std::format("[{}]: {}", timeStamp, msg);

    std::println(std::cerr, "{}", logMessage);
}

void ColorLogger::LogInternal(std::string_view msg, LogLevel level)
{
    std::string logMessage;
    const auto cfg = m_Style.GetConfig(level);

    bool fgColored = false;
    if (const auto fgColor = cfg.GetForegroundColor())
    {
        const auto color = fgColor.value();
        logMessage += std::format("\033[38;2;{};{};{}", color.r, color.g, color.b);
        fgColored = true;
    }

    if (const auto bgColor = cfg.GetBackgroundColor())
    {
        const auto color = bgColor.value();
        logMessage += std::format(";48;2;{};{};{}m", color.r, color.g, color.b);
    }
    else if (fgColored)
    {
        logMessage += 'm';
    }

    logMessage += m_Title.has_value() ? std::format("[{}]:", m_Title.value()) : "";

    const auto tag = cfg.GetTag();
    logMessage += std::format("[{}]:", tag);

    const auto timeStamp = TimeStamp::Now();
    logMessage += std::format("[{}]: {}\033[0m", timeStamp, msg);

#if defined(RKLOG_PLATFORM_WINDOWS)
    EnableVirtualConsole();
#endif

    std::println(std::cerr, "{}", logMessage);
}
    
}