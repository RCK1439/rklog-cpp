#pragma once

#include "Logger.hpp"

#include "../Config/Style.hpp"

#include <fstream>

namespace rklog {

class FileLogger final : public Logger
{
public:
protected:
    virtual void LogInternal(std::string_view msg, LogLevel level) override;

private:
    std::ofstream m_FileHandle;
};

}