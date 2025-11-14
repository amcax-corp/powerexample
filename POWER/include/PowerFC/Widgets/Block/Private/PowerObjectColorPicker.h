#pragma once
#include <QWidget>
#include <QPushButton>
#include <QColor>
#include <Widgets/Block/ColorTable.hpp>
#include <Widgets/Block/BlockColorPickerDialog.h>

class PowerObjectColorPicker : public QPushButton
{
    Q_OBJECT
public:

    explicit PowerObjectColorPicker(QWidget *parent = nullptr);

    ~PowerObjectColorPicker();

    int GetValue();

    void SetValue(int value);

    void SetColor(const QColor& color);

    QColor GetColor(int value);

    QColor GetColor();

signals:
    void SignalColorChanged(const QColor& color, int colorId); 

private slots:
    void OnColorPickerDialog();
    void OnColorChanged(const QColor& color, int colorId);

private:
    int m_value;
    BlockColorPickerDialog *m_color_dialog;
    DisplayColorTable m_color_table;
    QColor m_button_color;
};
