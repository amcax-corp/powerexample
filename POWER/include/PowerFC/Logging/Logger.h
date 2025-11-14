#pragma once
#include <Logging/ISink.h>
#include <cassert>
#include <functional>
#include <ranges>
#include <atomic>
namespace logging {

class LOGGING_API Logger
{
  public:
    explicit Logger(std::string_view name)
      : m_name(name)
    {}

    Logger(std::string_view name, std::ranges::range auto&& sinks)
      : m_name(name)
    {
        std::ranges::copy(sinks, std::back_inserter(m_sinks));
    }

    Logger(std::string_view name, std::shared_ptr<ISink> sink)
      : Logger(name, std::views::single(sink))
    {}

    Logger(Logger const&) noexcept;
    Logger(Logger&&) noexcept;

    virtual ~Logger() = default;

    void operator+=(Recorder&& recorder)
    {
        if (ShouldLog(recorder.GetLevel()))
        {
            LogItImpl(std::move(recorder));
        }
    }

    template<typename... Args>
    void Log(TimePoint tp, std::source_location const& loc, Level level, std::format_string<Args...> const& fmt, Args&&... args)
    {
        if (ShouldLog(level))
        {
            LogItImpl(std::move(Recorder(tp, loc, GetName(), level, ShouldLog(level)))(fmt, std::forward<Args>(args)...));
        }
    }

    template<typename... Args>
    void Print(Level level, std::format_string<Args...> const& fmt, Args&&... args)
    {
        if (ShouldLog(level)){
            LogItImpl(std::move(Recorder(GetName(), level, ShouldLog(level)))(fmt, std::forward<Args>(args)...));
        }
    }

    inline std::string const& GetName() const noexcept
    {
        return m_name;
    }

    inline void SetLevel(logging::Level level)
    {
        m_level.store(static_cast<int>(level), std::memory_order_relaxed);
    }

    inline auto GetLevel() const -> logging::Level
    {
        return static_cast<logging::Level>(m_level.load(std::memory_order_relaxed));
    }

    inline bool ShouldLog(Level recorder_level)
    {
        return recorder_level >= GetLevel();
    }

    inline void Flush()
    {
        FlushImpl();
    }

    inline void FulshOn(Level level)
    {
        m_flush_level.store(static_cast<int>(level), std::memory_order_relaxed);
    }
    inline auto GetFlushLevel() const -> logging::Level
    {
        return static_cast<logging::Level>(m_flush_level.load(std::memory_order_relaxed));
    }

    inline bool ShouldFlush(Level recorder_level) const
    {
        return recorder_level >= GetFlushLevel();
    }

    void SetStylizer(std::unique_ptr<Stylizer> stylizer);

    auto const& GetSinks() const
    {
        return m_sinks;
    }

    void AddSink(std::shared_ptr<ISink> sink)
    {
        m_sinks.emplace_back(sink);
    }

    void RemoveSink(std::shared_ptr<ISink> sink)
    {
        m_sinks.erase(std::remove(m_sinks.begin(), m_sinks.end(), sink), m_sinks.end());
    }

    void RemoveAllSinks()
    {
        m_sinks.clear();
    }

    virtual std::shared_ptr<Logger> Clone(std::string_view new_name) const;

  protected:
    std::string m_name;
    std::vector<std::shared_ptr<ISink>> m_sinks{};
    std::atomic_int m_level{static_cast<int>(LEVEL_TRACE)};
    std::atomic_int m_flush_level{static_cast<int>(LEVEL_TRACE)};
    std::function<void(const std::string& err_msg)> m_error_handler;

    virtual void LogItImpl(Recorder&& recorder)
    {
        assert(ShouldLog(recorder.GetLevel()));
        for (auto& sink : m_sinks)
        {
            sink->SinkIt(std::move(recorder));
        }
        if (ShouldFlush(recorder.GetLevel()))
        {
            FlushImpl();
        }
    }

    virtual void FlushImpl()
    {
        for (auto& sink : m_sinks)
        {
            sink->Flush();
        }
    }
};
}  // namespace logging
