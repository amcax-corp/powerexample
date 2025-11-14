#ifndef POWERFC_APP_PROPERTIES_PROPERTYPERCENT_H_
#define POWERFC_APP_PROPERTIES_PROPERTYPERCENT_H_
#pragma once

#include <App/Properties/PropertyIntegerConstraint.h>
namespace app {

class PFC_APP_API PropertyPercent : public PropertyIntegerConstraint
{
    PFC_TYPESYSTEM_DECL_WITH_OVERRIDE();

    public:
    /// Standard constructor
    PropertyPercent();

    /// destructor
    ~PropertyPercent() override=default;

    private:
    static std::shared_ptr<PropertyIntegerConstraint::Constraints> s_percent_constraint;
};

}
#endif