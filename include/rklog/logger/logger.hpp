#pragma once

#include "../Config/Level.hpp"

#include <format>
#include <optional>
#include <string>

namespace rklog {

class Logger
{
public:
    constexpr Logger() = default;
    constexpr Logger(std::string_view title) noexcept :
        m_Title(title) {}

    template<typename ... Args>
    void Debug(const std::format_string<Args...> fmt, Args&& ... args)
    {
        const std::string msg = std::format(fmt, std::forward<Args>(args)...);
        LogInternal(msg, LogLevel::LOG_DEBUG);
    }

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
    virtual void LogInternal(std::string_view msg, LogLevel level) = 0;

protected:
    std::optional<std::string> m_Title = std::nullopt;
};

}