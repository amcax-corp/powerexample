#pragma once

#include <Gui/ViewProvider/ViewProviderDocumentObjectPlugin.h>
#include <QVector3D>

namespace standard {
class ViewProviderPlane : public gui::ViewProviderDocumentObjectPlugin
{
    PFC_TYPESYSTEM_DECL_WITH_OVERRIDE()

  public:
    ViewProviderPlane();
    ~ViewProviderPlane() override;

    void Update(const app::Property*) override;
    QWidget* GetTaskView() const override;

  private:
    std::vector<QVector3D> GenerateRectanglePoints(const QVector3D& center, const QVector3D& normal, double length);
};
}  // namespace standard