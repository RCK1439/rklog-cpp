#pragma once

#include <cstdint>

namespace rklog {

/**
 * Class representing color in an RGB format
 */
struct Color final
{
public:
    uint8_t r = 0x00; // Red channel
    uint8_t g = 0x00; // Green channel
    uint8_t b = 0x00; // Blue channel

public:
    constexpr Color() = default;
    
    /**
     * Creates a new instance of `Color` with the given RGB channel values.
     *
     * @param r
     *      The red channel value
     * @param g
     *      The green channel value
     * @param b
     *      The blue channel value
     */
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