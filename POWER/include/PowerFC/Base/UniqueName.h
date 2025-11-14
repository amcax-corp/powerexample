#pragma once
#include <cstdint>
#include <string>
#include <vector>
#include <string_view>

namespace base{
class UniqueName{
    public:
    UniqueName(std::string const&name, const std::vector<std::string>& names, std::uint32_t padding);

    std::string const& GetName() const;

    private:
    static std::pair<std::string_view, std::string_view> SplitName(std::string_view name);
    static bool NumberSuffixLess(std::string const& lhs, std::string const& rhs);
    static std::string IncreaseNumberSuffix(std::string_view numbr_suffix);

    private:
    std::string m_name;

};

}