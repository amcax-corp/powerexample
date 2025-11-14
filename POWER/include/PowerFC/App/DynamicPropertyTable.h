/**
 * @file DynamicPropertyTable.h
 * @author 王康 (wkcagd@hotmail.com)
 * @brief 实现动态属性表，用于对象在运行时添加或删除属性
 * @version 0.1
 * @date 2025-03-13
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef POWERFC_APP_DYNAMIC_PROPERTY_TABLE_H
#define POWERFC_APP_DYNAMIC_PROPERTY_TABLE_H

#pragma once

#include <App/PropertyFlags.h>
#include <Base/Persistence.h>
#include <map>
#include <memory>
#include <vector>
#include <functional>

namespace app {
class Property;
class PropertyContainer;
}  // namespace app

namespace base {
class XMLReader;
class XMLWriter;
}  // namespace base

namespace app {

class PFC_APP_API DynamicPropertyTable
{
  public:
    struct PropertyData
    {
        std::unique_ptr<Property> property;
        std::string name;
        std::string group;
        std::string description;
        PropertyFlags flags;
        // short attributes;
        // bool read_only;
        // bool hidden;
        PropertyData() = default;

        //构建一个构造函数
        PropertyData(std::unique_ptr<Property>&& property,
                     std::string_view name = {},
                     std::string_view group = {},
                     std::string_view description = {},
                     PropertyFlags flags = {});
        ~PropertyData();

        std::string_view GetName() const
        {
            return name;
        }

        Property* GetProperty() const
        {
            return property.get();
        }
    };

    DynamicPropertyTable();
    virtual ~DynamicPropertyTable();

    void GetPropertyList(std::vector<Property*>& property_list) const;
    void GetPropertyMap(std::map<std::string_view, Property*>& property_map) const;
    void GetPropertyNamedList(std::vector<std::pair<std::string_view, Property*>>& List) const;

    void VisitProperties(const std::function<void(Property*)>& visitor) const;

    Property* GetDynamicPropertyByName(std::string_view name) const;

    /**
     * @brief 根据属性类型名，属性名，属性组，属性描述，属性标志，是否只读，是否隐藏，添加动态属性
     * 
     * @param owner 动态属性的所有者
     * @param property_class_name 
     * @param property_name 
     * @param property_group 
     * @param property_description 
     * @param property_flags 
     * @param is_read_only 
     * @param is_hidden 
     * @return Property* 
     * @exception base::PropertyError 如果property_name为空，或者已存在，则抛出base::PropertyError异常
     * @exception 如果property_class_name不是一个属性类型，抛出异常
        @code
        AddDynamicProperty(..., ..., "Base","blah", Prop_ReadOnly | Prop_Hidden);
        @endcode
        is equivalent to
        @code
        AddDynamicProperty(..., ..., "Base","blah", Prop_None, true, true);
        @endcode
     */
    Property* AddDynamicProperty(PropertyContainer& owner,
                                 std::string_view property_class_name,
                                 std::string_view property_name,
                                 std::string_view property_group = {},
                                 std::string_view property_description = {},
                                 PropertyFlags property_flags = {},
                                 const bool is_read_only = false,
                                 const bool is_hidden = false);

    Property* AddDynamicProperty(PropertyContainer& owner,
                                 base::Type property_class,
                                 std::string_view property_name,
                                 std::string_view property_group = {},
                                 std::string_view property_description = {},
                                 PropertyFlags property_flags = {},
                                 const bool is_read_only = false,
                                 const bool is_hidden = false);

    /*!
    Removes a dynamic property by name. Returns true if the property is part of the container, otherwise
    false is returned.
    */
    bool RemoveDynamicProperty(std::string_view name);

    std::vector<std::string> GetDynamicPropertyNames() const;

    std::string_view GetPropertyName(const Property* property) const;

    bool HasProperty(const Property* property) const;
    bool HasProperty(std::string_view name) const;

    /** @name 属性对象的变量操作接口*/
    //@{
    PropertyFlags GetPropertyFlags(const Property* property) const;
    PropertyFlags GetPropertyFlags(std::string_view name) const;
    std::string_view GetPropertyGroup(const Property* property) const;
    std::string_view GetPropertyGroup(std::string_view name) const;
    std::string_view GetPropertyDescription(const Property* property) const;
    std::string_view GetPropertyDescription(std::string_view name) const;

    //@}

    //删除所有属性对象
    void Clear();

    std::size_t GetNumberOfDynamicProperties() const;

    const PropertyData* GetDynamicPropertyData(const Property* property) const;
    const PropertyData* GetDynamicPropertyData(std::string_view property) const;

    void Store(const Property* property, base::XMLWriter& writer) const;

    Property* Restore(PropertyContainer& owner,
                      std::string_view property_name,
                      std::string_view property_class_name,
                      base::XMLReader& reader);

  private:
    std::string GetUniquePropertyName(PropertyContainer& owner, std::string_view name) const;

    struct PropertyDataCollection;
    std::unique_ptr<PropertyDataCollection> m_dynamic_property_datas;
};

}  // namespace app

#endif
