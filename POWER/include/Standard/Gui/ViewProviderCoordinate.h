#pragma once

#include <Gui/ViewProvider/ViewProviderDocumentObjectPlugin.h>

namespace standard {
class ViewProviderCoordinate : public gui::ViewProviderDocumentObjectPlugin
{
    PFC_TYPESYSTEM_DECL_WITH_OVERRIDE()

  public:
    ViewProviderCoordinate();
    ~ViewProviderCoordinate() override;

    void Update(const app::Property*) override;
    QWidget* GetTaskView() const override;
};
}  // namespace standard