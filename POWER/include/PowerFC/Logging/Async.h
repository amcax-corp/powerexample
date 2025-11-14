#pragma once
#include <Logging/Detail/Registry.h>
#include <Logging/Detail/ThreadPool.h>
namespace logging {

inline void InitThreadPool(size_t buffer_size, size_t number_of_workers, std::function<void()> on_thread_start, std::function<void()> on_thread_stop)
{
    auto tp = std::make_shared<Detail::ThreadPool>(buffer_size, number_of_workers, on_thread_start, on_thread_stop);
    Detail::Registry::Instance().SetThreadPool(tp);
}

inline void InitThreadPool(size_t buffer_size, size_t number_of_workers, std::function<void()> on_thread_start)
{
    InitThreadPool(buffer_size, number_of_workers, on_thread_start, []() {});
}

inline void InitThreadPool(size_t buffer_size, size_t number_of_workers)
{
    InitThreadPool(buffer_size, number_of_workers, []() {}, []() {});
}
}  // namespace logging
