#ifndef PFC_APP_PROPERTYLINKLIST_H_
#define PFC_APP_PROPERTYLINKLIST_H_
#pragma once

#include <App/Properties/PropertyLinkBase.h>

namespace app {

class PFC_APP_API PropertyLinkListBase : public PropertyLinkBase, public PropertyListsBase
{
    PFC_TYPESYSTEM_DECL_WITH_OVERRIDE();
};

class PFC_APP_API PropertyLinkList : public PropertyListsT<
                                         app::DocumentObject*,
                                         std::vector<app::DocumentObject*>,
                                         PropertyLinkListBase>
{
    PFC_TYPESYSTEM_DECL_WITH_OVERRIDE();

    using Super = PropertyListsT<app::DocumentObject*, std::vector<app::DocumentObject*>, PropertyLinkListBase>;

  public:
    PropertyLinkList();
    ~PropertyLinkList() override;

    void Resize(size_t new_size) override;
    void Resize(size_t new_size, const_reference preset) override;

    void SetValues(const std::vector<app::DocumentObject*>& new_elements = {}) override;
    void SetOneValue(size_t index, app::DocumentObject* const& value) override;

  public:
    void Store(base::XMLWriter&, std::uint32_t version) const override;

    void Restore(base::XMLReader&, std::uint32_t version) override;

    std::unique_ptr<Property> Clone() const override;

    void Paste(Property const& from) override;

  public:
  /**
   * @brief 获取所有引用对象
   * 
   * @param objects_out 输出的引用对象列表
   * @param include_implicit 是否输出隐式引用对象
   * @param subnames_out PropertyLinkList不引用子对象/元素，因此该参数未用
   */
    void CollectLinks(std::vector<app::DocumentObject*>& objects_out,
                  bool include_implicit = false,
                  std::vector<std::string>* subnames_out = nullptr) const override;
    
    /**
     * @brief 从该属性构造一个表示值为object的Identifer，即用指向object的index和self构造Identifier
     * 
     * @param identifiers_out 
     * @param object 
     * @param subname 未用
     * @param include_implicit 如果scope为Implicit且include_implicit为false，则不输出任何结果
     */
    void CollectLinksTo(std::vector<app::Identifier>& identifiers_out,
                    app::DocumentObject* object,
                    std::string_view subname = {},
                    bool include_implicit = false) const override;
    
    /**
     * @brief 断开到object对owner的依赖，并从m_elements中移除object
     * 
     * @param object 
     * @param clear 
     */
    void BreakLink(app::DocumentObject* object, bool clear) override;
    
    //!@brief 啥也没做，返回false
    bool AdjustLink(const std::set<app::DocumentObject*>& in_list) override;

    std::unique_ptr<app::Property> CloneOnLinkReplace(const app::DocumentObject* parent,
                                                      app::DocumentObject* old_object,
                                                      app::DocumentObject* new_object) const override;
    
    /**
     * @brief 使用Map查找，如果name_map.size!=GetSize()，这表面缓存过时，则使用Find接口
     * 
     * @param name 
     * @param index_out 
     * @return app::DocumentObject* 
     */
    app::DocumentObject* FindUsingMap(std::string const& name, int* index_out = nullptr) const;

    /**
     * @brief 根据名字查找引用对象，如果元素不多，则直接遍历列表查找，否则构建name_map查找
     * 
     * @param subname 
     * @param index_out 
     * @return app::DocumentObject* 
     */
    app::DocumentObject* Find(std::string_view subname, int* index_out = nullptr) const;

  protected:
  // 将obj.name_in_document映射到obj在list中的index
  // 作为Find的缓存，为空时表示需要重新构建索引
  mutable std::map<std::string_view, int> m_name_map;

};

}  // namespace app


namespace app{
  class PFC_APP_API PropertyLinkListChild: public PropertyLinkList{
    PFC_TYPESYSTEM_DECL();
    public:
    PropertyLinkListChild(){
      SetScope(LinkScope::Child);
    }
  };

  class PFC_APP_API PropertyLinkListGlobal: public PropertyLinkList{
    PFC_TYPESYSTEM_DECL();
    public:
    PropertyLinkListGlobal(){
      SetScope(LinkScope::Global);
    }
  };

  class PFC_APP_API PropertyLinkListImplicit: public PropertyLinkList{
    PFC_TYPESYSTEM_DECL();
    public:
    PropertyLinkListImplicit(){
      SetScope(LinkScope::Implicit);
    }
  };
}
#endif