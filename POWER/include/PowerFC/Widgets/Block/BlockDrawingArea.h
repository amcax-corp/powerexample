#pragma once

#include <QWidget>
#include <Widgets/PowerWidgetsConfig.h>

class PowerDrawingArea;
class PW_API BlockDrawingArea: public QWidget
{
    Q_OBJECT

    Q_PROPERTY(int Height READ GetHeight WRITE SetHeight)
    Q_PROPERTY(int Width READ GetWidth WRITE SetWidth)
    Q_PROPERTY(QPixmap Image READ GetImage WRITE SetImage)

public:
    /// @brief 构造函数，默认构造函数
    /// @param parent 父窗口指针
    explicit BlockDrawingArea(QWidget *parent = nullptr);

    /// @brief 析构函数
    ~BlockDrawingArea();

    /// @brief 获取高度
    /// @return int 高度
    int GetHeight();

    /// @brief 设置高度
    /// @param height int 高度
    void SetHeight(int height);

    /// @brief 获取宽度
    /// @return int 宽度
    int GetWidth();
    
    /// @brief 设置宽度
    /// @param width 宽度
    void SetWidth(int width);
    
    /// @brief 获取图像
    /// @return QPixmap 图像
    QPixmap GetImage();

    /// @brief 设置图像
    /// @param image 图像
    void SetImage(QPixmap image);

private:
    PowerDrawingArea *m_area;;
};
