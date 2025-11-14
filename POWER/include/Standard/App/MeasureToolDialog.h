#pragma once

#include "Widgets/Block/BlockEnumeration.h"
#include <AMCAXRender.h>
#include <Widgets/Block/BlockMoreDimension.h>
#include <Widgets/Block/BlockSelectObject.h>
#include <Widgets/ContainerBlock/BlockGeometryEditDialog.h>
#include <Widgets/ContainerBlock/BlockGroup.h>
#include <geometry/Geom3Curve.hpp>
#include <topology/TopoShape.hpp>

namespace standard {
#define TEMP_CENTER_POINT_IDPART "Centro"
class MeasureToolDialog : public BlockGeometryEditDialog
{
    Q_OBJECT
  public:
    enum MeasureType
    {
        Invalid,
        Distance,
        Length,
        Radius,
        BoundingBox,
        BoundingSphere,
        BoundingCylinder
    };

    explicit MeasureToolDialog(QWidget* parent = Q_NULLPTR);
    explicit MeasureToolDialog(MeasureType page, QWidget* parent = Q_NULLPTR);
    ~MeasureToolDialog() override = default;

    void SetMeasureType(MeasureType type);

    QSize sizeHint() const override;
    void Refresh() override;

public Q_SLOTS:
    bool OnConfirmed() override;
    void OnCanceled() override;
    void OnResetted() override;

private Q_SLOTS:
    void Recompute(bool);

protected:
    void ClearPreview() override;

private:
    void InitUI();
    void ShowPage();

    void ReComputeDistance();
    void ReComputeLength();
    void ReComputeRadius();
    void ReComputeBoundingBox();
    void ReComputeBoundingSphere();
    void ReComputeBoundingCylinder();

    static bool AlgorithmForRadius(const AMCAX::TopoShape& shape, AMCAX::Point3& center, AMCAX::Point3& edge, double& radius);
    static bool AlgorithmForBoundingBox(const std::vector<AMCAX::TopoShape>& shapes, AMCAXRender::Point3D& center, double& length, double& width, double& height);
    static bool AlgorithmForBoundingSphere(const std::vector<AMCAX::TopoShape>& shapes, AMCAXRender::Point3D& center, double& radius);
    static bool AlgorithmForBoundingCylinder(const std::vector<AMCAX::TopoShape>& shapes, const AMCAX::Direction3& direction, AMCAXRender::Point3D& center1, AMCAXRender::Point3D& center2, double& radius, double& height);
    static AMCAXRender::Line3D GetCurvePointsDividedBy64(const std::shared_ptr<AMCAX::Geom3Curve>& curve);
    static bool GetPointsFromCurveByParameter(const std::shared_ptr<AMCAX::Geom3Curve>& curve, int pointsNum, std::vector<AMCAX::Point3>& points);
    static bool IsPeriodicCurve(const std::shared_ptr<AMCAX::Geom3Curve>& curve);

    // static std::vector<AMCAX::Point3> GetCircularCenter(AMCAX::TopoShape& shape);

    void ClearMeasure();

    static QColor SettingRenderColor();

    void AddCircularPoint(const QString& parent, AMCAX::Point3 point, const QColor& color);
    void AddMeasureLine(std::vector<double> start, std::vector<double> end, const QString& text, QColor color, bool singleArrow);
    void AddTextRender(std::vector<double> pos, QString text, int fontSize, QColor color);
    void AddBoundingBox(const AMCAXRender::Point3D& center, const double length, const double width, const double height, const QColor& color);
    void AddBoundingSphere(const AMCAXRender::Point3D& center, const double radius, const QColor& color);
    void AddBoundingVolume(const AMCAXRender::Point3D& center1, const AMCAXRender::Point3D& center2, const double radius, const AMCAXRender::Point3D& normal, const QColor& color);

    void OnCenterPointClicked(const QString& parent, const double* point);

  private:
    MeasureType m_current_page { Invalid };

    BlockSelectObject* m_object_select_1 = nullptr;
    BlockSelectObject* m_object_select_2 = nullptr;
    BlockSelectObject* m_object_select_3 = nullptr;

    BlockGroup* m_pick_group = nullptr;
    BlockEnumeration* m_axis_block = nullptr;

    BlockGroup* m_data_group = nullptr;
    BlockMoreDimension* m_data_block_1 = nullptr;
    BlockMoreDimension* m_data_block_2 = nullptr;
    BlockMoreDimension* m_data_block_3 = nullptr;
    BlockMoreDimension* m_data_block_4 = nullptr;

    std::optional<std::string> m_measure_id;
};
}  // namespace standard