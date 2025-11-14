#pragma once
#include <QToolButton>
#include <QProxyStyle>
#include <QPainter>
#include <QStyleOption>

namespace standard{

class UndoRedoButton : public QToolButton
{
public:
    UndoRedoButton(QWidget* parent = nullptr);
    ~UndoRedoButton(){}
};

class CustomToolButtonStyle : public QProxyStyle
{
public:
    void drawPrimitive(PrimitiveElement element, const QStyleOption *option, QPainter *painter, const QWidget *widget) const override
    {
        if (element == PE_IndicatorArrowDown)
        {
            QIcon icon(widget->isEnabled() 
                ? ":icon/base/arrow-down-white.svg" 
                : ":icon/base/arrow-down-gray.svg"
            );
            // 获取适应大小的像素图
            QPixmap arrow = icon.pixmap(8, 8); // 自动处理 DPI 和缩放
            // 调整箭头位置（居中）
            QRect rect = option->rect;
            int x = rect.x() + (rect.width() - arrow.width()) / 2 + 3;
            int y = rect.y() + (rect.height() - arrow.height()) / 2 + 3;
            
            painter->drawPixmap(x, y, arrow);
        }
        else
        {
            QProxyStyle::drawPrimitive(element, option, painter, widget);
        }
    }
};
}