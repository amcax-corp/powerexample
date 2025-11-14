#pragma once
#include <Gui/ViewProvider/ViewProviderDocumentObjectTopoShape.h>

namespace Dev
{

  class ViewProviderCurvesLoft : public gui::ViewProviderDocumentObjectTopoShape
  {
    PFC_TYPESYSTEM_DECL_WITH_OVERRIDE()

  public:
    ViewProviderCurvesLoft();
    ~ViewProviderCurvesLoft() override;

    QWidget *GetTaskView() const override;

  protected:
  };
} // namespace Dev