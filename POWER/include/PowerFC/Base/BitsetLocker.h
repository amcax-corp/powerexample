#ifndef _POWERFC_BASE_BITSETLOCKER_H_
#define _POWERFC_BASE_BITSETLOCKER_H_
#pragma once
#include <cstddef>

namespace base {
template<typename T>
class BitsetLocker
{
public:
    BitsetLocker(T& flags, std::size_t flag, bool value = true)
        : flags(flags)
        , flag(flag)
    {
        old_value = flags.test(flag);
        flags.set(flag, value);
    }
    ~BitsetLocker()
    {
        flags.set(flag, old_value);
    }

private:
    T& flags;
    std::size_t flag;
    bool old_value;
};

template<typename T>
BitsetLocker(T&, std::size_t, bool)->BitsetLocker<T>;

}

#endif