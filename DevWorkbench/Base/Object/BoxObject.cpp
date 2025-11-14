#include "BoxObject.h"
#include "BoxObject.h"
#include <App/Properties/PropertyFloat.h>
#include <App/Properties/PropertyVector.h>

PFC_PROPERTY_IMPL(Dev::BoxObject, Dev::DevObject)
namespace Dev
{

    BoxObject::BoxObject()
        : DevObject()
    {
        TypeName.SetValue("Box");
        AddPropertyVector("Position", base::Vector3d(0, 0, 0));
        AddPropertyFloat("Length", 10);
        AddPropertyFloat("Width", 10);
        AddPropertyFloat("Height", 10);
    }

    BoxObject::~BoxObject()
    {
    }
} // namespace cam