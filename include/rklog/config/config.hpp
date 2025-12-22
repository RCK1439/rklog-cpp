#pragma once

#include "color.hpp"

#include "../core/time.hpp"

#include <optional>
#include <string_view>

namespace rklog {

// --- escape codes -----------------------------------------------------------

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

// --- type definitions -------------------------------------------------------

class LogConfig final
{
public:
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
    constexpr LogConfig() = default;
    constexpr LogConfig(std::string_view tag) :
        m_Tag(tag) {}

private:
    std::string_view     m_Tag;
    Color                m_Foreground;
    std::optional<Color> m_Background = std::nullopt;

    friend class LogStyle;
    friend class LogConfigBuilder;
};

class LogConfigBuilder
{
public:
    LogConfigBuilder() = delete;
    LogConfigBuilder(const LogConfigBuilder&) = delete;
    LogConfigBuilder(LogConfigBuilder&&) = delete;

    [[nodiscard]] constexpr LogConfigBuilder& Foreground(Color color) noexcept
    {
        m_Config.m_Foreground = color;
        return *this;
    }

    [[nodiscard]] constexpr LogConfigBuilder& Foreground(uint8_t r, uint8_t g, uint8_t b) noexcept
    {
        m_Config.m_Foreground = Color(r, g, b);
        return *this;
    }

    [[nodiscard]] constexpr LogConfigBuilder& Background(Color color) noexcept
    {
        m_Config.m_Background = color;
        return *this;
    }

    [[nodiscard]] constexpr LogConfigBuilder& Background(uint8_t r, uint8_t g, uint8_t b) noexcept
    {
        m_Config.m_Background = Color(r, g, b);
        return *this;
    }

    [[nodiscard]] constexpr LogConfig&& Build() noexcept
    {
        return std::move(m_Config);
    }

private:
    constexpr LogConfigBuilder(std::string_view tag) noexcept :
        m_Config(tag) {}

private:
    LogConfig m_Config;

    friend constexpr LogConfigBuilder InitBuildConfig(std::string_view) noexcept;
};

[[nodiscard]] constexpr LogConfigBuilder InitBuildConfig(std::string_view tag) noexcept
{
    return LogConfigBuilder(tag);
}

}

namespace rklog::defaults {

// --- tags -------------------------------------------------------------------

constexpr std::string_view INFO_TAG = "INFO";
constexpr std::string_view WARNING_TAG = "WARNING";
constexpr std::string_view ERROR_TAG = "ERROR";
constexpr std::string_view FATAL_TAG = "FATAL";

// --- configurations ---------------------------------------------------------

constexpr LogConfig INFO_CFG = InitBuildConfig(INFO_TAG)
    .Foreground(COLOR_GREEN)
    .Build();
constexpr LogConfig WARNING_CFG = InitBuildConfig(WARNING_TAG)
    .Foreground(COLOR_YELLOW)
    .Build();
constexpr LogConfig ERROR_CFG = InitBuildConfig(ERROR_TAG)
    .Foreground(COLOR_RED)
    .Build();
constexpr LogConfig FATAL_CFG = InitBuildConfig(FATAL_TAG)
    .Foreground(COLOR_WHITE)
    .Background(COLOR_RED)
    .Build();
}
