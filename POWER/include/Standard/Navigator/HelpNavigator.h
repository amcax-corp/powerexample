
#pragma once
#include <Gui/Workbench/Navigator/Navigator.h>

namespace gui {

class HelpNavigator : public Navigator
{
  public:
    HelpNavigator();
    virtual ~HelpNavigator();

  public:
    virtual QWidget* InitMainWidget(app::Document* doc) override;
};

}  // namespace gui
