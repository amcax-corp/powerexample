#pragma once

#include <App/Properties/PropertyEnumeration.h>
#include <App/Properties/PropertyString.h>
#include <Base/Object/DevObject.h>

namespace Dev {

class BoxObject;
class BoxObject : public Dev::DevObject
{
    PFC_PROPERTY_DECL_WITH_OVERRIDE()

  public:
    BoxObject();
    ~BoxObject() override;

  public:
    std::string_view GetViewProviderClassName() const override
    {
        return "Dev::ViewProviderBox";
    }
};

}  // namespace cam