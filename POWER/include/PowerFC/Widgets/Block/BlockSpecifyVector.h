#pragma once

#include "Gui/Selection/SelectionGateManager.h"

#include <App/DocumentObject.h>
#include <App/DocumentObjectTopoShape.h>
#include <Gui/Selection/Selection.h>
#include <QVector3D>
#include <Widgets/Block/BlockAbstractGeometry.h>
#include <Widgets/Block/BlockReverseDirection.h>
#include <Widgets/PowerWidgetsConfig.h>
#include <common/PointT.hpp>
#include <Widgets/Block/BlockSelectObject.h>
using CustomSelectionGateFunc = std::function<bool(app::Document* doc, app::DocumentObject*, const std::string&)>;

class PowerShowDetailSettingButton;
class PowerButton;
class PowerEnumeration;
class BlockSpecifyVectorGate;

class PW_API BlockSpecifyVector : public BlockSelectObject
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

    Q_PROPERTY(bool ReverseDirectionEnabled READ GetIsReverseDirectionEnabled WRITE SetReverseDirectionEnabled)
    Q_PROPERTY(bool Is2DMode READ GetIs2DMode WRITE Set2DMode)
    Q_PROPERTY(bool DoubleSide READ GetIsDoubleSide WRITE SetDoubleSide)
    Q_PROPERTY(BlockAbstractGeometry::StepStatus StepStatus READ GetStepStatus WRITE SetStepStatus)

  public:
    // 选择模式枚举
    enum SelectMode
    {
        Single,   // 单选模式
        Multiple  // 多选模式
    };
    Q_ENUM(SelectMode)

    explicit BlockSpecifyVector(QWidget* parent = nullptr);
    ~BlockSpecifyVector();
  
    bool GetIsReverseDirectionEnabled() const;
    void SetReverseDirectionEnabled(bool enabled);
    bool GetIs2DMode() const;
    void Set2DMode(bool enabled);
    bool GetIsDoubleSide() const;
    void SetDoubleSide(bool enabled);
    void SetStatusLabel(StepStatus status);

    void SetVector(const QVector3D& vector);
    const QVector3D& GetVector() const;

    void SetHasPreview(bool has_preview);
    bool HasPreview() const;
    AMCAX::Point3 GetEndPoint();
    
  Q_SIGNALS:
    void SignalGetVector(const QVector3D& vector);
    void SignalReverseVector();
  public Q_SLOTS:
    void OnGetSettingDone(const QVector3D& vector, const QVector3D& end_point);
    void Clear() override;

  protected:
    void showEvent(QShowEvent* event) override;
    void hideEvent(QHideEvent* event) override;
  
  private:
    void InitGate();
    void InitUi();
    void InitConnection();

    AMCAX::Point3 CalculationEndpoint(AMCAX::TopoEdge& edge, const AMCAX::Point3& cursorPoint);
    std::vector<AMCAX::Point3> GetClosedCurveVertex(AMCAX::TopoEdge& edge);

    PowerButton* m_title;
    PowerButton* m_reverse_button;
    PowerShowDetailSettingButton* m_dialog_button;
    PowerEnumeration* m_vector_types;

    QVector3D m_vector = QVector3D(0, 0, 0);

    bool m_reverse_enabled = true;
    bool m_is_2d_mode = false;
    bool m_double_side = false;

    bool m_has_preview = true;

    QList<gui::SelectionChanges> m_selection_changes;
    SelectMode m_select_mode = Single;
    QString m_selection_number = "";
    AMCAX::Point3 m_end_point;
};