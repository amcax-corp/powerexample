#pragma once

#include <QWidget>
#include <Widgets/Block/BlockBase.h>
class PowerObjectColorPicker;

class PW_API BlockObjectColorPicker : public BlockBase
{
    Q_OBJECT

    Q_PROPERTY(int Value READ GetValue WRITE SetValue FINAL)

public:

    /// @brief 构造函数，用于创建一个BlockRGBColorPicker对象
    /// @param parent 父QWidget对象，默认为nullptr
    explicit BlockObjectColorPicker(QWidget *parent = nullptr);
    ~BlockObjectColorPicker();

    /// @brief 获取初始颜色
    /// @return 当前颜色ID
    int GetValue();
    
    /// @brief 设置初始颜色
    /// @param value 根据ID设置颜色
    void SetValue(int value);

    /// @brief 设置初始颜色
    /// @param color QColor设置颜色
    void SetColor(const QColor& color);

    /// @brief 获取初始颜色
    /// @return QColor
    QColor GetColor();

signals:
    /// @brief 信号，当颜色状态改变时发出
    /// @param state 新的颜色状态，类型为QColor
    void SignalColorChanged(const QColor& color, int color_id);

public slots:
    /// @brief 处理颜色状态改变事件
    /// @param state 新的颜色状态，类型为QColor
    void OnColorChanged(const QColor& color, int color_id);

private:
    PowerObjectColorPicker *m_color_button;
    QColor m_color;
};
