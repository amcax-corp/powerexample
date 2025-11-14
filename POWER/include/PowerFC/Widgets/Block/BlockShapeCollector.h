#pragma once

#include <Widgets/Block/BlockBase.h>
#include <QWidget>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>

class PW_API BlockShapeCollector : public BlockBase
{
    Q_OBJECT
    Q_PROPERTY(BlockShapeCollector::StepStatus StepStatus READ GetStatus WRITE SetStatus)
    Q_PROPERTY(BlockShapeCollector::InterpartSelection InterpartSelection READ GetInterpartSelection WRITE SetInterpartSelection)
    Q_PROPERTY(BlockShapeCollector::MaximumScope MaximumScope READ GetMaximumScope WRITE SetMaximumScope)
    Q_PROPERTY(BlockShapeCollector::SelectMode SelectMode READ GetSelectMode WRITE SetSelectMode)
    Q_PROPERTY(BlockShapeCollector::DefaultCurveRules DefaultCurveRules READ GetDefaultCurveRules WRITE SetDefaultCurveRules)
    Q_PROPERTY(bool AllowConvergentObject READ GetAllowConvergentObject WRITE SetAllowConvergentObject)
    Q_PROPERTY(bool AutomaticProgression READ GetAutomaticProgression WRITE SetAutomaticProgression)
    Q_PROPERTY(bool BlendVirtualCurveOverlay READ GetBlendVirtualCurveOverlay WRITE SetBlendVirtualCurveOverlay)
    Q_PROPERTY(bool CreateInterpartLink READ GetCreateInterpartLink WRITE SetCreateInterpartLink)
    Q_PROPERTY(bool PopupMenuEnabled READ GetPopupMenuEnabled WRITE SetPopupMenuEnabled)

public:
    //部件间选择设置
    enum InterpartSelection{
        Simple,
        Non_Associative_Interpart_Copy_Only,
        Associative_And_Non_Associative_Interpart_Copy,
        Associative_Interpart_Copy
    };  
    Q_ENUM(InterpartSelection);
    //
    enum MaximumScope{
        Entire_Assembly,
        Within_Work_Part_Only,
        Within_Work_Part_And_Components
    };
    Q_ENUM(MaximumScope);
    //设置单选或多选
    enum SelectMode{
        Single,
        Multiple
    };  
    Q_ENUM(SelectMode);
    //设置确定和应用按钮的状态
    enum StepStatus{
        Required,
        Optional,
        Satisfied
    };  
    Q_ENUM(StepStatus);
    //默认曲线规则
    enum DefaultCurveRules{
        Single_Curve,
        Connected_Curves,
        Tangent_Curves,
        Face_Edges,
        Body_Edges,
        Vertex_Edges,
        Vertex_Tangent_Curves
    };  
    Q_ENUM(DefaultCurveRules);

    BlockShapeCollector(QWidget *parent = nullptr);
    ~BlockShapeCollector();

    /// @brief 获取部件间选择设置选项
    /// @return InterpartSelection类型
    InterpartSelection GetInterpartSelection() const;
    /// @brief 设置部件间选择设置选项
    /// @param interpart_selection 
    void SetInterpartSelection(InterpartSelection interpart_selection);
    /// @brief 获取最大范围选项
    /// @return MaximumScope类型
    MaximumScope GetMaximumScope() const;
    /// @brief 设置最大范围选项
    /// @param maximum_scope
    void SetMaximumScope(MaximumScope maximum_scope);
    /// @brief 获取选择模式选项
    /// @return SelectMode类型
    SelectMode GetSelectMode() const;
    /// @brief 设置选择模式选项
    /// @param select_mode 
    void SetSelectMode(SelectMode select_mode);
    /// @brief 获取默认曲线规则选项
    /// @return DefaultCurveRules类型
    DefaultCurveRules GetDefaultCurveRules() const;
    /// @brief 设置默认曲线规则选项
    /// @param default_curve_rules 
    void SetDefaultCurveRules(DefaultCurveRules default_curve_rules);
    /// @brief 获取确定和应用按钮的状态
    /// @return StepStatus类型
    StepStatus GetStatus();
    /// @brief 设置确定和应用按钮的状态
    /// @param status 
    void SetStatus(StepStatus status);
    /// @brief 获取是否允许选择收敛体
    /// @return bool类型
    bool GetAllowConvergentObject() const;
    /// @brief 设置是否允许选择收敛体
    /// @param allow_convergent_object
    void SetAllowConvergentObject(bool allow_convergent_object);
    /// @brief 获取是否自动跳到下一个控件
    /// @return bool类型
    bool GetAutomaticProgression() const;
    /// @brief 设置是否自动跳到下一个控件
    /// @param automatic_progression 
    void SetAutomaticProgression(bool automatic_progression);
    /// @brief 获取是否选择虚拟交线
    /// @return bool类型
    bool GetBlendVirtualCurveOverlay() const;
    /// @brief 设置是否选择虚拟交线
    /// @param blend_virtual_curve_overlay 
    void SetBlendVirtualCurveOverlay(bool blend_virtual_curve_overlay);
    /// @brief 获取是否显示部件间连接
    /// @return bool类型
    bool GetCreateInterpartLink() const;
    /// @brief 设置是否显示部件间连接
    /// @param create_interpart_link 
    void SetCreateInterpartLink(bool create_interpart_link);
    /// @brief 获取是否显示右键菜单
    /// @return bool类型
    bool GetPopupMenuEnabled() const;
    /// @brief 设置是否显示右键菜单
    /// @param popup_menu_enabled 
    void SetPopupMenuEnabled(bool popup_menu_enabled);

public:
    void SetMandatory(bool is_mandatory) override;
    bool IsMandatory() const override;
    void SetMandatoryFilled(bool filled) override;
    bool IsMandatoryFilled() const override;

signals:
    /// @brief 点击确定按钮
    void SignalClickedButton();

protected:
    /// @brief 绘制事件
    /// @param event 
    void paintEvent(QPaintEvent *event) override;

private slots:
    /// @brief 按钮点击事件
    void OnButtonClicked();

private:
    QHBoxLayout *m_layout;
    QPushButton *m_button;
    QLabel *m_stautus_label;

    bool m_allow_convergent_object;  //允许选择收敛体
    bool m_automatic_progression;  //自动跳到下一个控件
    bool m_blend_virtual_curve_overlay;  //是否选择虚拟交线
    bool m_create_interpart_link;  //是否显示部件间连接
    bool m_popup_menu_enabled;  //是否显示右键菜单
    QString m_cue;  //提示

    bool m_is_mandatory = false;
    bool m_mandatory_filled = true;

    StepStatus m_step_status = Optional;
    InterpartSelection m_interpart_selection = Simple;
    MaximumScope m_maximum_scope = Entire_Assembly;
    SelectMode m_select_mode = Single;
    DefaultCurveRules m_default_curve_rules = Single_Curve;


};