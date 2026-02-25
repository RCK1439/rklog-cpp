#pragma once

#include <cstdint>

namespace rklog {

/**
 * Struct containing color data for color logging using true color
 */
struct Color final
{
public:
    uint8_t r{}; // The red channel
    uint8_t g{}; // The green channel
    uint8_t b{}; // The blue channel

public:
    constexpr Color() noexcept = default;

    /**
     * Creates a new instance of the color struct with defined values for the
     * color channels
     *
     * @param[in] r
     *      The value of the red channel
     * @param[in] g
     *      The value of the green channel
     * @param[in] b
     *      The value of the blue channel
     */
    constexpr Color(uint8_t r, uint8_t g, uint8_t b) noexcept :
        r(r), g(g), b(b) {}
};

}

namespace rklog::defaults {

constexpr Color COLOR_RED{255, 0, 0};
constexpr Color COLOR_GREEN{0, 255, 0};
constexpr Color COLOR_BLUE{0, 0, 255};
constexpr Color COLOR_YELLOW{255, 255, 0};
constexpr Color COLOR_MAGENTA{255, 0, 255};
constexpr Color COLOR_LIGHTBLUE{0, 255, 255};
constexpr Color COLOR_WHITE{255, 255, 255};
constexpr Color COLOR_BLACK{0, 0, 0};

}