#ifndef POWERFC_BASE_PROPERTYLINK_H
#define POWERFC_BASE_PROPERTYLINK_H
#pragma once
#include <App/Properties/PropertyLinkBase.h>

namespace app {
/**
     * @brief 
     * 核心功能：实现文档中对象与特征的引用关联。与所有链接属性相同，本属性具有作用域感知能力，
     * 即根据所在GeoFeatureGroup自动限定允许链接的对象范围（默认作用域为Local）。
     * @note 重要注意事项：
     * - 不符合当前作用域的链接不会被拒绝，但会被标记为无效
     * - 无效链接将阻止所属特征的重新计算（recompute）
     */
class PFC_APP_API PropertyLink : public PropertyLinkBase
{
    PFC_TYPESYSTEM_DECL_WITH_OVERRIDE();

  public:
    PropertyLink();
    ~PropertyLink() override;

    void ResetLink();

    virtual void SetValue(app::DocumentObject* obj);

    app::DocumentObject* GetValue() const;

    /**
    * @brief 获取当前链接的对象，会先进行类型检查
    * 
    * @param type 
    * @return app::DocumentObject* 
    */
    app::DocumentObject* GetValue(base::Type type) const;

    void Store(base::XMLWriter&, std::uint32_t version) const override;

    void Restore(base::XMLReader&, std::uint32_t version) override;

    std::unique_ptr<Property> Clone() const override;

    void Paste(Property const& from) override;

    /**
     * @brief 将当前链接引用的对象添加到objects_out中
     * 
     * @param objects_out 输出到的对象列表
     * @param include_implicit 如果为假，且当前scope是Implicit则不做处理
     * @param subnames_out 未用
     */
    void CollectLinks(std::vector<DocumentObject*>& objects_out,
                      bool include_implicit = false,
                      std::vector<std::string>* subnames_out = nullptr) const override;

    /**
     * @brief 从当前链接属性构造一个值为object的Identifier
     * 如果m_object_linked==object，则用self构造一个Identifer添加到 identifiers_out中
     * 
     * @param identifiers_out 输出到的identifier列表
     * @param object 引用的对象
     * @param subname 引用的子元素（对象）名，未用
     * @param include_implicit 如果为假，且当前scope是Implicit则不做处理
     */
    void CollectLinksTo(std::vector<Identifier>& identifiers_out,
                        app::DocumentObject* object,
                        std::string_view subname = {},
                        bool include_implicit = false) const override;

    /**
     * @brief 如果object==m_object_linked，则断开依赖，并置空m_object_linked
     * 
     * @param object 
     * @param clear @copydoc PropertyLinkBase::BreakLink
     */
    void BreakLink(app::DocumentObject* object, bool clear) override;

    //!@brief 啥也没做，返回false
    bool AdjustLink(const std::set<app::DocumentObject*>& in_list) override;

    std::unique_ptr<Property> CloneOnLinkReplace(const app::DocumentObject* owner,
                                                 app::DocumentObject* old_object,
                                                 app::DocumentObject* new_object) const override;

  protected:
    app::DocumentObject* m_object_linked{nullptr};
};
}  // namespace app

namespace app {

class PFC_APP_API PropertyLinkChild : public app::PropertyLink
{
    PFC_TYPESYSTEM_DECL();

  public:
    PropertyLinkChild()
    {
        SetScope(LinkScope::Child);
    }
};

class PFC_APP_API PropertyLinkGlobal : public app::PropertyLink
{
    PFC_TYPESYSTEM_DECL();

  public:
    PropertyLinkGlobal()
    {
        SetScope(LinkScope::Global);
    }
};

class PFC_APP_API PropertyLinkImplicit : public app::PropertyLink
{
    PFC_TYPESYSTEM_DECL();

  public:
    PropertyLinkImplicit()
    {
        SetScope(LinkScope::Implicit);
    }
};

}  // namespace app

#endif