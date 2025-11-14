#ifndef POWERFC_APP_MATERIAL_H_
#define POWERFC_APP_MATERIAL_H_
#pragma once
#include <App/Color.h>

namespace app {

class PFC_APP_API Material
{
  public:
    enum class MaterialType
    {
        BRASS,
        BRONZE,
        COPPER,
        GOLD,
        PEWTER,
        PLASTER,
        PLASTIC,
        SILVER,
        STEEL,
        STONE,
        SHINY_PLASTIC,
        SATIN,
        METALIZED,
        NEON_GNC,
        CHROME,
        ALUMINIUM,
        OBSIDIAN,
        NEON_PHC,
        JADE,
        RUBY,
        EMERALD,
        DEFAULT,
        USER_DEFINED
    };

  public:
    /** @name Constructors
     */
    //@{
    /** Sets the USER_DEFINED material type. The user must set the colors afterwards. */
    Material();
    ~Material() = default;
    /** Copy constructor. */
    Material(const Material& other) = default;
    Material(Material&& other) = default;
    /** Defines the colors and shininess for the material \a MatName. If \a MatName isn't defined
     * then USER_DEFINED is set and the user must define the colors itself.
     */
    explicit Material(std::string_view material_name);
    /** Does basically the same as the constructor above unless that it accepts a MaterialType as
     * argument. */
    explicit Material(MaterialType material_type);
    //@}

    /** Set a material by name
     *  There are some standard materials defined which are:
     *  \li Brass
     *  \li Bronze
     *  \li Copper
     *  \li Gold
     *  \li Pewter
     *  \li Plaster
     *  \li Plastic
     *  \li Silver
     *  \li Steel
     *  \li Stone
     *  \li Shiny plastic
     *  \li Satin
     *  \li Metalized
     *  \li Neon GNC
     *  \li Chrome
     *  \li Aluminium
     *  \li Obsidian
     *  \li Neon PHC
     *  \li Jade
     *  \li Ruby
     *  \li Emerald
     * Furthermore there two additional modes \a Default which defines a kind of grey metallic and
     * user defined that does nothing. The Color and the other properties of the material are
     * defined in the range [0-1]. If \a MatName is an unknown material name then the type
     * USER_DEFINED is set and the material doesn't get changed.
     */
    void Set(std::string_view material_name);
    /**
     * This method is provided for convenience which does basically the same as the method above
     * unless that it accepts a MaterialType as argument.
     */
    void SetMaterialType(MaterialType MatType);
    /**
     * Returns the currently set material type.
     */
    MaterialType GetMaterialType() const
    {
        return m_material_type;
    }

    /** @name Properties */
    //@{
    // NOLINTBEGIN

    // NOLINTEND
    //@}

    bool operator==(const Material& m) const
    {
        // clang-format off
        return m_material_type == m.m_material_type
            && m_ambient_color == m.m_ambient_color
            && m_diffuse_color == m.m_diffuse_color
            && m_specular_color == m.m_specular_color
            && m_emissive_color == m.m_emissive_color
            && m_shininess == m.m_shininess
            && m_transparency == m.m_transparency
            && m_image == m.m_image
            && m_image_path == m.m_image_path
            && m_uuid == m.m_uuid;
        // clang-format on
    }
    bool operator!=(const Material& m) const
    {
        return !operator==(m);
    }
    Material& operator=(const Material& other) = default;
    Material& operator=(Material&& other) = default;

    static Material GetDefaultAppearance();

    void SetAmbientColor(const Color& col)
    {
        m_ambient_color = col;
    }
    void SetDiffuseColor(const Color& col)
    {
        m_diffuse_color = col;
    }
    void SetSpecularColor(const Color& col)
    {
        m_specular_color = col;
    }
    void SetEmissiveColor(const Color& col)
    {
        m_emissive_color = col;
    }
    void SetShininess(float shininess)
    {
        m_shininess = shininess;
    }
    void SetTransparency(float transparency)
    {
        m_transparency = transparency;
    }
    void SetImage(const std::string& image)
    {
        m_image = image;
    }
    void SetImagePath(const std::string& image_path)
    {
        m_image_path = image_path;
    }
    void SetUUID(const std::string& uuid)
    {
        m_uuid = uuid;
    }

    const Color& GetAmbientColor() const
    {
        return m_ambient_color;
    }
    const Color& GetDiffuseColor() const
    {
        return m_diffuse_color;
    }
    const Color& GetSpecularColor() const
    {
        return m_specular_color;
    }
    const Color& GetEmissiveColor() const
    {
        return m_emissive_color;
    }
    float GetShininess() const
    {
        return m_shininess;
    }
    float GetTransparency() const
    {
        return m_transparency;
    }
    const std::string& GetImage() const
    {
        return m_image;
    }
    const std::string& GetImagePath() const
    {
        return m_image_path;
    }
    const std::string& GetUUID() const
    {
        return m_uuid;
    }

  protected:
    Color m_ambient_color;  /**< Defines the ambient color. */
    Color m_diffuse_color;  /**< Defines the diffuse color. */
    Color m_specular_color; /**< Defines the specular color. */
    Color m_emissive_color; /**< Defines the emissive color. */
    float m_shininess;
    float m_transparency;
    std::string m_image;
    std::string m_image_path;
    std::string m_uuid;

  private:
    MaterialType m_material_type;
};

}  // namespace app

#endif