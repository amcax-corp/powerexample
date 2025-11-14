/// @file      ArrayAttribute.hpp
/// @brief     The class of ArrayAttribute
/// @details   This class implements the array attribute of the object.
/// @copyright Copyright (c) 2025 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX Kernel.
#pragma once
#include <af/attribute/Attribute.hpp>
#include <common/Exception.hpp>
#include <string>
#include <vector>
#include <memory>

namespace AMCAX {
/// @brief The templete class of ArrayAttribute
/// @details This class implements the array attribute of the object, for different instance, the guid is same.
/// @tparam _Attr The element type of the ArrayAttribute
template<typename _Attr>
class ArrayAttribute : public Attribute {
public:
    static_assert(
        std::disjunction_v<
            std::is_same<_Attr, int>,
            std::is_same<_Attr, float>,
            std::is_same<_Attr, double>,
            std::is_same<_Attr, char>,
            std::is_same<_Attr, std::string>,
            std::is_same<_Attr, int32_t>,
            std::is_same<_Attr, int64_t>,
            std::is_same<_Attr, uint32_t>,
            std::is_same<_Attr, uint64_t>
        >,
        "ArrayAttribute only supports int, float, double, char, string, "
        "int32_t, int64_t, uint32_t, uint64_t."
    );
    
    using value_type = std::vector<_Attr>;
    static constexpr AttributeMeta default_meta = MetaSet::HasDefaultValue | MetaSet::Persistable;
    
    /// @brief The constructor of the array attribute with id, metainfo and value
    /// @param id The input id
    /// @param metainfo The input metainfo
    /// @param value The input value
    ArrayAttribute(const std::string& id, AttributeMeta metainfo, value_type value) noexcept: Attribute{id, metainfo}, _value{value} {
        _type = ARRAY_ATTRIBUTE;
    }
    
    /// @brief Construct an array attribute with id and N size
    /// @param id The input id
    /// @param N The input size
    ArrayAttribute(const std::string& id, int N): Attribute(id, default_meta) {
        _type = ARRAY_ATTRIBUTE;
        _value.resize(N);
    }
    
    /// @brief Construct an default array attribute
    /// @details Costruct with no argument list, the id is ""
    ArrayAttribute(): ArrayAttribute("", default_meta, {}) {}

    /// @brief The constructor of the array attribute with id and value
    /// @param id The input id
    /// @param value The input value
    ArrayAttribute(const std::string& id, const value_type& value) noexcept: ArrayAttribute{id, default_meta, value} {}
    
    /// @brief Clone the attribute
    /// @return A new instance of ArrayAttribute
    std::shared_ptr<Attribute> Clone() override {
        auto cloned_attr = std::make_shared<ArrayAttribute<_Attr>>(_attr_id, _metainfo, _value);
        return cloned_attr;
    }

    /// @brief Get the size of the array
    /// @return The size of the array
    size_t Size() const {
        return _value.size();
    }

    /// @brief Get the index-th element of the array
    /// @param index The index of the element
    const _Attr& Get(int index) const {
        Throw_Out_of_Range_if(index < 0 || index >= (int)_value.size(), "Index out of range");
        return _value[index];
    }

    /// @brief Set the index-th element of the array
    /// @param index The index of the element
    /// @param value The value to set
    void Set(int index, _Attr value) {
        Throw_Out_of_Range_if(index < 0 || index >= (int)_value.size(), "Index out of range");
        _value[index] = value;
    }

    /// @brief Get the value of the ArrayAttribute
    /// @return The value of the ArrayAttribute
    value_type GetValue() const {
        return _value;
    }

    /// @brief Set the value of the ArrayAttribute
    /// @param value The value to set
    void SetValue(const value_type& value) {
        _value = value;
    }

    AMCAX_API std::string Serialize() const override;

private:
    value_type _value;
};
} // namespace AMCAX