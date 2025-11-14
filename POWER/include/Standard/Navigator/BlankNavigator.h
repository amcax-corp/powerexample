
#pragma once
#include <Gui/Workbench/Navigator/Navigator.h>

namespace gui {

class BlankNavigator : public Navigator
{
  public:
    BlankNavigator();
    virtual ~BlankNavigator();

  public:
    virtual QWidget* InitMainWidget(app::Document* doc) override;
};

}  // namespace gui
