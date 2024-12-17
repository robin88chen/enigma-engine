/*****************************************************************
 * \file   Logger.hpp
 * \brief
 *
 * \author Lancelot 'Robin' Chen
 * \date   December 2024
 ******************************************************************/
#ifndef PLATFORMS_LOGGER_HPP
#define PLATFORMS_LOGGER_HPP
#include <cstdint>
#include <string>
#include <fstream>

namespace Platforms
{
    class Logger
    {
    public:
        enum class Level : std::uint8_t
        {
            info,
            debug,
            warning,
            error,
            fatal
        };
    public:
        static void initLoggerFile(const std::string& filepath);
        static void closeLoggerFile();
        static bool logIf(bool cond, Level lv, const std::string& msg, const char* filename, int line);
        static void logInline(Level lv, const std::string& msg, const char* filename, int line);
        static void log(Level lv, const std::string& msg);
        static std::string printf(const char* fmt, ...);
    protected:
        static void outputLog(const std::string& msg);

    protected:
        static std::ofstream m_logFile;
    };
}

#ifdef DISABLE_FATAL_LOGGER
#define FATAL_LOG_EXPR(expr) (expr)
#else
#define FATAL_LOG_EXPR(expr) Platforms::Logger::logIf((expr), Platforms::Logger::Level::fatal, #expr, __FILE__, __LINE__)
#endif
#define LOG_INLINE(lv, msg) Platforms::Logger::logInline(Platforms::Logger::Level::lv, (msg), __FILE__, __LINE__)
#define LOG(lv, msg) Platforms::Logger::log(Platforms::Logger::Level::lv, (msg))
#define LOG_IF(lv, expr) Platforms::Logger::logIf((expr), Platforms::Logger::Level::lv, #expr, __FILE__, __LINE__)

#endif // PLATFORMS_LOGGER_HPP
