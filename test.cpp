#define RKLOG_IMPLEMENTATION
#include "rklog/rklog.hpp"

int main()
{
    rklog::InitGlobalLogging("test");
    rklog::LogInfo("Hello, World!");
}