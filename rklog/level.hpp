#pragma once

#include <cstdint>

namespace rklog {

enum class LogLevel : uint8_t
{
    INFO,
    WARNING,
    ERROR,
    FATAL,
};

}
