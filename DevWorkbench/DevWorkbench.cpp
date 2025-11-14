

#include "DevWorkbench.h"
#include <App/Application.h>
#include <App/Document.h>
#include <App/DocumentObject.h>
#include <Gui/MainWindow.h>
#include <QLabel>
#include <QObject>
#include <QSlider>
#include <QVBoxLayout>
#include <SARibbonCategory.h>
#include <Command/CommandDev.h>
#include <Base/Navigator/PartNavigator.h>

namespace Dev
{

    DevWorkbench::DevWorkbench()
        : gui::Workbench()
    {
    }

    DevWorkbench::~DevWorkbench()
    {
    }

    QMap<QString, QWidget *> DevWorkbench::CreatePreferrenceWidgetList() const
    {
        return QMap<QString, QWidget *>();
    }

    void DevWorkbench::RegistCommand()
    {
        CreateDevWorkbenchCommands();
    }

    void DevWorkbench::StartUp()
    {
    }

    void DevWorkbench::InitData(app::Document *doc)
    {
    }

    void DevWorkbench::CreateMainWindowPopupMenu(gui::MenuItem *item) const
    {
        *item << "Std_DlgCustomize";
    }

    gui::MenuItem *DevWorkbench::SetupMenuBar() const
    {
        // Setup the default menu bar
        gui::MenuItem *menuBar = new gui::MenuItem;

        // File
        {
            gui::MenuItem *item = new gui::MenuItem(menuBar);
            item->SetName("文件");
            *item << "Std_Open" << "Std_Save" << "Separator" << "Std_Import" << "Std_Export";
        }

        // Edit
        {
            gui::MenuItem *item = new gui::MenuItem(menuBar);
            item->SetName("编辑");
            *item << "Std_DlgPreference";
        }

        // Help
        {
            gui::MenuItem *item = new gui::MenuItem(menuBar);
            item->SetName("帮助");
            *item << "Std_About";
        }

        return menuBar;
    }

    gui::ToolBarItem *DevWorkbench::SetupToolBars() const
    {
        gui::ToolBarItem *root = new gui::ToolBarItem;

        {
            gui::ToolBarItem *wave = new gui::ToolBarItem(root, "Dev");

            gui::ToolBarItem *base = new gui::ToolBarItem(wave, "基本");
            *base << "Dev_Import" << "Dev_Export" << "Dev_CreateBox" << "Dev_CreateCurvesLoft" << "Dev_CreateRenderDistance";
        }

        return root;
    }

    QList<SARibbonCategory *> DevWorkbench::GetCategoryList() const
    {
        auto list = SetupCategory(SetupToolBars());
        return list;
    }

    std::vector<gui::Navigator *> DevWorkbench::GetNavigatorList() const
    {
        std::vector<gui::Navigator *> list;
        list.emplace_back(new Dev::PartNavigator());

        return list;
    }

} // namespace Dev