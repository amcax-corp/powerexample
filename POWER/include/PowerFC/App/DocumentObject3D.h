#pragma once

#include "DocumentObject.h"

namespace app {

class PFC_APP_API DocumentObject3D : public DocumentObject
{
    PFC_PROPERTY_DECL_WITH_OVERRIDE()

  public:
    DocumentObject3D();
    ~DocumentObject3D() override;

    std::string_view GetViewProviderClassName() const override
    {
        return "gui::ViewProviderDocument3D";
    }
    
    //返回一个字符串，用于在渲染场景中区分不同的对象，形式为doc_name.object_name_in_doc
    // std::string MakeObjectIDInRender() const;
};

}  // namespace app