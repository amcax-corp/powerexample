#ifndef POWERRGBCOLORPICKER_H
#define POWERRGBCOLORPICKER_H

#include <QWidget>
#include <QPushButton>
#include <QColor>
#include <QColorDialog>

class PowerRGBColorPicker : public QPushButton
{
    Q_OBJECT
public:

    explicit PowerRGBColorPicker(QWidget *parent = nullptr);

    ~PowerRGBColorPicker();

    QColor GetColor();

    void SetColor(QColor color);

signals:
    void SignalColorChanged(QColor color); 

private slots:
    void OnOpenColorDialog(); 

private:
    QColor m_color;
};

#endif // POWERRGBCOLORPICKER_H