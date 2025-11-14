#ifndef POWERFC_BASE_PARAMETERGROUPOBSERVER_H_
#define POWERFC_BASE_PARAMETERGROUPOBSERVER_H_
#pragma once

#include <Base/Parameter.h>

namespace base{
    class ParameterGroupObserver: public base::ParameterGroup::ObserverType{

        public:
        ParameterGroupObserver() {}

        virtual ~ParameterGroupObserver() {}
        void OnChange(ParameterGroup::SubjectType& caller, ParameterGroup::MessageType const& reason) override
        {
            if(auto group = dynamic_cast<ParameterGroup*>(&caller)){
                OnParameterChange(group, reason);
            }
        }

        virtual void OnParameterChange(ParameterGroup* group, std::string_view reason) = 0;
    };
}
#endif