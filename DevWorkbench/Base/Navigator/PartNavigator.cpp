

#include "PartNavigator.h"
#include "ShapeTree.h"

namespace Dev {

PartNavigator::PartNavigator()
  : Navigator("PartNavigator", tr("部件导航栏"))
  , tabWidget(nullptr)
  , shapebase(nullptr)
{
}

PartNavigator::~PartNavigator()
{
}

QWidget* PartNavigator::InitMainWidget(app::Document* doc)
{
    tabWidget = new QTabWidget();
    tabWidget->setStyleSheet(R"(
        QTabBar {
                    background-color: #FFFFFF;  
                    border: none; 
                    margin-left: 5px;   
                }
        QTabBar::tab {
                    min-width: 28px;
                    max-width: 28px; 
                    min-height: 28px; 
                    max-height: 28px;
                    margin-left: 2px; 
                    margin-bottom: 2px;
                    border: none;
                    icon-size: 28px;
                    }
        QTabWidget::pane { 
                    background-color : #FFFFFF;
                    border: 1px solid #DDDDDD; 
                    margin-left:0px;
                    margin-top: 0px;
                    margin-bottom :0px;
                    }
        QTabBar::tab:hover{
                    background-color: #E8E8F8;
                    border: none;
                    margin-left: 2px;
                    margin-bottom: 2px;
                    }
        QTabBar::tab:selected{
                    background-color: #E8E8F8;
                    border: none;
                    margin-left: 2px;
                    margin-bottom: 2px;
                    }
        )");

    shapebase = new ShapeTreeWidget(m_name, this);
    shapebase->Init(doc);
    tabWidget->addTab(shapebase, QIcon(), "");
    tabWidget->setTabIcon(0, QIcon(":icon/left-bar/object-view.png"));
    tabWidget->setIconSize(QSize(27, 27));
    tabWidget->setTabToolTip(0, QObject::tr("对象视图"));
    return tabWidget;
}

void PartNavigator::UpdateNavigator()
{
    shapebase->Refresh();
}

}  // namespace Dev