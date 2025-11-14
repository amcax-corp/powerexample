#pragma once

#include "DocumentObject.h"
#define DEFAULT_LAYER_NAME "DefaultLayer"

namespace app {

class PFC_APP_API DocumentObjectLayer : public DocumentObject
{
    PFC_PROPERTY_DECL_WITH_OVERRIDE()

  public:
    DocumentObjectLayer();
    ~DocumentObjectLayer() override;

  public:
    std::string_view GetViewProviderClassName() const override
    {
        return "gui::ViewProviderDocumentObjectLayer";
    }
};

}  // namespace app