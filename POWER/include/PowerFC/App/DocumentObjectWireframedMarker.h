#pragma once

#include "DocumentObjectTopoShape.h"

namespace app {

class PFC_APP_API DocumentObjectWireframedMarker : public DocumentObjectTopoShape
{
    PFC_PROPERTY_DECL_WITH_OVERRIDE()

    DocumentObjectWireframedMarker();
    ~DocumentObjectWireframedMarker() override;

    std::string_view GetViewProviderClassName() const override
    {
        return "gui::ViewProviderDocumentObjectWireframedMarker";
    }

  protected:
    void OnPropertyChanged(const app::Property*) override;
    void OnDocumentRestored() override;
};

}  // namespace app
