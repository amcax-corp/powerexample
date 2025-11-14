/// @file      DynamicAttribute.hpp
/// @brief     The class of DynamicAttribute
/// @details   The class of DynamicAttribute is used to store a dynamic attribute.
/// @copyright Copyright (c) 2025 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX Kernel.
#pragma once
#include "af/attribute/AttributeMeta.hpp"
#include "af/attribute/AttributeTool.hpp"
#include "af/attribute/DynamicAttribute.hpp"
#include <af/attribute/Attribute.hpp>
#include <common/Exception.hpp>
#include <string>
#include <unordered_map>
#include <stdexcept>
#include <memory>

namespace AMCAX {
/// @brief The class of DynamicAttribute
/// @details The class of DynamicAttribute is used to store a user defined attribute.
class DynamicAttribute: public Attribute {
public:
    using value_type = std::unordered_map<std::string, std::shared_ptr<Attribute>>;

    /// @brief Construct a DynamicAttribute with id, metainfo and value
    /// @param id The input id
    /// @param metainfo The input metainfo
    /// @param value The input value
    ATTR_CTOR DynamicAttribute(const std::string &id, AttributeMeta metainfo, value_type value) noexcept: Attribute(id, metainfo), _name_to_field_map(value){
        _type = AttributeType::DYNAMIC_ATTRIBURTE;
    }
    
    /// @brief Construct a default DynamicAttribute
    /// @details Costruct with no argument list, the id is "".
    ATTR_CTOR DynamicAttribute() noexcept: DynamicAttribute("", MetaSet::Dynamic, {}) {};

    /// @brief Construct a DynamicAttribute with id
    /// @param id The input id
    ATTR_CTOR DynamicAttribute(const std::string &id) noexcept: DynamicAttribute(id, MetaSet::Dynamic, {}) {}

    /// @brief Construct a DynamicAttribute with id and value
    /// @param id The input id
    /// @param value The input value
    ATTR_CTOR DynamicAttribute(const std::string &id, value_type value) noexcept: AMCAX::DynamicAttribute(id, MetaSet::Dynamic, value) {}

public:
    /// @brief Add a named field to the DynamicAttribute
    /// @param name The name of the field
    /// @param args The arguments to initialize the field
    template<class _Attr, class... Args>
    void AddNamedField(const std::string &name, Args... args) {
        auto newAttr = std::make_shared<_Attr>();
        newAttr->SetValue(std::forward<Args>(args)...);
        _name_to_field_map[name] = newAttr;
    }

    /// @brief Add a field to the DynamicAttribute
    /// @param name The name of the field
    /// @param attr The attribute to be added
    void AddField(const std::string &name, std::shared_ptr<Attribute> attr) {
        _name_to_field_map[name] = attr;
    }

    /// @brief Get the named_field_map from the DynamicAttribute
    /// @return The named_field_map
    std::unordered_map<std::string, std::shared_ptr<Attribute>> GetNamedFields() const noexcept {
        return _name_to_field_map;
    }

    /// @brief Remove a named field from the DynamicAttribute by name
    /// @param name The name of the field
    void RemoveField(const std::string &name) {
        auto field_iter = _name_to_field_map.find(name);
        if (field_iter != _name_to_field_map.end()) {
            _name_to_field_map.erase(field_iter);
        }
    }

    /// @brief Get a named field from the DynamicAttribute by name
    /// @tparam _Attr The attribute type
    /// @param name The name of the field
    /// @return The named field
    template<class _Attr>
    const _Attr &GetFieldAs(const std::string &name) {
        static_assert(std::is_base_of_v<Attribute, _Attr>, "Type argument `_Attr` must be a subclass of `Attribute`.");
        auto field_index_iter = _name_to_field_map.find(name);
        auto found = field_index_iter != _name_to_field_map.end();
        Throw_No_Such_Object_if(!found, "No such field");
        return _name_to_field_map[name]->As<_Attr>();
    }

    /// @brief Set the value of a named field in the DynamicAttribute by name and value
    /// @tparam _Attr The attribute type
    /// @tparam Args The input values
    /// @param name The name of the field
    /// @param args The arguments to initialize the field
    template<class _Attr, class... Args>
    void SetFieldValue(const std::string &name, Args... args) {
        static_assert(std::is_base_of_v<Attribute, _Attr>, "Type argument `_Attr` must be a subclass of `Attribute`.");
        auto attr = GetFieldAs<_Attr>(name);
        RemoveField(name);
        auto new_attr = std::make_shared<_Attr>(attr.ID(), std::forward<Args>(args)...);
        AddField(name, new_attr);
    }

    /// @brief Get the value of a named field in the DynamicAttribute by name
    /// @tparam _Attr The attribute type
    /// @param name The name of the field
    /// @return The value of the field
    template<class _Attr, class R = typename attribute_trait<_Attr>::value_type>
    R GetFieldValue(const std::string &name) {
        auto attr = GetFieldAs<_Attr>(name);
        return std::forward<R>(attr.GetValue());
    }

    /// @brief Implement the clone function to create a new instance of DynamicAttribute
    /// @return A new instance of DynamicAttribute
    std::shared_ptr<Attribute> Clone() override {
        auto clone = new DynamicAttribute(_attr_id, _metainfo, _name_to_field_map);
        clone->_attr_id = _attr_id;
        return std::shared_ptr<Attribute>(clone);
    }

    /// @brief Get named fileds count
    /// @return The size of the items of the DynamicAttribute
    size_t NamedSize() const noexcept {
        return _name_to_field_map.size();
    }

    /// @brief Clear fields
    /// @details The items of the DynamicAttribute will be cleared
    void Clear() noexcept {
        _name_to_field_map.clear();
    }

    /// @brief Get the value of the DynamicAttribute
    /// @return The value of the DynamicAttribute
    value_type GetValue() const {
        return  _name_to_field_map;
    }

    /// @brief Add A pair of field-attribute to the DynamicAttribute
    /// @param name The field name
    /// @param attr The input attribute
    void SetFieldValue(const std::string& name, std::shared_ptr<Attribute> attr) {
        _name_to_field_map[name] = attr;
    }

    /// @brief Set the value of the DynamicAttribute
    /// @param value The value to set
    void SetValue(value_type& value) {
        _name_to_field_map = value;
    }
    
    /// @brief Serialize the attribute to string
    /// @return The serialized string
    AMCAX_API std::string Serialize() const override;

private:
    // Be used to get field by it's name.
    std::unordered_map<std::string, std::shared_ptr<Attribute>> _name_to_field_map;
};

}  // namespace AMCAX