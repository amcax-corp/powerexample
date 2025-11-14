#pragma once

#include <Logging/Logger.h>
#include <Logging/Recorder.h>
#include <chrono>
#include <functional>
#include <memory>
#include <mutex>
#include <string>
#include <string_view>

namespace logging {



LOGGING_API void SetStylizer(std::unique_ptr<Stylizer> stylizer);

LOGGING_API void SetLevel(Level level);

LOGGING_API void FlushOn(Level level);

// template<typename Rep, typename Period>
// inline void FlushEvery(std::chrono::duration<Rep, Period> interval)
// {
//     return GetRegistry().FlushEvery(interval);
// }

LOGGING_API Logger* const RegisterLogger(std::shared_ptr<Logger> logger);

LOGGING_API std::shared_ptr<Logger> GetLogger(std::string_view name);

LOGGING_API void Drop(std::string const& name);

LOGGING_API void DropAll();

LOGGING_API void Shutdown();

LOGGING_API void SetDefaultLogger(std::shared_ptr<Logger> logger);

LOGGING_API std::shared_ptr<Logger> DefaultLogger();

LOGGING_API Logger* const DefaultLoggerRaw();

template<typename... Args>
struct Critical
{
    constexpr Critical(std::format_string<Args...> fmt, Args&&... args, std::source_location location = std::source_location::current())
    {
        DefaultLoggerRaw()->Log(Clock::now(), location, LEVEL_CRITICAL, fmt, std::forward<Args>(args)...);
    }
};

template<typename... Args>
Critical(std::format_string<Args...> fmt, Args&&... args) -> Critical<Args...>;

template<typename... Args>
struct Error
{
    constexpr Error(std::format_string<Args...> fmt, Args&&... args, std::source_location location = std::source_location::current())
    {
        DefaultLoggerRaw()->Log(Clock::now(), location, LEVEL_ERROR, fmt, std::forward<Args>(args)...);
    }
};

template<typename... Args>
Error(std::format_string<Args...> , Args&&... ) -> Error<Args...>;

template<typename... Args>
struct Warn
{
    constexpr Warn(std::format_string<Args...> fmt, Args&&... args, std::source_location location = std::source_location::current())
    {
        DefaultLoggerRaw()->Log(Clock::now(), location, LEVEL_WARN, fmt, std::forward<Args>(args)...);
    }
};

template<typename... Args>
Warn(std::format_string<Args...> fmt, Args&&... args) -> Warn<Args...>;

template<typename... Args>
struct Info
{
    constexpr Info(std::format_string<Args...> fmt, Args&&... args, std::source_location location = std::source_location::current())
    {
        DefaultLoggerRaw()->Log(Clock::now(), location, LEVEL_INFO, fmt, std::forward<Args>(args)...);
    }
};

template<typename... Args>
Info(std::format_string<Args...> fmt, Args&&... args) -> Info<Args...>;

template<typename... Args>
struct Debug
{
    constexpr Debug(std::format_string<Args...> fmt, Args&&... args, std::source_location location = std::source_location::current())
    {
        DefaultLoggerRaw()->Log(Clock::now(), location, LEVEL_DEBUG, fmt, std::forward<Args>(args)...);
    }
};


template<typename... Args>
Debug(std::format_string<Args...> fmt, Args&&... args) -> Debug<Args...>;

template<typename... Args>
struct Trace
{
    constexpr Trace(std::format_string<Args...> fmt, Args&&... args, std::source_location location = std::source_location::current())
    {
        DefaultLoggerRaw()->Log(Clock::now(), location, LEVEL_TRACE, fmt, std::forward<Args>(args)...);
    }
};


template<typename... Args>
Trace(std::format_string<Args...> fmt, Args&&... args) -> Trace<Args...>;

//按DEBUG水平打印不带时间，位置的信息，用于调试
template<typename... Args>
struct Print
{
    constexpr Print(std::format_string<Args...> fmt, Args&&... args)
    {
        DefaultLoggerRaw()->Print(LEVEL_DEBUG, fmt, std::forward<Args>(args)...);
    }
};

//按DEBUG水平打印不带时间，位置的信息，用于调试
template<typename... Args>
Print(std::format_string<Args...> fmt, Args&&... args) -> Print<Args...>;

}  // namespace logging

#define LOGGING_LOGGER_CALL(logger, level) (*logger) += std::move(logging::Recorder(std::chrono::system_clock::now(), std::source_location::current(), logger->GetName(), level, logger->ShouldLog(level)))

#define LOGGING_LOGGER_TRACE(logger) LOGGING_LOGGER_CALL(logger, logging::LEVEL_TRACE)
#define LOGGING_LOGGER_DEBUG(logger) LOGGING_LOGGER_CALL(logger, logging::LEVEL_DEBUG)
#define LOGGING_LOGGER_INFO(logger) LOGGING_LOGGER_CALL(logger, logging::LEVEL_INFO)
#define LOGGING_LOGGER_WARN(logger) LOGGING_LOGGER_CALL(logger, logging::LEVEL_WARN)
#define LOGGING_LOGGER_ERROR(logger) LOGGING_LOGGER_CALL(logger, logging::LEVEL_ERROR)
#define LOGGING_LOGGER_CRITICAL(logger) LOGGING_LOGGER_CALL(logger, logging::LEVEL_CRITICAL)

#define LOGGING_TRACE LOGGING_LOGGER_TRACE(logging::DefaultLoggerRaw())
#define LOGGING_DEBUG LOGGING_LOGGER_DEBUG(logging::DefaultLoggerRaw())
#define LOGGING_INFO LOGGING_LOGGER_INFO(logging::DefaultLoggerRaw())
#define LOGGING_WARN LOGGING_LOGGER_WARN(logging::DefaultLoggerRaw())
#define LOGGING_ERROR LOGGING_LOGGER_ERROR(logging::DefaultLoggerRaw())
#define LOGGING_CRITICAL LOGGING_LOGGER_CRITICAL(logging::DefaultLoggerRaw())
