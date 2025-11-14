#pragma once

#include "ViewProviderDocumentObject.h"

namespace gui {

class PFC_GUI_API ViewProviderDocumentObjectLayer : public ViewProviderDocumentObject
{
    PFC_PROPERTY_DECL_WITH_OVERRIDE()

  public:
    ViewProviderDocumentObjectLayer();
    ~ViewProviderDocumentObjectLayer() override;

    void SetHighlight(bool isHighlight);

    virtual void DeleteFromView() override;

    virtual bool OnDelete() override;
};

}  // namespace gui