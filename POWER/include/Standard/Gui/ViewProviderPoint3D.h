#pragma once

#include <Gui/ViewProvider/ViewProviderDocumentObjectPlugin.h>

namespace standard {
class ViewProviderPoint3D : public gui::ViewProviderDocumentObjectPlugin
{
    PFC_TYPESYSTEM_DECL_WITH_OVERRIDE()

  public:
    ViewProviderPoint3D();
    ~ViewProviderPoint3D() override;

    void Update(const app::Property*) override;
    QWidget* GetTaskView() const override;

  private:
    bool m_is_init = false;
};
}  // namespace standard