#ifndef POWERFC_APP_PROPERTIES_PROPERTY_MATERIAL_H_
#define POWERFC_APP_PROPERTIES_PROPERTY_MATERIAL_H_
#pragma once

#include <App/Material.h>
#include <App/Property.h>

namespace app {
class PFC_APP_API PropertyMaterial : public Property
{
    PFC_TYPESYSTEM_DECL_WITH_OVERRIDE()

  public:
    PropertyMaterial() = default;
    ~PropertyMaterial() override = default;

    void SetValue(const Material& mat);
    void SetValue(const Color& col);
    void SetValue(float r, float g, float b, float a = 0.0F);
    void SetValue(uint32_t rgba);
    void SetAmbientColor(const Color& col);
    void SetAmbientColor(float r, float g, float b, float a = 0.0F);
    void SetAmbientColor(uint32_t rgba);
    void SetDiffuseColor(const Color& col);
    void SetDiffuseColor(float r, float g, float b, float a = 0.0F);
    void SetDiffuseColor(uint32_t rgba);
    void SetSpecularColor(const Color& col);
    void SetSpecularColor(float r, float g, float b, float a = 0.0F);
    void SetSpecularColor(uint32_t rgba);
    void SetEmissiveColor(const Color& col);
    void SetEmissiveColor(float r, float g, float b, float a = 0.0F);
    void SetEmissiveColor(uint32_t rgba);
    void SetShininess(float);
    void SetTransparency(float);

    /** This method returns a string representation of the property
     */
    const Material& GetValue() const;
    const Color& GetAmbientColor() const;
    const Color& GetDiffuseColor() const;
    const Color& GetSpecularColor() const;
    const Color& GetEmissiveColor() const;
    double GetShininess() const;
    double GetTransparency() const;

    std::string_view GetEditorTypeName() const override;

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
    Material m_material;
};
}  // namespace app
#endif