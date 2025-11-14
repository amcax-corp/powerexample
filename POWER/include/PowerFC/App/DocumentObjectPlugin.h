#pragma once

#include "DocumentObject3D.h"

namespace app {
class PFC_APP_API DocumentObjectPlugin : public DocumentObject3D
{
    PFC_PROPERTY_DECL_WITH_OVERRIDE()

  public:
    DocumentObjectPlugin();
    ~DocumentObjectPlugin() override;

    std::string_view GetViewProviderClassName() const override
    {
        return "gui::ViewProviderDocumentObjectPlugin";
    }
};

}  // namespace app