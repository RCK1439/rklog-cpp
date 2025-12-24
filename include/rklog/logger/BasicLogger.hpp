#pragma once

#include "Logger.hpp"

#include "../Config/Style.hpp"

namespace rklog {

class BasicLogger final : public Logger
{
public:
    constexpr BasicLogger() noexcept :
        Logger() {}
    constexpr BasicLogger(std::string_view title) noexcept :
        Logger(title) {}
    constexpr BasicLogger(LogStyle style) noexcept :
        Logger(style) {}
    constexpr BasicLogger(std::string_view title, LogStyle style) noexcept :
        Logger(title, style) {}

protected:
    virtual void LogInternal(std::string_view msg, LogLevel level) override;
};

}