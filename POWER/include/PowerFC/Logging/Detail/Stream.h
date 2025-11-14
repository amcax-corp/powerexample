#include <format>
#include <sstream>
#include <streambuf>
#include <string>
#include <string_view>

namespace logging::Detail {

template<typename CharT, typename Traits = std::char_traits<CharT>>
struct Stream
{
  private:
    std::basic_ostringstream<CharT, Traits> oss;
    bool enable{true};

  public:
    Stream(bool enable = true)
      : enable(enable)
    {}
    Stream(bool enable, std::string_view s)
      : enable(enable)
    {
        oss << s;
    }

    template<typename T>
    auto& operator<<(T && v)
    {
        if (enable)
            oss << v;
        return *this;
    }

    template<typename... Args>
    auto& operator()(std::format_string<Args...> const& fmt, Args&&... args)
    {
        if (enable)
            std::format_to(std::ostreambuf_iterator(oss), fmt, std::forward<Args>(args)...);
        return *this;
    }

    template<typename T>
    auto& operator()(T && v)
    {
        return operator<<(v);
    }

    std::string_view View() const
    {
        return oss.view();
    }
};
}  // namespace logging::Detail