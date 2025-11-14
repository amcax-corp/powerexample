#pragma once
#include <Logging/AsyncLogger.h>
#include <Logging/Detail/Registry.h>
#include <Logging/Detail/ThreadPool.h>
namespace logging {
namespace Detail {
static const size_t default_async_buffer_size = 1024 * 8;
}

template<AsyncOverflowPolicy policy = AsyncOverflowPolicy::Block>
struct AsyncFactoryImpl
{
    template<typename Sink, typename... SinkArgs>
    static std::shared_ptr<AsyncLogger> Create(std::string const& logger_name, SinkArgs&&... sink_args)
    {
        auto& registry_instance = Detail::Registry::Instance();
        {
            std::lock_guard<std::recursive_mutex> lock(registry_instance.GetMutableThreadPoolMutex());
            //虽然GetThreadPool()和SetThreadPool()都是线程安全的，但为了防止多线程同时调用Create()，这里还是加锁了
            //使用m_mutex_thread_pool同时保护GetThreadPool()和SetThreadPool(),由于GetThreadPool()和SetThreadPool()中也会去加锁m_mutex_thread_pool，
            //所以使用递归锁
            if (auto tp = registry_instance.GetThreadPool();!tp)
            {
                registry_instance.SetThreadPool(std::make_shared<Detail::ThreadPool>(Detail::default_async_buffer_size, 1));
            }
        }
        auto sink = std::make_shared<Sink>(std::forward<SinkArgs>(sink_args)...);
        auto logger = std::make_shared<AsyncLogger>(logger_name, std::move(sink), registry_instance.GetThreadPool(), policy);
        registry_instance.RegisterLogger(logger);

        return logger;
    }
};

using AsyncFactory = AsyncFactoryImpl<AsyncOverflowPolicy::Block>;
using AsyncFactoryNoBlock = AsyncFactoryImpl<AsyncOverflowPolicy::OverrunOldest>;

template<typename Sink, typename... SinkArgs>
auto CreateAsync(std::string const& logger_name, SinkArgs&&... sink_args)
{
    return AsyncFactory::Create<Sink>(logger_name, std::forward<SinkArgs>(sink_args)...);
}

template<typename Sink, typename... SinkArgs>
auto CreateAsyncNoBlock(std::string const& logger_name, SinkArgs&&... sink_args)
{
    return AsyncFactoryNoBlock::Create<Sink>(logger_name, std::forward<SinkArgs>(sink_args)...);
}

//同步工厂
struct SyncFactory
{
    template<typename Sink, typename... SinkArgs>
    static std::shared_ptr<Logger> Create(std::string logger_name, SinkArgs&&... args)
    {
        auto sink = std::make_shared<Sink>(std::forward<SinkArgs>(args)...);
        auto new_logger = std::make_shared<Logger>(std::move(logger_name), std::move(sink));
        Detail::Registry::Instance().RegisterLogger(new_logger);
        return new_logger;
    }
};

template<typename Sink, typename... SinkArgs>
auto CreateSync(std::string const& logger_name, SinkArgs&&... sink_args)
{
    return SyncFactory::Create<Sink>(logger_name, std::forward<SinkArgs>(sink_args)...);
}
}  // namespace logging
