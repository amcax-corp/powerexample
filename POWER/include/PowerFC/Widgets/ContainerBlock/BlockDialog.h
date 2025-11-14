#pragma once

#include "../Block/BlockEnums.h"
#include <QAbstractButton>
#include <QDialog>
#include <QFlags>
#include <Widgets/Block/BlockBase.h>
#include <Widgets/PowerWidgetsConfig.h>

class QStackedWidget;
class QTreeWidgetItem;
namespace gui {
class TitleBar;
}
//class PowerTitleBar;
class PowerDialogButtonBox;
class BlockSeparator;
class BlockAbstractGeometry;
class BlockGroup;
class PW_API BlockDialog : public QDialog
{
    Q_OBJECT
    // Q_PROPERTY(bool Initialize READ GetInitialize WRITE SetInitialize DESIGNABLE true USER true)
    Q_PROPERTY(DialogButton DialogButtons READ GetDialogButtons WRITE SetDialogButtons DESIGNABLE true USER true)
    Q_PROPERTY(QString DialogTitle READ GetDialogTitle WRITE SetDialogTitle DESIGNABLE true USER true)
    Q_PROPERTY(bool HasClose READ HasClose WRITE SetHasClose DESIGNABLE true USER true)
    Q_PROPERTY(bool HasMinimize READ HasMinimize WRITE SetHasMinimize DESIGNABLE true USER true)
    Q_PROPERTY(bool HasMaximize READ HasMaximize WRITE SetHasMaximize DESIGNABLE true USER true)
    Q_PROPERTY(bool HasReset READ HasReset WRITE SetHasReset DESIGNABLE true USER true)
    Q_PROPERTY(bool HasHelp READ HasHelp WRITE SetHasHelp DESIGNABLE true USER true)
  public:
    enum DialogButton
    {
        None = 0,
        Only_OK = 1,
        Only_Cancel = 1 << 1,
        OK_Cancel = 1 << 2,
        OK_Apply_Cancel = 1 << 3
    };
    Q_ENUM(DialogButton)
    enum DialogModalType
    {
        NoModal = 0,
        WindowModal = 1,
        ApplicationModal = 2,
        DocumentModal = 3
    };
    Q_ENUM(DialogModalType)

    /// @brief 构造函数，BlockDialog是一模板化的基本对话框，也是BlockWizard和BlockGeometryEditDialog的基类
    explicit BlockDialog(QWidget* parent = nullptr);
    ~BlockDialog() override = default;

    /*
     *  按钮组
     */

    /// @brief 获取对话框按钮盒子中的按钮，按钮布局为5种固定的选项
    /// @return 按钮，分为None无按钮、Only_OK仅确认、Only_Cancel仅取消、OK_Cancel确认和取消、OK_Apply_Cancel确认应用和取消
    DialogButton GetDialogButtons() const;
    /// @brief 设置对话框按钮盒子中的按钮，按钮布局为5种固定的选项
    /// @param buttons 按钮分布，分为None无按钮、Only_OK仅确认、Only_Cancel仅取消、OK_Cancel确认和取消、OK_Apply_Cancel确认应用和取消
    void SetDialogButtons(DialogButton buttons);
    /// @brief 设置按钮盒子的文本
    /// @param texts 文本按照 确定 > 应用 > 取消 的顺序排列，有则设置没有则不设置，传空意味着跳过设置
    void SetButtonBoxText(QStringList texts);
    /// @brief 设置按钮盒子的文本
    /// @param okText 确认按钮的文本，若参数为QVariant{}、非QString类型变量或DialogButton未设置确认按钮时忽略该参数
    /// @param applyText 应用按钮的文本，若参数为QVariant{}、非QString类型变量或DialogButton未设置确认按钮时忽略该参数
    /// @param cancelText 取消按钮的文本，若参数为QVariant{}、非QString类型变量或DialogButton未设置确认按钮时忽略该参数
    void SetButtonBoxTexts(const QVariant& okText = {}, const QVariant& applyText = {}, const QVariant& cancelText = {});

    /// @brief 获取对话框标题
    QString GetDialogTitle() const;
public Q_SLOTS:
    /// @brief 设置对话框标题
    void SetDialogTitle(const QString& title);

public:
    /*
     * 标题栏按钮
     */
    /// @brief 获取是否显示关闭按钮
    bool HasClose() const;
    /// @brief 设置是否显示关闭按钮
    void SetHasClose(bool has_close);
    /// @brief 获取是否显示最小化按钮
    bool HasMinimize() const;
    /// @brief 设置是否显示最小化按钮
    void SetHasMinimize(bool has_minimize);
    /// @brief 获取是否显示最大化按钮
    bool HasMaximize() const;
    /// @brief 设置是否显示最大化按钮
    void SetHasMaximize(bool has_maximize);
    /// @brief 获取是否显示重置按钮
    bool HasReset() const;
    /// @brief 设置是否显示重置按钮
    void SetHasReset(bool has_reset);
    /// @brief 获取是否显示帮助按钮
    bool HasHelp() const;
    /// @brief 设置是否显示帮助按钮
    void SetHasHelp(bool has_setting);

    /*
     *  模态
     */
    /// @brief 设置对话框模式
    void SetDialogModalType(DialogModalType modal_type);
    /// @brief 获取对话框模式
    DialogModalType GetDialogModalType() const;

    /*
     *  聚焦控件
     */
    /// @brief 获得焦点控件
    BlockAbstractGeometry* GetFocusWidget() const;
    /// @brief 焦点链是否可用
    bool IsFocusChainValid() const;

    /// @brief 判断所有必填项是否已填
    bool IsMandatoryAllFilled() const;

    /// @brief 判断焦点链控件是否全部满足
    bool IsAllSatisfied() const;

    /// @brief 设置窗口当前是否是顶层窗口
    void SetTopLevel(bool is_top);
    /// @brief 判断窗口当前是否是顶层窗口
    bool IsTopLevel() const;

    /*
     *  QtDesigner
     */
    /// @brief 添加一个widget到对话框中
    /// @param widget 要添加的widget
    /// @param isAdd 是否添加widget,默认为true
    void AddWidget(QWidget* widget, bool isAdd = true);
    /// @brief 初始化容器widget
    /// @param widget 要初始化的容器widget
    void InitContainerWidget(QWidget* widget);
    /// @brief 获取内容widget
    /// @return 返回内容widget指针
    QWidget* GetContentWidget();

  protected:
    // 将包含必填项的Block设置为友元类，以便调用注册函数
    friend class BlockAbstractGeometry;
    friend class BlockString;
    friend class BlockGroup;
    /// @brief 注册包含必填项的Block并加以管理
    /// @param widget 要注册的Block指针
    void RegisterMandatory(BlockBase* widget);
    /// @brief 注册入焦点循环链, 要求必须是BlockAbstractGeometry的子类
    /// @param widget 要注册的BlockAbstractGeometry指针
    virtual void RegisterFocusChain(BlockAbstractGeometry* widget);
    /// @brief 注册组控件
    void RegisterBlockGroup(BlockGroup* group);

  Q_SIGNALS:
    void SignalConfirmed();
    void SignalApplied();
    void SignalResetted();
    void SignalCanceled();
    void SignalClosed();

    void SignalFocusChanged();
    void SignalMandatoryAllFilled(bool all_filled);
    void SignalAllSatisfied(bool all_satisfied);

  public Q_SLOTS:
    /// @brief 确认按钮点击事件
    /// @return 返回处理结果
    virtual bool OnConfirmed();
    /// @brief 应用按钮点击事件
    /// @return 返回处理结果
    virtual bool OnApplied();
    /// @brief 重置按钮点击事件
    virtual void OnResetted();
    /// @brief 取消按钮点击事件
    virtual void OnCanceled();

  protected Q_SLOTS:
    /// @brief 对话框确认按钮点击流程
    void OnConfirmedClose();

    /// @brief 按钮盒子的点击后的流程控制, 发射不同信号
    void OnButtonBoxClicked(QAbstractButton* button);

protected Q_SLOTS:
    void RefreshSelectionStatus();
    void RestoreSelectionStatus();
    void RefreshDialogHeight();

protected:
    void RefreshFocusChain();
    void ReloadSelections();
    void ResetFocusChain();


    void RefreshByMandatoryFilled() {}
    // void resizeEvent(QResizeEvent* event) override;

    void moveEvent(QMoveEvent* event) override;
    void showEvent(QShowEvent* event) override;
    void hideEvent(QHideEvent* event) override;
    void closeEvent(QCloseEvent* event) override;

    bool eventFilter(QObject* watched, QEvent* event) override;

private:
    void InitWidgets();
    void InitConnect();
    void LoadStyleFile();
    void ClearFocusChain();

    void InitSelection();

protected:
    gui::TitleBar* m_title_bar = nullptr;
    PowerDialogButtonBox* m_buttonbox = nullptr;
    DialogButton m_dialog_buttons = OK_Apply_Cancel;

private:
    bool m_init_mode = true;

    // title bar相关
    QString m_dialog_title = "";
    bool m_has_help = false;
    bool m_has_close = true;
    bool m_has_minimize = false;
    bool m_has_maximize = false;
    bool m_has_reset = true;

    std::once_flag m_init_flag;     // 窗口第一次show时进行初始化
    QStackedWidget* m_stack_widget = nullptr;   // 模态窗中的窗口栈

    QList<BlockBase*> m_mandatory_widgets;        // 必填项管理列表
    QList<BlockAbstractGeometry*> m_focus_chain;  // 焦点循环链

    QWidget* m_container_widget = nullptr;  // 这个是真正装载内容的widget
    QWidget* m_center_widget;               // 这个是装载m_container_widget的widget，在Qt Designer中实现需要利用“多页面”，因此需要这个widget承载分页
    bool m_has_container_widget = false;

    DialogModalType m_dialog_modal_type = DocumentModal;  // 对话框模态类型

    BlockSeparator* m_separator_line = nullptr;  //用于选择按钮分割线

    PickTypes m_pick_range{}, m_default_pick_types{};
    bool m_block_reload { false };
};
