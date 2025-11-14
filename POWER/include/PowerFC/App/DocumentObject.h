#pragma once

#include <App/Properties/PropertyBool.h>
#include <App/Properties/PropertyString.h>
#include <App/TransactionalObject.h>
#include <Base/Matrix.h>
#include <bitset>
#include <boost/signals2.hpp>

namespace app {

class Document;

class PropertyLinkSub;
class PropertyLinkSubList;

enum class ObjectStatus
{
    TOUCH = 0,
    ERROR_ = 1,
    NEW = 2,
    RECOMPUTE = 3,  // set when the object is currently being recomputed
    RESTORING = 4,
    REMOVE = 5,
    PYTHON_CALL = 6,
    DESTROY = 7,
    ENFORCE = 8,
    RECOMPUTE2 = 9,  // set when the object is being recomputed in the second pass
    PARTIAL_OBJECT = 10,
    PENDING_RECOMPUTE = 11,           // set by Document, indicating the object is in recomputation queue
    PENDING_REMOVE = 12,              // set by Document, indicating the object is in pending for remove after recompute
    OBJ_IMPORTING = 13,               // Mark the object as importing
    NO_TOUCH = 14,                    // no touch on any property change
    GEO_EXCLUDED = 15,                // mark as a member but not claimed by GeoFeatureGroup
    EXPAND = 16,                      // indicate the object's tree item expansion status
    NO_AUTO_EXPAND = 17,              // disable tree item auto expand on selection for this object
    PENDING_TRANSACTION_UPDATE = 18,  // mark that the object expects a call to onUndoRedoFinished() after transaction is finished.
    RECOMPUTEEXTENSION = 19,          // mark the object to recompute its extensions
    TOUCH_ON_COLOR_CHANGE = 20,       // inform view provider touch object on color change
    FREEZE = 21                       // do not recompute ever
};

class DocumentObject;
class DocumentObjectGroup;

class PFC_APP_API DocumentObjectExecReturn
{
  public:
    explicit DocumentObjectExecReturn(std::string_view why, DocumentObject* which_object = nullptr)
      : why(why)
      , which(which_object)
    {
    }

    std::string why;
    DocumentObject* which;
};

class PFC_APP_API DocumentObject : public TransactionalObject
{
    PFC_PROPERTY_DECL_WITH_OVERRIDE()

  public:
    PropertyString Label;
    PropertyString Label2;

    // PropertyExpressionEngine ExpressionEngine;//TODO:表达式引擎

    /// Allow control visibility status in App name space
    PropertyBool Visibility;

    /// 在准备改变该对象的某个属性前，发射该信号。
    boost::signals2::signal<void(const app::DocumentObject&, const app::Property&)> SignalBeforePropertyValueChanging;
    
    /// 已经改变了该对象的某个属性后，发射该信号。
    boost::signals2::signal<void(const app::DocumentObject&, const app::Property&)> SignalPropertyChanged;
    
    /// signal on changed property of this object before document scoped SignalObjectChanged
    boost::signals2::signal<void(const app::DocumentObject&, const app::Property&)> SignalEarlyChanged;

    //!@brief return the class name of the ViewProvider
    virtual std::string_view GetViewProviderClassName() const
    {
        return {};
    }

    /**
     * @brief 这个函数用于支持Python特性覆盖其视图提供器(view provider)。
     * 默认实现仅返回 \ref GetViewProviderClassName() 的结果。
     * 核心系统只会在满足以下条件时接受覆盖：
     * 当调用 gui::ViewProviderDocumentObject::AllowOverride(obj) 返回 true 时。
     * 如果不满足条件，视图提供器将被回退到 \ref GetViewProviderClassName() 返回的默认提供器。
     * 
     * @return std::string_view 
     */
    virtual std::string_view GetViewProviderClassNameOverride() const
    {
        return GetViewProviderClassName();
    }

    DocumentObject();
    ~DocumentObject() override;


    //!@return 对象在其所在文档中登记的名字（在文档中是唯一的，文档会以这个作为key，索引到对象），
    // 注意这个不是属性Name的值。
    std::string_view GetNameInDocument() const;

    std::string_view GetDagKey() const;

    //!@return 在文档中唯一的对象id
    long GetId() const;

    //!@return 能够导出到其他文档中，而无冲突的名字
    std::string GetExportName(bool forced = false) const;

    int IsExporting() const;

    //!@return 按DocName.ObjName的形式返回一个对象的完整名字（唯一的，可做id使用）
    std::string GetFullName() const override;

    //!@return 按 DocLabel#ObjLabel的形式返回一个对象的标签，用于显示
    std::string GetFullLabel() const;

    bool IsAttachedToDocument() const override;

    std::string_view DetachFromDocument() override;

    //!@return gets the document in which this Object is handled
    app::Document* GetDocument() const;

    /** Set the property touched -> changed, cause recomputation in Update()*/
    //@{

    //!@brief set this document object touched (cause recomputation on dependent features)
    void Touch(bool no_recompute = false);

    //!@brief test if this document object is touched
    bool IsTouched() const;

    //!@brief Enforce this document object to be recomputed
    void EnforceRecompute();

    //!@brief Test if this document object must be recomputed
    bool MustRecompute() const;

    /** MustExecute
    *  We call this method to check if the object was modified to
    *  be invoked. If the object label or an argument is modified.
    *  If we must recompute the object - to call the method Execute().
    *  0: no recomputation is needed
    *  1: recomputation needed
    *
    * @remark If an object is marked as 'touched' then this does not
    * necessarily mean that it will be recomputed. It only means that all
    * objects that link it (i.e. its InList) will be recomputed.
    */
    virtual int MustExecute() const;

    //!@brief reset this document object touched
    void PurgeTouched()
    {
        m_status_bits.reset(static_cast<size_t>(ObjectStatus::TOUCH));
        m_status_bits.reset(static_cast<size_t>(ObjectStatus::ENFORCE));
        SetPropertyStatus(static_cast<uint8_t>(PropertyStatusBit::TOUCHED), false);
    }

    //!@brief set this feature to error
    bool IsError() const
    {
        return m_status_bits.test(static_cast<size_t>(ObjectStatus::ERROR_));
    }

    bool IsValid() const
    {
        return !m_status_bits.test(static_cast<size_t>(ObjectStatus::ERROR_));
    }

    //!@brief remove the error from the object
    void PurgeError()
    {
        m_status_bits.reset(static_cast<size_t>(ObjectStatus::ERROR_));
    }

    //!@brief returns true if this objects is currently recomputing
    bool IsRecomputing() const
    {
        return m_status_bits.test(static_cast<size_t>(ObjectStatus::RECOMPUTE));
    }

    //!@brief returns true if this objects is currently restoring from file
    bool IsRestoring() const
    {
        return m_status_bits.test(static_cast<size_t>(ObjectStatus::RESTORING));
    }

    //!@brief returns true if this objects is currently removed from the document
    bool IsRemoving() const
    {
        return m_status_bits.test(static_cast<size_t>(ObjectStatus::REMOVE));
    }

    /**
     * @brief set this document object freezed (prevent recomputation)
     * A freezed document object does not recompute ever.
     */
    void Freeze();

    //!@brief set this document object unfreezed (and touch it)
    void Unfreeze(bool no_recompute = false);

    //!@brief returns true if this objects is currently freezed
    bool IsFreezed() const
    {
        return m_status_bits.test(static_cast<size_t>(ObjectStatus::FREEZE));
    }
    //!@brief return the status bits
    unsigned long GetStatus() const
    {
        return m_status_bits.to_ulong();
    }
    bool TestStatus(ObjectStatus pos) const
    {
        return m_status_bits.test(size_t(pos));
    }
    void SetStatus(ObjectStatus pos, bool on)
    {
        m_status_bits.set(size_t(pos), on);
    }

    // @}

  public:  //子元素处理
    /**
     * @brief 设置子元素可见性
     * 处于性能考虑，\c subname 不能包含任何子元素，即不包含'.'。
     * @param subname 子元素名称    
     * @param visible 可见性
     * @return int -1表示不支持可见性设置，0表示子元素不存在，1表示设置成功。
     */
    virtual int SetElementVisible(std::string_view subname, bool visible);
    /**
     * @brief 获取子元素可见性
     * 
     * @param subname 子元素名称
     * @return int int -1表示不支持可见性设置或者元素不存在，0表示不可见，1表示可见。
     */
    virtual int IsElementVisible(std::string_view subname) const;

  public:  //DAG接口(有向无环图)
    enum class OutListOption
    {
        NoExpression = 1,  //不考虑表达式
        NoImplicit = 2,    //不考虑LinkScope::Implicit引用的对象
        NoXLinked = 4      //不考虑PropertyXLink引用的对象
    };

    using OutListOptions = base::Flags<OutListOption>;

    //!@return 返回该对象的所有PropertyLink类型的属性引用的对象
    const std::vector<app::DocumentObject*>& GetOutList() const;

    //!@return 返回该对象的所有PropertyLink类型的属性引用的对象，根据选项过滤
    std::vector<app::DocumentObject*> GetOutList(OutListOptions options) const;

    //!@return 返回该对象的所有PropertyLink类型的属性引用的对象，根据选项过滤
    void GetOutList(std::vector<app::DocumentObject*>& out_list, OutListOptions options) const;

    //!@return 返回该对象通过property指向的对象
    std::vector<app::DocumentObject*> GetOutListByProperty(app::Property* property) const;

    //!@return 递归收集当前对象通过属性链接直接或间接引用的所有文档对象，即DAG中此对象所有可达的对象。
    std::vector<app::DocumentObject*> GetOutListRecursive() const;

    //!@brief 清空内部的OutList缓存。
    void ClearOutListCache() const;

    //!@return 返回DAG中从此对象到to对象的所有路径。
    std::vector<std::list<app::DocumentObject*>> GetPathsByOutList(app::DocumentObject* to) const;

    //!@return 返回所有以此对象为out的对象。
    const std::vector<app::DocumentObject*>& GetInList() const;

    //!@return 返回所有直接或间接链接到此对象的对象，即DAG中所有可达此对象的对象。
    std::set<app::DocumentObject*> GetInListRecursive() const;

    /**
     * @brief 获取所有直接或间接链接到该对象的对象，包括可能的外部对象。
     * 
     * @param 链接到该对象的对象集合
     * @param 可选输出列表，按引用层级排序（最远引用者排在最后）
     * 内部采用效率更高的广度优先搜索算法，而非递归。缺点是不检查循环依赖，即使有循环依赖，也不会造成crash。
     */
    void GetInListRecursive(std::set<app::DocumentObject*>& in_set,
                            std::vector<app::DocumentObject*>* in_list = nullptr) const;

    //!@return 返回该对象是否在object_to_test的递归in_list中，即在DAG中，object_to_test是否可以到达该对象
    bool IsInInListRecursive(app::DocumentObject* object_to_test) const;

    //!@return 返回该对象是否在object_to_test的直接in_list中，即在DAG中，object_to_test是否可以一步到达该对象
    bool IsInInList(app::DocumentObject* object_to_test) const;

    //!@return 返回该对象是否在object_to_test的递归out_list中，即在DAG中，该对象是否可以到达object_to_test
    bool IsInOutListRecursive(app::DocumentObject* object_to_test) const;

    //!@return 返回该对象是否在object_to_test的直接out_list中，即在DAG中，该对象是否可以一步到达object_to_test
    bool IsInOutList(app::DocumentObject* object_to_test) const;

  public:
    //!@brief 内部方法，在PropertyLink中使用于维护DAG
    //用于移除对象之间的引用关系，比如obj对象有一个链接L指向this，当L.SetValue(other)，需要调用this的__RemoveBackLink方法
    void __RemoveBackLink(app::DocumentObject* object);

    ///!@brief 内部方法，在PropertyLink中使用于维护DAG
    //用于添加对象之间的引用关系，比如obj对象有一个链接L指向other，当L.SetValue(*this)，需要调用this的__AddBackLink方法
    void __AddBackLink(app::DocumentObject* object);

  public:  //用于检测在创建新链接前是否会导致循环依赖关系，能否维护DAG状态。

    //!@brief 检查即将链接到的对象是否在InListRecursive中，即是否会导致循环依赖
    bool TestIfLinkDAGCompatible(app::DocumentObject* link_to) const;

    //!@brief 检查即将链接到的对象是否在InListRecursive中，即是否会导致循环依赖
    bool TestIfLinkDAGCompatible(std::vector<app::DocumentObject*> const& links_to) const;

    //!@brief 检查即将链接到的对象是否在InListRecursive中，即是否会导致循环依赖
    bool TestIfLinkDAGCompatible(app::PropertyLinkSubList& links_to) const;

    //!@brief 检查即将链接到的对象是否在InListRecursive中，即是否会导致循环依赖
    bool TestIfLinkDAGCompatible(app::PropertyLinkSub& link_to) const;

  public:
    /**
     * @brief 重新计算对象
     * 
     * @param recursive 
     * @return true 重新计算所有依赖此对象的对象
     * @return false 只重新计算此对象
     */
    bool RecomputeFeature(bool recursive = false);

    std::string_view GetStatusString() const;

    /**
     * @brief 链接丢失时的回调函数，默认情况只是重置指向object的link。
     * 通过重载该方法实现具体的逻辑。
     * @param object 
     */
    virtual void OnLostLinkToObject(DocumentObject* object)
    {

    }

    /**
     * @brief 获取引用链字符串获取引用对象或元素，比如Part.Fusion.Box，获取到的是Box对象
     * 
     * @param subname 使用'.'分割的字符串，表示子对象或子元素引用，空字符串表示自身,$开头的表示Label引用
     * @param py_object 
     * @param matrix 如果非空，则会返回子对象的变换矩阵，如果need_transform为true，则会累积变换
     * @param need_transform true表示累积变化，false则返回子对象变换矩阵
     * @param depth 查找深度限制
     * @return app::DocumentObject* 
     */
    virtual app::DocumentObject* GetSubObject(std::string_view subname,
                                              void** py_object = nullptr,
                                              base::Matrix4D* matrix = nullptr,
                                              bool need_transform = true,
                                              int depth = 0) const;
    /**
     * @brief 获取通过subname引用到的对象链，包括自身
     * 
     * @param subname 子名称
     * @param subsizes 可选的，表示每个对象在subname中对应的字符串的其实位置，ret[i]=GetSubObject(subname.substr(subsizes[i]));
     * @param flatten 是否将属于同一特征组的对象展平(Part.Fusion.Box->Part.Box)
     * @return std::vector<DocumentObject*> 
     */
    std::vector<DocumentObject*> GetSubObjectList(std::string_view subname,
                                                  std::vector<int>* subsizes = nullptr,
                                                  bool flatten = false) const;

    // enum class GSReason{
    //     Default,
    //     Select
    // };

    // /**
    //  * @brief Get the Sub Objects object
    //  *
    //  * @param reason
    //  * @return std::vector<std::string>
    //  */
    // virtual std::vector<std::string> GetSubObjects(GSReason reason = GSReason::Default) const;

    //!@return 返回指定深度的父对象，以及此对象在父对象中的名称
    std::vector<std::pair<app::DocumentObject*, std::string>> GetParents(int depth = 0) const;

    /**
     * @brief 获取第一个父对象
     * 
     * @return app::DocumentObject* 
     */
    app::DocumentObject* GetFirstParent() const;

    /**
     * @brief 返回链接的对象（当该对象被认为是个link）
     * 
     * @param recursive 
     * @param matrix 
     * @param need_transform 
     * @param depth 
     * @return app::DocumentObject* 
     */
    virtual app::DocumentObject* GetLinkedObject(bool recursive = true,
                                                 base::Matrix4D* matrix = nullptr,
                                                 bool need_transform = false,
                                                 int depth = 0) const;

    //!@return 表示此对象是否是个link
    virtual bool IsLink() const
    {
        return false;
    }

    //!@return 表示此对象是否是个link group
    virtual bool IsLinkGroup() const
    {
        return false;
    }

  public:  //依赖解析
           /**
   * @brief 解析subname中引用的最后一个对象 
   * 
   * @param subname '.'分隔的字符串
   * @param parent 返回此对象的直接父对象
   * @param child_name 返回可用来调用Is/SetElementVisible的子名字
   * @param sub_element 
   * @param py_object 
   * @param matrix 
   * @param need_transform 
   * @param depth 
   * @return app::DocumentObject* 
   */
    app::DocumentObject* Resolve(std::string_view subname,
                                 app::DocumentObject** parent = nullptr,
                                 std::string* child_name = nullptr,
                                 std::string_view* sub_element = nullptr,
                                 void** py_object = nullptr,
                                 base::Matrix4D* matrix = nullptr,
                                 bool need_transform = true,
                                 int depth = 0) const;

    app::DocumentObject* ResolveRelativeLink(std::string& subname,
                                             app::DocumentObject*& link,
                                             std::string& link_sub) const;

    virtual bool AdjustRelativeLinks(const std::set<app::DocumentObject*>& in_list,
                                     std::set<app::DocumentObject*>* visited = nullptr);

    virtual void OnUpdateElementReference(const Property*)
    {}

    /**
     * @brief 用于表示一个对象是隐藏的特殊标记，即"!hidden"
     * 在gui::ViewProvider::GetElementColors()使用，在此处定义是为了方便。
     * @return std::string_view 
     */
    static std::string_view HiddenMarker(){
        return "!hidden";
    }
    
    /**
     * @brief 检查子名称中是否以隐藏标记结尾
     * 
     * @param subname 
     * @return std::string_view::size_type 隐藏标记的位置 
     */
    static bool CheckHiddenMarker(std::string_view subname)
    {
        if(auto pos = subname.find_last_of('.');pos != std::string_view::npos){
            return subname.substr(pos+1)==HiddenMarker();
        }else{
            return subname==HiddenMarker();
        }
    }

    /// get group if object is part of a group, otherwise 0 is returned
    // DocumentObjectGroup* GetGroup() const;

    public:

    //!@return  Return true to bypass duplicate label checking
    virtual bool AllowDuplicateLabel() const
    {
        return false;
    }

    const std::string_view GetOldLabel() const
    {
        return m_old_label;
    }

    std::string_view GetViewProviderClassNameStored() const
    {
        return m_view_provider_class_name;
    }

    bool RemoveDynamicProperty(std::string_view property_name) override;

    app::Property* AddDynamicProperty(std::string_view property_class_name,
                                      std::string_view property_name,
                                      PropertyFlags property_flags = {},
                                      std::string_view property_group = {},
                                      std::string_view description = {},
                                      bool read_only = false,
                                      bool hidden = false) override;

  protected:
    app::Property* AddDynamicProperty(base::Type property_type,
                                      std::string_view property_name = {},
                                      PropertyFlags flags = {},
                                      std::string_view group = {},
                                      std::string_view description = {},
                                      bool read_only = false,
                                      bool hidden = false) override;

  public:
    virtual void OnBeforeLabelChanging(std::string& new_label)
    {
        (void)new_label;
    }

    friend class Document;
    friend class Transaction;

    /** allow partial loading of dependent objects
    *
    * @return Returns 0 means do not support partial loading. 1 means allow
    * dependent objects to be partially loaded, i.e. only create, but not
    * restored. 2 means this object itself can be partially loaded.
    */
    enum class LoadPartialPolicy
    {
        NONE = 0,             //do not support partial loading
        ALLOW_DEPENDENT = 1,  // allow dependent objects to be partially loaded, i.e. only create, but not restored.
        ALLOW_SELF = 2        //this object itself can be partially loaded.
    };

    virtual LoadPartialPolicy CanLoadPartial() const
    {
        return LoadPartialPolicy::NONE;
    }

    // bool HasExtension() const 
    // {
    //     //TODO: implement
    //     return false;
    // }

  protected:
    void SetError()
    {
        m_status_bits.set(static_cast<size_t>(ObjectStatus::ERROR_));
    }
    void ResetErrpr()
    {
        m_status_bits.reset(static_cast<size_t>(ObjectStatus::ERROR_));
    }

    void SetDocument(Document* doc);

    void OnBeforePropertyValueChanging(const Property*) override;
    void OnPropertyChanged(const Property*) override;
    void OnEarlyChange(const Property*) override;

    /// get called when a property status has changed
    void OnPropertyStatusChanged(const Property& prop, unsigned long old_status) override;

    //!@brief get called after a document has been fully restored
    virtual void OnDocumentRestored();

    //!@brief get called after an undo/redo transaction is finished
    virtual void OnUndoRedoFinished();

    //!@brief get called after setting the document
    virtual void OnSettingDocument();

    //!@brief get called after a brand new object was created
    virtual void SetupObject();

    //!@brief get called when object is going to be removed from the document
    virtual void UnsetupObject();

  protected:
    std::string m_old_label;
    app::Document* m_document;
    std::bitset<32> m_status_bits;
    std::string_view m_name_in_document;

  private:
    // accessed by App::Document to record and restore the correct view provider type
    //用于存储正确的view provider类型
    std::string m_view_provider_class_name;
    long m_id{0};

  private:

    std::vector<app::DocumentObject*> m_in_list;
    mutable std::vector<app::DocumentObject*> m_out_list;
    mutable std::unordered_map<std::string_view, app::DocumentObject*> m_out_map;//将object.GetDagKey()映射到object
    mutable bool m_is_out_list_cached{false};//out_list是否已经计算过

    void RecacheOutList() const;
};

}  // namespace app