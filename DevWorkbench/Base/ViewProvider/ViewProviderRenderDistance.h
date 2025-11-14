#pragma once
#include <Gui/ViewProvider/ViewProviderDocumentObjectTopoShape.h>

namespace Dev
{

  class ViewProviderRenderDistance : public gui::ViewProviderDocumentObjectTopoShape
  {
    PFC_TYPESYSTEM_DECL_WITH_OVERRIDE()

  public:
    ViewProviderRenderDistance();
    ~ViewProviderRenderDistance() override;

    QWidget *GetTaskView() const override;
    void UpdateData(const app::Property *) override;
    virtual void FinishRestore() override;

    virtual void DeleteFromView() override;   

  private:
    std::optional<std::string> m_measure_id;
  };
} // namespace Dev