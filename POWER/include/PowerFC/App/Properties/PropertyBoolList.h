#ifndef POWERFC_APP_PROPERTIES_PROPERTY_BOOL_LIST_H_
#define POWERFC_APP_PROPERTIES_PROPERTY_BOOL_LIST_H_
#pragma once
#include <App/Property.h>

namespace app {

class PFC_APP_API PropertyBoolList : public PropertyListsT<bool>
{
    PFC_TYPESYSTEM_DECL_WITH_OVERRIDE();

  public:
    PropertyBoolList() = default;
    ~PropertyBoolList() override = default;

    std::string_view GetEditorTypeName() const override
    {
        return "Gui::PropertyEditor::PropertyBoolListItem";
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