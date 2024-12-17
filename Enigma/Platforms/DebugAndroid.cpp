#include "PlatformConfig.hpp"

#if TARGET_PLATFORM == PLATFORM_ANDROID
#include "Debug.hpp"
#include <cstdarg>
#include <android/log.h>

namespace Platforms
{
    int Debug::printf(const char* format, ...)
    {
        va_list arg_list;
        va_start(arg_list, format);
        int n_written = __android_log_vprint(ANDROID_LOG_DEBUG, "EnigmaAndroid", format, arg_list);
        va_end(arg_list);
        return n_written;
    }
    int Debug::errorPrintf(const char* format, ...)
    {
        va_list arg_list;
        va_start(arg_list, format);
        int n_written = __android_log_vprint(ANDROID_LOG_ERROR, "EnigmaAndroid", format, arg_list);
        va_end(arg_list);
        return n_written;
    }
}

#endif
