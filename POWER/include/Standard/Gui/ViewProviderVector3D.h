#pragma once

#include <Gui/ViewProvider/ViewProviderDocumentObjectPlugin.h>

namespace standard {
class ViewProviderVector3D : public gui::ViewProviderDocumentObjectPlugin
{
    PFC_TYPESYSTEM_DECL_WITH_OVERRIDE()

  public:
    ViewProviderVector3D();
    ~ViewProviderVector3D() override;

    void Update(const app::Property*) override;
    QWidget* GetTaskView() const override;
};
}  // namespace standard