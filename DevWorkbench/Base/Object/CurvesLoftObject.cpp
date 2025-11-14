#include "CurvesLoftObject.h"
#include "CurvesLoftObject.h"
#include <App/Properties/PropertyFloat.h>
#include <App/Properties/PropertyString.h>
#include <App/Properties/PropertyBool.h>
#include <App/Properties/PropertyTopoShape.h>

PFC_PROPERTY_IMPL(Dev::CurvesLoftObject, Dev::DevObject)
namespace Dev
{

    CurvesLoftObject::CurvesLoftObject()
        : DevObject()
    {
        TypeName.SetValue("CurvesLoft");
        AddPropertyString("CurvesName1");
        AddPropertyString("CurvesName2");
        AddDynamicProperty(app::PropertyTopoShape::GetClassType(), "TopeShape1");
        AddDynamicProperty(app::PropertyTopoShape::GetClassType(), "TopeShape2");
    }

    CurvesLoftObject::~CurvesLoftObject()
    {
    }
} // namespace cam