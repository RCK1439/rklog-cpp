#pragma once

#include "time.hpp"

#include <cstdint>
#include <optional>
#include <string>
#include <string_view>

namespace rklog {

#define RKLOG_ESC_CODE_START "\033["
#define RKLOG_ESC_CODE_END   "m"

#define RKLOG_ESC_CODE_RESET RKLOG_ESC_CODE_START "0" RKLOG_ESC_CODE_END

#define RKLOG_TRUE_COLOR_MODE "2;"
#define RKLOG_256_COLOR_PALETTE_MODE "5;"

#define RKLOG_FG_COLOR_MODE "38;"
#define RKLOG_BG_COLOR_MODE "48;"

// --- format specifiers ------------------------------------------------------

#define RKLOG_FG_COLOR_FMT\
    RKLOG_FG_COLOR_MODE RKLOG_TRUE_COLOR_MODE "{};{};{}"
#define RKLOG_BG_COLOR_FMT\
    RKLOG_BG_COLOR_MODE RKLOG_TRUE_COLOR_MODE "{};{};{}"

#define RKLOG_FMT_COLOR_PRELUDE\
    RKLOG_ESC_CODE_START RKLOG_FG_COLOR_FMT ";" RKLOG_BG_COLOR_FMT RKLOG_ESC_CODE_END

#define RKLOG_FMT_COLOR_PRELUDE_NO_BG\
    RKLOG_ESC_CODE_START RKLOG_FG_COLOR_FMT RKLOG_ESC_CODE_END

#define RKLOG_FMT_LABEL "[{}]:[{}]:[{}]: "

struct Color final
{
public:
    uint8_t r;
    uint8_t g;
    uint8_t b;

public:
    constexpr Color(uint8_t r, uint8_t g, uint8_t b) noexcept :
        r(r), g(g), b(b) {}

    static constexpr Color Green() noexcept
    {
        return Color(0, 255, 0);
    }

    static constexpr Color Yellow() noexcept
    {
        return Color(255, 255, 0);
    }

    static constexpr Color Red() noexcept
    {
        return Color(255, 0, 0);
    }

    static constexpr Color White() noexcept
    {
        return Color(255, 255, 255);
    }

    static constexpr Color Black() noexcept
    {
        return Color(0, 0, 0);
    }
};

class LogConfig final
{
public:
    constexpr LogConfig(std::string_view tag, Color foreground) noexcept :
        m_Tag(tag), m_Foreground(foreground) {}
    constexpr LogConfig(std::string_view tag, Color foreground, Color background) noexcept :
        m_Tag(tag), m_Foreground(foreground), m_Background(background) {}

    static constexpr LogConfig DefaultInfo() noexcept
    {
        return LogConfig("INFO", Color::Green());
    }

    static constexpr LogConfig DefaultWarning() noexcept
    {
        return LogConfig("WARNING", Color::Yellow());
    }

    static constexpr LogConfig DefaultError() noexcept
    {
        return LogConfig("ERROR", Color::Red());
    }

    static constexpr LogConfig DefaultFatal() noexcept
    {
        return LogConfig("FATAL", Color::White(), Color::Red());
    }

    std::string GenerateLabel(std::string_view title, const TimeStamp& ts) const
    {
        return std::format(RKLOG_FMT_LABEL, title, m_Tag, ts);
    }

    std::string GenerateColorPrelude() const
    {
        if (m_Background.has_value())
        {
            const Color background = m_Background.value();
            return std::format(RKLOG_FMT_COLOR_PRELUDE, m_Foreground.r, m_Foreground.g, m_Foreground.b, background.r, background.g, background.b);
        }
        
        return std::format(RKLOG_FMT_COLOR_PRELUDE_NO_BG, m_Foreground.r, m_Foreground.g, m_Foreground.b);
    }

private:
    std::string_view     m_Tag;                       // tag title for the severity level
    Color                m_Foreground;                // background color
    std::optional<Color> m_Background = std::nullopt; // foreground color
};

}