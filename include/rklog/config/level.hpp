#pragma once

#include <cstdint>

namespace rklog {

enum class LogLevel : uint8_t
{
    LOG_DEBUG,
    LOG_INFO,
    LOG_WARNING,
    LOG_ERROR,
    LOG_FATAL,
};

}
