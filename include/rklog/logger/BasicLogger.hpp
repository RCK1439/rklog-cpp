#pragma once

#include "Logger.hpp"

namespace rklog {

class BasicLogger final : public Logger
{
public:
    constexpr BasicLogger() noexcept :
        Logger() {}
    constexpr BasicLogger(std::string_view title) noexcept :
        Logger(title) {}
    constexpr BasicLogger(LogStyle style) noexcept :
        Logger(), m_Style(style) {}
    constexpr BasicLogger(std::string_view title, LogStyle style) noexcept :
        Logger(title), m_Style(style) {}

protected:
    virtual void LogInternal(std::string_view msg, LogLevel lvl) override;

private:
    LogStyle m_Style = defaults::DEFAULT_STYLE;
};

}