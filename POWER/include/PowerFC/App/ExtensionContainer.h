#ifndef POWERFC_APP_EXTENSIONCONTAINER_H_
#define POWERFC_APP_EXTENSIONCONTAINER_H_

#pragma once
#include <App/Property.h>
#include <App/PropertyContainer.h>

namespace app {

class PFC_APP_API ExtensionContainer : public app::PropertyContainer
{
    PFC_TYPESYSTEM_DECL_WITH_OVERRIDE();

  public:
    using ExtensionIterator = std::map<base::Type, app::Extension*>::iterator;

  public:
    ExtensionContainer();
    ~ExtensionContainer() override;

    /**
     * @brief 注册一个扩展
     * 
     * @param type 扩展的类型
     * @param extension 扩展
     */
    void RegisterExtension(base::Type type, app::Extension* extension);

    /**
     * @brief 是否包含某个指定类型的扩展
     * 
     * @param type 指定的类型
     * @param derived 是否考虑子类型，默认为true
     * @return true 
     * @return false 
     */
    bool HasExtension(base::Type type, bool derived = true) const;

    /**
     * @brief 是否包含指定扩展名(不带命名空间的类名)的扩展，该方法会不检查派生类
     * 
     * @param name 
     * @return true 
     * @return false 
     */
    bool HasExtension(std::string_view extension_name) const;

    //!@return 是否有扩展
    bool HasExtensions() const;

    /**
     * @brief 返回指定类型的扩展
     * 
     * @param type 指定的类型
     * @param include_derived 是否考虑派生类型
     * @param no_exception 没找到时是否抛出异常，默认抛出异常，否则返回nullptr
     * @return app::Extension* 
     */
    app::Extension* GetExtension(base::Type type, bool include_derived = true, bool no_exception = false) const;

    /**
     * @brief 返回指定类型名的扩展，不考虑派生类，如果找不到返回空指针
     * 
     * @param name 
     * @return app::Extension* 
     */
    app::Extension* GetExtension(std::string_view name) const;

    /**
     * @brief 模板方法获取指定类型的扩展，考虑派生类，如果找不到返回空指针。
     * 
     * @tparam ExtensionT 
     * @param include_derived 
     * @param no_exception 
     * @return ExtensionT* 
     */
    template<typename ExtensionT>
    ExtensionT* GetExtension(bool include_derived = true, bool no_exception = true) const
    {
        return static_cast<ExtensionT*>(GetExtension(ExtensionT::GetExtensionClassType(), include_derived, no_exception));
    }

    /**
     * @brief 获取继承自指定类型的所有扩展
     * 
     * @param type 
     * @return std::vector<Extension*> 
     */
    std::vector<Extension*> GetExtensionsDerivedFrom(base::Type type) const;

    template<typename ExtensionT>
    std::vector<ExtensionT*> GetExtensionsDerivedFrom() const
    {
        std::vector<ExtensionT*> extensions;
        for (auto&& [type, extension] : m_extensions)
        {
            if (type.IsDerivedFrom(ExtensionT::GetExtensionClassType()))
            {
                extensions.push_back(static_cast<ExtensionT*>(extension));
            }
        }
        return extensions;
    }

    ExtensionIterator ExtensionBegin()
    {
        return m_extensions.begin();
    }

    ExtensionIterator ExtensionEnd()
    {
        return m_extensions.end();
    }

  public:  //属性相关接口，不仅仅考虑PropertyContainer中的静态属性和动态属性，还需要考虑到扩展中的静态属性
    Property* GetPropertyByName(std::string_view name) const override;

    template<std::derived_from<app::Property> PropertyT>
    PropertyT* GetPropertyByName(std::string_view name) const
    {
        return GetPropertyByName(name)->SafeDownCast<PropertyT>();
    }

    std::string_view GetPropertyName(const Property* property) const override;

    void GetPropertyMap(std::map<std::string_view, Property*>& property_map) const override;

    void VisitProperties(const std::function<void(Property*)>& visitor) const override;

    void GetPropertyList(std::vector<Property*>& property_list) const override;

    PropertyFlags GetPropertyFlags(const Property* property) const override;

    PropertyFlags GetPropertyFlags(std::string_view name) const override;

    void OnPropertyChanged(const Property* property) override;

    void Store(base::XMLWriter& writer, std::uint32_t version) const override;

    void Restore(base::XMLReader& reader, std::uint32_t version) override;

  protected:
    /**
     * @brief 写入扩展信息
     * 
     * @param writer 
     */
    void StoreExtensions(base::XMLWriter& writer, std::uint32_t version) const;

    /**
     * @brief 读取扩展信息
     * 
     * @param reader 
     */
    void RestoreExtensions(base::XMLReader& reader, std::uint32_t version);

    /**
     * @brief 处理属性名称变更时的恢复操作
     * 此方法扩展了处理属性名称变更的规则，为扩展模块提供了处理机会。如果某个扩展模块处理了变更，则其他扩展模块和容器本身都不会再处理该变更。
     * @param reader 
     * @param version 
     * @param type_name 要处理的属性类型名
     * @param property_name 要处理的属性名称
     */
    void HandleChangedPropertyName(base::XMLReader& reader, std::uint32_t version, std::string_view type_name, std::string_view property_name) override;

    /**
     * @brief 处理属性类型变更时的恢复操作
     * 此方法扩展了处理属性类型变更的规则，为扩展模块提供了处理机会。如果某个扩展模块处理了变更，则其他扩展模块和容器本身都不会再处理该变更。
     * @param reader 
     * @param version 
     * @param type_name 要处理的属性类型名称
     * @param property 需要恢复的属性对象
     */
    void HandleChangedPropertyType(base::XMLReader& reader, std::uint32_t version, std::string_view type_name, Property* property) override;

  private:
    std::map<base::Type, app::Extension*> m_extensions;
};
}  // namespace app

#endif