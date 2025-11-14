#pragma once

#include "RenderDataHelper.h"
#include "ViewProviderDocumentObjectTopoShape.h"
#include <app/Properties/PropertyMaterial.h>

namespace gui {

class PFC_GUI_API ViewProviderDocumentObjectWireframedMarker : public ViewProviderDocumentObjectTopoShape
{
    PFC_PROPERTY_DECL_WITH_OVERRIDE()

  public:

    ViewProviderDocumentObjectWireframedMarker();
    ~ViewProviderDocumentObjectWireframedMarker() override;
    
    virtual void UpdateData(const app::Property*) override;
};

}  // namespace gui