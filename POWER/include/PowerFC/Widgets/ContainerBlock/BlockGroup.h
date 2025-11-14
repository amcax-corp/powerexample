#pragma once

#include <QPushButton>
#include <Widgets/Block/BlockBase.h>
#include <Widgets/PowerWidgetsConfig.h>

class PW_API BlockGroup : public BlockBase
{
    Q_OBJECT
    Q_PROPERTY(bool Folded READ IsFolded WRITE SetFolded NOTIFY SignalFoldStateChanged DESIGNABLE true USER true FINAL)
  public:
    BlockGroup(const QString& title, QWidget* parent = nullptr);
    BlockGroup(QWidget* parent = nullptr);

  public:  // Container
    void AddContent(QWidget* content);
    int ContentsCount() const;
    int CurrentContentIndex() const;
    QWidget* CurrentContent() const;

  public:  // Qt Designer
    bool IsFolded() const;
    void SetFolded(bool folded);

  public:  // Layout
    void AddStretch();

  Q_SIGNALS:
    void SignalFoldStateChanged(bool fold);

  public Q_SLOTS:
    void OnLabelVisibleChanged(bool visible);
    void OnLabelTextVisibleChanged(bool visible);

  private:
    void InitLayout();
    void InitStyle();
    QPushButton* CreateDropdownTitle(const QString& title);

  private:
    QWidget* m_contents;
    QWidget* m_inner_content;
    QPushButton* m_title;
    bool m_folded;
    QPushButton* m_dropdown;
};