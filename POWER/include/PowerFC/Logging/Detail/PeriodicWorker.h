#pragma once

#include <Logging/Common.h>
#include <chrono>
#include <condition_variable>
#include <functional>
#include <mutex>
#include <thread>

namespace logging::Detail {
class LOGGING_API PeriodicWorker
{
  public:
    template<typename Rep, typename Period>
    PeriodicWorker(std::chrono::duration<Rep, Period> interval, std::function<void()> const& task)
    {
        m_active = (interval > std::chrono::duration<Rep, Period>::zero());
        if (m_active)
        {
            m_thread = std::thread([this, interval, task]() {
                while (true)
                {
                    std::unique_lock<std::mutex> lock(m_mutex);
                    m_cv.wait_for(lock, interval, [this] {
                        return !m_active;
                    });
                    task();
                }
            });
        }
    }

    std::thread& GetThread()
    {
        return m_thread;
    }

    PeriodicWorker(PeriodicWorker const&) = delete;
    PeriodicWorker& operator=(PeriodicWorker const&) = delete;

    /**
     * @brief stop the worker thread and join it
     * 
     */
    ~PeriodicWorker();

  private:
    bool m_active;
    std::mutex m_mutex;
    std::condition_variable m_cv;
    std::thread m_thread;
};
}  // namespace logging::Detail