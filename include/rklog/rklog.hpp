#pragma once

#include "core/logger.hpp"

#include <string_view>
#include <format>

namespace rklog {

/**
 * Initializes a basic global console logger with default styling
 *
 * @param title
 *      The title of the global logger
 */
void InitGlobalLogging(std::string_view title);

/**
 * Initializes a basic global console logger with custom styling
 *
 * @param title
 *      The title of the global logger
 * @param style
 *      The style of the log messages
 */
void InitGlobalLogging(std::string_view title, LogStyle style);

/**
 * Uses the global console logger to log a message with info severity to the
 * console
 *
 * @param fmt
 *      The format specifier of the message
 * @param args
 *      The variadic arguments according to the format specifier
 */
template<typename ... Args>
void LogInfo(const std::format_string<Args...> fmt, Args&& ... args)
{
    extern std::shared_ptr<ConsoleLogger> g_GlobalLogger;
    g_GlobalLogger->Info(fmt, std::forward<Args>(args)...);
}

/**
 * Uses the global console logger to log a message with warning severity to the
 * console
 *
 * @param fmt
 *      The format specifier of the message
 * @param args
 *      The variadic arguments according to the format specifier
 */
template<typename ... Args>
void LogWarning(const std::format_string<Args...> fmt, Args&& ... args)
{
    extern std::shared_ptr<ConsoleLogger> g_GlobalLogger;
    g_GlobalLogger->Warn(fmt, std::forward<Args>(args)...);
}

/**
 * Uses the global console logger to log a message with error severity to the
 * console
 *
 * @param fmt
 *      The format specifier of the message
 * @param args
 *      The variadic arguments according to the format specifier
 */
template<typename ... Args>
void LogError(const std::format_string<Args...> fmt, Args&& ... args)
{
    extern std::shared_ptr<ConsoleLogger> g_GlobalLogger;
    g_GlobalLogger->Error(fmt, std::forward<Args>(args)...);
}

/**
 * Uses the global console logger to log a message with fatal severity to the
 * console
 *
 * @param fmt
 *      The format specifier of the message
 * @param args
 *      The variadic arguments according to the format specifier
 */
template<typename ... Args>
void LogFatal(const std::format_string<Args...> fmt, Args&& ... args)
{
    extern std::shared_ptr<ConsoleLogger> g_GlobalLogger;
    g_GlobalLogger->Fatal(fmt, std::forward<Args>(args)...);
}

}
