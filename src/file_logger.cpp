#include "../include/rklog/logger/file_logger.hpp"

#include <iostream>
#include <print>

namespace rklog {

void FileLogger::LogInternal(std::string_view msg, LogLevel lvl)
{
    const LogConfig cfg = m_Style.GetConfig(lvl);
    const std::string label = cfg.GenerateLabel(m_Title, TimeStamp::Now());

#if defined(RKLOG_COMPILER_GCC)
    m_FileHandle << std::format(RKLOG_FMT_OUTPUT, label, msg) << '\n';
#else
    std::println(m_FileHandle, RKLOG_FMT_OUTPUT, label, msg);
#endif
}

}