#pragma once

#include "Color.hpp"
#include "Level.hpp"

#include "../Core/Platform.hpp"

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
    constexpr LogLevel GetLevel() const noexcept
    {
        return m_Level;
    }

    constexpr std::string_view GetTag() const noexcept
    {
        if (m_Tag.has_value())
        {
            return m_Tag.value();
        }

        switch (m_Level)
        {
            case LogLevel::LOG_DEBUG:
                return "DEBUG";
            case LogLevel::LOG_INFO:
                return "INFO";
            case LogLevel::LOG_WARNING:
                return "WARNING";
            case LogLevel::LOG_ERROR:
                return "ERROR";
            case LogLevel::LOG_FATAL:
                return "FATAL";
        }

        RKLOG_UNREACHABLE();
    }

    constexpr std::optional<Color> GetForegroundColor() const noexcept
    {
        return m_Foreground;
    }

    constexpr std::optional<Color> GetBackgroundColor() const noexcept
    {
        return m_Background;
    }

private:
    constexpr LogConfig(LogLevel level) noexcept :
        m_Level(level) {}

private:
    LogLevel                        m_Level;
    std::optional<Color>            m_Foreground = std::nullopt;
    std::optional<Color>            m_Background = std::nullopt;
    std::optional<std::string_view> m_Tag = std::nullopt;

    friend class LogConfigBuilder;
};

class LogConfigBuilder final
{
public:
    LogConfigBuilder(const LogConfigBuilder&) = delete;
    LogConfigBuilder(LogConfigBuilder&&) = delete;

    [[nodiscard]] constexpr LogConfigBuilder& SetTag(std::string_view tag) noexcept
    {
        m_Config.m_Tag = tag;
        return *this;
    }

    [[nodiscard]] constexpr LogConfigBuilder& SetForeground(Color color) noexcept
    {
        m_Config.m_Foreground = color;
        return *this;
    }

    [[nodiscard]] constexpr LogConfigBuilder& SetForeground(uint8_t r, uint8_t g, uint8_t b) noexcept
    {
        m_Config.m_Foreground = Color(r, g, b);
        return *this;
    }

    [[nodiscard]] constexpr LogConfigBuilder& SetBackground(Color color) noexcept
    {
        m_Config.m_Background = color;
        return *this;
    }

    [[nodiscard]] constexpr LogConfigBuilder& SetBackground(uint8_t r, uint8_t g, uint8_t b) noexcept
    {
        m_Config.m_Background = Color(r, g, b);
        return *this;
    }

    [[nodiscard]] constexpr LogConfig&& Build() noexcept
    {
        return std::move(m_Config);
    }

private:
    constexpr LogConfigBuilder(LogLevel level) noexcept :
        m_Config(level) {}

private:
    LogConfig m_Config;

    friend constexpr LogConfigBuilder InitBuildConfig(LogLevel) noexcept;
};

[[nodiscard]] constexpr LogConfigBuilder InitBuildConfig(LogLevel level) noexcept
{
    return LogConfigBuilder(level);
}

}

namespace rklog::defaults {

constexpr auto DEBUG_CFG = InitBuildConfig(LogLevel::LOG_DEBUG)
    .SetForeground(COLOR_BLUE)
    .Build();
constexpr auto INFO_CFG = InitBuildConfig(LogLevel::LOG_INFO)
    .SetForeground(COLOR_GREEN)
    .Build();
constexpr auto WARNING_CFG = InitBuildConfig(LogLevel::LOG_WARNING)
    .SetForeground(COLOR_YELLOW)
    .Build();
constexpr auto ERROR_CFG = InitBuildConfig(LogLevel::LOG_ERROR)
    .SetForeground(COLOR_RED)
    .Build();
constexpr auto FATAL_CFG = InitBuildConfig(LogLevel::LOG_FATAL)
    .SetForeground(COLOR_WHITE)
    .SetBackground(COLOR_RED)
    .Build();

}
