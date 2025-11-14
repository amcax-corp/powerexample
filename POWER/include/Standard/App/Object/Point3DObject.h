#pragma once

#include <App/DocumentObject3D.h>
#include <App/Properties/PropertyVector.h>

namespace standard {
class Point3DObject : public app::DocumentObject3D
{
    PFC_PROPERTY_DECL_WITH_OVERRIDE()
  public:
    Point3DObject();
    ~Point3DObject() override;

    std::string_view GetViewProviderClassName() const override;
};
}  // namespace standard