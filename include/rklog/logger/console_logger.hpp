#pragma once

#include "logger.hpp"

namespace rklog {

class ConsoleLogger final : public Logger
{
public:
    explicit ConsoleLogger(std::string_view title) noexcept;
    explicit ConsoleLogger(std::string_view title, LogStyle style) noexcept;

protected:
    virtual void LogInternal(std::string_view msg, LogLevel lvl) override;
};

}