#pragma once
#include <Gui/ViewProvider/ViewProviderDocumentObjectTopoShape.h>

namespace Dev {

class ViewProviderBox : public gui::ViewProviderDocumentObjectTopoShape
{
    PFC_TYPESYSTEM_DECL_WITH_OVERRIDE()

  public:
    ViewProviderBox();
    ~ViewProviderBox() override;

    QWidget* GetTaskView() const override;

  protected:
};
}  // namespace Dev