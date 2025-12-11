#pragma once

#include "logger.hpp"

#include <filesystem>
#include <fstream>

namespace rklog {

class FileLogger final : public Logger
{
public:
    FileLogger() = delete;

    explicit FileLogger(std::filesystem::path fileName, std::string_view title) :
        Logger(title), m_FileHandle(fileName) {}

    explicit FileLogger(std::filesystem::path fileName, std::string_view title, LogStyle style) :
        Logger(title, style), m_FileHandle(fileName) {}

protected:
    virtual void LogInternal(std::string_view msg, LogLevel lvl) override;
    
private:
    std::ofstream m_FileHandle;
};

}