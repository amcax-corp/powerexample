#ifndef POWERCORE_APP_PROPERTIES_PROPERTY_FONT_H_
#define POWERCORE_APP_PROPERTIES_PROPERTY_FONT_H_
#pragma once

#include <App/Properties/PropertyString.h>

namespace app{

    class PFC_APP_API PropertyFont : public PropertyString
    {
        PFC_TYPESYSTEM_DECL_WITH_OVERRIDE();

    public:
    PropertyFont()=default;
    ~PropertyFont() override = default;

    std::string_view GetEditorTypeName() const override
    {
        return "Gui::PropertyEditor::PropertyFontItem";

    }

    bool IsSame(const Property& other) const override
    {
        if (&other == this)
        {
            return true;
        }
        return GetClassTypePolymorphic() == other.GetClassTypePolymorphic() &&
               GetValue() == static_cast<decltype(this)>(&other)->GetValue();
    }
};

}

#endif