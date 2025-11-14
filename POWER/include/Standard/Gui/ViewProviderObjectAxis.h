#pragma once

#include <Gui/ViewProvider/ViewProviderDocumentObjectPlugin.h>

namespace standard {
class ViewProviderObjectAxis : public gui::ViewProviderDocumentObjectPlugin
{
    PFC_TYPESYSTEM_DECL_WITH_OVERRIDE()

  public:
    ViewProviderObjectAxis();
    ~ViewProviderObjectAxis() override;

    void Update(const app::Property*) override;
    QWidget* GetTaskView() const override;
};
} // namespace standard