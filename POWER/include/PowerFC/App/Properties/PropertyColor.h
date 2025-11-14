#ifndef POWERFC_APP_PROPERTIES_PROPERTY_COLOR_H_
#define POWERFC_APP_PROPERTIES_PROPERTY_COLOR_H_
#pragma once
#include <App/Color.h>
#include <App/Property.h>


namespace app {
class PFC_APP_API PropertyColor : public Property
{
    PFC_TYPESYSTEM_DECL_WITH_OVERRIDE()

  public:
    PropertyColor() = default;
    ~PropertyColor() override = default;

    void SetValue(Color const& value);
    void SetValue(float r, float g, float b, float a = 0.0);

    //!@brief  Sets color as a 32 bit packed unsigned int in the form 0xAARRGGBB.
    void SetValue(uint32_t rgba);

    Color const& GetValue() const;

    std::string_view GetEditorTypeName() const override
    {
        return "Gui::PropertyEditor::PropertyColorItem";
    }

    // PyObject* getPyObject() override;
    // void setPyObject(PyObject* py) override;

    void Store(base::XMLWriter& writer, std::uint32_t) const override;
    void Restore(base::XMLReader& reader, std::uint32_t) override;

    std::unique_ptr<Property> Clone() const override;
    void Paste(const Property& from) override;

    size_t GetEstimatedSize() const override
    {
        return sizeof(Color);
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
    Color m_color;
};
}  // namespace app
#endif