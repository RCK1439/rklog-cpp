#pragma once

#include "../config/style.hpp"

#include <string>

namespace rklog {

// --- format specifiers ------------------------------------------------------

#define RKLOG_FMT_COLOR_OUTPUT "{}{}{}" RKLOG_ESC_CODE_RESET
//                               | | |
//                               | | log message
//                               | log label
//                               log prelude

#define RKLOG_FMT_OUTPUT "{}{}"
//                         | |
//                         | log message
//                         log label

// --- type definitions -------------------------------------------------------

class Logger
{
public:
    constexpr explicit Logger(std::string_view title) noexcept :
        m_Title(title) {}

    constexpr explicit Logger(std::string_view title, LogStyle style) noexcept :
        m_Title(title), m_Style(style) {}

    template<typename ... Args>
    void Info(const std::format_string<Args...> fmt, Args&& ... args)
    {
        const std::string msg = std::format(fmt, std::forward<Args>(args)...);
        LogInternal(msg, LogLevel::LOG_INFO);
    }

    template<typename ... Args>
    void Warn(const std::format_string<Args...> fmt, Args&& ... args)
    {
        const std::string msg = std::format(fmt, std::forward<Args>(args)...);
        LogInternal(msg, LogLevel::LOG_WARNING);
    }

    template<typename ... Args>
    void Error(const std::format_string<Args...> fmt, Args&& ... args)
    {
        const std::string msg = std::format(fmt, std::forward<Args>(args)...);
        LogInternal(msg, LogLevel::LOG_ERROR);
    }

    template<typename ... Args>
    void Fatal(const std::format_string<Args...> fmt, Args&& ... args)
    {
        const std::string msg = std::format(fmt, std::forward<Args>(args)...);
        LogInternal(msg, LogLevel::LOG_FATAL);
    }

protected:
    virtual void LogInternal(std::string_view msg, LogLevel lvl) = 0;

protected:
    const std::string m_Title;
    const LogStyle    m_Style;
};

}