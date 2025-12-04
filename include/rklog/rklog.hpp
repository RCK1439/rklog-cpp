#pragma once

#include "core/logger.hpp"

#include <string_view>

namespace rklog {

class GlobalLogger
{
public:
    static void InitConsole(std::string_view title);
    static void InitConsole(std::string_view title, LogStyle style);

    static void InitFile(std::filesystem::path fileName, std::string_view title);
    static void InitFile(std::filesystem::path fileName, std::string_view title, LogStyle style);

    static std::shared_ptr<Logger> Get()
    {
        if (!s_Logger)
        {
            throw std::runtime_error("GlobalLogger was not initialized");
        }

        return s_Logger;
    }

private:
    static std::shared_ptr<Logger> s_Logger;
};

}
