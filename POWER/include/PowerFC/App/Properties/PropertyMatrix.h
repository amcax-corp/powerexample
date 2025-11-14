#ifndef POWERFC_APP_PROPERTIES_PROPERTYMATRIX_H_
#define POWERFC_APP_PROPERTIES_PROPERTYMATRIX_H_
#pragma once
#include <App/Property.h>
#include <Base/Matrix.h>

namespace app {

class PFC_APP_API PropertyMatrix : public Property
{
    PFC_TYPESYSTEM_DECL_WITH_OVERRIDE()

  public:
    /**
     * A constructor.
     * A more elaborate description of the constructor.
     */
    PropertyMatrix() = default;

    /**
     * A destructor.
     * A more elaborate description of the destructor.
     */
    ~PropertyMatrix() override = default;

    void SetValue(const base::Matrix4D& value);
    void SetValue(double x, double y, double z);
    const base::Matrix4D& GetValue() const;

    std::string_view GetEditorTypeName() const override
    {
        return "Gui::PropertyEditor::PropertyMatrixItem";
    }

    // PyObject* getPyObject() override;
    // void setPyObject(PyObject* py) override;

    void Store(base::XMLWriter& writer, std::uint32_t) const override;
    void Restore(base::XMLReader& reader, std::uint32_t) override;

    std::unique_ptr<Property> Clone() const override;
    void Paste(const Property& from) override;

    size_t GetEstimatedSize() const override
    {
        return sizeof(base::Matrix4D);
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
    base::Matrix4D m_value;
};

}  // namespace app

#endif