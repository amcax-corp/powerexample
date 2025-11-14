#ifndef POWERFC_APP_PROPERTIES_PROPERTYDIRECTION_H_
#define POWERFC_APP_PROPERTIES_PROPERTYDIRECTION_H_
#pragma once

#include <App/Properties/PropertyVector.h>

namespace app {

class PFC_APP_API PropertyDirection : public PropertyVector
{
    PFC_TYPESYSTEM_DECL_WITH_OVERRIDE()
    public:
    
    /**
     * A constructor.
     * A more elaborate description of the constructor.
     */
    PropertyDirection()=default;

    /**
     * A destructor.
     * A more elaborate description of the destructor.
     */
    ~PropertyDirection() override=default;

    base::Unit GetUnit() const override
    {
        return base::Unit::Length;
    }

    std::string_view GetEditorTypeName() const override
    {
        return "Gui::PropertyEditor::PropertyDirectionItem";
    }
};

}  // namespace app

#endif