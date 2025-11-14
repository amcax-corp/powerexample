#ifndef POWERFC_APP_EXTENSION_H
#define POWERFC_APP_EXTENSION_H
#pragma once
#include <App/PropertyContainer.h>
#include <functional>

class PyObject;

namespace app {

class ExtensionContainer;

/**
 * @brief 扩展的类只包含静态属性，通过InitializeExtension接口将属性attach到DocumentObject上
 * 
 */
class PFC_APP_API Extension
{
  public:
    static base::Type GetExtensionClassType();
    virtual base::Type GetExtensionClassTypePolymorphic() const;
    static void* Create();

  public:
    static app::StaticPropertyTable* ExtensionGetStaticPropertyTable();
    virtual app::StaticPropertyTable* ExtensionGetStaticPropertyTablePolymorphic() const;

  public:
    Extension() = default;
    virtual ~Extension();

    /**
     * @brief 初始化扩展，将拓展的属性附加到被扩展的对象上，并完成注册
     * 
     * @param object_extened 
     */
    virtual void InitExtension(app::ExtensionContainer* object_extened);

    //!@return 获取该扩展的owner，即被扩展的对象
    app::ExtensionContainer* GetExtendedOwner()
    {
        return m_owner;
    }

    //!@return 获取该扩展的owner，即该扩展所attach的对象
    const app::ExtensionContainer* GetExtendedOwner() const
    {
        return m_owner;
    }

    /**
     * @brief 获取扩展的名字，即不带命名空间的类名
     * 
     * @return std::string_view 
     * @throw base::RuntimeError 如果扩展类型是Bad，则抛出异常
     */
    std::string_view GetExtensionName() const;

    //!@return 该扩展是否是Python扩展
    bool IsPythonExtension() const;

    //!@return 获取该扩展的Python对象
    virtual PyObject* GetExtensionPyObject();

  public:  //属性接口
    //!@copydoc PropertyContainer::GetPropertytByName
    virtual Property* ExtensionGetPropertyByName(std::string_view name) const;

    //!@copydoc PropertyContainer::GetPropertyName
    virtual std::string_view ExtensionGetPropertyName(const app::Property* property) const;

    //!@copydoc PropertyContainer::GetPropertyMap
    virtual void ExtensionGetPropertyMap(std::map<std::string_view, app::Property*>& property_map) const;

    //!@copydoc PropertyContainer::VisitProperties
    virtual void ExtensionVisitProperties(const std::function<void(app::Property*)>& visitor) const;

    //!@copydoc PropertyContainer::GetPropertyList
    virtual void ExtensionGetPropertyList(std::vector<app::Property*>& property_list) const;

    //!@copydoc PropertyContainer::GetPropertyFlags
    virtual PropertyFlags ExtensionGetPropertyFlags(const app::Property* property) const;

    //!@copydoc PropertyContainer::GetPropertyFlags
    virtual PropertyFlags ExtensionGetPropertyFlags(std::string_view name) const;

  public:  //序列化接口
    //!@copydoc base::Persistence::Store
    virtual void ExtensionStore(base::XMLWriter& writer, unsigned int version) const {}

    //!@copydoc base::Persistence::Restore
    virtual void ExtensionRestore(const base::XMLReader& reader, unsigned int version) {}

    //!@copydoc base::Type::IsDerivedFrom
    bool ExtensionIsDerivedFrom(const base::Type& type) const
    {
        return GetExtensionClassType().IsSubTypeOf(type);
    }

  protected:
    /**
     * @brief 扩展类型的注册函数
     * 
     * @param class_name 当前扩展的类名
     * @param super_type 当前扩展的父类的类型
     * @param create_instance_func 当前扩展的实例化函数
     * @return base::Type 返回当前扩展注册后的类型
     */
    static base::Type RegisterExtensionType(std::string_view class_name,
                                            const base::Type super_type,
                                            base::Type::CreateInstanceFunc create_instance_func);

    //!@copydoc PropertyContainer::OnPropertyChanged
    virtual void ExtensionOnPropertyChanged([[maybe_unused]] const app::Property* property) {}

    /**
     * @copydoc PropertyContainer::HandleChangedPropertyName
     * 
     * @param reader 
     * @param type_name 
     * @param property_name 
     * @return bool 属性名更改已被当前扩展所处理，则返回true，否则false
     */
    virtual bool ExtensionHandleChangedPropertyName(base::XMLReader& reader,std::uint32_t version, std::string_view type_name, std::string_view property_name);

    /**
     * @copydoc PropertyContainer::HandleChangedPropertyType
     * 
     * @param reader 
     * @param type_name 
     * @param property 
     * @return bool 属性类型更改已被当前扩展所处理，则返回true，否则false
     */
    virtual bool ExtensionHandleChangedPropertyType(base::XMLReader& reader, std::uint32_t version, std::string_view type_name, Property* property);

    friend class app::ExtensionContainer;

  protected:
    bool m_is_py_extension = false;

  private:
    base::Type m_extension_type = base::Type::BadType();
    app::ExtensionContainer* m_owner = nullptr;
};

}  // namespace app

namespace app {

//扩展系统声明宏，在类中声明
#define PFC_EXTENSION_PROPERTY_DECL()                            \
  public:                                                        \
    static base::Type GetExtensionClassType();                   \
    virtual base::Type GetExtensionClassTypePolymorphic() const; \
    static void* Create();                                       \
                                                                 \
  public:                                                        \
    static app::StaticPropertyTable* ExtensionGetStaticPropertyTable();   \
    virtual app::StaticPropertyTable* ExtensionGetStaticPropertyTablePolymorphic() const;

//扩展系统声明宏，带override后缀，用于在派生类中声明
#define PFC_EXTENSION_PROPERTY_DECL_WITH_OVERRIDE()                            \
  public:                                                                 \
    static base::Type GetExtensionClassType();                            \
    virtual base::Type GetExtensionClassTypePolymorphic() const override; \
    static void* Create();                                                \
                                                                          \
  public:                                                                 \
    static app::StaticPropertyTable* ExtensionGetStaticPropertyTable();            \
    virtual app::StaticPropertyTable* ExtensionGetStaticPropertyTablePolymorphic() const override;

//扩展系统实现宏，在类中实现
#define PFC_EXTENSION_PROPERTY_IMPL(_class_, _super_class_)                                                            \
    static const bool UNIQUE_VAR(s_is_extension_registed) = !_class_::GetExtensionClassType().IsBad();                 \
    base::Type _class_::GetExtensionClassType()                                                                        \
    {                                                                                                                  \
        static base::Type s_type = RegisterExtensionType(#_class_, _super_class_::GetExtensionClassType(), &(_class_::Create)); \
        return s_type;                                                                                                 \
    }                                                                                                                  \
    base::Type _class_::GetExtensionClassTypePolymorphic() const                                                       \
    {                                                                                                                  \
        return _class_::GetExtensionClassType();                                                                       \
    }                                                                                                                  \
    void* _class_::Create()                                                                                            \
    {                                                                                                                  \
        return new _class_();                                                                                          \
    }                                                                                                                  \
    app::StaticPropertyTable* _class_::ExtensionGetStaticPropertyTable()                                               \
    {                                                                                                                  \
        static app::StaticPropertyTable s_table(_super_class_::ExtensionGetStaticPropertyTable());                     \
        return &s_table;                                                                                               \
    }                                                                                                                  \
    app::StaticPropertyTable* _class_::ExtensionGetStaticPropertyTablePolymorphic(void) const                          \
    {                                                                                                                  \
        return _class_::ExtensionGetStaticPropertyTable();                                                             \
    }

//扩展系统实现宏，在抽象类中实现
#define PFC_EXTENSION_PROPERTY_IMPL_ABSTRACT(_class_, _super_class_)                                                   \
    static const bool UNIQUE_VAR(s_is_extension_registed) = !_class_::GetExtensionClassType().IsBad();                 \
    template<>                                                                                                         \
    base::Type _class_::GetExtensionClassType()                                                                        \
    {                                                                                                                  \
        static base::Type s_type = RegisterExtensionType(#_class_, _super_class_::GetExtensionClassType(), &(_class_::Create)); \
        return s_type;                                                                                                 \
    }                                                                                                                  \
    template<>                                                                                                         \
    base::Type _class_::GetExtensionClassTypePolymorphic() const                                                       \
    {                                                                                                                  \
        return _class_::GetExtensionClassType();                                                                       \
    }                                                                                                                  \
    template<>                                                                                                         \
    void* _class_::Create()                                                                                            \
    {                                                                                                                  \
        return nullptr;                                                                                                \
    }                                                                                                                  \
    template<>                                                                                                         \
    app::StaticPropertyTable* _class_::ExtensionGetStaticPropertyTable()                                               \
    {                                                                                                                  \
        static app::StaticPropertyTable s_table(_super_class_::ExtensionGetStaticPropertyTable());                     \
        return &s_table;                                                                                               \
    }                                                                                                                  \
    template<>                                                                                                         \
    app::StaticPropertyTable* _class_::ExtensionGetStaticPropertyTablePolymorphic(void) const                          \
    {                                                                                                                  \
        return _class_::ExtensionGetStaticPropertyTable();                                                             \
    }

//扩展系统实现宏，在模板类中实现
#define PFC_EXTENSION_PROPERTY_IMPL_TEMPLATE(_class_, _super_class_)                                                   \
    static const bool UNIQUE_VAR(s_is_extension_registed) = !_class_::GetExtensionClassType().IsBad();                 \
    template<>                                                                                                         \
    base::Type _class_::GetExtensionClassType()                                                                        \
    {                                                                                                                  \
        static base::Type s_type = RegisterExtensionType(#_class_, _super_class_::GetExtensionClassType(), &(_class_::Create)); \
        return s_type;                                                                                                 \
    }                                                                                                                  \
    template<>                                                                                                         \
    base::Type _class_::GetExtensionClassTypePolymorphic() const                                                       \
    {                                                                                                                  \
        return _class_::GetExtensionClassType();                                                                       \
    }                                                                                                                  \
    template<>                                                                                                         \
    void* _class_::Create()                                                                                            \
    {                                                                                                                  \
        return new _class_();                                                                                          \
    }                                                                                                                  \
    template<>                                                                                                         \
    app::StaticPropertyTable* _class_::ExtensionGetStaticPropertyTable()                                               \
    {                                                                                                                  \
        static app::StaticPropertyTable s_table(_super_class_::ExtensionGetStaticPropertyTable());                     \
        return &s_table;                                                                                               \
    }                                                                                                                  \
    template<>                                                                                                         \
    app::StaticPropertyTable* _class_::ExtensionGetStaticPropertyTablePolymorphic(void) const                          \
    {                                                                                                                  \
        return _class_::ExtensionGetStaticPropertyTable();                                                             \
    }
}  // namespace app

namespace app {

//以下宏用在构造函数中需要添加属性，将属性注册到静态属性表中
#define PFC_EXTENSION_ADD_PROPERTY(_prop_, _defaultval_)                                                            \
    do                                                                                                              \
    {                                                                                                               \
        this->_prop_.SetValue _defaultval_;                                                                         \
        ExtensionGetStaticPropertyTable()->AddProperty(static_cast<app::Extension*>(this), &this->_prop_, #_prop_); \
    } while (0)

}  // namespace app
#endif