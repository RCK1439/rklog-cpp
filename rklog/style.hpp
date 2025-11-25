#pragma once

#include "config.hpp"
#include "level.hpp"
#include "platform.hpp"

namespace rklog {

class LogStyle final
{
public:
    constexpr LogStyle(LogConfig cfgInfo, LogConfig cfgWarning, LogConfig cfgError, LogConfig cfgFatal) noexcept :
        m_CfgInfo(cfgInfo), m_CfgWarning(cfgWarning), m_CfgError(cfgError), m_CfgFatal(cfgFatal) {}

    static constexpr LogStyle Default() noexcept
    {
        return LogStyle(LogConfig::DefaultInfo(), LogConfig::DefaultWarning(), LogConfig::DefaultError(), LogConfig::DefaultFatal());
    }

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
    LogConfig m_CfgInfo;
    LogConfig m_CfgWarning;
    LogConfig m_CfgError;
    LogConfig m_CfgFatal;
};
    
}