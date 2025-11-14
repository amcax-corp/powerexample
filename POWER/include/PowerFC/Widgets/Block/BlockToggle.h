#pragma once

#include <QWidget>
#include <QCheckBox>
#include <Widgets/Block/BlockBase.h>

class PW_API BlockToggle : public BlockBase
{
    Q_OBJECT

    Q_PROPERTY(bool Value READ GetValue WRITE SetValue FINAL)

public:

    /// @brief 构造函数，用于创建一个BlockToggle对象
    /// @param parent 父QWidget对象，默认为nullptr
    explicit BlockToggle(QWidget *parent = nullptr);
    ~BlockToggle();

    /// @brief 获取当前值
    /// @return 当前值，类型为bool
    bool GetValue();
    
    /// @brief 设置当前值
    /// @param checked 要设置的值，类型为bool
    void SetValue(bool checked);

signals:
    /// @brief 信号，当Check状态改变时发出
    /// @param state 新的Check状态，类型为bool
    void SignalCheckStateChanged(bool state);

private:
    QCheckBox *m_checkbox;
};
