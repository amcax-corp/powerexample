
#pragma once
#include <Gui/Workbench/Navigator/Navigator.h>
#include <QTabWidget.h>

namespace Dev {

class ShapeTreeWidget;

class PartNavigator : public gui::Navigator
{
  public:
    PartNavigator();
    virtual ~PartNavigator();

    virtual QIcon GetIcon() override
    {
        return QIcon(":/icon/left-bar/part.png");
    }
    void UpdateNavigator();

  public:
    virtual QWidget* InitMainWidget(app::Document* doc) override;

  private:
    QTabWidget* tabWidget;
    ShapeTreeWidget* shapebase;
    // PartLayerTree* layer_tree;
};

}  // namespace Dev
