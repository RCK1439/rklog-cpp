#pragma once

#include "Logger/BasicLogger.hpp"
#include "Logger/ColorLogger.hpp"
#include "Logger/FileLogger.hpp"

namespace rklog {

ColorLogger& GetColorLogger(std::string_view title = "global") noexcept;
BasicLogger& GetBasicLogger(std::string_view title = "global") noexcept;

}
