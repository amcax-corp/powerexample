#ifndef POWERFC_APP_PROPERTIES_PROPERTYENUMERATION_H_
#define POWERFC_APP_PROPERTIES_PROPERTYENUMERATION_H_
#pragma once
#include <App/Enumeration.h>
#include <App/Property.h>

namespace app {

    /// Property wrapper around an Enumeration object.
class PFC_APP_API PropertyEnumeration: public Property
{
    PFC_TYPESYSTEM_DECL_WITH_OVERRIDE()

public:
    /// Standard constructor
    PropertyEnumeration();

    /// Obvious constructor
    explicit PropertyEnumeration(const Enumeration &e);

    /// destructor
    ~PropertyEnumeration() override;

    template<std::size_t... N>
    void SetEnums(const char (&... enums)[N]){
        AboutSetEnums();
        m_enumeration.SetEnums(enums...);
        HasSetEnums();
    }

    /// Enumeration methods
    /** setting the enumeration string as vector of strings
     * This makes the enumeration custom.
     */
    void SetEnums(std::vector<std::string> &&enums);

    //!@brief 设置当前的枚举字符串，比直接设置索引慢
    void SetValue(std::string_view value);

    //!@brief 直接设置当前枚举索引，比设置字符串快
    void SetValue(std::size_t index);

    //!@brief 从另一个枚举对象中设置值
    void SetValue(const Enumeration &source);

    //!@brief 获取当前枚举索引
    std::size_t GetValue() const;

    //!@brief 判断当前枚举字符串是否等于value
    bool IsValue(std::string_view value) const;

    //!@brief 判断当前枚举对象是否包含value
    bool IsPartOf(std::string_view value) const;

    ////!@brief 获取当前枚举字符串
    std::string_view GetValueAsString() const;

    /// Returns Enumeration object
    const Enumeration &GetEnum() const;

    //!@brief 获取所有可用的枚举字符串的列表
    std::vector<std::string> GetEnumVector() const;

    //!@brief 检查是否为空
    bool HasEnums() const;

    //!@brief 检查枚举对象是否在可用状态，即有枚举值，索引有效
    bool IsValid() const;
    //@}

    std::string_view GetEditorTypeName() const override { return m_editor_type_name; }
    void SetEditorName(std::string_view name) { m_editor_type_name.assign(name); }

    // PyObject * getPyObject() override;
    // void setPyObject(PyObject* py) override;

    void Store(base::XMLWriter& writer, std::uint32_t) const override;
    void Restore(base::XMLReader& reader, std::uint32_t) override;

    std::unique_ptr<Property> Clone() const override;
    void Paste(const Property& from) override;

        // void SetPathValue(const app::ObjectIdentifier& path, const std::any& value) override;
    // const std::any GetPathValue(const app::ObjectIdentifier& path) const override;

    bool IsSame(const Property &other) const override {
        if (&other == this) {
            return true;
        }
        return GetClassTypePolymorphic() == other.GetClassTypePolymorphic()
            && GetEnum() == static_cast<decltype(this)>(&other)->GetEnum();
    }

    private:
    void AboutSetEnums();
    void HasSetEnums();

private:
    Enumeration m_enumeration;
    std::string m_editor_type_name;
};

}

#endif