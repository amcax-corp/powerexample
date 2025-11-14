#pragma once
#include <Logging/Detail/RingBuffer.h>
#include <mutex>
#include <optional>
#include <condition_variable>

namespace logging {
namespace Detail {
template<typename T>
class MPMCQueue
{
  public:
    using value_type = T;
    explicit MPMCQueue(std::size_t max_size)
      : m_buffer(max_size)
    {}

    /**
    * @brief 等到有空位时，将数据放入队列，会阻塞
    * 
    * @param item 
    */
    void Enqueue(T&& item)
    {
        {
            std::unique_lock<std::mutex> lock(m_buffer_mutex);
            m_pop_cv.wait(lock, [this]() {
                return !m_buffer.Full();
            });
            m_buffer.Push(std::move(item));
        }
        m_push_cv.notify_one();
    }

    /**
    * @brief 立即将数据放入队列，如果队列已满，则冲掉头部数据
    * 
    * @param item 
    */
    void EnqueueImediate(T&& item)
    {
        {
            std::unique_lock<std::mutex> lock(m_buffer_mutex);
            m_buffer.Push(std::move(item));
        }
        m_push_cv.notify_one();
    }

    void EnqueueIfNotFull(T&& item){
        bool pushed = false;
        std::unique_lock<std::mutex> lock(m_buffer_mutex);
        if (!m_buffer.Full())
        {
            m_buffer.Push(std::move(item));
            pushed = true;
        }
        
        if (pushed)
        {
            m_push_cv.notify_one();
        }else{
            ++m_discard_counter;
        }
        
    }


    /**
    * @brief 等待一段时间，如果不空，则取出数据，否则返回空
    * 
    * @param timeout 
    * @return std::optional<T&> 
    */
    std::optional<T> DequeueFor(std::chrono::milliseconds timeout)
    {
        std::optional<T> item = std::nullopt;
        {
            std::unique_lock<std::mutex> lock(m_buffer_mutex);
            if (!m_push_cv.wait_for(lock, timeout, [this]() {
                    return !m_buffer.Empty();
                }))
            {
                return item;
            }
            item = m_buffer.Front();
            m_buffer.Pop();
        }
        m_pop_cv.notify_one();
        return item;
    }

    /**
    * @brief 等待直到队列不空时，Pop，会阻塞
    * 
    * @return T 
    */
    T Dequeue()
    {
        std::optional<T> item;
        {
            std::unique_lock<std::mutex> lock(m_buffer_mutex);
            m_push_cv.wait(lock, [this]() {
                return !m_buffer.Empty();
            });
            item.emplace(std::move(m_buffer.Front()));
            m_buffer.Pop();
        }
        m_pop_cv.notify_one();
        return std::move(*item);
    }

    std::size_t Size() const
    {
        return m_buffer.Size();
    }

    std::size_t OverrunCounter() const
    {
        return m_buffer.OverrunCounter();
    }

    void ResetOverrunCounter()
    {
        std::unique_lock<std::mutex> lock(m_buffer_mutex);
        m_buffer.ResetOverrunCounter();
    }

    std::size_t DiscardCounter() const
    {
        return m_discard_counter.load(std::memory_order_relaxed);
    }
    void ResetDiscardCounter()
    {
        m_discard_counter.store(0, std::memory_order_relaxed);
    }

  private:
    std::mutex m_buffer_mutex;
    std::condition_variable m_push_cv;
    std::condition_variable m_pop_cv;
    RingBuffer<T> m_buffer;
    std::atomic<std::size_t> m_discard_counter{0};
};
}  // namespace Detail
}  // namespace logging