#pragma once

#include <App/DocumentObject.h>
#include <Widgets/ContainerBlock/BlockGeometryEditDialog.h>
#include <Widgets/ContainerBlock/BlockDialog.h>
#include <Widgets/PowerWidgetsConfig.h>
#include <topology/TopoEdge.hpp>
#include <topology/TopoFace.hpp>
#include <common/PointT.hpp>
#include <QVector3D>

class ViewProviderPoint3D;
class BlockSelectObject;
class BlockMoreDimension;
class BlockGroup;
class PowerEnumeration;
class BlockEnumeration;

namespace standard {
    class ViewProviderPoint3D;
}
class PW_API PowerPointSettingDialog : public BlockDialog
{
    Q_OBJECT

    friend class standard::ViewProviderPoint3D;

  public:
    // 拾取类型
    enum PickPointType
    {
        Parameter,                // 参数
        Cursor,                   // 光标
        Vertex,                   // 顶点
        Edge,                     // 边上的点
        FaceEdgeIntersection,     // 面线、线线交点
        CircleCenter,             // 圆心
        Face                      // 面上的点
    };

    // 判断线面相交点
    struct IntersectionInfo
    {
        AMCAX::TopoEdge edge_first;
        AMCAX::TopoEdge edge_second;
        AMCAX::TopoFace face;
    };
    explicit PowerPointSettingDialog(QVector3D point, bool has_preview, QWidget* parent = nullptr);
    ~PowerPointSettingDialog();
  public:
    QSize sizeHint() const override;

    const QVector3D GetCurrentPoint() const;
    std::string_view GetDocumentObjectName() const;
    void SetEnumIndex(int index);
  protected:
    explicit PowerPointSettingDialog(app::DocumentObject* origin_doc, QWidget* parent = nullptr);

  signals:
    void SignalConfirmed(const QVector3D& point);

  public Q_SLOTS:
    // group中的多个specify box由block_id区分
    void OnSelectionChanged(const QList<gui::SelectionData>& datas, int select_block_id = 0);
  protected Q_SLOTS:
    bool OnConfirmed() override;
    void OnResetted() override;
    void OnCanceled() override;
    void showEvent(QShowEvent *event) override;
    void hideEvent(QHideEvent *event) override;
  private Q_SLOTS:
    void OnXValueChanged(double value);
    void OnYValueChanged(double value);
    void OnZValueChanged(double value);

  private:
    void InitUI();
    void InitGate();
    void InitConnection();
    void ClearOutsideSelection();
    void SetDeimensionReadOnly(bool read_only);
    std::vector<AMCAX::Point3> GetCurveCenter(AMCAX::TopoEdge& edge);
    std::vector<AMCAX::Point3> GetClosedCurveVertex(AMCAX::TopoEdge& edge);
    std::vector<AMCAX::Point3> GetSphereCenter(const AMCAX::TopoShape& shape);

  private:
    BlockMoreDimension* m_specify_x;
    BlockMoreDimension* m_specify_y;
    BlockMoreDimension* m_specify_z;
    BlockMoreDimension* m_cam_u_para;
    BlockMoreDimension* m_cam_v_para;
    PowerEnumeration* m_enum_select_types;

    app::DocumentObject* m_specify_doc = nullptr;
    app::DocumentObject* m_tmp_doc = nullptr;
    
    PickPointType m_pick_type = PickPointType::Parameter;
    IntersectionInfo m_intersection_info;
    
    BlockSelectObject *select_surface;
    BlockSelectObject *select_curve_surface_plane;
    BlockSelectObject *select_curve_intersected;
    BlockSelectObject *select_cursor_vertex_curve;

    BlockGroup *group_select_surface;
    BlockGroup *group_surface_position;
    BlockGroup *group_select_curve_surface;
    BlockGroup *group_curve_intersected;
    BlockGroup *group_select_point;
    BlockGroup *group_output_coordinates;
    BlockGroup *group_offset;

    BlockEnumeration* enum_offset;

    BlockMoreDimension *cam_x_increment;
    BlockMoreDimension *cam_y_increment;
    BlockMoreDimension *cam_z_increment;
    double m_original_x = 0.0;
    double m_original_y = 0.0;
    double m_original_z = 0.0;
};