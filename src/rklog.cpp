#include "rklog/rklog.hpp"

#include <memory>

namespace rklog {

std::shared_ptr<ConsoleLogger> g_GlobalLogger = nullptr;

void InitGlobalLogging(std::string_view title)
{
    if (!g_GlobalLogger)
    {
        g_GlobalLogger = std::make_shared<ConsoleLogger>(title);
    }
}

void InitGlobalLogging(std::string_view title, LogStyle style)
{
    if (!g_GlobalLogger)
    {
        g_GlobalLogger = std::make_shared<ConsoleLogger>(title, style);
    }
}


}