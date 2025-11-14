#ifndef POWERFC_APP_PROPERTIES_PROPERTYFLOATCONSTRAINT_H_
#define POWERFC_APP_PROPERTIES_PROPERTYFLOATCONSTRAINT_H_
#pragma once
#include <App/Properties/PropertyFloat.h>

namespace base {
class XMLReader;
class Writer;
}  // namespace base

namespace app {

class PFC_APP_API PropertyFloatConstraint : public PropertyFloat
{
    PFC_TYPESYSTEM_DECL_WITH_OVERRIDE()

  public:
    /**
     * A constructor.
     * A more elaborate description of the constructor.
     */
    PropertyFloatConstraint()=default;

    /**
     * A destructor.
     * A more elaborate description of the destructor.
     */
    ~PropertyFloatConstraint() override=default;


    struct Constraints{
        double lower_bound{0};
        double upper_bound{0};
        double step{0};
    };


    /**
     * @brief 设定约束边界
     * 
     * @param constraint 可以是动态创建的或者作为类静态成员创建的
     */
    void SetConstraints(std::shared_ptr<const Constraints> constraint);

    /// get the constraint struct
    std::shared_ptr<const Constraints>  GetConstraints() const;
    //@}

    double GetMinimum() const;
    double GetMaximum() const;
    double GetStep() const;

    std::string_view GetEditorTypeName() const override
    {
        return "Gui::PropertyEditor::PropertyFloatConstraintItem";
    }

  private:
  std::shared_ptr<const Constraints> m_const_constraint{};
};
}  // namespace app
#endif