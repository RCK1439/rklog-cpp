#pragma once

#include "Logger.hpp"

#include "../Config/Style.hpp"

#include <fstream>
#include <filesystem>

namespace rklog {

class FileLogger final : public Logger
{
public:
    FileLogger(std::filesystem::path filePath) :
        Logger(), m_FileHandle(filePath) {}
    FileLogger(std::filesystem::path filePath, std::string_view title) :
        Logger(title), m_FileHandle(filePath) {}
    FileLogger(std::filesystem::path filePath, LogStyle style) :
        Logger(style), m_FileHandle(filePath) {}
    FileLogger(std::filesystem::path filePath, std::string_view title, LogStyle style) :
        Logger(title, style), m_FileHandle(filePath) {}
    
    inline void EnableWriteToStdErr() noexcept
    {
        m_WriteToStdErr = true;
    }

    inline void DisableWriteToStdErr() noexcept
    {
        m_WriteToStdErr = false;
    }

protected:
    virtual void LogInternal(std::string_view msg, LogLevel level) override;

private:
    std::ofstream m_FileHandle;
    bool          m_WriteToStdErr = false;
};

}