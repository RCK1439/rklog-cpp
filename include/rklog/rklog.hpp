#pragma once

#include "Logger/BasicLogger.hpp"
#include "Logger/ColorLogger.hpp"
#include "Logger/FileLogger.hpp"

namespace rklog {

ColorLogger& GetColorLogger(std::string_view title = "global");
BasicLogger& GetBasicLogger(std::string_view title = "global");
FileLogger& GetFileLogger(std::filesystem::path filePath, std::string_view title = "global");

}
