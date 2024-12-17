#include "Logger.hpp"
#include "Debug.hpp"
#include <cstdarg>
#include <cstdio>
#include <array>

using namespace Platforms;

constexpr unsigned int MAX_CHARS = 2048;

std::ofstream Logger::m_logFile;

static const std::array<std::string, 5> LEVEL_TOKEN{ "Info", "Debug", "Warning", "Error", "Fatal" };

void Logger::initLoggerFile(const std::string& filepath)
{
    if (m_logFile.is_open())
    {
        m_logFile.close();
    }
    m_logFile.open(filepath.c_str(), std::fstream::out | std::fstream::trunc);
}

void Logger::closeLoggerFile()
{
    if (m_logFile) m_logFile.close();
}

bool Logger::logIf(bool cond, Level lv, const std::string& msg, const char* filename, int line)
{
    if (cond) logInline(lv, msg, filename, line);
    return cond;
}

void Logger::logInline(Level lv, const std::string& msg, const char* filename, int line)
{
    outputLog(printf("[%s] %s @ %s(%d)\n", LEVEL_TOKEN[static_cast<int>(lv)].c_str(), msg.c_str(), filename, line));
}

void Logger::log(Level lv, const std::string& msg)
{
    outputLog(printf("[%s] %s\n", LEVEL_TOKEN[static_cast<int>(lv)].c_str(), msg.c_str()));
}

std::string Logger::printf(const char* fmt, ...)
{
    std::va_list arg_list{};
    va_start(arg_list, fmt);
    // NOLINTNEXTLINE(cppcoreguidelines-avoid-c-arrays, modernize-avoid-c-arrays)
    static char s_buffer[MAX_CHARS];
    const int written = std::vsnprintf(s_buffer, MAX_CHARS, fmt, arg_list);  // NOLINT(clang-diagnostic-format-nonliteral)
    s_buffer[MAX_CHARS - 1] = '\0';
    va_end(arg_list);
    if (written < 0) return "Logger Printf Error!!\n";
    return s_buffer;
}

void Logger::outputLog(const std::string& msg)
{
    if (m_logFile)
    {
        m_logFile.write(msg.c_str(), static_cast<std::streamsize>(msg.length())).flush();
    }
    Debug::printf(msg.c_str());
}

