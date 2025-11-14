#ifndef POWERFC_GUI_TITLEBAR_H
#define POWERFC_GUI_TITLEBAR_H
#pragma once
#include <PFCGlobal.h>
#include <QWidget>

class QAbstractButton;
class QPushButton;
class QMenu;

namespace gui {

class TitleBarPrivate;

class PFC_GUI_API TitleBar : public QWidget
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(TitleBar)

  public:
    enum ButtonRole
    {
        InvalidRole = 0,
        MinimizeRole = 1,
        MaximizeRole = 2,
        CloseRole = 3,
        HelpRole = 4,
        ResetRole = 5,
        CustomRole = 6
    };

    enum StandardButton
    {
        MinimizeButton = 1,
        MaximizeButton = 1 << 1,
        CloseButton = 1 << 2,
        ResetButton = 1 << 3,
        HelpButton = 1 << 4,
        NoButtons = 0
    };
    Q_ENUM(StandardButton)
    Q_DECLARE_FLAGS(StandardButtons, StandardButton)

  public:
    explicit TitleBar(QWidget* parent = nullptr);
    explicit TitleBar(QString const& title,
                      TitleBar::StandardButtons buttons,
                      QWidget* parent = nullptr);
    ~TitleBar();

  public:
    void AddButton(QAbstractButton* button, TitleBar::ButtonRole role = CustomRole);
    QPushButton* AddButton(QString const& text, TitleBar::ButtonRole role = CustomRole);
    QPushButton* AddButton(QIcon const& icon, QString const& text, TitleBar::ButtonRole role = CustomRole);
    void ClearButtons();

    QPushButton* GetStandardButton(TitleBar::StandardButton which) const;

    void SetStandardButtons(TitleBar::StandardButtons buttons);
    TitleBar::StandardButtons GetButtonsFormat() const;

    void SetTitle(QString const& title);
    QString GetTitle() const;

    QMenu* GetMenu() const;

    QAction* AddAction(QAction* action);

    void SetActions(QList<QAction*> const& actions);

    void SetIcon(QIcon const& icon);

    void SetSettingMenuVisibility(bool show);
    void EnableSettingMenu(bool enable);

    bool IsDragging() const;

  Q_SIGNALS:
    void SignalReset();
    void SignalMinimize();
    void SignalMaximize(bool);
    void SignalHelp();
    void SignalClose();
    void SignalDoubleClicked();       //鼠标双击发出信号
    void SignalMouseDragged(QPoint);  //鼠标拖动了一段位移发出信号

  protected:
    void mousePressEvent(QMouseEvent* event) override;

    void mouseMoveEvent(QMouseEvent* event) override;

    void mouseReleaseEvent(QMouseEvent* event) override;

  private:
    void ConnectMouseMoveEventToParent();
    bool IsOnEdge(QPoint const& pos) const;
    QScopedPointer<TitleBarPrivate> d_ptr;

    bool m_drag_needed = false;
};

Q_DECLARE_OPERATORS_FOR_FLAGS(TitleBar::StandardButtons)

}  // namespace gui

#endif
