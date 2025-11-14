#pragma once

#include <Widgets/Block/BlockEnumeration.h>
#include <AMCAXRender.h>
#include <Widgets/Block/BlockCAMDimension.h>
#include <Widgets/Block/BlockSelectObject.h>
#include <Widgets/ContainerBlock/BlockGeometryEditDialog.h>
#include <Widgets/ContainerBlock/BlockGroup.h>
#include <Widgets/Block/BlockLabel.h>
#include <geometry/Geom3Curve.hpp>
#include <topology/TopoShape.hpp>

namespace standard {
class CurveContinuityDetectionDialog : public BlockGeometryEditDialog
{
    Q_OBJECT
  public:
    CurveContinuityDetectionDialog(QWidget* parent = nullptr);
    ~CurveContinuityDetectionDialog() = default;

    QSize sizeHint() const override;

  public Q_SLOTS:
    bool OnConfirmed() override;
    void OnCanceled() override;
    void OnResetted() override;

  public:
    void Refresh() override;

    QStringList GenerateModelImplement(const QList<AMCAX::TopoShape>& inputs) override;

    auto ReCompute() -> QList<AMCAX::TopoShape> override;
    void ResumeRender() override;

  protected:
    void showEvent(QShowEvent* event) override;

  private:
    void InitUI();
    void ClearLabels();

    QColor LabelColor();

    std::string AddPluginLabel(const QString& text, const AMCAXRender::Point3D& pos, const QColor& color);

  private:
    BlockGroup* m_pick_group;
    BlockGroup* m_result_group;
    BlockSelectObject* m_curve_select_1 = nullptr;
    BlockSelectObject* m_curve_select_2 = nullptr;
    BlockLabel* m_result_label;

    QList<std::string> m_labels;

    CustomSelectionGateFunc m_gate_curve;
};
}  // namespace standard