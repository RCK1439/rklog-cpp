#pragma once

#if defined(_WIN32) || defined(_WIN64)
#define RKLOG_PLATFORM_WINDOWS
#elif defined(__linux__)
#define RKLOG_PLATFORM_LINUX
#elif defined(__APPLE__)
#define RKLOG_PLATFORM_APPLE
#else
#error "Unsupported platform"
#endif

#if defined(_MSC_VER)
#define RKLOG_COMPILER_MSVC
#elif defined(__clang__)
#define RKLOG_COMPILER_LLVM
#elif defined(__GNUC__)
#define RKLOG_COMPILER_GCC
#else
#error "Unsupported compiler"
#endif
