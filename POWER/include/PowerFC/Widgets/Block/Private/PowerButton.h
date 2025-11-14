#pragma once
#include <QPushButton>
#include <QStyleOptionButton>
#include <QStylePainter>
class PowerButton : public QPushButton
{
    Q_OBJECT
  private:
  public:
    PowerButton(QWidget* parent = nullptr);
    ~PowerButton();

};