#pragma once

#include <App/Properties/PropertyEnumeration.h>
#include <App/Properties/PropertyString.h>
#include <Base/Object/DevObject.h>

namespace Dev
{

  class CurvesLoftObject;
  class CurvesLoftObject : public Dev::DevObject
  {
    PFC_PROPERTY_DECL_WITH_OVERRIDE()

  public:
    CurvesLoftObject();
    ~CurvesLoftObject() override;

  public:
    std::string_view GetViewProviderClassName() const override
    {
      return "Dev::ViewProviderCurvesLoft";
    }
  };

} // namespace cam