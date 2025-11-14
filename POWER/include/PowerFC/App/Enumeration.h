#ifndef POWERFC_APP_ENUMERATION_H_
#define POWERFC_APP_ENUMERATION_H_
#pragma once

#include <PFCGlobal.h>
#include <memory>
#include <string>
#include <string_view>
#include <variant>
#include <vector>

namespace app {

struct PFC_APP_API Enumeration
{
    template<std::size_t... N>
    constexpr Enumeration(const char (&... names)[N])
      : m_index(0)
      , m_enums{std::vector<std::string_view>{names...}}
    {}

    Enumeration(std::vector<std::string>&& names)
      : m_index(0)
      , m_enums(std::make_shared<std::vector<std::string>>(std::move(names)))
    {
    }

    template<std::size_t... N>
    void SetEnums(const char (&... names)[N])
    {
        bool is_valid = IsValid();
        std::string old_value = std::string{GetString()};
        auto values = std::vector<std::string_view>{names...};
        if (is_valid)
        {
            auto iter = std::find(values.begin(), values.end(), old_value);
            if (iter == values.end())
            {
                m_index = 0;
            }
            else
            {
                m_index = std::distance(values.begin(), iter);
            }
        }
        m_enums = values;
    }

    //!@brief 重新设置所有的枚举值字符串，并尝试将当前值设置为旧值，
    // 如果旧值不在新的枚举范围中，则设置为第一个
    //!@param names 枚举值字符串
    void SetEnums(std::vector<std::string>&& names);

    //!@brief 判断是否为编译期确定的枚举范围，如果是，则返回false，否则返回true
    //使用编译器字符串常量列表初始化时，返回false
    //使用std::vector<std::string>初始化时，返回true
    bool IsCustom() const
    {
        return m_enums.index() == 1;
    }

    //!@brief 判断当前枚举值是否在枚举范围内
    bool IsValid() const
    {
        return (m_enums.index() != std::variant_npos) && (m_index < NumberOfEnums());
    }

    //!@brief 返回当前枚举值的索引，如果不在枚举范围内，则返回-1
    std::size_t GetIndex() const
    {
        return m_index < NumberOfEnums() ? m_index : -1;
    }

    //!@brief 返回当前枚举值的字符串，如果不在枚举范围内，则会抛出异常
    std::string_view GetString() const
    {
        return GetString(m_index);
    }

    //!@brief 返回指定索引的枚举值
    //!@exception 如果index不在枚举范围内，则抛出base::ValueError
    std::string_view GetString(std::size_t index) const;

    //!@brief 设置指定索引为枚举值
    //!@exception 如果index不在枚举范围内，则抛出base::ValueError
    void SetIndex(std::size_t index);

    //!@brief 设置指定字符串为枚举值
    //!@exception 如果str不是合法的枚举值，则抛出base::ValueError
    void SetString(std::string_view str);

    //!@brief 返回指定字符串在枚举中的索引，如果不存在，则返回-1
    std::size_t GetIndex(std::string_view str) const;

    //!@brief 返回枚举是否包含指定的字符串
    bool Contain(std::string_view str) const;

    bool IsEmpty() const
    {
        return (m_enums.index() == std::variant_npos) || NumberOfEnums() == 0;
    }

    std::size_t NumberOfEnums() const;

    std::vector<std::string> GetEnumVector() const;

    bool operator==(const Enumeration& other) const;

    bool operator==(std::string_view str) const
    {
        return IsValid() ? GetString() == str : false;
    }

  private:
    std::size_t m_index = -1;
    std::variant<std::vector<std::string_view>, std::shared_ptr<std::vector<std::string>>> m_enums;
};

}  // namespace app

#endif