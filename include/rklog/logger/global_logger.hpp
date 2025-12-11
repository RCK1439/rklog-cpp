#pragma once

#include "logger.hpp"

#include <filesystem>
#include <memory>
#include <string_view>

namespace rklog {

class GlobalLogger
{
public:
    static void InitConsole(std::string_view title) noexcept;
    static void InitConsole(std::string_view title, LogStyle style) noexcept;

    static void InitFile(std::filesystem::path fileName, std::string_view title);
    static void InitFile(std::filesystem::path fileName, std::string_view title, LogStyle style);

    static std::shared_ptr<Logger> Get() noexcept
    {
        return s_Logger;
    }

private:
    static std::shared_ptr<Logger> s_Logger;
};

}