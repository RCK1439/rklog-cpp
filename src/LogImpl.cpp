#pragma once

#include "rklog/Logger/BasicLogger.hpp"
#include "rklog/Logger/ColorLogger.hpp"
#include "rklog/Logger/FileLogger.hpp"

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

static std::string BuildLogMessage(std::optional<std::string> title, const LogConfig& cfg, std::string_view msg)
{
    const TimeStamp ts = TimeStamp::Now();

    std::string logMessage = title.has_value() ? std::format("[{}]:", title.value()) : "";
    logMessage += std::format("[{}]:[{}]: {}", cfg.GetTag(), ts, msg);

    return logMessage;
}

static std::string ColorizeString(std::optional<Color> fg, std::optional<Color> bg, std::string_view str)
{
    std::string colorCode;
    
    bool fgColored = false;
    if (fg.has_value())
    {
        const auto color = fg.value();
        colorCode += std::format("\033[38;2;{};{};{}", color.r, color.g, color.b);
        fgColored = true;
    }

    if (bg.has_value())
    {
        const auto color = bg.value();
        colorCode += std::format(";48;2;{};{};{}m", color.r, color.g, color.b);
    }
    else if (fgColored)
    {
        colorCode += 'm';
    }

    return std::format("{}{}{}", colorCode, str, "\033[0m");
}

void BasicLogger::LogInternal(std::string_view msg, LogLevel level)
{
    const auto cfg = m_Style.GetConfig(level);
    const auto logMessage = BuildLogMessage(m_Title, cfg, msg);

    std::println(std::cerr, "{}", logMessage);
}

void ColorLogger::LogInternal(std::string_view msg, LogLevel level)
{
    const auto cfg = m_Style.GetConfig(level);
    const auto logMessage = BuildLogMessage(m_Title, cfg, msg);
    const auto coloredLogMessage = ColorizeString(cfg.GetForegroundColor(), cfg.GetBackgroundColor(), logMessage);

#if defined(RKLOG_PLATFORM_WINDOWS)
    EnableVirtualConsole();
#endif

    std::println(std::cerr, "{}", coloredLogMessage);
}

void FileLogger::LogInternal(std::string_view msg, LogLevel level)
{
    const auto cfg = m_Style.GetConfig(level);
    const auto logMessage = BuildLogMessage(m_Title, cfg, msg);
    std::println(m_FileHandle, "{}", logMessage);
    
    if (m_WriteToStdErr)
    {
#if defined(RKLOG_PLATFORM_WINDOWS)
        EnableVirtualConsole();
#endif
        const auto coloredLogMessage = ColorizeString(cfg.GetForegroundColor(), cfg.GetBackgroundColor(), logMessage);
        std::println(std::cerr, "{}", coloredLogMessage);
    }
}

ColorLogger& GetColorLogger(std::string_view title = "global")
{
    static ColorLogger colorLogger(title);
    return colorLogger;
}

BasicLogger& GetBasicLogger(std::string_view title = "global")
{
    static BasicLogger basicLogger(title);
    return basicLogger;
}

}