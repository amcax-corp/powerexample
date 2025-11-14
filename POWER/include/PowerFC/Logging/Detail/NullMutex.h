#pragma once

#include <atomic>
#include <utility>
namespace logging {
namespace Detail {
struct NullMutex
{
    void lock() const {}
    void unlock() const {}
};

struct NullAtomicInt{
    int value;
    NullAtomicInt()=default;
    explicit NullAtomicInt(int v):value(v){}
    
    int load(std::memory_order=std::memory_order_relaxed) const{
        return value;
    }

    void store(int v, std::memory_order=std::memory_order_relaxed){
        value=v;
    }

    int exchange(int v, std::memory_order=std::memory_order_relaxed){
        std::swap(value, v);
        return v;
    }
};


}  // namespace Detail
}  // namespace logging