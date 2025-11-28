#pragma once

#include "core/logger.hpp"

namespace rklog {

void InitGlobalLogging(std::string_view title);
void InitGlobalLogging(std::string_view title, LogStyle style);

template<typename ... Args>
void LogInfo(std::format_string<Args...> fmt, Args&& ...args);
template<typename ... Args>
void LogWarning(std::format_string<Args...> fmt, Args&& ...args);
template<typename ... Args>
void LogError(std::format_string<Args...> fmt, Args&& ...args);
template<typename ... Args>
void LogFatal(std::format_string<Args...> fmt, Args&& ...args);

#if defined(RKLOG_IMPLEMENTATION)

static ConsoleLogger s_GlobalLogger;

void InitGlobalLogging(std::string_view title)
{
    s_GlobalLogger = ConsoleLogger(title);
}

void InitGlobalLogging(std::string_view title, LogStyle style)
{
    s_GlobalLogger = ConsoleLogger(title, style);
}

template<typename ... Args>
void LogInfo(std::format_string<Args...> fmt, Args&& ...args)
{
    s_GlobalLogger.Info(fmt, args...);
}

template<typename ... Args>
void LogWarning(std::format_string<Args...> fmt, Args&& ...args)
{
    s_GlobalLogger.Warn(fmt, args...);
}

template<typename ... Args>
void LogError(std::format_string<Args...> fmt, Args&& ...args)
{
    s_GlobalLogger.Error(fmt, args...);
}

template<typename ... Args>
void LogFatal(std::format_string<Args...> fmt, Args&& ...args)
{
    s_GlobalLogger.Fatal(fmt, args...);
}

#endif

}
