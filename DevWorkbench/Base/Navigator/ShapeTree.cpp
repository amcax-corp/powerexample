
#include "ShapeTree.h"
#include "PartNavigator.h"
#include <App/DocumentObjectTopoShape.h>
#include <Base/DevSetup.h>
#include <Base/PartCollection.h>
#include <Gui/Application.h>
#include <Gui/ViewProvider/ViewProvider.h>
#include <Gui/ViewProvider/ViewProviderDocumentObject3D.h>
#include <App/Properties/PropertyString.h>
#include <App/PropertyContainer.h>
#include <Gui/MainWindow.h>
#include <Gui/Command/WorkbenchCommand.h>

namespace Dev
{
    ShapeTreeWidget::ShapeTreeWidget(std::string name, PartNavigator *parent)
        : gui::TreeWidget(name, parent), m_nav(parent)
    {
        InitRoot();
        connectCreateObject = Dev::DevSetup::GetCurDevSetup()->DevPartCollection()->SignalNewObject.connect(boost::bind(&ShapeTreeWidget::OnCreateObject, this, boost::placeholders::_1));
        connectDeleteObject = Dev::DevSetup::GetCurDevSetup()->DevPartCollection()->SignalDeletedObject.connect(boost::bind(&ShapeTreeWidget::OnDeleteObject, this, boost::placeholders::_1));
        connectChangedObject = Dev::DevSetup::GetCurDevSetup()->DevPartCollection()->SignalObjectPropertyChanged.connect(boost::bind(&ShapeTreeWidget::OnChangeObject, this, boost::placeholders::_1, boost::placeholders::_2));
    }

    ShapeTreeWidget::~ShapeTreeWidget()
    {
        if (connectCreateObject.connected())
            connectCreateObject.disconnect();
        if (connectDeleteObject.connected())
            connectDeleteObject.disconnect();
        if (connectChangedObject.connected())
            connectChangedObject.disconnect();
    }

    void ShapeTreeWidget::InitTree(app::Document *doc)
    {
        if (!doc)
            return;
        m_doc = doc;
        while (Root()->childCount() > 0)
        {
            QTreeWidgetItem *child = Root()->takeChild(0); // 取出并移除第一个子节点
            delete child;                                    // 手动释放内存
        }
        auto parts = DevSetup::GetCurDevSetup()->DevPartCollection()->PartList();
        for (auto obj : parts)
        {
            gui::DocumentObjectItem *item = new gui::DocumentObjectItem(obj, Root());
            UpdateItem(item);
            Root()->addChild(item);
        }
        this->expandAll();
    }

    gui::DocumentObjectItem *ShapeTreeWidget::UpdateItem(gui::DocumentObjectItem *item)
    {
        auto obj = item->GetObject();
        if (!obj)
            return item;
        item->Data()->type = PART;
        if (obj->GetClassTypePolymorphic().IsDerivedFrom("app::DocumentObjectTopoShape"))
        {
            QString name = QString::fromUtf8(obj->Label.GetString());
            item->setText(COLUMN_NAME, name);
            bool visiable = item->GetViewProvider()->Visibility.GetValue();
            item->setIcon(COLUMN_VISIABLE, visiable ? QIcon(":icon/base/icon_visiable.png") : QIcon(":icon/base/icon_invisiable.png"));
        }
        return item;
    }

    QStringList ShapeTreeWidget::GetHeaders()
    {
        QStringList list;
        list << tr("名称") << tr("可见");
        return list;
    }

    QTreeWidgetItem *ShapeTreeWidget::Root()
    {
        return m_root;
    }

    void ShapeTreeWidget::InitRoot()
    {
        m_root = new gui::DocumentObjectItem(nullptr, invisibleRootItem());
        m_root->Data()->type = MAIN;
        m_root->setText(0, "部件");
        invisibleRootItem()->addChild(m_root);
    }

    void ShapeTreeWidget::dragMoveEvent(QDragMoveEvent *event)
    {
        auto target = itemAt(event->position().toPoint());
        auto targetItem = dynamic_cast<gui::DocumentObjectItem *>(target); // 目标item
        auto sources = GetSelectedWithFilter();
        for (auto source : sources)
        {
            auto sourceItem = dynamic_cast<gui::DocumentObjectItem *>(source); // 正在拖动的item
        }
        return; // 禁止拖拽
        event->acceptProposedAction();
    }
    void ShapeTreeWidget::dropEvent(QDropEvent *event)
    {
        return; // 禁止拖拽
        gui::TreeWidget::dropEvent(event);
    }

    void ShapeTreeWidget::OnCreateObject(const app::DocumentObject &obj)
    {
        if (!obj.GetClassTypePolymorphic().IsSubTypeOf(app::DocumentObjectTopoShape::GetClassType()))
            return;
        gui::DocumentObjectItem *item = new gui::DocumentObjectItem(&obj, Root());
        UpdateItem(item);
        Root()->addChild(item);
    }

    void ShapeTreeWidget::OnDeleteObject(const app::DocumentObject &obj)
    {
        if (!obj.GetClassTypePolymorphic().IsSubTypeOf(app::DocumentObjectTopoShape::GetClassType()))
            return;
        auto item = FindItem(Root(), &obj);
        if (item)
            item->parent()->removeChild(item);
    }

    void ShapeTreeWidget::OnChangeObject(const app::DocumentObject &obj, const app::Property &)
    {
        if (!obj.GetClassTypePolymorphic().IsSubTypeOf(app::DocumentObjectTopoShape::GetClassType()))
            return;
        auto item = FindItem(Root(), &obj);
        if (item)
            UpdateItem(item);
    }

    void ShapeTreeWidget::OnItemClick(QTreeWidgetItem *item, int column)
    {
        if (column == COLUMN_VISIABLE)
        {
            auto obj_item = dynamic_cast<gui::DocumentObjectItem *>(item);
            if (obj_item->Data()->type == MAIN)
                return;
            auto view = obj_item->GetViewProvider();
            bool visible = view->Visibility.GetValue();
            if (visible)
                app::OpenCommand(ShapeTreeWidget::tr("隐藏").toStdString());
            else
                app::OpenCommand(ShapeTreeWidget::tr("显示").toStdString());
            view->Visibility.SetValue(!visible);
            app::CommitCommand();
            m_nav->UpdateNavigator();
        }
    }

    void ShapeTreeWidget::SlotCustomContextMenu(const QPoint &pos)
    {
        QModelIndex index = indexAt(pos);
        if (index.row() < 0 || index.column() < 0)
        {
            return;
        }
        auto inds = selectedIndexes();
        if (inds.size() / (header()->count()) > 1)
        {
            InitMultiSelectionActions();
            return;
        }

        gui::DocumentObjectItem *item = static_cast<gui::DocumentObjectItem *>(index.internalPointer());
        int type = item->Data()->type;
        auto mainMenu = new QMenu(this);
        if (type == PART)
        {
            // mainMenu->addAction(GetAction("CAM_Export"));
            mainMenu->addAction(GetAction("Std_Delete"));
        }
        mainMenu->exec(QCursor::pos());

        delete mainMenu;
    }

    void ShapeTreeWidget::OnSelectionChanged(const gui::SelectionChanges &msg)
    {
        gui::TreeWidget::OnSelectionChanged(msg);
    }

    void ShapeTreeWidget::InitMultiSelectionActions()
    {
        if (selectedIndexes().size() == 0)
        {
            return;
        }
        int type = 0;
        type = static_cast<gui::DocumentObjectItem *>(selectedIndexes()[0].internalPointer())->Data()->type;

        for (auto &index : selectedIndexes())
        {
            auto item = static_cast<gui::DocumentObjectItem *>(index.internalPointer());
            if (item->Data()->type != type)
            {
                return;
            }
        }
        auto m_multiSelectionMenu = new QMenu(this);

        if (type == PART)
        {
            m_multiSelectionMenu->addAction(GetAction("CAM_Export"));
            // m_multiSelectionMenu->addAction(GetAction("CAM_Part_Delete"));
        }

        m_multiSelectionMenu->exec(QCursor::pos());

        delete m_multiSelectionMenu;
    }

    void ShapeTreeWidget::mouseDoubleClickEvent(QMouseEvent *event)
    {
        gui::CommandManager::GetInstance().RunCommandByName("Dev_EditDisplay");
    }

} // namespace cam
