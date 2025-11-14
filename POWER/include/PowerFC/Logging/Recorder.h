#pragma once
#include <Logging/Common.h>
#include <Logging/Detail/Stream.h>
#include <Logging/Level.h>
#include <chrono>
#include <source_location>

namespace logging {

using Clock = std::chrono::system_clock;
using TimePoint = Clock::time_point;

class LOGGING_API Recorder : public Detail::Stream<char>
{
  public:
    Recorder() = default;
    Recorder(TimePoint tp,
             std::source_location const& loc,
             std::string_view logger_name,
             logging::Level level,
             bool enable = true,//控制是否流入字符串
             std::string_view init_msg = {});
    Recorder(std::source_location const& loc,
             std::string_view logger_name,
             logging::Level level,
             bool enable = true,//控制是否流入字符串
             std::string_view init_msg = {});

    Recorder(std::string_view logger_name,
             logging::Level level,
             bool enable = true,//控制是否流入字符串
             std::string_view init_msg = {});

    Recorder(Recorder const&) = delete;
    Recorder& operator=(Recorder const&) = delete;

    Recorder(Recorder&&) = default;
    Recorder& operator=(Recorder&&) = default;

    auto GetLoggerName() const
    {
        return logger_name;
    }

    auto const& GetTimePoint() const
    {
        return time_point;
    }

    auto GetPayload() const
    {
        return View();
    }

    auto GetLevel() const
    {
        return level;
    }

    auto const& GetSourceLocation() const
    {
        return source_loc;
    }

    auto const GetThreadID() const
    {
        return thread_id;
    }

    void SetThreadID(std::size_t id)
    {
        thread_id = id;
    }

    std::pair<std::size_t, std::size_t> const& GetColorRange() const
    {
        return color_range;
    }

    void SetColorRange(std::size_t start, std::size_t end)
    {
        color_range = {start, end};
    }

    void SetColorStart(std::size_t start){
        color_range.first = start;
    }

    void SetColorEnd(std::size_t end){
        color_range.second = end;
    }

    template<typename... Args>
    Recorder&& operator()(std::format_string<Args...> const& fmt, Args&&... args)
    {
        Stream<char>::operator()(fmt, std::forward<Args>(args)...);
        return std::move(*this);
    }

    template<typename T>
    Recorder&& operator<<(T const& t)
    {
        Stream<char>::operator<<(t);
        return std::move(*this);
    }

    bool JustRaw() const{
        return just_raw;
    }

  private:
    TimePoint time_point{Clock::now()};
    std::source_location source_loc{};
    std::string_view logger_name{};
    Level level{LEVEL_OFF};
    std::size_t thread_id{0};
    std::pair<std::size_t, std::size_t> color_range{0u, 0u};
    bool just_raw{false};//在风格化的时候是否仅输出payload
};
}  // namespace logging
