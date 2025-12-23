#pragma once

#include "config.hpp"

#include "../core/platform.hpp"

namespace rklog {

class LogStyle final
{
public:
    template<LogLevel TLevel>
    constexpr LogConfig<TLevel> GetConfig() const noexcept
    {
        switch (TLevel)
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
    LogConfig<LogLevel::LOG_DEBUG> m_CfgDebug = defaults::DEBUG_CFG;
    LogConfig<LogLevel::LOG_INFO> m_CfgInfo    = defaults::INFO_CFG;
    LogConfig<LogLevel::LOG_WARNING> m_CfgWarning = defaults::WARNING_CFG;
    LogConfig<LogLevel::LOG_ERROR> m_CfgError   = defaults::ERROR_CFG;
    LogConfig<LogLevel::LOG_FATAL> m_CfgFatal   = defaults::FATAL_CFG;

    friend class LogStyleBuilder;
    friend class Logger;
};

class LogStyleBuilder
{
public:
    LogStyleBuilder(const LogStyleBuilder&) = delete;
    LogStyleBuilder(LogStyleBuilder&&) = delete;

    [[nodiscard]] constexpr LogStyleBuilder& SetDebugConfig(const LogConfig<LogLevel::LOG_DEBUG>& cfg) noexcept
    {
        m_Style.m_CfgDebug = cfg;
        return *this;
    }

    [[nodiscard]] constexpr LogStyleBuilder& SetInfoConfig(const LogConfig<LogLevel::LOG_INFO>& cfg) noexcept
    {
        m_Style.m_CfgInfo = cfg;
        return *this;
    }

    [[nodiscard]] constexpr LogStyleBuilder& SetWarningConfig(const LogConfig<LogLevel::LOG_WARNING>& cfg) noexcept
    {
        m_Style.m_CfgWarning = cfg;
        return *this;
    }

    [[nodiscard]] constexpr LogStyleBuilder& SetErrorConfig(const LogConfig<LogLevel::LOG_ERROR>& cfg) noexcept
    {
        m_Style.m_CfgError = cfg;
        return *this;
    }

    [[nodiscard]] constexpr LogStyleBuilder& SetFatalConfig(const LogConfig<LogLevel::LOG_FATAL>& cfg) noexcept
    {
        m_Style.m_CfgFatal = cfg;
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
    .SetDebugConfig(DEBUG_CFG)
    .SetInfoConfig(INFO_CFG)
    .SetWarningConfig(WARNING_CFG)
    .SetErrorConfig(ERROR_CFG)
    .SetFatalConfig(FATAL_CFG)
    .Build();

}
