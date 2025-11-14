#ifndef POWERFC_APP_PROPERTIES_PROPERTY_STRING_H_
#define POWERFC_APP_PROPERTIES_PROPERTY_STRING_H_
#pragma once
#include <App/Property.h>
#include <string_view>

namespace base {
class XMLReader;
class Writer;
}  // namespace base

namespace app {

class PFC_APP_API PropertyString : public Property
{
    PFC_TYPESYSTEM_DECL_WITH_OVERRIDE()

  public:
    /**
     * A constructor.
     * A more elaborate description of the constructor.
     */
    PropertyString();

    /**
     * A destructor.
     * A more elaborate description of the destructor.
     */
    ~PropertyString() override;

    virtual void SetValue(std::string_view value);
    std::string_view GetValue() const;

    std::string const& GetString() const{
        return m_value;
    }

    std::string_view GetEditorTypeName() const override
    {
        return "Gui::PropertyEditor::PropertyStringItem";
    }

    // PyObject* getPyObject() override;
    // void setPyObject(PyObject* py) override;

    void Store(base::XMLWriter& writer, std::uint32_t) const override;
    void Restore(base::XMLReader& reader, std::uint32_t) override;

    std::unique_ptr<Property> Clone() const override;
    void Paste(const Property& from) override;

    size_t GetEstimatedSize() const override
    {
        return m_value.size();
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

  protected:
    std::string m_value;
};
}  // namespace app

#endif /* POWERFC_APP_PROPERTIES_PROPERTYBOOL_H_ */