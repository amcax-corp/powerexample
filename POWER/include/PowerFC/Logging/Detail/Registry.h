#pragma once
#include <Logging/AsyncOverflowPolicy.h>
#include <Logging/Common.h>
#include <Logging/Detail/PeriodicWorker.h>
#include <Logging/Level.h>
#include <memory>
#include <string_view>
#include <unordered_map>
namespace logging {
class Logger;
class Stylizer;

namespace Detail {
class ThreadPool;
}
}  // namespace logging
namespace logging::Detail {

class LOGGING_API Registry
{
  public:
    static Registry& Instance();
    Registry(const Registry&) = delete;
    Registry& operator=(const Registry&) = delete;

    void RegisterLogger(std::shared_ptr<Logger> logger);

    std::shared_ptr<Logger> GetLogger(std::string_view const name) const;
    std::shared_ptr<Logger> DefaultLogger() const;
    Logger* const DefaultLoggerRaw() const;

    void SetDefaultLogger(std::shared_ptr<Logger> logger);

    void SetThreadPool(std::shared_ptr<ThreadPool> threadPool);

    std::shared_ptr<ThreadPool> GetThreadPool() const;

    void SetStylizer(std::unique_ptr<Stylizer> sylizer);

    void SetLevel(Level level);

    void FlushOn(Level level);

    void FlushAll();

    void Drop(std::string const& name);
    void DropAll();

    void Shutdown();

    template<typename Rep, typename Period>
    void FlushEvery(std::chrono::duration<Rep, Period> const& interval)
    {
        std::lock_guard<std::mutex> lock(m_mutex_flusher);
        m_periodic_flusher = std::make_unique<PeriodicWorker>(interval, [this]() {
            FlushAll();
        });
    }

    std::unique_ptr<PeriodicWorker>& GetFlusher()
    {
        std::lock_guard<std::mutex> lock(m_mutex_flusher);
        return m_periodic_flusher;
    }

    std::recursive_mutex & GetMutableThreadPoolMutex()
    {
        return m_mutex_thread_pool;
    }

  private:
    Registry();
    ~Registry();

    std::mutex m_mutex_logger_map;
    std::mutex m_mutex_flusher;
    std::recursive_mutex m_mutex_thread_pool;

    std::unordered_map<std::string, std::shared_ptr<Logger>> m_logger_map;
    std::unique_ptr<Stylizer> m_stylizer;

    std::shared_ptr<ThreadPool> m_thread_pool;
    std::unique_ptr<PeriodicWorker> m_periodic_flusher;
    std::shared_ptr<Logger> m_default_logger;

    Level m_global_level{LEVEL_INFO};
    Level m_global_flush_level{LEVEL_OFF};

    bool automatic_registration{true};
};
}  // namespace logging::Detail