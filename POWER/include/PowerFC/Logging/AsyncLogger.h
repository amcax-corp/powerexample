#pragma once
#include <Logging/Logger.h>
#include <Logging/AsyncOverflowPolicy.h>
#include <memory>

namespace logging {
namespace Detail {
class ThreadPool;
}

class LOGGING_API AsyncLogger final : public std::enable_shared_from_this<AsyncLogger>,public Logger
{
    friend class Detail::ThreadPool;

  public:
    AsyncLogger(std::string_view name,
                std::vector<std::shared_ptr<ISink>> const& sinks,
                std::weak_ptr<Detail::ThreadPool> thread_pool,
                AsyncOverflowPolicy overflow_policy = AsyncOverflowPolicy::Block);

    AsyncLogger(std::string_view name,
                std::shared_ptr<ISink> const& sinks,
                std::weak_ptr<Detail::ThreadPool> thread_pool,
                AsyncOverflowPolicy overflow_policy = AsyncOverflowPolicy::Block);

    std::shared_ptr<Logger> Clone(std::string_view new_name) const override;

  protected:
    void LogItImpl(Recorder&& recorder) override;
    void FlushImpl() override;
    void BackendSinkIt(Recorder&& incoming_recorder);
    void BackendFlushImpl();

  private:
    std::weak_ptr<Detail::ThreadPool> m_thread_pool;
    AsyncOverflowPolicy m_overflow_policy{AsyncOverflowPolicy::Block};
};
}  // namespace logging
