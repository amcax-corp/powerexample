#pragma once

#include <Widgets/Block/BlockBase.h>
#include <Widgets/PowerWidgetsConfig.h>
#include "Gui/Selection/SelectionChanges.h"

class PW_API BlockAbstractGeometry : public BlockBase
{
    Q_OBJECT
    Q_PROPERTY(BlockAbstractGeometry::StepStatus StepStatus READ GetStepStatus WRITE SetStepStatus)
public:
    enum StepStatus
    {
        Required,
        Optional,
        Satisfied
    };
    Q_ENUM(StepStatus)

    explicit BlockAbstractGeometry(QWidget* parent = nullptr);
    ~BlockAbstractGeometry() override = default;
    
    /// @brief 设置是否聚焦
    /// @note 当父窗口为 BlockDialog 时，触发父窗口的焦点链更新事件，否则直接设置
    void SetFocused(bool focused);
    bool IsFocused() const { return m_focused;}

    /// @brief 获取当前必填状态
    /// @return Required = 必填未填, Optional = 非必填, Satisfied = 必填已填
    StepStatus GetStepStatus() const { return m_step_status; }
    /// @brief 设置当前必填状态
    /// @param status Required = 必填未填, Optional = 非必填, Satisfied = 必填已填
    virtual void SetStepStatus(StepStatus status);
    virtual void SetStatusLael(StepStatus) {}

    /// @brief 设置必填项
    void SetMandatory(bool mandatory) override;
    /// @brief 获取是否为必填项
    bool IsMandatory() const override { return m_is_mandatory; }

    /// @brief 设置已填状态
    void SetMandatoryFilled(bool) override;
    /// @brief 获取是否已填
    bool IsMandatoryFilled() const override;

    virtual void SetStatusLabel(StepStatus status) {}

    /// @brief 获取当前是否满足条件
    /// @note 需要重写为更复杂的条件已实现具体的满足状态
    virtual bool IsSatisfied() const { return m_mandatory_filled; }

    virtual void Clear() {}

    virtual void SetSelections(const QList<gui::SelectionData>& selections) {}
    [[nodiscard]] virtual QList<gui::SelectionData> GetSelections() const { return {}; }

    bool IsInitialMode() const { return m_initial_mode; }
    virtual void NotifyInitFinished();

Q_SIGNALS:
    /// @brief 聚焦状态改变信号, 改为true时, 表示执行聚焦, 改为false时, 表示执行失焦
    void SignalFocusChanged(bool in);
    /// @brief 聚焦时发射的信号，表示执行聚焦操作
    void SignalFocusIn();
    void SignalFocusOut();


    void SignalSatisfied(bool);

protected:
    friend class BlockDialog;
    void NotifyUpdatingFocusChain();
    void NotifyReloadSelections();

    virtual void SetFocusedDirectly(bool focused);

private:
    bool m_initial_mode = true;
    bool m_is_mandatory = false;
    bool m_mandatory_filled = false;
    StepStatus m_step_status = Optional;

    std::optional<bool> m_forced_focus {};

    bool m_focused = false;
};