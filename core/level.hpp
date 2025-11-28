#pragma once

#include <cstdint>

namespace rklog {

/**
 * Enum representing the log level severity
 */
enum class LogLevel : uint8_t
{
    INFO,
    WARNING,
    ERROR,
    FATAL,
};

}
