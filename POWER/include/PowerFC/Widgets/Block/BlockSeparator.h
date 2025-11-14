#pragma once
#include <QWidget>
#include <Widgets/PowerWidgetsConfig.h>
class PW_API BlockSeparator : public QWidget
{
    Q_OBJECT
public:
    /// @brief 构造一个BlockSeparator对象
    /// @param parent 
    explicit BlockSeparator(QWidget *parent = nullptr);

    /// @brief 析构函数
    ~BlockSeparator();

protected:

    /// @brief 绘制事件
    /// @param event 
    void paintEvent(QPaintEvent *event) override;
};