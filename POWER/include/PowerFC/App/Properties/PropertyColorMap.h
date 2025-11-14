#ifndef POWERFC_APP_PROPERTIES_PROPERTY_COLORMAP_H_
#define POWERFC_APP_PROPERTIES_PROPERTY_COLORMAP_H_
#pragma once
#include <App/Property.h>
#include <App/Color.h>

namespace app {

class PFC_APP_API PropertyColorMap : public Property
{
    PFC_TYPESYSTEM_DECL_WITH_OVERRIDE();

  public:
    PropertyColorMap() = default;
    ~PropertyColorMap() override = default;

    // PyObject* getPyObject() override;
    // void setPyObject(PyObject* py) override;

    void SetValues(const std::unordered_map<int, Color>& colors);
    void SetValue(const std::unordered_map<int, Color>& colors);
    void SetValue(int index, const Color& color);
    const Color& GetValue(int index) const;

    std::unordered_map<int, Color> const& GetValues() const{
        return m_colors;
    }

    std::size_t GetSize() const{
        return m_colors.size();
    }

    void Store(base::XMLWriter& writer, std::uint32_t) const override;
    void Restore(base::XMLReader& reader, std::uint32_t) override;

    std::unique_ptr<Property> Clone() const override;
    void Paste(const Property& from) override;

    size_t GetEstimatedSize() const override;

    private:
    std::unordered_map<int, Color> m_colors;
};

}  // namespace app
#endif