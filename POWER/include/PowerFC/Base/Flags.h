#ifndef POWERFC_BASE_FLAGS_H
#define POWERFC_BASE_FLAGS_H
#pragma once
#include <type_traits>


template<class T = void>
struct enum_traits
{};

template<>
struct enum_traits<void>
{
    struct _allow_bitops
    {
        static constexpr bool allow_bitops = true;
    };
    using allow_bitops = _allow_bitops;

    template<class T, class R = T>
    using t = typename std::enable_if<std::is_enum<T>::value &&
                                          enum_traits<T>::allow_bitops,
                                      R>::type;

    template<class T>
    using u = typename std::underlying_type<T>::type;
};

template<class T>
constexpr enum_traits<>::t<T> operator~(T a)
{
    return static_cast<T>(~static_cast<enum_traits<>::u<T>>(a));
}
template<class T>
constexpr enum_traits<>::t<T> operator|(T a, T b)
{
    return static_cast<T>(
        static_cast<enum_traits<>::u<T>>(a) |
        static_cast<enum_traits<>::u<T>>(b));
}
template<class T>
constexpr enum_traits<>::t<T> operator&(T a, T b)
{
    return static_cast<T>(
        static_cast<enum_traits<>::u<T>>(a) &
        static_cast<enum_traits<>::u<T>>(b));
}
template<class T>
constexpr enum_traits<>::t<T> operator^(T a, T b)
{
    return static_cast<T>(
        static_cast<enum_traits<>::u<T>>(a) ^
        static_cast<enum_traits<>::u<T>>(b));
}
template<class T>
constexpr enum_traits<>::t<T, T&> operator|=(T& a, T b)
{
    a = a | b;
    return a;
}
template<class T>
constexpr enum_traits<>::t<T, T&> operator&=(T& a, T b)
{
    a = a & b;
    return a;
}
template<class T>
constexpr enum_traits<>::t<T, T&> operator^=(T& a, T b)
{
    a = a ^ b;
    return a;
}


#define ENABLE_BITMASK_OPERATORS(x)                     \
    template<>                                          \
    struct enum_traits<x> : enum_traits<>::allow_bitops \
    {};                                                 \

namespace base {

template<typename Enum>
class Flags
{
    static_assert(std::is_enum<Enum>::value, "Flags is only usable on enumeration types.");
    //Enum i{};
    typename std::underlying_type_t<Enum> v{};

  private:
    static constexpr inline typename std::underlying_type_t<Enum> Underling(Enum e)
    {
        return static_cast<typename std::underlying_type_t<Enum>>(e);
    }

  public:
    // Linter seems wrong on next line, don't want explicit here forcing downstream changes
    constexpr inline Flags(Enum e)
      : v(static_cast<std::underlying_type_t<Enum>>(e))
    {}  // NOLINT (runtime/explicit)

    constexpr inline Flags(typename std::underlying_type_t<Enum> const v = 0)
      : v(v)
    {}

    constexpr inline Flags& operator=(typename std::underlying_type_t<Enum> const v)
    {
        this->v = v;
        return *this;
    }

    constexpr inline Flags& operator=(Enum e)
    {
        this->v = Underling(e);
        return *this;
    }

    constexpr bool TestFlag(Enum e) const
    {
        auto u = Underling(e);
        return ((v & u) == u) && (u != 0 || v == u);
    }
    constexpr inline void SetFlag(Enum e, bool on = true)
    {
        on ? (v |= Underling(e)) : (v &= ~Underling(e));
    }
    constexpr bool IsEqual(Flags flags) const
    {
        return v == flags.v;
    }
    constexpr Enum GetFlags() const
    {
        return static_cast<Enum>(v);
    }

    constexpr Flags<Enum>& operator|=(Flags other)
    {
        v |= other.v;
        return *this;
    }

    constexpr Flags<Enum>& operator|=(Enum e)
    {
        v |= Underling(e);
        return *this;
    }

    constexpr Flags<Enum> operator|(Flags other) const
    {
        return Flags<Enum>(v | other.v);
    }
    constexpr Flags<Enum> operator|(Enum e) const
    {
        //return Or(i, f);
        return Flags<Enum>(v | Underling(e));
    }
    constexpr Flags<Enum>& operator&=(Flags other)
    {
        v &= other.v;
        return *this;
    }
    constexpr Flags<Enum>& operator&=(Enum e)
    {
        v &= Underling(e);
        return *this;
    }
    constexpr Flags<Enum> operator&(Flags other) const
    {
        return Flags<Enum>(v & other.v);
    }
    constexpr Flags<Enum> operator&(Enum e) const
    {
        return Flags<Enum>(v & Underling(e));
    }
    constexpr Flags<Enum> operator~() const
    {
        return Flags<Enum>(~v);
    }

    constexpr operator typename std::underlying_type_t<Enum>() const
    {
        return v;
    }

    constexpr operator Enum() const
    {
        return static_cast<Enum>(v);
    }

    explicit operator bool() const
    {
        return v != 0;
    }
};
}  // namespace base

#endif