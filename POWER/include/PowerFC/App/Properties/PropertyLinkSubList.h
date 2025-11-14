#ifndef PFC_BASE_PROPERTYLINKSUBLIST_H
#define PFC_BASE_PROPERTYLINKSUBLIST_H
#pragma once
#include <App/Properties/PropertyLinkBase.h>

namespace app {

class PropertyLinkSubList : public app::PropertyLinkBase
{
    PFC_TYPESYSTEM_DECL_WITH_OVERRIDE();

  public:
    using SubSet = std::pair<app::DocumentObject*, std::vector<std::string>>;

    PropertyLinkSubList();
    ~PropertyLinkSubList() override;

    void AfterRestore() override;
    void OnOwnerRestored() override;

    int GetSize() const;
    void Resize(int size);

    void SetValue(app::DocumentObject*, std::string_view);
    void SetValues(std::vector<app::DocumentObject*> const&, std::vector<std::string_view> const&);

    void SetValue(app::DocumentObject* object, std::vector<std::string> const& sub_list = {});

    void AddValue(app::DocumentObject* object, std::vector<std::string> const& sub_list = {}, bool reset = false);

    const std::vector<DocumentObject*>& GetValues() const
    {
        return m_values;
    }

    //!@brief 这个方法模拟单对象引用的情况，当仅引用一个对象时，返回该对象，如果链接为空，或者链接到多个对象，返回nullptr
    DocumentObject* GetValue() const;

    std::vector<std::string> const& GetSubList() const
    {
        return m_sub_list;
    }

    //!@brief 删除指定引用对象及其子元素引用，返回删除的对象个数
    int RemoveValue(app::DocumentObject* object);

    //!@brief 使用SubSet对象设置值
    void SetSubListValues(std::vector<SubSet> const&);

    //!@brief 作为std::vector<SubSet>对象的返回值
    std::vector<SubSet> GetSubListValues() const;

    void Store(base::XMLWriter&, unsigned int) const override;
    void Restore(base::XMLReader&, unsigned int) override;

    bool Upgrade(base::XMLReader&, std::string_view type_name);

    std::unique_ptr<Property> Clone() const override;
    void Paste(Property const&) override;

    std::string_view GetEditorTypeName() const override
    {
        return "";
    }

  public:  //重载PropertyLinkBase的接口
    void CollectLinks(std::vector<app::DocumentObject*>& objects,
                  bool need_all = false,
                  std::vector<std::string>* subs = nullptr) const override;

    void BreakLink(app::DocumentObject* object, bool clear) override;

    bool AdjustLink(const std::set<app::DocumentObject*>& in_list) override;

    void SetSyncSubObject(bool enable);

  private:
    void VerifyObject(app::DocumentObject*, app::DocumentObject*);

  private:
    std::vector<app::DocumentObject*> m_values;
    std::vector<std::string> m_sub_list;
};
}  // namespace app
#endif