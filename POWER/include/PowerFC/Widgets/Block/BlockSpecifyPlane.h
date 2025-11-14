#pragma once

#include <QVector3D>
#include <Widgets/Block/BlockSelectObject.h>
#include <Widgets/Block/BlockSelectionEnum.h>
#include <Widgets/PowerWidgetsConfig.h>
#include <Gui/Selection/Selection.h>
#include <App/Document.h>
#include <AMCAXRender.h>
#include <topology/TopoFace.hpp>
#include <math/GeometryMacros.hpp>
#include <common/PointT.hpp>
#include <common/DirectionT.hpp>
class PowerShowDetailSettingButton;
class PowerButton;
class PowerEnumeration;
class BlockSpecifyPlaneGate;

class PW_API BlockSpecifyPlane : public BlockSelectObject
{
    Q_OBJECT


    Q_PROPERTY(QString LabelText READ GetLabelText WRITE SetLabelText DESIGNABLE false)
    Q_PROPERTY(bool LabelTextVisibility READ IsLabelTextVisibility WRITE SetLabelTextVisibility DESIGNABLE false)
    Q_PROPERTY(QPixmap LabelBitmap READ GetLabelBitmap WRITE SetLabelBitmap DESIGNABLE false)
    Q_PROPERTY(bool LabelBitmapVisibility READ IsLabelBitmapVisibility WRITE SetLabelBitmapVisibility DESIGNABLE false)
    Q_PROPERTY(bool LabelVisibility READ IsLabelVisibility WRITE SetLabelVisibility FINAL DESIGNABLE false)
    Q_PROPERTY(QString TooltipTitle READ GetTooltipTitle WRITE SetTooltipTitle DESIGNABLE false)
    Q_PROPERTY(QString TooltipText READ GetTooltipText WRITE SetTooltipText DESIGNABLE false)
    Q_PROPERTY(QPixmap TooltipImage READ GetTooltipImage WRITE SetTooltipImage DESIGNABLE false)
    Q_PROPERTY(TooltipLayout TooltipLayout READ GetTooltipLayout WRITE SetTooltipLayout DESIGNABLE false)

    Q_PROPERTY(BlockAbstractGeometry::StepStatus StepStatus READ GetStepStatus WRITE SetStepStatus)

  public:
    explicit BlockSpecifyPlane(QWidget* parent = nullptr);
    ~BlockSpecifyPlane();
  
    // 选择模式枚举
    enum SelectMode
    {
        Single,   // 单选模式
        Multiple  // 多选模式
    };
    Q_ENUM(SelectMode)

    const std::pair<AMCAX::Point3, AMCAX::Direction3>& GetPlane() const;
    void SetHasPreview(bool has_preview);
    bool HasPreview() const;
    void SetPlane(std::pair<AMCAX::Point3, AMCAX::Direction3> plane);

  Q_SIGNALS:
    void SignalGetPlane(const std::pair<AMCAX::Point3, AMCAX::Direction3>&);

    void SignalSelectionInBlockChanged(const QList<gui::SelectionChanges>& changes);
    void SignalSatisfied(bool satisfied);
  public Q_SLOTS:
    void OnGetSettingDone(const std::pair<AMCAX::Point3, AMCAX::Direction3>&);

    void Clear() override;

  protected:
    void SetStatusLabel(StepStatus status) override;
  private:
    void InitGate();
    void InitUi();
    void InitConnection();
    
    void RenderPlane(AMCAX::TopoFace face, AMCAX::Direction3 direct, double dis_ratio);
    void RenderPlane(const QVector3D& point, const QVector3D& normal);
    void RemoveRenderPlane();
    AMCAX::TopoShape ExtendFaceBoundary(const AMCAX::TopoFace& face, 
                                      double extendDistance,
                                      AMCAX::JoinType joinType = AMCAX::JoinType::Arc);

    bool CalculateBoundingBoxVertices(const QList<AMCAX::TopoShape>& shapes, std::vector<AMCAX::Point3>& vertices);
    PowerButton* m_title;
    PowerShowDetailSettingButton* m_dialog_button;
    PowerEnumeration* m_plane_types;
    BlockSpecifyPlaneGate* m_selection_gate = nullptr;

    std::pair<AMCAX::Point3, AMCAX::Direction3> m_plane;
    bool m_has_preview = true;
    QString m_selection_number = "";
    std::optional<AMCAXRender::EntityId> m_render_id;
};