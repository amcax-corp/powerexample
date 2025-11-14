#pragma once

#include <App/Properties/PropertyEnumeration.h>
#include <App/Properties/PropertyString.h>
#include <Base/Object/DevObject.h>

namespace Dev {

class RenderDistanceObject;
class RenderDistanceObject : public Dev::DevObject
{
    PFC_PROPERTY_DECL_WITH_OVERRIDE()

  public:
    RenderDistanceObject();
    ~RenderDistanceObject() override;

  public:
    std::string_view GetViewProviderClassName() const override
    {
        return "Dev::ViewProviderRenderDistance";
    }
};

}  // namespace cam