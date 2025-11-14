#ifndef POWERFC_STANDARD_GUI_UNDOMENU_H
#define POWERFC_STANDARD_GUI_UNDOMENU_H
#pragma once
#include <Gui/Command/Action.h>
#include <QMenu>


namespace standard {
class UndoMenu : public QMenu
{
    Q_OBJECT

  public:
    explicit UndoMenu(QWidget* parent = nullptr);
    ~UndoMenu() override = default;

  protected Q_SLOTS:
    void OnSelected();
    void OnFetchInfo();
};

class UndoAction : public gui::Action
{
    Q_OBJECT
  public:
    explicit UndoAction(gui::Command* cmd, QWidget* parent = nullptr);
    ~UndoAction() override;

    void AddTo(QWidget* widget) override;
    void SetEnabled(bool enabled) override;
    void SetVisible(bool visible) override;

  private:
    Q_DISABLE_COPY(UndoAction);
};
}  // namespace standard

#endif