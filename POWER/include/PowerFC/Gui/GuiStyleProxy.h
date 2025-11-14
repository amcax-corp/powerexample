#ifndef POWERFC_GUISTYLEPROXY_H
#define POWERFC_GUISTYLEPROXY_H

#pragma once

#include <QProxyStyle>
namespace gui {

/**
* @brief 这个类用于代理QProxyStyle，替换Qt的标准资源，比如QMessageBox中的图标
* 
*/
class GuiProxyStyle : public QProxyStyle
{
  public:
    QIcon standardIcon(StandardPixmap sp,
                       const QStyleOption* opt = nullptr,
                       const QWidget* widget = nullptr) const override;
};
}  // namespace gui

#endif  //POWERFC_GUISTYLEPROXY_H