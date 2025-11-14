#ifndef POWERFC_BASE_PROPERTYLINKSUB_H_
#define POWERFC_BASE_PROPERTYLINKSUB_H_
#pragma once
#include <App/Properties/PropertyLinkBase.h>

namespace app {

/**
* @brief 支持子元素引用的链接属性
* 该属性链接一个对象和一组定义好的子元素，这些子元素（比如一个Shape的Edge）存储为subname字符串，
* 这些subname可以通过ComplexGeometryDataType接口解析为实际几何对象。
*/
class PFC_APP_API PropertyLinkSub : public PropertyLinkBase
{
    PFC_TYPESYSTEM_DECL_WITH_OVERRIDE();

  public:
    PropertyLinkSub();
    ~PropertyLinkSub() override;

    void OnOwnerRestored() override;

    void SetValue(app::DocumentObject* object, std::vector<std::string> const& subnames);
    void SetValue(app::DocumentObject* object, std::vector<std::string> && subnames={});

    ///!@brief 返回链接的对象
    app::DocumentObject* GetValue() const;

    ///!@brief 返回链接的对象子元素名称列表
    std::vector<std::string> const& GetSubNames() const;

    /**
    * @brief 获取以指定前缀开头的子元素名称
    * 
    * @param prefix 指定的前缀
    * @return std::vector<std::string> 返回以指定前缀开头的子元素名称列表
    */
    std::vector<std::string> GetSubNamesStartWith(std::string_view prefix) const;

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

    void CollectLinks(std::vector<DocumentObject*>& objects_out,
                      bool need_all = false,
                      std::vector<std::string>* subnames_out = nullptr) const override;

    /**
     * @brief 从当前链接属性构造一个值为object的Identifier
     * 如果m_object_linked==object，则用self构造一个Identifer添加到 identifiers_out中
     * 
     * @param identifiers_out 输出到的identifier列表
     * @param object 引用的对象
     * @param subname 引用的子元素（对象）名，要判断其引用的对象是否与object相同，且子元素名是否在m_sub_names中
     * @param include_implicit 如果为假，且当前scope是Implicit则不做处理
     * 对象和subname是一对多的关系，即多个subname可以引用同一个对象，因此不能简单地用字符串比较去判断，而是要解析到对象去比较
     */
    void CollectLinksTo(std::vector<Identifier>& identifiers_out,
                        app::DocumentObject* object,
                        std::string_view subname = {},
                        bool include_implicit = false) const override;

    void BreakLink(app::DocumentObject* obj, bool clear) override;

    bool AdjustLink(const std::set<app::DocumentObject*>& in_list) override;

    std::unique_ptr<Property> CloneOnLinkReplace(const app::DocumentObject* owner,
                                                 app::DocumentObject* old_object,
                                                 app::DocumentObject* new_object) const override;

    void UpdateElementReference(app::DocumentObject* object, 
                                bool reverse = false, 
                                bool notify = false) override;

  protected:
    app::DocumentObject* m_object_linked{nullptr}; //链接的对象指针 */
    std::vector<std::string> m_sub_names;           //子元素名称列表 */
    bool m_need_restore_label{false};
};
}  // namespace app
#endif