#pragma once

#include "rklog/Logger/BasicLogger.hpp"

#include "rklog/Core/Time.hpp"

#include <iostream>

namespace rklog {

void BasicLogger::LogInternal(std::string_view msg, LogLevel lvl)
{
    auto logMessage = m_Title.has_value() ? std::format("[{}]:", m_Title.value()) : "";
    const auto cfg = m_Style.GetConfig(lvl);
    
    const auto tag = cfg.GetTag();
    logMessage += std::format("[{}]:", tag);

    const auto timeStamp = TimeStamp::Now();
    logMessage += std::format("[{}]: {}", timeStamp, msg);

    std::println(std::cerr, "{}", logMessage);
}
    
}