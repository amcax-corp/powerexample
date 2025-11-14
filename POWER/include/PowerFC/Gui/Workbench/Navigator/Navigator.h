
#ifndef GUI_NAVIGATOR_H
#define GUI_NAVIGATOR_H

#pragma once
#include <Base/BaseClass.h>
#include <QWidget>
#include <list>
#include <string>

namespace app {
class Document;
class DocumentObject;
}  // namespace app

namespace gui {

class MenuItem;
class ToolBarItem;
class NavigatorManager;

class PFC_GUI_API Navigator : public QWidget
{
    Q_OBJECT
  public:
    Navigator(std::string name, QString label = "");
    virtual ~Navigator();
    std::string Name() const;
    QString Label() const;
    void SetName(const std::string&);
    void SetupDocument(app::Document* doc);
    QWidget* MainWidget();
    virtual QIcon GetIcon();
    virtual QWidget* InitMainWidget(app::Document* doc);

  protected:
    QString m_label;
    QWidget* m_main_widget;
    std::string m_name;
};

}  // namespace gui

#endif  // GUI_NAVIGATOR_H
