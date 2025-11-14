#ifndef POWERFC_APP_PROPERTIES_PROPERTY_H_
#define POWERFC_APP_PROPERTIES_PROPERTY_H_
#pragma once
#include <App/Properties/PropertyFloatConstraint.h>

namespace app {
/** @brief 精度属性，该属性用于处理具有多位小数的浮点数值，例如存储 Precision::Confusion() 这类精度值。默认带有非负约束，但该约束可以被覆盖。
*/
class PFC_APP_API PropertyPrecision : public PropertyFloatConstraint
{
    PFC_TYPESYSTEM_DECL_WITH_OVERRIDE();

  public:
    PropertyPrecision();
    ~PropertyPrecision() override = default;

    std::string_view GetEditorTypeName() const override
    {
        return "Gui::PropertyEditor::PropertyPrecisionItem";
    }

    private:
    static std::shared_ptr<PropertyFloatConstraint::Constraints> s_precision_constraints;
};

}  // namespace app
#endif