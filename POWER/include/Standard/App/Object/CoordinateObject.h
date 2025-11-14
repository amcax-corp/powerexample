#pragma once

#include <App/DocumentObject3D.h>
#include <App/Properties/PropertyVector.h>

namespace standard {
class CoordinateObject : public app::DocumentObject3D
{
    PFC_PROPERTY_DECL_WITH_OVERRIDE()
  public:
    CoordinateObject();
    ~CoordinateObject() override;

    std::string_view GetViewProviderClassName() const override;
};
}  // namespace standard