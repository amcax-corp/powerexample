
#ifndef GUI_ACTION_H
#define GUI_ACTION_H

#pragma once
#include <PFCGlobal.h>
#include <QAction>
#include <QComboBox>
#include <QKeySequence>
#include <memory>

namespace gui {
class Command;

class PFC_GUI_API Action : public QObject
{
    Q_OBJECT

  public:
    Action(Command* cmd, QObject* parent = nullptr);
    Action(Command* cmd, QAction* action, QObject* parent);
    virtual ~Action();

    virtual void AddTo(QWidget* w);
    virtual void SetEnabled(bool);
    virtual void SetVisible(bool);

    void SetCheckable(bool);
    void SetChecked(bool, bool no_signal = false);
    bool IsChecked() const;

    void SetShortcut(const QString&);
    QKeySequence Shortcut() const;
    void SetIcon(const QIcon&);
    QIcon Icon() const;
    void SetStatusTip(const QString&);
    QString StatusTip() const;
    void SetText(const QString&);
    QString Text() const;
    void SetToolTip(const QString&);
    QString ToolTip() const;
    void SetWhatsThis(const QString&);
    QString WhatsThis() const;
    void SetMenuRole(QAction::MenuRole menuRole);
    QAction* GetAction() const
    {
        return m_action;
    }

  public Q_SLOTS:
    virtual void OnActivated();
    virtual void OnToggled(bool);

  protected:
    QAction* m_action;
    Command* m_cmd;
};

class PFC_GUI_API ActionGroup : public Action
{
    Q_OBJECT

  public:
    ActionGroup(Command* cmd, QObject* parent = 0);
    virtual ~ActionGroup();

    void AddTo(QWidget* widget);
    void SetEnabled(bool);
    void SetDisabled(bool);
    void SetExclusive(bool);
    bool IsExclusive() const;
    void SetVisible(bool);

    void SetDropDownMenu(bool b)
    {
        m_drop_down = b;
    }
    QAction* AddAction(QAction*);
    QAction* AddAction(const QString&);
    QList<QAction*> Actions() const;
    int CheckedAction() const;
    void SetCheckedAction(int);

  public Q_SLOTS:
    void OnActivated();
    void OnToggled(bool);
    void OnActivated(QAction*);
    void OnHovered(QAction*);

  protected:
    QActionGroup* m_group;
    bool m_drop_down;
    bool m_external;
    bool m_toggle;
};

}  // namespace gui

#endif  // GUI_ACTION_H
