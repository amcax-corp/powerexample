#pragma once

#include <QWidget>
#include <Widgets/Block/BlockBase.h>

class PowerRGBColorPicker;

class PW_API BlockRGBColorPicker : public BlockBase
{
    Q_OBJECT

    Q_PROPERTY(QColor InitColor READ GetInitColor WRITE SetInitColor FINAL)

public:

    /// @brief 构造函数，用于创建一个BlockRGBColorPicker对象
    /// @param parent 父QWidget对象，默认为nullptr
    explicit BlockRGBColorPicker(QWidget *parent = nullptr);
    ~BlockRGBColorPicker();

    /// @brief 获取当前颜色
    /// @return 当前颜色，类型为QColor
    QColor GetInitColor();
    
    /// @brief 设置当前颜色
    /// @param checked 要设置的颜色，类型为QColor
    void SetInitColor(QColor color);

signals:
    /// @brief 信号，当颜色状态改变时发出
    /// @param state 新的颜色状态，类型为QColor
    void SignalColorChanged(QColor current_color);

public slots:
    /// @brief 处理颜色状态改变事件
    /// @param state 新的颜色状态，类型为QColor
    void OnColorChanged(QColor color);

private:
    PowerRGBColorPicker *m_color_button;
};
