#ifndef POWERFC_APP_PROPERTIES_PROPERTYMAP_H_
#define POWERFC_APP_PROPERTIES_PROPERTYMAP_H_
#pragma once
#include <App/Property.h>

namespace app {

/**
* @brief 实现了一个键/值列表作为属性，键应为 ASCII 字符，值应被视为 UTF-8 编码以进行保存。
* 
*/
class PFC_APP_API PropertyMap : public Property
{
    PFC_TYPESYSTEM_DECL_WITH_OVERRIDE();

  public:
    PropertyMap();
    virtual ~PropertyMap() override;

    virtual std::size_t GetSize() const;

    void SetValue() {}

    //!@brief 设置一个键值对，并触发AboutSetValue和HasSetValue。
    void SetValue(const std::string& key, const std::string& value);
    
    //!@brief 设置一个所有值，并触发AboutSetValue和HasSetValue。
    void SetValues(const std::map<std::string, std::string>&);

    const std::string& operator[](const std::string& key) const;

    //!@brief 设置一个键值对，但和SetValue不同，仅仅设置值，不会发送通知。
    void SetOneValue(const std::string& key, const std::string& value);

    const std::map<std::string, std::string>& GetValues() const;

    size_t GetEstimatedSize() const override;
    void Store(base::XMLWriter& writer, std::uint32_t) const override;
    void Restore(base::XMLReader& reader, std::uint32_t) override;

    std::unique_ptr<Property> Clone() const override;
    void Paste(const Property& from) override;

    bool IsSame(const Property& other) const override;

  private:
    std::map<std::string, std::string> m_value_list;
};

}  // namespace app

#endif