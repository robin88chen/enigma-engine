#include "PlatformConfig.hpp"
#include "Debug.hpp"

#if TARGET_PLATFORM == PLATFORM_WIN32
#include <Windows.h>
#include <cstdarg>
#include <cstdio>
constexpr unsigned int MAX_CHARS = 1023;

static int win32VDebugPrintf(const char* format, va_list arg_list)
{
    // NOLINTNEXTLINE(cppcoreguidelines-avoid-c-arrays, modernize-avoid-c-arrays)
    static char s_buffer[MAX_CHARS + 1];
    const int n_written = vsnprintf_s(s_buffer, MAX_CHARS, format, arg_list);
    s_buffer[MAX_CHARS] = '\0';
    OutputDebugString(s_buffer);
    return n_written;
}

namespace Platforms
{
    int Debug::printf(const char* format, ...)
    {
        va_list arg_list = nullptr;
        va_start(arg_list, format);
        const int n_written = win32VDebugPrintf(format, arg_list);
        va_end(arg_list);
        return n_written;
    }
    int Debug::errorPrintf(const char* format, ...)
    {
        va_list arg_list = nullptr;
        va_start(arg_list, format);
        const int n_written = win32VDebugPrintf(format, arg_list);
        va_end(arg_list);
        return n_written;
    }
}
#endif
