#pragma once
#include <cassert>
#include <queue>
namespace base {
class IDProvider
{
  public:
    using value_type = uint32_t;

    value_type next()
    {
        if (m_heap.empty())
        {
            return m_last++;
        }
        else
        {
            auto const v = m_heap.top();
            m_heap.pop();
            return v;
        }
    }
    std::uint32_t Provide()
    {
        return next();
    }
    bool done() const
    {
        return m_heap.empty() && m_last == std::numeric_limits<uint32_t>::max();
    }
    value_type value() const
    {
        return m_last;
    }

    //it is not allowed to recycle a value repeatly
    void Recycle(std::uint32_t v)
    {
        if (v < m_last)
        {
            m_heap.push(v);
        }
    }

  private:
    std::uint32_t m_last{0};
    std::priority_queue<uint32_t, std::vector<uint32_t>, std::greater<uint32_t>> m_heap;
};


}  // namespace base