#ifndef POWERFC_APP_PROPERTIES_PROPERTYBOOL_H_
#define POWERFC_APP_PROPERTIES_PROPERTYBOOL_H_
#pragma once
#include <App/Property.h>

namespace base {
class XMLReader;
class Writer;
}  // namespace base

namespace app {

class PFC_APP_API PropertyBool : public Property
{
    PFC_TYPESYSTEM_DECL_WITH_OVERRIDE()

  public:
    /**
     * A constructor.
     * A more elaborate description of the constructor.
     */
    PropertyBool();

    /**
     * A destructor.
     * A more elaborate description of the destructor.
     */
    ~PropertyBool() override;

    void SetValue(bool value);
    bool GetValue() const;

    std::string_view GetEditorTypeName() const override
    {
        return "Gui::PropertyEditor::PropertyBoolItem";
    }

    // PyObject* getPyObject() override;
    // void setPyObject(PyObject* py) override;

    void Store(base::XMLWriter& writer, std::uint32_t) const override;
    void Restore(base::XMLReader& reader, std::uint32_t) override;

    std::unique_ptr<Property> Clone() const override;
    void Paste(const Property& from) override;

    size_t GetEstimatedSize() const override
    {
        return sizeof(bool);
    }

    // void SetPathValue(const app::ObjectIdentifier& path, const std::any& value) override;
    // const std::any GetPathValue(const app::ObjectIdentifier& path) const override;

    bool IsSame(const Property& other) const override
    {
        if (&other == this)
        {
            return true;
        }
        return GetClassTypePolymorphic() == other.GetClassTypePolymorphic() &&
               GetValue() == static_cast<decltype(this)>(&other)->GetValue();
    }

  private:
    bool m_value;
};
}  // namespace app

#endif /* POWERFC_APP_PROPERTIES_PROPERTYBOOL_H_ */