#pragma once

#include "Config.hpp"

#include "../Core/Platform.hpp"

namespace rklog {

class LogStyle final
{
public:
    constexpr const LogConfig& GetConfig(LogLevel lvl) const noexcept
    {
        switch (lvl)
        {
            case LogLevel::LOG_DEBUG: return m_CfgDebug;
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
    LogConfig m_CfgDebug   = defaults::DEBUG_CFG;
    LogConfig m_CfgInfo    = defaults::INFO_CFG;
    LogConfig m_CfgWarning = defaults::WARNING_CFG;
    LogConfig m_CfgError   = defaults::ERROR_CFG;
    LogConfig m_CfgFatal   = defaults::FATAL_CFG;

    friend class LogStyleBuilder;
    friend class Logger;
};

class LogStyleBuilder
{
public:
    LogStyleBuilder(const LogStyleBuilder&) = delete;
    LogStyleBuilder(LogStyleBuilder&&) = delete;

    [[nodiscard]] constexpr LogStyleBuilder& SetConfig(const LogConfig& cfg) noexcept
    {
        switch (cfg.GetLevel())
        {
            case LogLevel::LOG_DEBUG:
                m_Style.m_CfgDebug = cfg;
                return *this;
            case LogLevel::LOG_INFO:
                m_Style.m_CfgInfo = cfg;
                return *this;
            case LogLevel::LOG_WARNING:
                m_Style.m_CfgWarning = cfg;
                return *this;
            case LogLevel::LOG_ERROR:
                m_Style.m_CfgError = cfg;
                return *this;
            case LogLevel::LOG_FATAL:
                m_Style.m_CfgFatal = cfg;
                return *this;
        }

        RKLOG_UNREACHABLE();
    }

    [[nodiscard]] constexpr LogStyle&& Build() noexcept
    {
        return std::move(m_Style);
    }

private:
    constexpr LogStyleBuilder() noexcept = default;

private:
    LogStyle m_Style;

    friend constexpr LogStyleBuilder InitBuildStyle() noexcept;
};

[[nodiscard]] constexpr LogStyleBuilder InitBuildStyle() noexcept
{
    return LogStyleBuilder();
}
    
}

namespace rklog::defaults {

constexpr LogStyle DEFAULT_STYLE = InitBuildStyle()
    .SetConfig(DEBUG_CFG)
    .SetConfig(INFO_CFG)
    .SetConfig(WARNING_CFG)
    .SetConfig(ERROR_CFG)
    .SetConfig(FATAL_CFG)
    .Build();

}
