#ifndef POWERFC_APP_PROPERTIES_PROPERTY_VECTOR_LIST_H_
#define POWERFC_APP_PROPERTIES_PROPERTY_VECTOR_LIST_H_
#pragma once
#include <App/Property.h>
#include <Base/Vector3D.h>

namespace app {

class PFC_APP_API PropertyVectorList : public PropertyListsT<base::Vector3d>
{
    PFC_TYPESYSTEM_DECL_WITH_OVERRIDE();

  public:
    PropertyVectorList() = default;
    ~PropertyVectorList() override = default;

    void SetValue(double x, double y, double z);
    
    using PropertyListsT<base::Vector3d>::SetValue;

    std::string_view GetEditorTypeName() const override
    {
        return "Gui::PropertyEditor::PropertyVectorListItem";
    }

    // PyObject* getPyObject() override;
    // void setPyObject(PyObject* py) override;

    void Store(base::XMLWriter& writer, std::uint32_t) const override;
    void Restore(base::XMLReader& reader, std::uint32_t) override;

    std::unique_ptr<Property> Clone() const override;
    void Paste(const Property& from) override;

    size_t GetEstimatedSize() const override;
};

}  // namespace app
#endif