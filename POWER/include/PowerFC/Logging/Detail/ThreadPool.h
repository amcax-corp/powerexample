#pragma once
#include <Logging/AsyncOverflowPolicy.h>
#include <Logging/Detail/MPMCQueue.h>
#include <Logging/Recorder.h>
#include <functional>
#include <memory>
#include <thread>
#include <vector>

namespace logging {
class AsyncLogger;
}

namespace logging::Detail {

class AsyncTask
{
  public:
    enum class Type
    {
        Log,
        Flush,
        Terminate
    };

  public:
    AsyncTask::Type type{AsyncTask::Type::Log};
    std::shared_ptr<AsyncLogger> worker{nullptr};
    Recorder m_recorder;

    AsyncTask(std::shared_ptr<AsyncLogger> logger, AsyncTask::Type type, Recorder&& recorder)
      : worker{logger}
      , type{type}
      , m_recorder(std::move(recorder))
    {}

    AsyncTask(std::shared_ptr<AsyncLogger> logger, AsyncTask::Type type)
      : worker{logger}
      , type{type}
    {}

    AsyncTask() = default;
};

class LOGGING_API ThreadPool
{
  public:
    ThreadPool(std::size_t max_queue_size,
               std::size_t num_threads,
               std::function<void()> on_thread_start,
               std::function<void()> on_thread_stop);

    ThreadPool(std::size_t max_queue_size,
               std::size_t num_threads,
               std::function<void()> on_thread_start);

    ThreadPool(std::size_t max_queue_size,
               std::size_t num_threads);

    ~ThreadPool();

    ThreadPool(ThreadPool const&) = delete;
    ThreadPool& operator=(ThreadPool const&) = delete;
    void CommitLog(std::shared_ptr<AsyncLogger> logger, Recorder&& recorder, AsyncOverflowPolicy overflow_policy);
    void CommitFlush(std::shared_ptr<AsyncLogger> logger, AsyncOverflowPolicy overflow_policy);
    std::size_t OverrunCounter() const;

  private:
    MPMCQueue<AsyncTask> m_queue;
    std::vector<std::thread> m_threads;

    void CommitAsyncTask(AsyncTask&& task, AsyncOverflowPolicy overflow_policy);
    void WorkLoop();

    bool ProcessNextTask();
};
}  // namespace logging::Detail
