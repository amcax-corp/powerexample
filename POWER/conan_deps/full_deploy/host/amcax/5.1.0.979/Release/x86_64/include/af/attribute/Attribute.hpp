/// @file      Attribute.hpp
/// @brief     The class of Attribute.
/// @details   The class of Attribute is the base class of all attribute types. It provides a common interface for all attribute types.
/// @copyright Copyright (c) 2025 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX Kernel.
#pragma once

#include <af/attribute/AttributeException.hpp>
#include <af/attribute/SFINAE.hpp>
#include <af/common/Macros.hpp>
#include <common/Exception.hpp>
#include <common/Macros.hpp>
#include <memory>
#include <string>
#include <type_traits>

namespace AMCAX {


/// @brief The enumeration of attribute type
enum AttributeType : uint64_t {
    STRING_ATTRIBUTE,
    FLOAT_ATTRIBUTE,
    DOUBLE_ATTRIBUTE,
    INT8_ATTRIBUTE,
    INT16_ATTRIBUTE,
    INT32_ATTRIBUTE,
    INT64_ATTRIBUTE,
    UINT8_ATTRIBUTE,
    UINT16_ATTRIBUTE,
    UINT32_ATTRIBUTE,
    UINT64_ATTRIBUTE,
    COLOR_ATTRIBUTE,
    BLOB_ATTRIBUTE,
    ARRAY_ATTRIBUTE,
    DYNAMIC_ATTRIBURTE
};

/// @brief The base class of all attributes
class Attribute {
#ifndef DOXYGEN_SKIP
    friend std::hash<AMCAX::Attribute>;
#endif

public:
    AMCAXAF_API static AttributePolicy policy;

protected:
    /// @brief Construct an attribute with id and meta
    /// @param id The input id
    /// @param meta The input metainfo
    ATTR_CTOR Attribute(std::string_view id, AttributeMeta meta): _attr_id{id}, _metainfo{meta} {}
    
    ATTR_CTOR Attribute() {}

public:

    /// @brief Get the policy of the attribute
    /// @return The policy of the attribute
    AMCAX_API AttributePolicy Policy() const;

    /// @brief Get the attribute ID
    /// @return The attribute id
    AMCAX_API const std::string ID() const;
    
    /// @brief Clone the attribute
    /// @return A new instance of Attribute
    AMCAX_API virtual std::shared_ptr<Attribute> Clone() = 0;

    /// @brief Determine whether an attribute is created anonymously
    /// @return true is represent anonymous
    AMCAX_API bool IsAnonymous() const { return _attr_id == ""; };

    /// @brief Check if the attribute is a specific type
    /// @param type The given type to check
    /// @return True if the attribute is the given type
    AMCAX_API bool IsAttributeOf(AttributeType type) const;

    /// @brief Get the attribute type
    /// @return The attribute type
    AMCAX_API AttributeType Type();

    /// @brief  Cast the attribute to a specific type
    /// @tparam _Attr The specific type
    /// @return The casted attribute
    template<class _Attr>
    const _Attr &As() const {
        auto attrPtr = dynamic_cast<const _Attr*>(this);
        Throw_Null_Object_if(attrPtr == nullptr, "Type missmatch");
        return *attrPtr;
    }

    /// @brief Get the value of the attribute
    /// @return The value of this attribute
    template<class _Attr, class R = typename attribute_trait<_Attr>::value_type>
    decltype(auto) GetValue() const {
        auto attrPtr = dynamic_cast<const _Attr*>(this);
        Throw_Null_Object_if(attrPtr == nullptr, "Type missmatch");
        return attrPtr->GetValue();
    }

    /// @brief Set the value of the attribute
    /// @param args The values to set
    template<typename T, typename ... Args>
    void SetValue(Args... args) {
        if constexpr (std::is_invocable_v<decltype(&T::SetValue), T*, Args...>) {
            static_cast<T &>(*this).SetValue(std::forward<Args>(args)...);
        } else {
            throw BadAttributeValue{""};
        }
    }

    /// @brief Overload the operator == to compare two attributes
    /// @param base The attribute to compare with
    /// @return True if the two attributes are equal, otherwise return false
    AMCAX_API bool operator==(const Attribute& base) const;
    
    /// @brief Serialize the attribute to a string
    /// @return The serialized string
    AMCAX_API virtual std::string Serialize() const = 0;

protected:
    std::string _attr_id;
    AttributeMeta _metainfo;
    AttributeType _type;
};
}

/// @brief Hash function for Attribute
template<>
struct std::hash<AMCAX::Attribute>
{
    /// @brief Hash function for Attribute
    /// @details This function combines the hash of the attribute name and its metadata.
    /// @param attributeBase The attribute base to hash
    /// @return The hash value of the attribute base
	[[nodiscard]] size_t operator()(const AMCAX::Attribute& attributeBase) const noexcept {
        std::size_t h1 = std::hash<std::string>{}(attributeBase._attr_id);
        std::size_t h2 = std::hash<AMCAX::AttributeMeta>()(attributeBase._metainfo); 
        return h1 ^ (h2 << 1);
    }
};
