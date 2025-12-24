#pragma once

#include "Logger.hpp"

#include "../Config/Style.hpp"

namespace rklog {

class ColorLogger final : public Logger
{
public:
    constexpr ColorLogger() noexcept :
        Logger() {}
    constexpr ColorLogger(std::string_view title) noexcept :
        Logger(title) {}
    constexpr ColorLogger(LogStyle style) noexcept :
        Logger(), m_Style(style) {}
    constexpr ColorLogger(std::string_view title, LogStyle style) noexcept :
        Logger(title), m_Style(style) {}

protected:
    virtual void LogInternal(std::string_view msg, LogLevel lvl) override;

private:
    LogStyle m_Style = defaults::DEFAULT_STYLE;
};

}