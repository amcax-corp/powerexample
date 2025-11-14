#ifndef POWERFC_GUI_WINDOWPARAMETER_H_
#define POWERFC_GUI_WINDOWPARAMETER_H_

#pragma once
#include <Base/Parameter.h>
#include <boost/signals2.hpp>

namespace gui {

class PFC_GUI_API WindowParameter : public base::ParameterGroup::ObserverType
{
  public:
    WindowParameter(std::string_view);
    ~WindowParameter();

    void OnChange(base::Subject<std::string_view>& caller, std::string_view const&) override;

    //返回参数组节点User parameter:BaseApp/Preference
    static base::ParameterGroup* GetDefaultParameter();

    //返回窗体的参数组
    base::ParameterGroup* GetWindowParameter();

  protected:
    bool SetGroupName(std::string_view name);

    //连接slot到参数组信号
    template<typename S, typename T>
    void SetSlotParameterChanged(S slot, T* observer);

  private:
    base::ParameterGroup* m_window_grp;
    boost::signals2::connection m_connection_parameter_changed;
};


template<typename S, typename T>
void WindowParameter::SetSlotParameterChanged(S slot, T* observer)
{
    if(m_window_grp->GetManager()){
        m_connection_parameter_changed =  m_window_grp->GetManager()->SignalParameterChanged.connect(
            [&](base::ParameterGroup* grp, std::string_view name, std::any value){
                slot(observer, grp, name, value);
            }
        );
    }
}

}  // namespace gui
#endif /* POWERFC_GUI_WINDOWPARAMETER_H_ */