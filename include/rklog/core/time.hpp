#pragma once

#include "Platform.hpp"

#include <format>
#include <cstdint>
#include <chrono>

namespace rklog {

class TimeStamp final
{
public:
    static TimeStamp Now() noexcept
    {
        const std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
        const std::time_t cNow = std::chrono::system_clock::to_time_t(now);

#if defined(RKLOG_PLATFORM_WINDOWS)
        std::tm localTime;
        const errno_t err = localtime_s(&localTime, &cNow);
        if (err == 0)
        {
            return TimeStamp(static_cast<uint32_t>(localTime.tm_hour), static_cast<uint32_t>(localTime.tm_min), static_cast<uint32_t>(localTime.tm_sec));
        }

        return TimeStamp();
#else
    const std::tm* const localTime = std::localtime(&cNow);
    return TimeStamp(static_cast<uint32_t>(localTime->tm_hour), static_cast<uint32_t>(localTime->tm_min), static_cast<uint32_t>(localTime->tm_sec));
#endif
    }

    inline uint32_t Hours() const noexcept
    {
        return m_Hours;
    }

    inline uint32_t Minutes() const noexcept
    {
        return m_Minutes;
    }

    inline uint32_t Seconds() const noexcept
    {
        return m_Seconds;
    }

private:
    TimeStamp() = default;

    constexpr explicit TimeStamp(uint32_t hours, uint32_t minutes, uint32_t seconds) noexcept :
        m_Hours(hours), m_Minutes(minutes), m_Seconds(seconds) {}

private:
    const uint32_t m_Hours = 0;
    const uint32_t m_Minutes = 0;
    const uint32_t m_Seconds = 0;
};

}

// --- custom formatting implementation of the time stamp ---------------------

template<>
struct std::formatter<rklog::TimeStamp>
{
    constexpr auto parse(std::format_parse_context& ctx) const
    {
        return ctx.begin();
    }

    auto format(const rklog::TimeStamp& timeStamp, std::format_context& ctx) const
    {
        return std::format_to(ctx.out(), "{:02}:{:02}:{:02}", timeStamp.Hours(), timeStamp.Minutes(), timeStamp.Seconds());
    }
};
