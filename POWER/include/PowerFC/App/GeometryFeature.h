#ifndef POWERFC_APP_GEOMETRYFEATURE_H_
#define POWERFC_APP_GEOMETRYFEATURE_H_
#pragma once

#include <App/DocumentObject.h>
#include <App/Properties/PropertyPlacement.h>

namespace app {
class PFC_APP_API GeometryFeature : public DocumentObject
{
    PFC_PROPERTY_DECL_WITH_OVERRIDE();

  public:
    PropertyPlacement Placement;
    PropertyString _ElementMapVersion;
    GeometryFeature();
    ~GeometryFeature();

    enum class ReasonGettingElementName
    {
        Normal = 0,  //正常
        Import = 1,  //for importing
        Export = 2   //for exporting
    };

    /**
     * @brief 解析子元素名字
     * 
     * @param object 顶层父对象
     * @param subname 子名字引用
     * @param element_name_out 输出的元素名字
     * @param append 是否输出前缀到element_name_out
     * @param reason 
     * @param filter 过滤条件对象指针，nullptr表示不过滤，非nullptr时只查找属于该对象的元素
     * @param element_offset_out 输出参数，返回subname中元素名的起始位置指针
     * @param geometry_out 
     * @return DocumentObject* 返回该元素的实际所属对象指针
     */
    static DocumentObject* ResolveElement(const app::DocumentObject* object,
                                          std::string_view subname,
                                          std::string& element_name_out,
                                          bool append = false,
                                          ReasonGettingElementName reason = ReasonGettingElementName::Normal,
                                          const app::DocumentObject* filter = nullptr,
                                          std::string_view* element_offset_out = nullptr,
                                          app::GeometryFeature** geometry_out = nullptr);
};
}  // namespace app

#endif