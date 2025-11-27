#pragma once

#include "config.hpp"
#include "level.hpp"
#include "platform.hpp"

namespace rklog {

/**
 * Class representing the style of the log messages
 */
class LogStyle final
{
public:
    /**
     * Creates an instance of `LogStyle` with different configurations for
     * different log severities
     *
     * @param cfgInfo
     *      The configuration for info log level
     * @param cfgWarning
     *      The configuration for warning log level
     * @param cfgError
     *      The configuration for error log level
     * @param cfgFatal
     *      The configuration for fatal log level
     */
    constexpr LogStyle(LogConfig cfgInfo, LogConfig cfgWarning, LogConfig cfgError, LogConfig cfgFatal) noexcept :
        m_CfgInfo(cfgInfo), m_CfgWarning(cfgWarning), m_CfgError(cfgError), m_CfgFatal(cfgFatal) {}

    /**
     * Creates the default `LogStyle`
     *
     * @return
     *      The default style of the logs
     */
    static constexpr LogStyle Default() noexcept
    {
        return LogStyle(
            LogConfig::DefaultFor<LogLevel::INFO>(),
            LogConfig::DefaultFor<LogLevel::WARNING>(),
            LogConfig::DefaultFor<LogLevel::ERROR>(),
            LogConfig::DefaultFor<LogLevel::FATAL>()
        );
    }

    /**
     * Gets the configuration for `lvl`
     *
     * @param lvl
     *      The log level severity corresponding to the log configuration
     */
    constexpr LogConfig GetConfig(LogLevel lvl) const noexcept
    {
        switch (lvl)
        {
        case LogLevel::INFO:
            return m_CfgInfo;
        case LogLevel::WARNING:
            return m_CfgWarning;
        case LogLevel::ERROR:
            return m_CfgError;
        case LogLevel::FATAL:
            return m_CfgFatal;
        }

        RKLOG_UNREACHABLE();
    }

private:
    LogConfig m_CfgInfo;    // The configuration for info logs
    LogConfig m_CfgWarning; // The configuration for warning logs
    LogConfig m_CfgError;   // The configuration for error logs
    LogConfig m_CfgFatal;   // The configuration for fatal logs
};
    
}
