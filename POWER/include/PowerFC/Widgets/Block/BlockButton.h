#pragma once

#include <QWidget>
#include <Widgets/Block/BlockBase.h>
class PowerButton;

class PW_API BlockButton : public BlockBase
{
    Q_OBJECT
    Q_PROPERTY(QPixmap ButtonIcon READ GetButtonIcon WRITE SetButtonIcon)
    Q_PROPERTY(bool ButtonEnable READ GetButtonEnable WRITE SetButtonEnable)

public:
    /// @brief 构造函数，创建一个BlockButton对象
    /// @param parent 父QWidget对象，默认为nullptr
    explicit BlockButton(QWidget *parent = nullptr);
    ~BlockButton();

    /// @brief 获取按钮图标
    /// @return 按钮图标的QPixmap对象
    QPixmap GetButtonIcon();

    /// @brief 设置按钮图标
    /// @param button_icon 按钮图标的QPixmap对象
    void SetButtonIcon(const QPixmap &button_icon);

    /// @brief 获取是否禁用按钮
    /// @return 是否禁用按钮
    bool GetButtonEnable();

    /// @brief 设置是否禁用按钮
    /// @param button_enable 是否禁用按钮
    void SetButtonEnable(bool button_enable);

    void SetButtonTip(const QString &tip);
    
signals:
    /// @brief 按钮点击信号
    void SignalButtonClicked();

private slots:
    void OnResizeButton(bool labelVisibility);

private:
    PowerButton *m_button;
};
