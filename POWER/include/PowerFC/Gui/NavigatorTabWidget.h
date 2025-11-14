
#pragma once
#include <QTabBar>
#include <QTabWidget>
#include <QToolButton>

namespace gui {

class CustomTabBar : public QTabBar
{
    Q_OBJECT
  public:
    explicit CustomTabBar(QWidget* parent = nullptr);

  protected:
    void resizeEvent(QResizeEvent* event) override;

    void tabLayoutChange() override;

    void paintEvent(QPaintEvent* event) override;

    QSize tabSizeHint(int index) const override;

  private:
    void updateButtonPosition();
    QAction* GetAction(const std::string& commandName);

    QToolButton* m_button;
};

class NavigatorTabWidget : public QTabWidget
{
    Q_OBJECT
  public:
    explicit NavigatorTabWidget(QWidget* parent = nullptr);
    void setTabPosition(QTabWidget::TabPosition position);

  signals:
    void tabPositionChanged(QTabWidget::TabPosition);
};


}  // namespace gui