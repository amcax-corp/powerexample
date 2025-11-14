#ifndef POWERFC_STANDARD_GUI_REDOMENU_H
#define POWERFC_STANDARD_GUI_REDOMENU_H
#pragma once
#include <Gui/Command/Action.h>
#include <QMenu>

namespace standard {
class RedoMenu : public QMenu
{
    Q_OBJECT

  public:
    explicit RedoMenu(QWidget* parent = nullptr);
    ~RedoMenu() override = default;

  protected Q_SLOTS:
    void OnSelected();
    void OnFetchInfo();
};

class RedoAction : public gui::Action
{
    Q_OBJECT
  public:
    explicit RedoAction(gui::Command* cmd, QWidget* parent = nullptr);
    ~RedoAction() override;

    void AddTo(QWidget* widget) override;
    void SetEnabled(bool enabled) override;
    void SetVisible(bool visible) override;

  private:
    Q_DISABLE_COPY(RedoAction);
};
}  // namespace standard

#endif