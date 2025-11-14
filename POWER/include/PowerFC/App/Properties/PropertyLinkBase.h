#ifndef POWERFC_BASE_PROPERTYLINKBASE_H_
#define POWERFC_BASE_PROPERTYLINKBASE_H_
#pragma once
#include <App/Identifier.h>
#include <App/Property.h>
#include <set>
#include <unordered_set>

namespace app {
class Document;
class DocumentObject;

enum class LinkScope
{
    Local,
    Child,
    Global,
    Implicit
};

/**
 * @brief 链接对象包含两张引用注册表，一张是Label引用，以label为key，一张是对象引用，以对象指针为key。
 * 这两张表合起来组成了所有链接包含的引用目标。
 * ProertyLinkBase类还有两张静态引用表，记录了对象和link之间的映射关系
 */

class PFC_APP_API PropertyLinkBase : public Property
{
    PFC_TYPESYSTEM_DECL_WITH_OVERRIDE();

  public:
    PropertyLinkBase();
    virtual ~PropertyLinkBase() override;

  public:
    /**
     * @brief 更新此链接包含的对象引用
     * 
     * @param object 
     * @param reverse 
     * @param notify 
     */
    virtual void UpdateElementReference(app::DocumentObject* object, bool reverse = false, bool notify = false)
    {
        PFC_UNUSED(object);
        PFC_UNUSED(reverse);
        PFC_UNUSED(notify);
    }

    //!@brief 清除内部对象引用m_object_refs
    void ClearElementReferences();

    /**
     * @brief 注册几何元素引用的辅助函数，从subname中解析引用的对象，添加到m_object_refs中
     * 在子名称中搜索任何几何元素引用，并在几何模型更新时注册，以便进行后续更新。
     * @param object 
     * @param subname 
     */
    void AddElementReference(app::DocumentObject* object, std::string& subname);

    /**
     * @brief 添加Label引用，用于对象的重命名更新
     * 
     * @param labels 注册的labels
     * @param reset 是否在注册前调用UnregisterLabelReference()
     */
    void AddLabelReferences(std::vector<std::string>&& labels, bool reset = true);

    /**
     * @brief 尝试从subnames中提取Label，并添加到Label引用注册表中
     * 
     * @param subs 子名称列表，可能包含Label信息
     * @param reset 是否清空已有的Label引用注册表，即调用ClearLabelReference()
     */
    void CheckLabelReferences(std::vector<std::string> const& subnames, bool reset = true);

    //!@brief 清除内部的Label引用注册表
    void ClearLabelReferences();

    //!@brief 检查在restore之后是否发生了object reference变化
    virtual bool IsReferenceChanged() const
    {
        return false;
    }

    /**
     * @brief 当前链接属性所引用的对象列表
     * 
     * @param objects_out 必选输出，返回当前链接属性所引用的对象列表，
     * 该参数设置为列表类型，是为了兼容PropertyLinkList、PropertyLinkSubList和PropertyXLinkList
     * @param include_implicit 控制返回范围的标志：
     *             - true: 返回所有链接对象（忽略LinkScope限制）
     *             - false: 仅返回LinkScope非Implicit的对象
     * @param subnames 可选输出，返回所引用的子元素或者子对象信息(编码的字符串)
     */
    virtual void CollectLinks(std::vector<DocumentObject*>& objects_out,
                              bool include_implicit = false,
                              std::vector<std::string>* subnames = nullptr) const = 0;

    /**
     * @brief 获取当前链接属性中可到指定对象的Identifer，
     * 比如PropertyLinkSubList会引用一个对象的多个子元素或者子对象，那么就返回多个Identifier
     * 
     * @param identifiers_out 输出的Identifier列表
     * @param object 引用的对象
     * @param subname 引用的子元素（对象）名
     * @param include_implicit 是否包含LinkScope为Implicit
     */
    virtual void CollectLinksTo(std::vector<Identifier>& identifiers_out,
                                app::DocumentObject* object,
                                std::string_view subname = {},
                                bool include_implicit = false) const = 0;

    /**
     * @brief 删除链接中包含的指定对象的引用
     * 
     * @param obj 如果链接到object，则取消该引用
     * @param clear 如果为真，当object是link property的Ower时，则清空该link property
     */
    virtual void BreakLink(app::DocumentObject* obj, bool clear) = 0;

    /**
     * @brief 用于调整链接，以避免循环依赖，如果避免不了，则会抛出异常
     * 
     * @param in_list 调整范围内的对象列表
     * @return true 
     * @return false 
     */
    virtual bool AdjustLink(const std::set<app::DocumentObject*>& in_list) = 0;

    /**
     * @brief 在链接替换操作中创建一个调整后的属性副本。
     * 
     * @param owner 正在被替换链接的父对象。注意，这个父对象不一定是当前属性的直接容器。子链接属性可以利用这个机会调整其相对链接。
     * @param old_object 将被替换的旧对象。
     * @param new_object 用于替换的新对象。
     * @return std::unique_ptr<Property> 返回一个经过调整的属性的副本，以适应链接替换操作。
     */
    virtual std::unique_ptr<Property> CloneOnLinkReplace(const app::DocumentObject* owner,
                                                         app::DocumentObject* old_object,
                                                         app::DocumentObject* new_object) const = 0;

    /**
     * @brief 在导入外部链接对象时，生成更新了引用关系的属性副本，确保导入后的属性指向正确的新对象。
     * 
     * @param map_name_to_name 名称映射词典：key: 原始外部对象标识（格式"对象名@文档名"）,value: 导入后的新对象名称。
     * @return std::unique_ptr<Property> 
     */
    virtual std::unique_ptr<Property> CloneOnImportExternal(std::map<std::string, std::string> const& map_name_to_name) const
    {
        PFC_UNUSED(map_name_to_name);
        return nullptr;
    }

    /**
     * @brief 当通过Label引用的对象发生Label变化时，会调用此函数更新Label引用
     * 
     * @param object Label发生变化的那个对象
     * @param ref 指向旧的Label的引用的subname
     * @param new_label 新的Label值
     * @return std::unique_ptr<Property> 
     * 返回的克隆体随后会通过Paste()粘贴到该链接属性。
     */
    virtual std::unique_ptr<Property> CloneOnLabelChange(app::DocumentObject* object,
                                                         std::string_view ref,
                                                         std::string_view new_label) const
    {
        PFC_UNUSED(object);
        PFC_UNUSED(ref);
        PFC_UNUSED(new_label);
        return nullptr;
    }

    std::vector<app::DocumentObject*> GetLinkedObjects(bool include_implicit = false) const
    {
        std::vector<app::DocumentObject*> objects;
        CollectLinks(objects, include_implicit);
        return objects;
    }

    /**
     * @brief 获取此链接属性所引用的对象及其子元素信息(编码的字符串)
     * 由于一个Object可能包含多个LinkProperty，此方法可用在Object的接口中， 用于收集Object所依赖的对象或元素。
     * @param elements_out 
     * @param include_implicit 
     */
    void GetLinkedElements(std::map<app::DocumentObject*, std::vector<std::string>>& elements_out,
                           bool include_implicit = false) const
    {
        std::vector<app::DocumentObject*> objects;
        std::vector<std::string> subnames;
        CollectLinks(objects, include_implicit, &subnames);
        assert(objects.size() == subnames.size());
        std::size_t i{0};
        for (auto obj : objects)
        {
            elements_out[obj].emplace_back(subnames[i++]);
        }
    }

    std::map<app::DocumentObject*, std::vector<std::string>> GetLinkedElements(bool include_implicit = false) const
    {
        std::map<app::DocumentObject*, std::vector<std::string>> elements;
        GetLinkedElements(elements, include_implicit);
        return elements;
    }

    /**
    * 链接替换辅助函数
    * 
    * 核心功能：检测并修复因对象替换导致的链接断裂问题
    * 
    * @param owner: 当前属性的所属对象
    * @param obj: 当前链接的对象指针
    * @param parent: 发生替换操作的父级对象（可能与owner相同）
    * @param old_object: 待替换的旧对象
    * @param new_object: 替换后的新对象
    * @param sub: 当前子元素引用路径（可选）
    * 
    * @return 返回std::pair<DocumentObject*, std::string>：
    *         - first: 替换后的对象指针（未找到替换时返回nullptr）
    *         - second: 更新后的子元素引用路径
    * 
    * 典型应用场景：
    * 当组(Group)中的子对象被替换时，修复通过该组引用的所有子元素路径
    * 示例：
    *   [装配体] -> [旧零件] 被替换为 [装配体] -> [新零件] 时，
    *   自动更新所有指向"装配体/旧零件/面1"的引用为"装配体/新零件/面1"
    */
    static std::pair<app::DocumentObject*, std::string>
    TryReplaceLink(const app::PropertyContainer* owner,
                   app::DocumentObject* object,
                   const app::DocumentObject* parent,
                   app::DocumentObject* old_object,
                   app::DocumentObject* new_object,
                   std::string_view sub = {});

    /**
     * @brief 用于检查或替换一个具有多个子元素引用的链接
     * 
     * @param owner 当前属性的所属对象
     * @param obj 当前链接的对象指针
     * @param parent 发生替换操作的父级对象（可能与owner相同）
     * @param old_object 待替换的旧对象
     * @param new_object 替换后的新对象
     * @param subs 当前的子元素引用列表
     * @return std::pair<app::DocumentObject*, std::vector<std::string>> 
     */
    static std::pair<app::DocumentObject*, std::vector<std::string>>
    TryReplaceLinkSubs(const app::PropertyContainer* owner,
                       app::DocumentObject* obj,
                       const app::DocumentObject* parent,
                       app::DocumentObject* old_object,
                       app::DocumentObject* new_object,
                       const std::vector<std::string>& subs);

    /**
     * @brief 更新一个对象的所有链接属性
     * 
     * @param obj 对obj的所有链接属性进行更新，即更新每个链接属性的引用对象
     * @param reverse 
     */
    static void UpdateReferences(app::DocumentObject* obj, bool reverse = false);

    /**
     * @brief 获取所有引用该对象的PropertyLinkBase实例
     * 
     * @param obj 
     * @return const std::unordered_set<PropertyLinkBase*>& 
     */
    static const std::unordered_set<PropertyLinkBase*>& GetReferences(app::DocumentObject* obj);

    /**
     * @brief 用于断开引用指定对象的链接
     * 
     * @param object_link_to 如果一个link指向这个对象，则断开这个link
     * @param object_links_from 待检查的对象集合
     * @param clear  是否清除object_lin_to对象的所有链接属性
     * app::Document::BreakDependency()函数是调用此方法实现的
     */
    static void BreakLinks(app::DocumentObject* object_link_to,
                           const std::vector<app::DocumentObject*>& object_links_from,
                           bool clear);

    public://导入
    
    /**
     * @brief 链接导入操作的辅助函数
     * 
     * @param doc 正在导入的文档
     * @param object 被链接的对象
     * @param subname 子名称引用
     * @param name_map 从源对象到其导入后对应对象的名称映射表
     * @return std::string 返回修改后的子名称引用，若无变化则返回空字符串。
     * 链接导入操作会遍历所有链接属性，并导入所有外部链接的对象。
     * 导入完成后，链接属性必须更新以指向新导入的对象，这一过程应在CopyOnImportExternal() 内部完成。
     * 此函数有助于重写子名称引用，使其指向已导入的正确子对象。
     */
    static std::string TryImportSubName(const app::Document* doc,
                                                const app::DocumentObject* object,
                                                std::string_view subname,
                                                const std::map<std::string, std::string>& name_map);

    /**
     * @brief link import操作的辅助函数
     * 
     * @param doc 被导入对象所属的文档
     * @param object 被链接的对象
     * @param name_map 从源对象到其导入后对应对象的名称映射表
     * @sa TryImportSubNames
     * @return app::DocumentObject* 如果找到对应的导入后对象则返回该对象，否则返回输入的 \c object（无变化）。
     * 该函数在名称映射表中进行查找，尝试根据给定的源对象找到其对应的导入对象。
     */
    static app::DocumentObject* TryImport(const app::Document* doc, 
                                          const app::DocumentObject* object,
                                          const std::map<std::string, std::string>& name_map);


  public:  //用于拷贝、粘贴对象，拷贝是Export，粘贴是Import

    /** 
     * 在将对象导出和导入（即复制和粘贴）到同一文档时，新对象必须重命名，包括其内部name和Label。
     * 因此，新对象的链接引用也必须相应地进行修正。
     * 基本思路是：在导出对象时，所有对象名称引用会被更改为 'objName@docName' 格式，而标签引用则会被更改为 'objName@docName@' 格式。
     * 在导入时，MergeDocument 会维护一个从 objName@docName 到对象新名称的映射表。对象名称引用可以通过查询该映射表立即恢复；
     * 而标签引用则会在属性的 AfterRestore() 函数中稍后恢复，AfterRestore()函数会调用此函数来进行字符串解析。
    */

    /**
     * @brief 导出子名称引用的辅助函数
     * 
     * @param output 如果子名称被修改，则输出修改后的子名称
     * @param object 被链接的对象
     * @param subname 输入的子名称引用
     * @param include_first_object 如果为 true，则通过搜索 object 所属的文档来获取子名称中引用的第一个对象；否则，在 obj 的子对象中搜索该子名称。
     * @return std::string_view 如果子名称被修改用于导出，则返回 output；否则，返回输入的子名称。
     * @sa ImportSubName(), RestoreLabelReference()
     * 该函数遍历输入的子名称引用，并将其中包含的任何子对象引用修改为适合导出的格式。
     * 如果子对象是通过其内部对象名称引用的，则引用将从 'objName' 更改为 'objName@docName'；
     * 如果是通过标签引用的，则更改为 'objName@docName@'。
     * 在导入时，可以结合使用 ImportSubName() 和 RestoreLabelReference() 来恢复这些引用。
     */
    static std::string_view ExportSubName(std::string& output,
                                          const app::DocumentObject* object,
                                          std::string_view subname,
                                          bool include_first_object = false);

    /**
    * @brief 导入一个子名称引用的辅助函数
    * 
    * @param reader 
    * @param version 
    * @param subname 输入的子名称引用
    * @param need_restore_label 输出参数，指示恢复后是否需要进行后续处理
    * @sa ExportSubName(), RestoreLabelReference()
    * @return std::string 返回更新后的子名称引用，若无变化则返回输入的引用。
    * 如果输出参数 need_restore_label 被设置为 true，则表示存在一些标签引用的更改，
    * 必须在恢复后通过在属性的 AfterRestore() 函数中调用 RestoreLabelReference() 来修正。
    */
    static std::string ImportSubName(base::XMLReader& reader,
                                     std::uint32_t version,
                                     std::string_view subname,
                                     bool& need_restore_label);

    /**
     * @brief 导入期间用于恢复标签引用的辅助函数
     * 
     * @param object 被链接的对象
     * @param subname 子名称引用
     * @sa ExportSubName(), ImportSubName()
     * 在将对象导出和导入（即复制和粘贴）到同一文档时，新对象必须重命名，包括其内部name和Label。
     * 因此，新对象的链接引用也必须相应地进行修正。
     * 基本思路是：在导出对象时，所有对象名称引用会被更改为 'objName@docName' 格式，而标签引用则会被更改为 'objName@docName@' 格式。
     * 在导入时，MergeDocument 会维护一个从 objName@docName 到对象新名称的映射表。对象名称引用可以通过查询该映射表立即恢复；
     * 而标签引用则会在属性的 AfterRestore() 函数中稍后恢复，AfterRestore()函数会调用此函数来进行字符串解析。
     */
    static void RestoreLabelReference(app::DocumentObject* object, std::string& subname);

    /**
     * @brief 根据引用的subname提取labels
     * 
     * @param labels 提取到的labels
     * @param subname 引用的子名称
     * @sa RegisterLabelReferences()
     */
    static void GetReferences(std::vector<std::string>& labels, std::string_view subname);

    /**
     * @brief 当一个对象relabel时，收集改变的属性
     * 
     * @param object label属性的owner
     * @param new_label 新的label
     * @return std::vector<std::pair<Property*, std::unique_ptr<Property>>> 
     */
    static std::vector<std::pair<Property*, std::unique_ptr<Property>>>
    UpdateReferences(app::DocumentObject* object, std::string_view new_label);

    /**
     * @brief 在relabel时更新子名称引用
     * 
     * @param linked 引用的对象
     * @param subname 引用的子名称
     * @param object label的owner
     * @param ref 
     * @param new_label 
     * @return std::string 
     */
    static std::string UpdateLabelReference(const app::DocumentObject* linked,
                                            std::string_view subname,
                                            const app::DocumentObject* object,
                                            std::string_view ref,
                                            std::string_view new_label);

    enum class LinkFlag
    {
        AllowExternal,
        Detached,
        Restoring,
        AllowPartial,
        NeedRestoreLabel,
        SyncSubObject,
        SilentRestore /*不报告错误信息，比如缺失外部链接*/
    };

    inline bool TestFlag(LinkFlag flag) const
    {
        return m_flags.test(static_cast<size_t>(flag));
    }

    virtual void SetAllowPartial(bool enable)
    {
        PFC_UNUSED(enable);
    }

    boost::signals2::signal<void(std::string_view, std::string_view)> SignalUpdateElementReference;

  public:
    void SetScope(LinkScope scope)
    {
        m_scope = scope;
    }
    LinkScope GetScope() const
    {
        return m_scope;
    }

  public:
    virtual bool IsSame(Property const& other) const override;
    virtual void HasSetValue() override;


    protected:

  protected:
    std::bitset<32> m_flags;
    inline void SetFlag(LinkFlag flag, bool value = true)
    {
        m_flags.set(static_cast<size_t>(flag), value);
    }

    inline bool IsImplicit() const{
        return m_scope == LinkScope::Implicit;
    }

    /**
     * @brief 收集能够指向object.subname的Identifier
     * 
     * @param identifiers_out 
     * @param object 在子类中，要保证object为object_linked时才调用此函数。
     * @param subname 为空时，用this构造Identifer，否则在subnames中，取其索引，用于构造Identifier。
     * @param subnames 
     */
    void __CollectIdentifiersTo(std::vector<Identifier>& identifiers_out,
                             app::DocumentObject* object, 
                             std::string_view subname, 
                            const std::vector<std::string>& subnames) const;

  private:
    LinkScope m_scope{LinkScope::Local};
    std::set<std::string> m_label_refs{};       //通过Label建立的引用
    std::set<DocumentObject*> m_object_refs{};  //通过对象指针建立的引用
    inline static std::unordered_map<std::string, std::set<app::PropertyLinkBase*>> s_map_label_to_links{};
    inline static std::unordered_map<app::DocumentObject*, std::unordered_set<PropertyLinkBase*>> s_map_object_to_links{};
};

}  // namespace app

#endif
