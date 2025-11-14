#ifndef POWERFC_APP_PROPERTIES_PROPERTY_STRING_LIST_H_
#define POWERFC_APP_PROPERTIES_PROPERTY_STRING_LIST_H_

#pragma once
#include <App/Property.h>

namespace app {

    class PFC_APP_API PropertyStringList: public PropertyListsT<std::string>
{
    PFC_TYPESYSTEM_DECL_WITH_OVERRIDE();
    using Base = PropertyListsT<std::string>;

public:

    /**
     * A constructor.
     * A more elaborate description of the constructor.
     */
    PropertyStringList()=default;

    /**
     * A destructor.
     * A more elaborate description of the destructor.
     */
    ~PropertyStringList() override=default;

    void SetValues(const std::list<std::string>&);
    using Base::SetValues;

    std::string_view GetEditorTypeName() const override
    { return "Gui::PropertyEditor::PropertyStringListItem"; }


    void Store(base::XMLWriter& writer, std::uint32_t) const override;
    void Restore(base::XMLReader& reader, std::uint32_t) override;

    std::unique_ptr<Property> Clone() const override;
    void Paste(const Property& from) override;

    size_t GetEstimatedSize() const override;

protected:
    // std::string getPyValue(PyObject *item) const override;
};

}
#endif