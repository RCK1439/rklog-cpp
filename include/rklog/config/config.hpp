#pragma once

#include "color.hpp"
#include "level.hpp"

#include "rklog/core/platform.hpp"

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

template<LogLevel TLevel>
class LogConfig final
{
public:
    constexpr LogLevel GetLevel() const noexcept
    {
        return TLevel;
    }

    constexpr std::string_view GetTag() const noexcept
    {
        if constexpr (m_Tag.has_value())
        {
            return m_Tag.value();
        }

        switch (TLevel)
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
    constexpr LogConfig() = default;

private:
    std::optional<std::string_view> m_Tag = std::nullopt;
    std::optional<Color>            m_Foreground = std::nullopt;
    std::optional<Color>            m_Background = std::nullopt;

    template<LogLevel>
    friend class LogConfigBuilder;
};

template<LogLevel TLevel>
class LogConfigBuilder final
{
public:
    using Builder = LogConfigBuilder<TLevel>;
    using Config = LogConfig<TLevel>;

public:
    LogConfigBuilder(const Builder&) = delete;
    LogConfigBuilder(Builder&&) = delete;

    [[nodiscard]] constexpr Builder& SetTag(std::string_view tag) noexcept
    {
        m_Config.m_Tag = tag;
        return *this;
    }

    [[nodiscard]] constexpr Builder& SetForeground(Color color) noexcept
    {
        m_Config.m_Foreground = color;
        return *this;
    }

    [[nodiscard]] constexpr Builder& SetForeground(uint8_t r, uint8_t g, uint8_t b) noexcept
    {
        m_Config.m_Foreground = Color(r, g, b);
        return *this;
    }

    [[nodiscard]] constexpr Builder& SetBackground(Color color) noexcept
    {
        m_Config.m_Background = color;
        return *this;
    }

    [[nodiscard]] constexpr Builder& SetBackground(uint8_t r, uint8_t g, uint8_t b) noexcept
    {
        m_Config.m_Background = Color(r, g, b);
        return *this;
    }

    [[nodiscard]] constexpr Config&& Build() noexcept
    {
        return std::move(m_Config);
    }

private:
    constexpr LogConfigBuilder() = default;

private:
    Config m_Config;

    template<LogLevel L>
    friend constexpr LogConfigBuilder<L> InitBuildConfig() noexcept;
};

template<LogLevel TLevel>
[[nodiscard]] constexpr LogConfigBuilder<TLevel> InitBuildConfig() noexcept
{
    return LogConfigBuilder<TLevel>();
}

}

namespace rklog::defaults {

constexpr auto DEBUG_CFG = InitBuildConfig<LogLevel::LOG_DEBUG>()
    .SetForeground(COLOR_BLUE)
    .Build();
constexpr auto INFO_CFG = InitBuildConfig<LogLevel::LOG_INFO>()
    .SetForeground(COLOR_GREEN)
    .Build();
constexpr auto WARNING_CFG = InitBuildConfig<LogLevel::LOG_WARNING>()
    .SetForeground(COLOR_YELLOW)
    .Build();
constexpr auto ERROR_CFG = InitBuildConfig<LogLevel::LOG_ERROR>()
    .SetForeground(COLOR_RED)
    .Build();
constexpr auto FATAL_CFG = InitBuildConfig<LogLevel::LOG_FATAL>()
    .SetForeground(COLOR_WHITE)
    .SetBackground(COLOR_RED)
    .Build();

}
