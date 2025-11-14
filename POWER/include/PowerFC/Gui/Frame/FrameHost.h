#pragma once

#include "PFCGlobal.h"
#include <QObject>
#include <QPoint>

#include <QPointer>

class QMouseEvent;
class QDialog;
namespace gui {
class MainWindow;
class PFC_GUI_API FrameHost : public QObject
{
    Q_OBJECT
  public:
    explicit FrameHost(QWidget* parent = nullptr);
    ~FrameHost() override = default;

    /// @brief 获取当前托管的，且在窗口信息表中的对话框数量
    /// @return 数量
    int GetDialogCount() const;

    /// @brief 判断是否包含指定窗口
    /// @param block_dialog 指定窗口指针
    bool ContainsDialog(QDialog* block_dialog) const;

    /// @brief 获取当前显示窗口
    QDialog* GetCurrentDialog() const;

    /// @brief 释放当前窗口栈
    /// @note 释放后会调用 RefreshWindowStatus()
    void ClearDialog();
    /// @brief 根据当前窗口栈刷新主窗口各个控件的使能状态
    void RefreshWindowStatus();

    /// @brief 更新已记录的窗口位置
    /// @note 当窗口全部关闭或强制清空窗口栈时该位置会被覆盖
    void SetDialogPos(QPoint pos);

Q_SIGNALS:
    void SignalBlockDialogChanged();

  private:
    /// @brief 托管事件过滤器，托管实现核心
    bool eventFilter(QObject* watched, QEvent* event) override;

    /// @brief 主窗口中添加子窗口后的处理函数
    /// @note 新窗体的 parent 设置为 gui::MainWindow() 则会进入该函数，根据当前标志位判断是否清空栈，以及入栈
    void OnMainWindowChildAdded(QDialog* child);
    /// @brief 收到 BlockDialog 关闭事件的处理函数
    void OnBlockDialogClosed(QDialog* block_dialog);
    /// @brief 收到 BlockDialog 显示事件的处理函数
    void OnBlockDialogShowed(QDialog* block_dialog);
    /// @brief 调整 BlockDialog 大小
    void OnBlockDialogResize(QDialog* block_dialog, QPoint mouse_pos);
    /// @brief 调整鼠标光标
    void OnBlockDialogCursorChanged(QDialog* block_dialog, QPoint mouse_pos);

    /// @brief 适配当前屏幕移动窗口
    static void AdaptiveMove(QDialog* dialog, QPoint pos);

    // /// @brief 设置预选高亮是否生效
    // static void ClearHoveredHighlight();
    //
    // static void RefreshHighlight();

    /// @brief 检查鼠标位置是否在窗口边缘
    static Qt::Edges CheckEdge(const QPoint& pos, QDialog* dialog) ;
    /// @brief 窗口边缘对应鼠标形状
    static Qt::CursorShape Edge2CursorShape(Qt::Edges edges);

private:
    void ClearStack();
    void ShrinkStack();

  private:
    MainWindow* m_parent;
    bool m_is_mouse_pressing = false;
    QPoint m_last_dialog_pos {};

    bool m_mainwindow_moving { false };

    bool m_flag_is_child { false };
    QList<QPointer<QDialog>> m_stack_dialogs;
};
}  // namespace gui