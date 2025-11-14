#pragma once

#include <App/DocumentObjectTopoShape.h>
#include <Base/Vector3D.h>
#include <App/Properties/PropertyVector.h>
#include <App/Properties/PropertyDirection.h>
#include "DevGlobal.h"

#define Dev_SETUP_NAME "DevSetup"

namespace Dev
{

  class DevObject : public app::DocumentObjectTopoShape
  {
    PFC_PROPERTY_DECL_WITH_OVERRIDE()

  public:
    app::PropertyString TypeName;

    DevObject();
    ~DevObject() override;
    app::PropertyVector *AddPropertyVector(const std::string &name, base::Vector3d values);
    app::PropertyVector *GetPropertyVector(const std::string &name, bool is_creator = true, base::Vector3d values = base::Vector3d(0, 0, 0));
    app::PropertyDirection *AddPropertyDirection(const std::string &name, base::Vector3d values);
    app::PropertyDirection *GetPropertyDirection(const std::string &name, bool is_creator = true, base::Vector3d values = base::Vector3d(0, 0, 0));

  protected:
    virtual void OnBeforePropertyValueChanging(const app::Property *) override;
    virtual void OnPropertyChanged(const app::Property *) override;
  };

} // namespace Dev