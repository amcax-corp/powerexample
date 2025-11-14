#ifndef POWERFC_APP_PROPERTIES_PROPERTYVECTOR_H_
#define POWERFC_APP_PROPERTIES_PROPERTYVECTOR_H_
#pragma once
#include <App/Property.h>
#include <Base/Unit.h>
#include <Base/Vector3D.h>

namespace app {

class PFC_APP_API PropertyVector : public Property
{
    PFC_TYPESYSTEM_DECL_WITH_OVERRIDE()

  public:
    /**
     * A constructor.
     * A more elaborate description of the constructor.
     */
    PropertyVector() = default;

    /**
     * A destructor.
     * A more elaborate description of the destructor.
     */
    ~PropertyVector() override = default;

    void SetValue(const base::Vector3d& value);
    void SetValue(double x, double y, double z);
    const base::Vector3d& GetValue() const;

    std::string_view GetEditorTypeName() const override
    {
        return "Gui::PropertyEditor::PropertyVectorItem";
    }

    // PyObject* getPyObject() override;
    // void setPyObject(PyObject* py) override;

    void Store(base::XMLWriter& writer, std::uint32_t) const override;
    void Restore(base::XMLReader& reader, std::uint32_t) override;

    std::unique_ptr<Property> Clone() const override;
    void Paste(const Property& from) override;

    virtual base::Unit GetUnit() const
    {
        return {};
    }

    size_t GetEstimatedSize() const override
    {
        return sizeof(base::Vector3d);
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
    base::Vector3d m_value;
};

}  // namespace app

#endif