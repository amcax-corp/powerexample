#ifndef PFC_APP_GEOMETRYFEATUREGROUPEXTENSION_H
#define PFC_APP_GEOMETRYFEATUREGROUPEXTENSION_H
#pragma once
#include <App/GroupExtension.h>
#include <App/Properties/PropertyGeometry.h>
#include <App/Properties/PropertyPlacement.h>
#include <Base/Placement.h>

namespace app {

/**
* @brief The base of class of placeable group of DocumentObjects，用于表示局部坐标系
* 这个类用于实现局部坐标系，它会将其子对象归组，并通过GeometryFeatureGroupExtension的Placement属性对所有子对象进行坐标变换。
* 以下是几个重要特性：
* @li 所有属于该坐标系的子对象必须位于Group属性(从GroupExtension继承而来, LinkList类型的属性)中。即使某个草图(sketch)是某个拉伸体(pad)的组成部分，
* 也必须同时位于该GeometryFeatureGroupExtension的Group属性中。此规则同样适用于普通GroupExtensions。
* @li 一个对象只能属于单个GeometryFeatureGroupExtension。不允许将文档对象同时添加到多个GeometryFeatureGroupExtensions中。
* @li 禁止在不同GeometryFeatureGroupExtension之间建立PropertyLinks。系统提供了特殊的链接属性来实现跨坐标系的引用。
* @li 表达式(Expressions)可以跨GeometryFeatureGroupExtension边界使用。
*/
class GeometryFeatureGroupExtension : public GroupExtension
{
    PFC_EXTENSION_PROPERTY_DECL_WITH_OVERRIDE();

  public:
    GeometryFeatureGroupExtension();
    ~GeometryFeatureGroupExtension() override;

    //!@brief 此扩展只能用于GeometryFeature的子类，否则会抛出异常
    //!@exception 如果 object_extened 不是GeometryFeature的子类，则抛出RuntimeError
    void InitExtension(app::ExtensionContainer* object_extened) override;

  protected:
    //!@brief 被扩展对象(GeometryFeature)的Placement属性的引用
    app::PropertyPlacement& GetPlacement();

  public:
    //!@brief 对被扩展对象(GeometryFeature)施加一个坐标变换，重载该接口可实现坐标变换向基类特征的传播。
    virtual void TransformPlacement(const base::Placement& transformation);

    void ExtensionOnPropertyChanged(const app::Property*) override;

    /**
     * @brief 返回包含某对象的geometry feature group，找不到则返回nullptr。
     * 与DocumentObjectGroup::GetGroupOfObject不同，本方法仅搜索GeometryFeatureGroups。
     * @param object 
     * @return app::DocumentObject* 
     */
    static app::DocumentObject* GetGroupOfObject(const app::DocumentObject* object);

    /**
     * @brief 计算该组的全局定位
     * 返回的定位信息描述了从全局坐标系到该几何特征组（GeometryFeatureGroup）局部坐标系的变换。
     * 如果该组没有父级GeometryFeatureGroup，则直接返回该组自身的位置信息。
     * 对于多层嵌套的GeometryFeatureGroups，返回的位置信息是所有父级位置（包括本组位置）的组合变换结果。
     * @return base::Placement 
     */
    base::Placement GetGlobalGroupPlacement();

    /**
     * @brief 判断某对象是否属于某个GeometryFeatureGroup
     * 
     * @param object 
     * @return true 
     * @return false 
     */
    static bool IsInGeometryGroup(const app::DocumentObject* object);

    bool ExtensionGetSubObject(DocumentObject*& object_out,
                               std::string_view subname,
                               void** py_object_out,
                               base::Matrix4D* matrix_out,
                               bool need_transform,
                               int depth) const override;

    std::vector<app::DocumentObject*> AddObjects(std::vector<DocumentObject*> const& objects) override;

    std::vector<app::DocumentObject*> RemoveObjects(std::vector<DocumentObject*> const& objects) override;

    /**
     * @brief 收集与坐标系相关的所有链接，包括递归的in和out链接，排除表达式(expressions)产生的链接，遇到其他几何特征组(GeometryFeatureGroups)时停止递归。
     * 其结果就是CSOutList和CSInList的并集。
     * @param cs_object 输入的坐标系对象
     * @return std::vector<app::DocumentObject*> 
     */
    static std::vector<app::DocumentObject*> GetCSRelevantLinks(const app::DocumentObject* cs_object);

    //! @brief 检查给定对象的链接是否符合所有几何特征组(GeometryFeatureGroup)的要求，即普通链接是否仅存在于父级几何特征组内部。
    static bool AreLinksValid(const app::DocumentObject* cs_object);

    //!@brief 检查给定链接是否符合所有几何特征组(GeometryFeatureGroup)的要求，即普通链接是否仅存在于父级几何特征组内部。
    static bool IsLinkValid(app::Property* link);

    //!@brief 返回从cs_object错误链接的所有对象，即那些超出cs_object链接允许范围的对象
    static void GetInvalidLinkObjects(const app::DocumentObject* cs_object, std::vector<app::DocumentObject*>& objects_out);

  private:
    base::Placement GetRecursiveGroupPlacement(GeometryFeatureGroupExtension* group,
                                               std::unordered_set<GeometryFeatureGroupExtension*>& history);
    static std::vector<app::DocumentObject*> GetScopedObjectsFromLinks(const app::DocumentObject*,
                                                                       LinkScope scope = LinkScope::Local);

    static std::vector<app::DocumentObject*> GetScopedObjectsFromLink(app::Property*, 
                                                                 LinkScope scope = LinkScope::Local);

    /**
     * @brief 收集从给定对象链接的、与几何特征组(GeometryFeatureGroup)相关的对象。具体规则：
     * @li 包含所有链接对象（除几何特征组本身外）
     * @li 忽略表达式(expressions)生成的链接
     * @li 仅考虑当前Local Scope的链接
     * @li 不进行递归搜索
     * @param obj 
     * @param out_list 
     * @exception base::RuntimeError 若检测到依赖循环，则抛出异常
     */
    static void GetCSOutList(const app::DocumentObject* obj,
                             std::vector<app::DocumentObject*>& out_list);

    /**
     * @brief 收集从给定对象链接的、与几何特征组(GeometryFeatureGroup)相关的对象。具体规则：
     * @li 包含所有链接对象（除几何特征组本身外）
     * @li 忽略表达式(expressions)生成的链接
     * @li 仅考虑当前Local Scope的链接
     * @li 不进行递归搜索
     * @param obj 
     * @param out_list 
     * @exception base::RuntimeError 若检测到依赖循环，则抛出异常
     */
    static void GetCSInList(const app::DocumentObject* obj, std::vector<app::DocumentObject*>& in_list);

    static void GetRecursiveCSRelevantLinks(const app::DocumentObject* obj,
                                            std::vector<app::DocumentObject*>& cs_list);
};

}  // namespace app

#endif