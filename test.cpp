#include "rklog/rklog.hpp"

int main()
{
    rklog::ConsoleLogger logger("global");
    logger.Info("Hello, {}!", "World");
    logger.Warn("Hello, {}!", "World");
    logger.Error("Hello, {}!", "World");
    logger.Fatal("Hello, {}!", "World");
}