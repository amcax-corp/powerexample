#pragma once

#include <App/DynamicPropertyTable.h>
#include <App/StaticPropertyTable.h>
#include <Base/Persistence.h>
#include <map>
#include <memory>
#include <string>

namespace app {

class Property;
class PropertyString;
class PropertyFloat;
class PropertyBool;
class PropertyBoolList;
class PropertyFloatList;
class PropertyStringList;
class PropertyEnumeration;
class PropertyInteger;
class PropertyIntegerList;

class PFC_APP_API PropertyContainer : public base::Persistence
{
    PFC_TYPESYSTEM_DECL_WITH_OVERRIDE()

  public:
    PropertyContainer();
    ~PropertyContainer() override = default;

#define DYNAMIC_PROPERTY_ADD_GET_DECL(CLASS_NAME, VALUE_TYPE, DEFAULT_VALUE)                 \
    CLASS_NAME* Add##CLASS_NAME(std::string_view name, VALUE_TYPE const& v = DEFAULT_VALUE); \
    CLASS_NAME* Get##CLASS_NAME(std::string_view name, bool need_create = true);                \
    VALUE_TYPE Get##CLASS_NAME##Value(std::string_view name, VALUE_TYPE const& v = DEFAULT_VALUE);

    DYNAMIC_PROPERTY_ADD_GET_DECL(PropertyString, std::string_view, {});
    DYNAMIC_PROPERTY_ADD_GET_DECL(PropertyInteger, int, 0);
    DYNAMIC_PROPERTY_ADD_GET_DECL(PropertyFloat, double, 0.0);
    DYNAMIC_PROPERTY_ADD_GET_DECL(PropertyBool, bool, false);
    DYNAMIC_PROPERTY_ADD_GET_DECL(PropertyBoolList, std::vector<bool>, {});
    DYNAMIC_PROPERTY_ADD_GET_DECL(PropertyIntegerList, std::vector<long>, {});
    DYNAMIC_PROPERTY_ADD_GET_DECL(PropertyFloatList, std::vector<double>, {});
    DYNAMIC_PROPERTY_ADD_GET_DECL(PropertyStringList, std::vector<std::string>, {});

#undef DYNAMIC_PROPERTY_ADD_GET_DECL

    virtual std::string GetFullName() const
    {
        return {};
    }

    //判断是否包含动态属性
    bool HasDynamicProperty(const Property* prop) const;

    //判断是否包含动态属性
    bool HasDynamicProperty(std::string_view name) const;

    //判断是否包含静态属性
    bool HasStaticProperty(const Property* prop) const;

    //根据属性名获取属性
    virtual Property* GetPropertyByName(std::string_view name) const;

    //获取属性在当前对象中的名字
    virtual std::string_view GetPropertyName(const Property* property) const;

    //获取类所有的属性，包括从父类那继承而来的(静态)属性
    virtual void GetPropertyMap(std::map<std::string_view, Property*>& map) const;

    virtual void VisitProperties(const std::function<void(Property*)>& visitor) const;

    //获取类所有的属性，包括从父类那继承而来的(静态)属性，返回list
    virtual void GetPropertyList(std::vector<Property*>& list) const;

    //获取所有属性和他们的名字，可能有重复的的
    virtual void GetPropertyNamedList(std::vector<std::pair<std::string_view, Property*>>& list) const;

    //一次性设置所有属性的指定(bit)状态位
    void SetPropertyStatus(uint8_t bit, bool value);

    /**属性对象的接口代理 */
    /// get the Type of a Property
    virtual PropertyFlags GetPropertyFlags(const Property* prop) const;
    /// get the Type of a named Property
    virtual PropertyFlags GetPropertyFlags(std::string_view name) const;
    /// get the Group of a Property
    virtual std::string_view GetPropertyGroup(const Property* prop) const;
    /// get the Group of a named Property
    virtual std::string_view GetPropertyGroup(std::string_view name) const;
    /// get the Group of a Property
    virtual std::string_view GetPropertyDescription(const Property* prop) const;
    /// get the Group of a named Property
    virtual std::string_view GetPropertyDescription(std::string_view name) const;
    /// check if the property is read-only
    bool IsReadOnly(const Property* prop) const;
    /// check if the named property is read-only
    bool IsReadOnly(std::string_view name) const;
    /// check if the property is hidden
    bool IsHidden(const Property* prop) const;
    /// check if the named property is hidden
    bool IsHidden(std::string_view name) const;

    //添加一个动态属性
    virtual Property* AddDynamicProperty(std::string_view property_class_name,
                                         std::string_view property_name = {},
                                         PropertyFlags flags = {},
                                         std::string_view group = {},
                                         std::string_view description = {},
                                         bool read_only = false,
                                         bool hidden = false);

  protected:
    virtual Property* AddDynamicProperty(base::Type property_type,
                                         std::string_view property_name = {},
                                         PropertyFlags flags = {},
                                         std::string_view group = {},
                                         std::string_view description = {},
                                         bool read_only = false,
                                         bool hidden = false);

  public:
    virtual bool RemoveDynamicProperty(std::string_view name);

    virtual std::vector<std::string> GetDynamicPropertyNames() const;
    virtual Property* GetDynamicPropertyByName(std::string_view name) const;

  public:
    virtual std::size_t GetEstimatedSize() const override;
    virtual void Store(base::XMLWriter&, std::uint32_t version) const override;
    virtual void Restore(base::XMLReader&, std::uint32_t version) override;
    virtual void BeforeStore() const;

    std::string const& GetPropertyPrefix() const
    {
        return m_property_prefix;
    }
    void SetPropertyPrefix(std::string const& prefix);

  protected:
    /// get called by the container when a property has changed，include status changed and value changed
    virtual void OnPropertyChanged(const Property*) {}
    /// get called before the value changing
    virtual void OnBeforePropertyValueChanging(const Property*) {}

    virtual void OnEarlyChange(const Property*) {}

    virtual void OnPropertyStatusChanged(const Property& property, unsigned long old_status);

  public:
    //@brief 获取当前类型的静态属性表
    static StaticPropertyTable* GetStaticPropertyTable();

    //@brief 获取多态类型的静态属性表
    virtual StaticPropertyTable* GetStaticPropertyTablePolymorphic() const;

    virtual void HandleChangedPropertyName(base::XMLReader& reader,std::uint32_t version, std::string_view  type_name, std::string_view property_name);
    virtual void HandleChangedPropertyType(base::XMLReader& reader,std::uint32_t version, std::string_view  type_name, Property* property);

  private:
    friend class Property;
    friend class DynamicPropertyTable;

  protected:
    DynamicPropertyTable m_dynamic_property_table;

  private:
    PropertyContainer(PropertyContainer const&) = delete;
    PropertyContainer& operator=(PropertyContainer const&) = delete;

    std::string m_property_prefix;

    static StaticPropertyTable s_static_property_table;

  protected:
    static void RegisterStaticPropertyTable(StaticPropertyTable* table, const StaticPropertyTable* parent_table);
};
}  // namespace app

namespace app {

#define _PFC_PROPERTY_DECL(_override_postfix_)                 \
  public:                                                      \
    static app::StaticPropertyTable* GetStaticPropertyTable(); \
    virtual app::StaticPropertyTable* GetStaticPropertyTablePolymorphic() const _override_postfix_;

#define PFC_PROPERTY_DECL() \
    PFC_TYPESYSTEM_DECL()   \
    _PFC_PROPERTY_DECL(/**/)

#define PFC_PROPERTY_DECL_WITH_OVERRIDE() \
    PFC_TYPESYSTEM_DECL_WITH_OVERRIDE()   \
    _PFC_PROPERTY_DECL(override)

#define _PFC_PROPERTY_IMPL(_class_, _parentclass_, _template_prefix_)                                  \
    _template_prefix_ app::StaticPropertyTable* _class_::GetStaticPropertyTable()                      \
    {                                                                                                  \
        static app::StaticPropertyTable s_table(_parentclass_::GetStaticPropertyTable());              \
        return &s_table;                                                                               \
    }                                                                                                  \
    _template_prefix_ app::StaticPropertyTable* _class_::GetStaticPropertyTablePolymorphic(void) const \
    {                                                                                                  \
        return _class_::GetStaticPropertyTable();                                                      \
    }

#define PFC_PROPERTY_IMPL(_class_, _parentclass_) \
    PFC_TYPESYSTEM_IMPL(_class_, _parentclass_)   \
    _PFC_PROPERTY_IMPL(_class_, _parentclass_, )

#define PFC_PROPERTY_IMPL_ABSTRACT(_class_, _parentclass_) \
    PFC_TYPESYSTEM_IMPL_ABSTRACT(_class_, _parentclass_)   \
    _PFC_PROPERTY_IMPL(_class_, _parentclass_, )

#define PFC_PROPERTY_IMPL_TEMPLATE(_class_, _parentclass_) \
    PFC_TYPESYSTEM_IMPL_TEMPLATE(_class_, _parentclass_, template<>)

#define _PFC_ADD_PROPERTY(_name, _prop_, _defaultval_)                                                           \
    do                                                                                                           \
    {                                                                                                            \
        this->_prop_.SetValue _defaultval_;                                                                      \
        this->_prop_.SetOwner(this);                                                                             \
        GetStaticPropertyTable()->AddProperty(static_cast<app::PropertyContainer*>(this), &this->_prop_, _name); \
    } while (0)

#define PFC_ADD_PROPERTY(_prop_, _defaultval_) \
    _PFC_ADD_PROPERTY(#_prop_, _prop_, _defaultval_)

#define _PFC_ADD_PROPERTY_TYPE(_name, _prop_, _defaultval_, _group_, _type_, _desc_)                                                      \
    do                                                                                                                                    \
    {                                                                                                                                     \
        this->_prop_.SetValue _defaultval_;                                                                                               \
        this->_prop_.SetOwner(this);                                                                                                      \
        GetStaticPropertyTable()->AddProperty(static_cast<app::PropertyContainer*>(this), &this->_prop_, _name, _group_, _type_, _desc_); \
    } while (0)

#define PFC_ADD_PROPERTY_TYPE(_prop_, _defaultval_, _group_, _type_, _Docu_) \
    _PFC_ADD_PROPERTY_TYPE(#_prop_, _prop_, _defaultval_, _group_, _type_, _Docu_)
}  // namespace app