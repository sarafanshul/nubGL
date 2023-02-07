//
// Created by Anshul Saraf on 08/02/23.
//

#ifndef OPENGLBASICS_LOGGER_H
#define OPENGLBASICS_LOGGER_H
#define GLM_ENABLE_EXPERIMENTAL
#include "glm/gtx/string_cast.hpp"
#include "Common.h"

// This ignores all warnings raised inside External headers
#pragma warning(push, 0)
#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>
#include "spdlog/sinks/stdout_color_sinks.h"
#include <spdlog/sinks/basic_file_sink.h>
#pragma warning(pop)

    class Logger{
    public:
        static void Init();

        static std::shared_ptr<spdlog::logger> GetCoreLogger() {
            if (s_CoreLogger==NULL) {
                Logger::Init();
            }
            return s_CoreLogger;
        }
        static std::shared_ptr<spdlog::logger> GetClientLogger() {
            if (s_ClientLogger==NULL) {
                Logger::Init();
            }
            return s_ClientLogger;
        }
    private:
        static std::shared_ptr<spdlog::logger> s_CoreLogger;
        static std::shared_ptr<spdlog::logger> s_ClientLogger;
    };


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

// Core log macros
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


#endif //OPENGLBASICS_LOGGER_H
