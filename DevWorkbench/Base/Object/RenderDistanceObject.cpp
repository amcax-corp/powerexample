#include "RenderDistanceObject.h"
#include <App/Properties/PropertyFloat.h>
#include <App/Properties/PropertyVector.h>

PFC_PROPERTY_IMPL(Dev::RenderDistanceObject, Dev::DevObject)
namespace Dev
{

    RenderDistanceObject::RenderDistanceObject()
        : DevObject()
    {
        AddPropertyFloat("point1x");
        AddPropertyFloat("point1y");
        AddPropertyFloat("point1z");
        AddPropertyFloat("point2x");
        AddPropertyFloat("point2y");
        AddPropertyFloat("point2z");
    }

    RenderDistanceObject::~RenderDistanceObject()
    {
    }
} // namespace cam