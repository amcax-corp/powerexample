#ifndef PFC_APP_GROUP_EXTENSION_H_
#define PFC_APP_GROUP_EXTENSION_H_
#pragma once

#include <App/DocumentObjectExtension.h>
#include <App/Properties/PropertyBool.h>
#include <App/Properties/PropertyLinkList.h>


namespace app {

class PFC_APP_API GroupExtension : public DocumentObjectExtension
{
    PFC_EXTENSION_PROPERTY_DECL_WITH_OVERRIDE();

  public:
    GroupExtension();
    ~GroupExtension() override;

    /**
         * @brief 添加一个对象到该组所在的文档，同时将该对象添加到该组中
         * 
         * @param class_name 对象的类名
         * @param object_name 对象名
         * @return app::DocumentObject* 
         */
    virtual app::DocumentObject* AddObject(std::string_view class_name, std::string_view object_label);

    template<std::derived_from<app::DocumentObject> ObjectT>
    ObjectT* AddObject(std::string_view object_label)
    {
        return static_cast<ObjectT*>(AddObject(ObjectT::GetClassTypeName(), object_label));
    }

    /**
         * @brief 添加一个对象后，返回所有加到该组中的对象
         * 
         * @param object 
         * @return std::vector<app::DocumentObject*> 
         */
    std::vector<app::DocumentObject*> AddObject(DocumentObject* object);

    /**
         * @brief 添加一些对象，返回所有加到该组中的对象
         * 
         * @param objects 
         * @return std::vector<app::DocumentObject*> 
         */
    virtual std::vector<app::DocumentObject*> AddObjects(std::vector<DocumentObject*> const& objects);

    /**
         * @brief 设置该组中的对象，原来的组内的对象会被清空
         * 
         * @param objects 
         * @return std::vector<app::DocumentObject*> 
         */
    virtual std::vector<app::DocumentObject*> SetObjects(std::vector<DocumentObject*> const& objects);

    //!@brief 控制某个对象是否可加入到该组中，请重载该函数进行控制
    virtual bool AllowObject(DocumentObject*)
    {
        return true;
    }

    std::vector<app::DocumentObject*> RemoveObject(DocumentObject* object);

    /**
         * @brief 从组内移除一些对象，返回所有移除的对象
         * 
         * @param objects 
         * @return std::vector<app::DocumentObject*> 
         */
    virtual std::vector<app::DocumentObject*> RemoveObjects(std::vector<DocumentObject*> const& objects);

    //!@brief 移除该组的所有子对象，同时从文档中删除这些对象。
    virtual void RemoveObjectsFromDocument();

    /**
    * @brief 返回组内名字为object_name的对象
    * @note 函数名后缀的'_'是为了避免和windows宏冲突
    * @param object_name 
    * @return app::DocumentObject* 如果组内没有，即使组所在的文档中有这个对象，也返回nullptr
    */
    app::DocumentObject* GetObject_(std::string_view object_name) const;

    /**
    * @brief 检查组内是否有某个对象
    * 
    * @param object 带检查的对象指针
    * @param recursive 是否在子组中检查，默认为真
    * @return true 
    * @return false 
    */
    virtual bool HasObject(const app::DocumentObject* object, bool recursive = true) const;

    /**
    * @brief 检查该组对象是否是某个组的子对象(子组)
    * 
    * @param group 给定的父组对象
    * @param recursive 是否检查group的子组，默认为真
    * @return true 
    * @return false 
    */
    bool IsChildOf(const GroupExtension* group, bool recursive = true) const;

    bool IsSubGroupOf(const GroupExtension* group, bool recursive = true) const
    {
        return IsChildOf(group, recursive);
    }

    //!@brief 返回组内的所有直接包含的对象(Group属性中包含的对象列表)，不包括孙子对象
    const std::vector<app::DocumentObject*>& GetObjects() const;

    //!@brief 返回组内指定类型的对象
    std::vector<app::DocumentObject*> GetObjectsOfType(base::Type type) const;

    //!@brief 返回组内指定类型的对象数量
    std::size_t GetNumberOfObjects(base::Type type) const;

    /**
    * @brief 返回给定对象 \a object 所属的文档对象组。如果该对象不属于任何组，则返回nullptr。
    * @note 本方法仅返回普通Group，不包括GeometryFeatureGroups或OriginGroups等特殊派生类型。如需获取这些特殊组，请使用其对应的专用函数。
    * @param object 
    * @return app::DocumentObject* 
    */
    static app::DocumentObject* GetGroupOfObject(const app::DocumentObject* object);

    //PyObject* GetExtensionPyObject() override;

    /**
     * @brief 当Group属性改变时，调用此回调进行检查是否有循环依赖
     * 如果有，则去除循环依赖的项，并抛出异常
     * 如果没有，则建立Group中对象的SignalPropertyChanged信号和GroupExtension的SlotChildChanged槽的连接
     * @param prop 
     */
    void ExtensionOnPropertyChanged(const app::Property* prop) override;

    /**
     * @brief 根据Name引用或Label引用，获取子对象，object_out是subname中第一个对象
     * 比如"A."返回A对象，"$line."返回Label为line的对象
     * "A"返回false，object_out为nullptr
     * @param object_out 
     * @param subname 
     * @param py_object_out 
     * @param matrix_out 
     * @param need_transform 
     * @param depth 
     * @return true 
     * @return false 
     */
    bool ExtensionGetSubObject(DocumentObject*& object_out,
                               std::string_view subname,
                               void** py_object_out,
                               base::Matrix4D* matrix_out,
                               bool need_transform,
                               int depth) const override;

    /**
     * @brief 返回组内对象作为子对象的名字列表，如["Obj1.","Obj2.",...]
     * 
     * @param subnames_out 输出的子名字列表
     * @param reason 未用
     */
    bool ExtensionGetSubObjects(std::vector<std::string>& subnames_out, 
                                std::string_view reason) const override;

    app::DocumentObjectExecReturn* ExtensionExecute() override;
    
    //!@brief 返回组内所有对象，包括GroupExtension维护的孙子对象，按深度优先遍历顺序存储
    std::vector<app::DocumentObject*> GetAllChildren() const;
    
    /**
     * @brief 获取所有的子对象，包括GroupExtension维护的孙子对象
     * 
     * @param children_out 按深度优先遍历顺序存储子对象
     * @param objects 用于去重，其中的顺序和遍历顺序无关了
     */
    void GetAllChildren(std::vector<app::DocumentObject*>& children_out, std::set<app::DocumentObject*>& objects) const;

  public:  //属性
    PropertyLinkList Group;
    PropertyBool GroupTouched;

  private:
    void RemoveObjectFromDocument(DocumentObject* object);

    /**
    * @brief 此函数会存储已搜索过的对象，以防止在出现循环组图时发生无限递归。
    * 如果检测到循环依赖，将抛出 Base::RuntimeError 类型的异常。
    * 
    * @param object 
    * @param group 
    * @param history 
    * @return true 检测到包含object
    * @return false 不包含object
    */
    bool RecursiveHasObject(const DocumentObject* object,
                           const GroupExtension* group,
                           std::vector<const GroupExtension*> & history) const;

    //!@brief 用来跟踪子对象的visibility，当prop为object的Visibility属性时，touch GroupTouched属性
    void SlotChildChanged(const app::DocumentObject& object, const app::Property& prop);

    std::unordered_map<const app::DocumentObject*, boost::signals2::connection> m_child_changed_connection_map;
};

}  // namespace app

#endif