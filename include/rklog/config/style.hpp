#pragma once

#include "config.hpp"
#include "level.hpp"

#include "../core/platform.hpp"

namespace rklog {

class LogStyle final
{
public:
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

    template<LogLevel lvl>
    [[nodiscard]] constexpr LogStyleBuilder& SetConfig(const LogConfig& cfg) noexcept
    {
        switch (lvl)
        {
            case LogLevel::LOG_INFO:
                m_Style.m_CfgInfo = cfg;
                break;
            case LogLevel::LOG_WARNING:
                m_Style.m_CfgWarning = cfg;
                break;
            case LogLevel::LOG_ERROR:
                m_Style.m_CfgError = cfg;
                break;
            case LogLevel::LOG_FATAL:
                m_Style.m_CfgFatal = cfg;
                break;
        }

        return *this;
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
    .SetConfig<LogLevel::LOG_INFO>(INFO_CFG)
    .SetConfig<LogLevel::LOG_WARNING>(WARNING_CFG)
    .SetConfig<LogLevel::LOG_ERROR>(ERROR_CFG)
    .SetConfig<LogLevel::LOG_FATAL>(FATAL_CFG)
    .Build();

}
