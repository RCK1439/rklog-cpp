#pragma once

#include "Logger/BasicLogger.hpp"
#include "Logger/ColorLogger.hpp"

#include <exception> // Provides std::terminate()

namespace rklog {

/**
 * Gets the global instance of a basic logger
 *
 * @param[in] title
 *      The title to give the basic logger
 *
 * @return
 *      The global basic logger instance
 */
BasicLogger& GetBasicLogger(std::string_view title = "global") noexcept;

/**
 * Gets the global instance of a color logger
 *
 * @param[in] title
 *      The title to give the global logger
 *
 * @return
 *      The global color logger instance
 */
ColorLogger& GetColorLogger(std::string_view title = "global") noexcept;

/**
 * Asserts that the given expression results to `true`. In the event that the
 * expression results to `false` a message is logged as "fatal" to the given
 * logger and the program is terminated via std::terminate()
 *
 * @param[in] logger
 *      The logger to log to if the assertion fails
 * @param[in] expr
 *      The expression to assert on
 * @param[in] fmt
 *      The format specifier of the log message
 * @param[in] args
 *      The arguments for the format specifier
 */
template<typename ... Args>
void Assert(Logger& logger, bool expr, std::format_string<Args...> fmt, Args&& ... args) noexcept
{
    if (expr)
        return;

    logger.Fatal(fmt, std::forward<Args>(args)...);
    std::terminate();
}

/**
 * Asserts that the given expression results to `true`. In the event that the
 * expression results to `false` a message is logged as "fatal" to the given
 * logger and the program is terminated via std::terminate().
 *
 * Unlike the previous `Assert` function, this one requires a function name,
 * file name and a file line for where the error occured. This makes the log
 * message provide additional information on where the error occured.
 *
 * This is intended to be used in macros where '__func__', '__FILE__' and
 * '__LINE__' can be easily provided
 *
 * @param[in] logger
 *      The logger to log to if the assertion fails
 * @param[in] expr
 *      The expression to assert on
 * @param[in] funcName
 *      The name of the function where the assert statement exists in code
 * @param[in] fileName
 *      The name of the file where the assert statement exists in code
 * @param[in] line
 *      The line in the source file where the assert statement exists in code
 * @param[in] fmt
 *      The format specifier of the log message
 * @param[in] args
 *      The arguments for the format specifier
 */
template<typename ... Args>
void DetailedAssert(Logger& logger, bool expr, std::string_view funcName, std::string_view fileName, uint32_t line, std::format_string<Args...> fmt, Args&& ... args) noexcept
{
    if (expr)
        return;

    const std::string assertionFailedMessage = std::format("Assertion failed in {}: {}:{}: ", funcName, fileName, line);
    const std::string logMessage = std::format(fmt, std::forward<Args>(args)...);
    logger.Fatal("{}{}", assertionFailedMessage, logMessage);
    std::terminate();
}

}
