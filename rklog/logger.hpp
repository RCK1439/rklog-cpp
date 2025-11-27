#pragma once

#include "level.hpp"
#include "time.hpp"
#include "style.hpp"
#include "platform.hpp"

#include <format>
#include <fstream>
#include <iostream>
#include <print>
#if defined(RKLOG_PLATFORM_WINDOWS)
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#ifdef ERROR // Stupid thing conflicts with LogLevel::ERROR
#undef ERROR
#endif
#endif

namespace rklog {

#define RKLOG_FMT_COLOR_OUTPUT "{}{}{}" RKLOG_ESC_CODE_RESET
//                               | | |
//                               | | log message
//                               | log label
//                               log prelude

#define RKLOG_FMT_OUTPUT "{}{}"
//                         | |
//                         | log message
//                         log label

class Logger
{
public:
    constexpr Logger(std::string_view title, LogStyle style) noexcept :
        m_Title(title), m_Style(style) {}

    template<typename ... Args>
    void Info(const std::format_string<Args...> fmt, Args&& ... args)
    {
        const std::string msg = std::format(fmt, std::forward<Args>(args)...);
        LogInternal(msg, LogLevel::INFO);
    }

    template<typename ... Args>
    void Warn(const std::format_string<Args...> fmt, Args&& ... args)
    {
        const std::string msg = std::format(fmt, std::forward<Args>(args)...);
        LogInternal(msg, LogLevel::WARNING);
    }

    template<typename ... Args>
    void Error(const std::format_string<Args...> fmt, Args&& ... args)
    {
        const std::string msg = std::format(fmt, std::forward<Args>(args)...);
        LogInternal(msg, LogLevel::ERROR);
    }

    template<typename ... Args>
    void Fatal(const std::format_string<Args...> fmt, Args&& ... args)
    {
        const std::string msg = std::format(fmt, std::forward<Args>(args)...);
        LogInternal(msg, LogLevel::FATAL);
    }

protected:
    virtual void LogInternal(std::string_view msg, LogLevel lvl) = 0;

protected:
    std::string m_Title;
    LogStyle    m_Style;
};

// --- console logger ---------------------------------------------------------

class ConsoleLogger final : public Logger
{
public:
    ConsoleLogger(std::string_view title, LogStyle style) noexcept :
        Logger(title, style)
    {
#if defined(RKLOG_PLATFORM_WINDOWS)
        const HANDLE hErr = GetStdHandle(STD_ERROR_HANDLE);
        DWORD dwMode = 0;
        GetConsoleMode(hErr, &dwMode);
        dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
        SetConsoleMode(hErr, dwMode);
#endif
    }

    static inline ConsoleLogger Default(std::string_view title) noexcept
    {
        return ConsoleLogger(title, LogStyle::Default());
    }

protected:

    virtual void LogInternal(std::string_view msg, LogLevel lvl) override
    {
        const LogConfig cfg = m_Style.GetConfig(lvl);

        const std::string label = cfg.GenerateLabel(m_Title, TimeStamp::Now());
        const std::string colorPrelude = cfg.GenerateColorPrelude();

        std::println(std::cerr, RKLOG_FMT_COLOR_OUTPUT, colorPrelude, label, msg);
    }
};

// --- file logger ------------------------------------------------------------

class FileLogger final : public Logger
{
public:
    FileLogger(std::string_view fileName, std::string_view title, LogStyle style) :
        Logger(title, style), m_FileHandle(fileName.data()) {}

    static inline FileLogger Default(std::string_view fileName, std::string_view title)
    {
        return FileLogger(fileName, title, LogStyle::Default());
    }

protected:
    virtual void LogInternal(std::string_view msg, LogLevel lvl) override
    {
        const LogConfig cfg = m_Style.GetConfig(lvl);
        const std::string label = cfg.GenerateLabel(m_Title, TimeStamp::Now());

        std::println(m_FileHandle, RKLOG_FMT_OUTPUT, label, msg);
    }
    
private:
    std::ofstream m_FileHandle;
};

}
