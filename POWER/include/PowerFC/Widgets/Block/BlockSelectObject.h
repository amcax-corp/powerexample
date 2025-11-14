#pragma once

#include <Gui/Selection/Selection.h>
#include <Gui/Selection/SelectionChanges.h>
#include <Widgets/Block/BlockAbstractGeometry.h>
#include <Widgets/PowerWidgetsConfig.h>
#include "BlockEnums.h"

namespace gui {
class VirtualSelectionHelper;

class SelectionGateManager;
class EnhancedSelectionManager;
}

class PowerButton;
class PowerShowDetailSettingButton;
using CustomSelectionGateFunc = std::function<bool(app::Document*, app::DocumentObject*, const std::string&)>;

class PW_API BlockSelectObject : public BlockAbstractGeometry, public gui::SelectionObserver
{
    Q_OBJECT

    Q_PROPERTY(QString ButtonTip READ GetButtonTip WRITE SetButtonTip)
    Q_PROPERTY(QPixmap ButtonIcon READ GetButtonIcon WRITE SetButtonIcon)

    Q_PROPERTY(bool PointOverlay READ GetPointOverlay WRITE SetPointOverlay)

    Q_PROPERTY(BlockSelectObject::SelectMode SelectMode READ GetSelectMode WRITE SetSelectMode)
    Q_PROPERTY(int MultiSelectionCountLimit READ GetMultiSelectionCountLimit WRITE SetMultiSelectionCountLimit)
    Q_PROPERTY(PickTypes PickRange READ GetPickRange WRITE SetPickRange)
    Q_PROPERTY(PickTypes DefaultPickType READ GetDefaultPickType WRITE SetDefaultPickType)
public:
    explicit BlockSelectObject(QWidget* parent = nullptr);
    ~BlockSelectObject() override = default;

    /// @brief 设置按钮tip
    void SetButtonTip(const QString& tip);
    QString GetButtonTip() const;
    /// @brief 设置按钮图标
    void SetButtonIcon(const QPixmap &button_icon);
    QPixmap GetButtonIcon();

    /// @brief 设置右侧按钮是否可见
    void SetPointOverlay(bool overlay);
    bool GetPointOverlay() const { return m_point_overlay; }

    /// @brief 设置状态图标可见性
    void SetLabelStatusVisibility(bool is_visibility);
    bool IsLabelStatusVisibility() const { return m_label_status_visibility; }

    enum SelectMode
    {
        Single,
        Multiple
    };
    Q_ENUM(SelectMode)
    /// @brief 设置选择模式
    void SetSelectMode(SelectMode mode);
    SelectMode GetSelectMode() const { return m_select_mode; }

    enum { NO_LIMIT = -1 };
    /// @brief 设置多选模式时的数量限制
    /// @note 负数均视为无限制
    void SetMultiSelectionCountLimit(int limit);
    int GetMultiSelectionCountLimit() const { return m_multi_selection_count_limit;}

    enum Tribool
    {
        No_Value,
        True,
        False
    };
    Q_ENUM(Tribool);
    /// @brief 设置是否允许框选
    void SetEnableRubberBand(Tribool enable);
    void SetEnableRubberBand(bool enable);
    Tribool GetEnableRubberBand() const { return m_enable_rubber_band; }

    /// @brief 设置是否允许自动清空
    void SetEnableAutoClear(Tribool enable);
    void SetEnableAutoClear(bool enable);
    Tribool GetEnableAutoClear() const { return m_enable_auto_clear; }

    /// @brief 设置选取范围
    /// @note PickType::Unknown 表示无设置
    void SetPickRange(PickTypes pick);
    PickTypes GetPickRange() const { return m_pick_range; }

    /// @brief 设置默认选取类型
    /// /// @note PickType::Unknown 表示无设置
    void SetDefaultPickType(PickTypes pick);
    PickTypes GetDefaultPickType() const { return m_default_pick_filter; }

    /// @brief 设置门
    void SetSelectionGateManager(const std::shared_ptr<gui::SelectionGateManager>& gate_manager);
    auto GetSelectionGateManager() const { return m_gate_manager;}
    void SetCustomHandleForSelection(CustomSelectionGateFunc func);

    /// @brief 设置进阶选择
    void SetEnhancedSelectionManager(const std::shared_ptr<gui::EnhancedSelectionManager>& enhanced_selection_manager);
    auto GetEnhancedSelectionManager() const { return m_enhanced_selections; }

    /// @brief 是否已满足限制
    bool IsSatisfied() const override;

    /// @brief 获取当前选择的对象
    /// @return 当前选择的对象
    QT_DEPRECATED_X("Use GetSelections()") [[nodiscard]] QList<gui::SelectionChanges> GetSelection() const;
    [[nodiscard]] QList<gui::SelectionData> GetSelections() const override { return m_selections; }
    /// @brief 设置当前选择的对象，覆盖原先选择
    /// @param changes 当前选择的对象
    /// @note 该函数会根据当前选择模式以及选择数量进行判断，若不符合则忽略
    QT_DEPRECATED_X("Use GetSelections()") void SetSelection(const QList<gui::SelectionChanges>& changes);
    void SetSelections(const QList<gui::SelectionData>& changes) override;
    void SetSelections(const std::vector<gui::SelectionData>& changes);

    int GetSelectionCount() const;

    const auto& GetVirtualSelection() const { return m_virtual_selection_helper;}

    void Clear() override;

    void SetMandatoryFilled(bool) override {}
    bool IsMandatoryFilled() const override;

    bool IsValid() const override;
    void NotifyInitFinished() override;

Q_SIGNALS:
    /// @brief 只要选择的对象发生变化时就会发出此信号
    QT_DEPRECATED_X("Use SignalSelectionChanged()")
    void SignalSelectionInBlockChanged(const QList<gui::SelectionChanges>& changes);
    void SignalSelectionChanged(const QList<gui::SelectionData>& changes);

protected:
    void hideEvent(QHideEvent* event) override;;

    void InitWidgets();
    void InitStyle();
    void InitConnections();

    bool SelectionChangesPrefilter(const gui::SelectionChanges& msg) const override;
    void OnSelectionChanged(const gui::SelectionChanges& msg) override;

    bool CheckSelection(const QList<gui::SelectionData>& changes) const;

private Q_SLOTS:
    /// @brief 刷新文本、图标、样式
    void Refresh();

    void RefreshVirtualSelectionHelper();
    void RefreshSelf();

private:
    friend class BlockDialog;
    PowerButton* m_title;
    PowerButton* m_button;
    PowerShowDetailSettingButton* m_point_overlay_button;
    bool m_label_status_visibility = true;
    bool m_point_overlay = false;

    // 若父窗口包含QStackedWidget，记录当前控件所属的页
    QWidget* m_stacked_parent = nullptr;

    SelectMode m_select_mode { Single };
    int m_multi_selection_count_limit { 1 };
    Tribool m_enable_auto_clear { No_Value };
    Tribool m_enable_rubber_band { False };
    PickTypes m_pick_range{}, m_default_pick_filter{};
    std::shared_ptr<gui::SelectionGateManager> m_gate_manager;
    std::shared_ptr<gui::EnhancedSelectionManager> m_enhanced_selections;

    bool m_dirty_selections = false;
    QList<gui::SelectionData> m_selections{};

    std::shared_ptr<gui::VirtualSelectionHelper> m_virtual_selection_helper{};
    boost::signals2::connection m_virtual_selection_helper_connection;
};
