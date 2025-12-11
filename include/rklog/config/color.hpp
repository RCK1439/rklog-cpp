#pragma once

#include <cstdint>

namespace rklog {

struct Color final
{
public:
    uint8_t r = 0x00;
    uint8_t g = 0x00;
    uint8_t b = 0x00;

public:
    constexpr Color() = default;
    constexpr Color(uint8_t r, uint8_t g, uint8_t b) noexcept :
        r(r), g(g), b(b) {}
};

}

namespace rklog::defaults {

constexpr Color COLOR_RED       = Color(255, 0, 0);
constexpr Color COLOR_GREEN     = Color(0, 255, 0);
constexpr Color COLOR_BLUE      = Color(0, 0, 255);
constexpr Color COLOR_YELLOW    = Color(255, 255, 0);
constexpr Color COLOR_MAGENTA   = Color(255, 0, 255);
constexpr Color COLOR_LIGHTBLUE = Color(0, 255, 255);
constexpr Color COLOR_WHITE     = Color(255, 255, 255);
constexpr Color COLOR_BLACK     = Color(0, 0, 0);

}