#ifndef POWERFC_APP_PROPERTIES_PROPERTY_FLOAT_H_
#define POWERFC_APP_PROPERTIES_PROPERTY_FLOAT_H_
#pragma once
#include <App/Property.h>

namespace base {
class XMLReader;
class Writer;
}  // namespace base

namespace app {

/** @brief 浮点型属性，这是所有浮点型处理属性的基类。仅在少数情况下使用此类型，通常您会需要使用更专门的类型，例如 PropertyLength（长度属性）。
这些属性也满足单位系统的需求。有关带单位的所有属性，请参阅 PropertyUnits.h。
*/
class PFC_APP_API PropertyFloat : public Property
{
    PFC_TYPESYSTEM_DECL_WITH_OVERRIDE()

  public:
    /**
     * A constructor.
     * A more elaborate description of the constructor.
     */
    PropertyFloat();

    /**
     * A destructor.
     * A more elaborate description of the destructor.
     */
    ~PropertyFloat() override;

    void SetValue(double value);
    double GetValue() const;

    std::string_view GetEditorTypeName() const override
    {
        return "Gui::PropertyEditor::PropertyFloatItem";
    }

    // PyObject* getPyObject() override;
    // void setPyObject(PyObject* py) override;

    void Store(base::XMLWriter& writer, std::uint32_t) const override;
    void Restore(base::XMLReader& reader, std::uint32_t) override;

    std::unique_ptr<Property> Clone() const override;
    void Paste(const Property& from) override;

    size_t GetEstimatedSize() const override
    {
        return sizeof(double);
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
    double m_value;
};
}  // namespace app

#endif /* POWERFC_APP_PROPERTIES_PROPERTYFloat_H_ */