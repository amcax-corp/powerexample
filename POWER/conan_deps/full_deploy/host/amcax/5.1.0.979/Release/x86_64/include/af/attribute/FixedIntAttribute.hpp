/// @file      FixedIntAttribute.hpp
/// @brief     The class of FixedIntAttribute
/// @details   The class of FixedIntAttribute is used to store a fixed-width integer value. The width can be 8, 16, 32, or 64 bits, and the value can be signed or unsigned.
/// @copyright Copyright (c) 2025 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX Kernel.
#pragma once
#include <af/attribute/Attribute.hpp>
#include <common/Macros.hpp>
#include <memory>
#include <string>

namespace AMCAX {

/// @brief   The template class of FixedIntAttribute
/// @details The template class of FixedIntAttribute is used to store a fixed-width integer value. The width can be 8, 16, 32, or 64 bits, and the value can be signed or unsigned.
/// @tparam _Width The width of the IntAttribute
/// @tparam _Signed The sign to indicate whether the attribute value is signed
template<size_t _Width, bool _Signed>
class FixedIntAttribute : public Attribute {
    static_assert(_Width == 8 || _Width == 16 || _Width == 32 || _Width == 64);

private:
    // Helper templates
    template<size_t W, bool S>
    struct fixed_int {};

    template<bool S>
    struct fixed_int<8, S> {
        using type = std::conditional_t<S, int8_t, uint8_t>;
    };

    template<bool S>
    struct fixed_int<16, S> {
        using type = std::conditional_t<S, int16_t, uint16_t>;
    };

    template<bool S>
    struct fixed_int<32, S> {
        using type = std::conditional_t<S, int32_t, uint32_t>;
    };

    template<bool S>
    struct fixed_int<64, S> {
        using type = std::conditional_t<S, int64_t, uint64_t>;
    };

public:
    // Type define
    using value_type = typename fixed_int<_Width, _Signed>::type;
    constexpr static AttributeMeta default_meta = MetaSet::Persistable | MetaSet::HasDefaultValue;

public:
    /// @brief Construct a FixedIntAttribute with id, metainfo and value
    /// @param id The input id
    /// @param metainfo The input metainfo
    /// @param value The input value
    ATTR_CTOR FixedIntAttribute(const std::string& id, AttributeMeta metainfo, value_type value) noexcept: _data{value}, Attribute{id, metainfo} {
        if constexpr (_Width == 8 && !_Signed) {
            _type = AttributeType::UINT8_ATTRIBUTE;
        } else if constexpr (_Width == 8 && _Signed) {
            _type = AttributeType::INT8_ATTRIBUTE;
        } else if constexpr (_Width == 16 && !_Signed) {
            _type = AttributeType::UINT16_ATTRIBUTE;
        } else if constexpr (_Width == 16 && _Signed) {
            _type = AttributeType::INT16_ATTRIBUTE;
        } else if constexpr (_Width == 32 && !_Signed) {
            _type = AttributeType::UINT32_ATTRIBUTE;
        } else if constexpr (_Width == 32 && _Signed) {
            _type = AttributeType::INT32_ATTRIBUTE;
        } else if constexpr (_Width == 64 && !_Signed) {
            _type = AttributeType::UINT64_ATTRIBUTE;
        } else if constexpr (_Width == 64 && _Signed) {
            _type = AttributeType::INT64_ATTRIBUTE;
        }
    }

    /// @brief Construct a FixedIntAttribute with id and value
    /// @param id The input id
    /// @param value The input value
    ATTR_CTOR FixedIntAttribute(const std::string& id, value_type value) noexcept: FixedIntAttribute(id, default_meta, value) {}

    /// @brief Construct a default FixedIntAttribute
    /// @details Costruct with no argument list, the id is ""
    ATTR_CTOR FixedIntAttribute() noexcept: FixedIntAttribute{"", default_meta, 0} {}

public:
    /// @brief Set the value of the FixedIntAttribute
    /// @param value The value to set
    void SetValue(value_type value) {
        _data = value;
    }

    /// @brief Get the value of the FixedIntAttribute
    /// @return The value of the FixedIntAttribute
    value_type GetValue() const {
        return _data;
    }

    /// @brief Implement the clone function to create a new instance of FixedIntAttribute
    /// @return A new instance of FixedIntAttribute
    std::shared_ptr<Attribute> Clone() override {
        auto cloned_attr = std::make_shared<FixedIntAttribute>(_attr_id, _metainfo, _data);
        cloned_attr->_attr_id = _attr_id;
        return cloned_attr;
    }

    /// @brief Serialize the attribute to string
    /// @return The serialized string
    AMCAX_API std::string Serialize() const override;

private:
    value_type _data;
};

template<size_t _Width>
using IntAttribute = FixedIntAttribute<_Width, true>;

template<size_t _Width>
using UnsignedIntAttribute = FixedIntAttribute<_Width, false>;

using Int8Attribute = IntAttribute<8>;
using Int16Attribute = IntAttribute<16>;
using Int32Attribute = IntAttribute<32>;
using Int64Attribute = IntAttribute<64>;
using UInt8Attribute = UnsignedIntAttribute<8>;
using UInt16Attribute = UnsignedIntAttribute<16>;
using UInt32Attribute = UnsignedIntAttribute<32>;
using UInt64Attribute = UnsignedIntAttribute<64>;
}  // namespace AMCAX