//
// Created by Anshul Saraf on 08/02/23.
//


#ifndef OPENGLBASICS_LOGGER_H
#define OPENGLBASICS_LOGGER_H
#include "Common.h"


// This ignores all warnings/deprecated-declarations raised inside External headers
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#define GLM_ENABLE_EXPERIMENTAL
#include "glm/gtx/string_cast.hpp"
#pragma GCC diagnostic pop

#pragma warning(push, 0)
#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>
#include "spdlog/sinks/stdout_color_sinks.h"
#include <spdlog/sinks/basic_file_sink.h>
#include <string_view>
#include <string>
#pragma warning(pop)

class Logger{
public:
    static void Init();

    static std::shared_ptr<spdlog::logger> GetCoreLogger() {
        if (s_CoreLogger==nullptr) {
            Logger::Init();
        }
        return s_CoreLogger;
    }
    static std::shared_ptr<spdlog::logger> GetClientLogger() {
        if (s_ClientLogger==nullptr) {
            Logger::Init();
        }
        return s_ClientLogger;
    }
private:
    static std::shared_ptr<spdlog::logger> s_CoreLogger;
    static std::shared_ptr<spdlog::logger> s_ClientLogger;
};


// Use SPDLog's formatter which internally chooses between it's own formatter or std::format depending on support
template<typename... Args>
static std::string GetString(fmt::format_string<Args...> fmt, Args &&... args) {
#ifdef SPDLOG_USE_STD_FORMAT
    spdlog::memory_buf_t buf = std::vformat(fmt, std::make_format_args(std::forward<Args>(args)...));
#else
    spdlog::memory_buf_t buf;
    fmt::detail::vformat_to(buf,
                            spdlog::string_view_t(fmt),
                            fmt::make_format_args(std::forward<Args>(args)...));
#endif
    return std::string(std::string_view(buf.data(), buf.size()));
}

static std::string GetString(const std::string& string) {
    return string;
}

#define STRING(...) ::Shutter::GetString(__VA_ARGS__)


template<typename OStream, glm::length_t L, typename T, glm::qualifier Q>
inline OStream& operator<<(OStream& os, const glm::vec<L, T, Q>& vector)
{
    return os << glm::to_string(vector);
}

template<typename OStream, glm::length_t C, glm::length_t R, typename T, glm::qualifier Q>
inline OStream& operator<<(OStream& os, const glm::mat<C, R, T, Q>& matrix)
{
    return os << glm::to_string(matrix);
}

template<typename OStream, typename T, glm::qualifier Q>
inline OStream& operator<<(OStream& os, glm::qua<T, Q> quaternion)
{
    return os << glm::to_string(quaternion);
}

#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCUnusedMacroInspection"
// Core log macros

#define SOURCE_TRACE STRING("{0}:{1}::[{2}]", __FILE_NAME__, __LINE__, __PRETTY_FUNCTION__)
#define FUNCTION_TRACE __PRETTY_FUNCTION__

#define CORE_TRACE(...)    ::Logger::GetCoreLogger()->trace(__VA_ARGS__)
#define CORE_INFO(...)     ::Logger::GetCoreLogger()->info(__VA_ARGS__)
#define CORE_WARN(...)     ::Logger::GetCoreLogger()->warn(__VA_ARGS__)
#define CORE_ERROR(...)    ::Logger::GetCoreLogger()->error(__VA_ARGS__)
#define CORE_CRITICAL(...) ::Logger::GetCoreLogger()->critical(__VA_ARGS__)

// Client log macros
#define TRACE(...)         ::Logger::GetClientLogger()->trace(__VA_ARGS__)
#define INFO(...)          ::Logger::GetClientLogger()->info(__VA_ARGS__)
#define WARN(...)          ::Logger::GetClientLogger()->warn(__VA_ARGS__)
#define ERROR(...)         ::Logger::GetClientLogger()->error(__VA_ARGS__)
#define CRITICAL(...)      ::Logger::GetClientLogger()->critical(__VA_ARGS__)

#pragma clang diagnostic pop

#endif //OPENGLBASICS_LOGGER_H
