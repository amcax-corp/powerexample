#ifndef POWERFC_APP_PROPERTIES_PROPERTYPLACEMENT_H_
#define POWERFC_APP_PROPERTIES_PROPERTYPLACEMENT_H_
#pragma once
#include <App/Property.h>
#include <Base/Placement.h>

namespace app {

class PFC_APP_API PropertyPlacement : public Property
{
    PFC_TYPESYSTEM_DECL_WITH_OVERRIDE()

  public:
    /**
     * A constructor.
     * A more elaborate description of the constructor.
     */
    PropertyPlacement() = default;

    /**
     * A destructor.
     * A more elaborate description of the destructor.
     */
    ~PropertyPlacement() override = default;

    void SetValue(const base::Placement& value);

    /**
     * @brief Set the Value If Changed object
     * 
     * @param value 
     * @param position_tolerance 
     * @param angular_tolerance 
     * @return true 
     * @return false 
     */
    bool SetValueIfChanged(const base::Placement& value,
                           double position_tolerance = 1e-7,
                           double angular_tolerance = 1e-12);

    const base::Placement& GetValue() const;

    std::string_view GetEditorTypeName() const override
    {
        return "Gui::PropertyEditor::PropertyPlacementItem";
    }

    // PyObject* getPyObject() override;
    // void setPyObject(PyObject* py) override;

    void Store(base::XMLWriter& writer, std::uint32_t) const override;
    void Restore(base::XMLReader& reader, std::uint32_t) override;

    std::unique_ptr<Property> Clone() const override;
    void Paste(const Property& from) override;

    size_t GetEstimatedSize() const override
    {
        return sizeof(base::Placement);
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

    static const base::Placement Null();

  private:
  base::Placement m_value;
};

}  // namespace app

#endif