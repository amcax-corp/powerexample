/// @file      FloatPointAttribute.hpp
/// @brief     The class of FloatingPotintAttribute
/// @details   The class of FloatingPotintAttribute is used to store a floating point value. The value can be float or double.
/// @copyright Copyright (c) 2025 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX Kernel.
#pragma once
#include <af/attribute/Attribute.hpp>
#include <common/Macros.hpp>
#include <memory>
#include <string>

namespace AMCAX {

/// @brief   The template class of FloatingPotintAttribute
/// @details The template class of FloatingPotintAttribute is used to store a floating point value. The value can be float or double
/// @tparam  T The float or double
template<class T>
class FloatingPotintAttribute: public Attribute {
    static_assert(std::is_floating_point_v<T>, "`T` must be a floating point type.");

public:
    using value_type = std::decay_t<T>;
    constexpr static AttributeMeta default_meta = MetaSet::Persistable | MetaSet::HasDefaultValue;

public:
    /// @brief Construct a FloatingPotintAttribute with id, metainfo and value
    /// @param id The input id
    /// @param metainfo The input metainfo
    /// @param value The input value
    ATTR_CTOR FloatingPotintAttribute(const std::string& id, AttributeMeta metainfo, value_type value) noexcept: _data{value}, Attribute{id, metainfo} {
        if (std::is_same_v<T, float>) {
            _type = AttributeType::FLOAT_ATTRIBUTE;
        }  else if (std::is_same_v<T, double>) {
            _type = AttributeType::DOUBLE_ATTRIBUTE;
        }
    }

    /// @brief Construct a FloatingPotintAttribute with id and value
    /// @param id The input id
    /// @param value The input value
    ATTR_CTOR FloatingPotintAttribute(const std::string& id, value_type value) noexcept: FloatingPotintAttribute(id, default_meta, value) {}

    /// @brief Construct a default FloatingPotintAttribute, the id is ""
    ATTR_CTOR FloatingPotintAttribute() noexcept: FloatingPotintAttribute{"", default_meta, 0.0} {}

public:
    /// @brief Set the value of the FloatingPotintAttribute
    /// @param value The value to set
    void SetValue(value_type value) {
        _data = value;
    }

    /// @brief Get the value of the FloatingPotintAttribute
    /// @return The value of the FloatingPotintAttribute
    value_type GetValue() const {
        return _data;
    }

    /// @brief Implement the clone function to create a new instance of FloatingPotintAttribute
    /// @return A new instance of FloatingPotintAttribute
    std::shared_ptr<Attribute> Clone() override {
        auto cloned_attr = std::make_shared<FloatingPotintAttribute>(_attr_id, _metainfo, _data);
        cloned_attr->_attr_id = _attr_id;
        return cloned_attr;
    }

    /// @brief Serialize the attribute to string
    /// @return The serialized string
    AMCAX_API std::string Serialize() const override;

private:
    value_type _data;
};

using FloatAttribute = FloatingPotintAttribute<float>;
using DoubleAttribute = FloatingPotintAttribute<double>;
}  // namespace AMCAX