#include "DevObject.h"

PFC_PROPERTY_IMPL(Dev::DevObject, app::DocumentObjectTopoShape)
namespace Dev {

DevObject::DevObject()
  : DocumentObjectTopoShape()
{
    PFC_ADD_PROPERTY_TYPE(TypeName, (""), app::PropertyFlag::PROPERTY_NONE, "DevObject", "TypeName");
}

DevObject::~DevObject()
{
}

app::PropertyVector* DevObject::AddPropertyVector(const std::string& name, base::Vector3d values)
{
    AddDynamicProperty(app::PropertyVector::GetClassType().GetName(), name);
    auto point = GetDynamicPropertyByName(name)->SafeDownCast<app::PropertyVector>();
    point->SetValue(values);
    return point;
}

app::PropertyVector* DevObject::GetPropertyVector(const std::string& name, bool is_creator, base::Vector3d values)
{
    if (auto p = GetDynamicPropertyByName(name))
    {
        return p->SafeDownCast<app::PropertyVector>();
    }
    else if (is_creator)
    {
        return AddPropertyVector(name, values);
    }
    else
    {
        return nullptr;
    }
}

app::PropertyDirection* DevObject::AddPropertyDirection(const std::string& name, base::Vector3d values)
{
    AddDynamicProperty(app::PropertyDirection::GetClassType().GetName(), name);
    auto point = GetDynamicPropertyByName(name)->SafeDownCast<app::PropertyDirection>();
    point->SetValue(values);
    return point;
}

app::PropertyDirection* DevObject::GetPropertyDirection(const std::string& name, bool is_creator, base::Vector3d values)
{
    if (auto p = GetDynamicPropertyByName(name))
    {
        return p->SafeDownCast<app::PropertyDirection>();
    }
    else if (is_creator)
    {
        return AddPropertyDirection(name, values);
    }
    else
    {
        return nullptr;
    }
}

// void DevObject::OnPipeValueChangd(const app::Property *prop)
// {
    
// }

void DevObject::OnBeforePropertyValueChanging(const app::Property* prop)
{
    app::DocumentObjectTopoShape::OnBeforePropertyValueChanging(prop);
}

void DevObject::OnPropertyChanged(const app::Property* prop)
{
    app::DocumentObjectTopoShape::OnPropertyChanged(prop);
}

}  // namespace Dev