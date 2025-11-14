#ifndef _POWERFC_BASE_STATICPROPERTYDATA_H_
#define _POWERFC_BASE_STATICPROPERTYDATA_H_
#pragma once
#include <App/PropertyFlags.h>
#include <limits>
#include <map>
#include <memory>
#include <functional>
#include <string_view>
#include <vector>

namespace app {
class Property;
class PropertyContainer;
class Extension;
}  // namespace app

namespace app {
class PFC_APP_API StaticPropertyTable
{
  public:
    struct PropertySpec
    {
        short offset;  //静态属性成员变量地址相对于类起始地址的偏移量
        std::string_view name;
        std::string_view group;
        std::string_view description;
        PropertyFlags flags;
    };

    struct OffsetBase
    {
        //获取偏移量
        short GetOffsetTo(const void* ptr_property) const
        {
            auto* pointer = (const char*)ptr_property;
            auto* base = (const char*)owner;
            if (pointer < base || pointer > base + std::numeric_limits<short>::max())
                return -1;
            return (short)(pointer - base);
        }

        //获取基准指针
        char* GetBasePointer() const
        {
            return (char*)owner;
        }

        OffsetBase(const PropertyContainer* owner)
          : owner(owner)
        {}

        OffsetBase(const Extension* owner)
          : owner(owner)
        {}

        const void* owner;
    };

  public:
    /**添加一个PropertySpec，并返回指向property的指针 */
    Property* AddProperty(OffsetBase offset_base,
                          Property* property_pointer,
                          std::string_view property_name,
                          PropertyFlags property_flags = {},
                          std::string_view property_group = {},
                          std::string_view property_description = {});

    const PropertySpec* FindProperty(OffsetBase offset_base, std::string_view property_name) const;
    const PropertySpec* FindProperty(OffsetBase offset_base, const Property* property_pointer) const;

    std::string_view GetPropertyName(OffsetBase offset_base, const Property* property_pointer) const;
    PropertyFlags GetPropertyFlags(OffsetBase offset_base, const Property* property_pointer) const;
    PropertyFlags GetPropertyFlags(OffsetBase offset_base, std::string_view property_name) const;
    std::string_view GetPropertyGroup(OffsetBase offset_base, std::string_view property_name) const;
    std::string_view GetPropertyGroup(OffsetBase offset_base, const Property* property_pointer) const;
    std::string_view GetPropertyDescription(OffsetBase offset_base, std::string_view property_name) const;
    std::string_view GetPropertyDescription(OffsetBase offset_base, const Property* property_pointer) const;
    
    bool HasProperty(OffsetBase offset_base, const Property* property_pointer) const;

    Property* GetPropertyByName(OffsetBase offset_base, std::string_view property_name) const;
    void GetPropertyMap(OffsetBase offset_base, std::map<std::string_view, Property*>& property_map) const;
    void GetPropertyList(OffsetBase offset_base, std::vector<Property*>& property_list) const;
    void GetPropertyNamedList(OffsetBase offset_base, std::vector<std::pair<std::string_view, Property*>>& List) const;
    void VisitProperties(OffsetBase offset_base, const std::function<void(app::Property*)>& visitor) const;

    void Merge(StaticPropertyTable* other = nullptr) const;
    void Split(StaticPropertyTable* other);

    StaticPropertyTable(const StaticPropertyTable* parent=nullptr);
    ~StaticPropertyTable();

    void Debug() const;

    friend class PropertyContainer;

  private:
    const StaticPropertyTable* m_parent{nullptr};
    mutable bool m_is_merged{false};

    struct PropertySpecContainer;
    std::unique_ptr<PropertySpecContainer> m_property_specs;
};
}  // namespace app
#endif