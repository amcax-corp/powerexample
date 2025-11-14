#pragma once

#include "Gui/Selection/SelectionGateManager.h"

#include <App/Document.h>
#include <Gui/Selection/Selection.h>
#include <QVector3D>
#include <Widgets/Block/BlockAbstractGeometry.h>
#include <Widgets/PowerWidgetsConfig.h>
#include <Widgets/Block/BlockSelectObject.h>
using CustomSelectionGateFunc = std::function<bool(app::Document* doc, app::DocumentObject*, const std::string&)>;
class PowerShowDetailSettingButton;
class PowerButton;
class PowerEnumeration;
class BlockSpecifyPointGate;

class PW_API BlockSpecifyPoint : public BlockSelectObject
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

    explicit BlockSpecifyPoint(QWidget* parent = nullptr);
    ~BlockSpecifyPoint();
    
    // 过滤类型枚举
    enum FilterType
    {
        FilterTypeAll,    // 所有类型
        FilterTypeFaces,  // 仅面
        FilterTypeEdges   // 仅边
    };

    // 选择模式枚举
    enum SelectMode
    {
        Single,   // 单选模式
        Multiple  // 多选模式
    };
    Q_ENUM(SelectMode)
    
    explicit BlockSpecifyPoint(const QVector3D& original_point, QWidget* parent = nullptr);

    void SetPoint(const QVector3D& point);
    const QVector3D& GetPoint() const;
    void SetHasPreview(bool has_preview);
    bool HasPreview() const;
    void SetCaptureScreenPoinitAvailable(bool available);

Q_SIGNALS:
    void SignalGetPoint(const QVector3D& point);
    void SignalCaptureScreenPoint(const QVector3D& point);
public Q_SLOTS:
    void OnGetSettingDone(const QVector3D& point);
    void Clear() override;

  protected:
    void SetFocusedDirectly(bool focused) override;
    void OnSelectionChanged(const gui::SelectionChanges& msg) override;
    void SetStatusLabel(StepStatus status) override;
    void hideEvent(QHideEvent* event) override;
    void showEvent(QShowEvent* event) override;
    
private:
    void InitGate();
    void InitUi();
    void InitConnection();
    void UpdataSelectCount(); 
    void RegisterMouseClickedEvent();
    void UnRegisterMouseClickedEvent();
    void CreatePreviewDocument(const QVector3D& point);
    void UpdatePreviewDocument(const QVector3D& point);
    void RemovePreviewDocument();
    void RemoveRenderOriginalPoint();
    void UpdateCaptureScreenEventStatu(bool focused);

    PowerButton* m_title;
    PowerShowDetailSettingButton* m_dialog_button;
    PowerEnumeration* m_point_types;
    QVector3D m_point;
    bool m_has_preview = true;
    QList<gui::SelectionChanges> m_selection_changes;
    SelectMode m_select_mode = Single;
    QString m_selection_number = "";
    std::optional<int> m_pick_mouse_clicked_event_id;
    
    std::optional<std::string> m_point_entity_id;
    app::DocumentObject* m_preview_doc = nullptr;
    bool m_capture_screen_point_available = false;
};