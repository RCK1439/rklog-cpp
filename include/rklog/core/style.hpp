#pragma once

#include "../config/config.hpp"
#include "level.hpp"
#include "platform.hpp"

namespace rklog {

/**
 * Class representing the style of the log messages
 */
class LogStyle final
{
public:
    constexpr static LogStyle Create() noexcept
    {
        return LogStyle();
    }

    template<LogLevel lvl>
    constexpr LogStyle& SetConfig(const LogConfig& cfg) noexcept
    {
        switch (lvl)
        {
            case LogLevel::LOG_INFO:
                m_CfgInfo = cfg;
                break;
            case LogLevel::LOG_WARNING:
                m_CfgWarning = cfg;
                break;
            case LogLevel::LOG_ERROR:
                m_CfgError = cfg;
                break;
            case LogLevel::LOG_FATAL:
                m_CfgFatal = cfg;
                break;
        }

        return *this;
    }

    constexpr LogStyle&& Build() noexcept
    {
        return std::move(*this);
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
            case LogLevel::LOG_INFO: return m_CfgInfo;
            case LogLevel::LOG_WARNING: return m_CfgWarning;
            case LogLevel::LOG_ERROR: return m_CfgError;
            case LogLevel::LOG_FATAL: return m_CfgFatal;
        }

        RKLOG_UNREACHABLE();
    }

private:
    constexpr LogStyle() = default;

private:
    LogConfig m_CfgInfo    = defaults::INFO_CFG;    // The configuration for info logs
    LogConfig m_CfgWarning = defaults::WARNING_CFG; // The configuration for warning logs
    LogConfig m_CfgError   = defaults::ERROR_CFG;   // The configuration for error logs
    LogConfig m_CfgFatal   = defaults::FATAL_CFG;   // The configuration for fatal logs

    friend class Logger;
};
    
}

namespace rklog::defaults {

constexpr LogStyle DEFAULT_STYLE = LogStyle::Create()
    .SetConfig<LogLevel::LOG_INFO>(INFO_CFG)
    .SetConfig<LogLevel::LOG_WARNING>(WARNING_CFG)
    .SetConfig<LogLevel::LOG_ERROR>(ERROR_CFG)
    .SetConfig<LogLevel::LOG_FATAL>(FATAL_CFG)
    .Build();

}
