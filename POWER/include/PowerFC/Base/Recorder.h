#pragma once
#include <PFCGlobal.h>
#include <format>
#include <sstream>

namespace base {
template<typename Derived>
class Recorder
{
  protected:
    std::stringstream stream;

  protected:
    Derived const& Self() const
    {
        return static_cast<const Derived&>(*this);
    }

    Derived& Self()
    {
        return static_cast<Derived&>(*this);
    }

  public:
    template<typename... Args>
    Recorder(std::format_string<Args...> fmt, Args&&... args)
    {
        std::format_to(std::ostreambuf_iterator(stream), fmt, std::forward<Args>(args)...);
    }

    template<typename... Args>
    Derived& operator()(std::format_string<Args...> fmt, Args&&... args) &
    {
        std::format_to(std::ostreambuf_iterator(stream), fmt, std::forward<Args>(args)...);
        return Self();
    }

    template<typename... Args>
    Derived operator()(std::format_string<Args...> fmt, Args&&... args) &&
    {
        std::format_to(std::ostreambuf_iterator(stream), fmt, std::forward<Args>(args)...);
        return std::move(Self());
    }

    auto& GetMutableStream()
    {
        return stream;
    }

    auto const& GetStream() const
    {
        return stream;
    }

    Recorder() = default;
};
}  // namespace base