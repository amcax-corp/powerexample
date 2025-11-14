#pragma once
#include <Gui/Workbench/Navigator/Tree.h>

namespace Dev {

enum ShapeTreeItemType
{
    MAIN = 0,
    PART
};
class PartNavigator;

class ShapeTreeWidget : public gui::TreeWidget
{
  public:
    ShapeTreeWidget(std::string name, PartNavigator* parent = 0);
    ~ShapeTreeWidget();

    virtual void InitTree(app::Document* doc) override;
    virtual gui::DocumentObjectItem* UpdateItem(gui::DocumentObjectItem* item) override;
    virtual QStringList GetHeaders() override;

    QTreeWidgetItem* Root() override;
    void InitRoot();

    protected:
    void dragMoveEvent(QDragMoveEvent* event) override; //拖拽时的事件
    void dropEvent(QDropEvent* event) override;         //拖拽释放的事件

  private:
    void OnCreateObject(const app::DocumentObject&);
    void OnDeleteObject(const app::DocumentObject&);
    void OnChangeObject(const app::DocumentObject&, const app::Property&);

    virtual void OnItemClick(QTreeWidgetItem* item, int column) override;
    void mouseDoubleClickEvent(QMouseEvent* event) override;

    void InitMultiSelectionActions();
    void OnActionTrigger(const std::string& name);

  protected slots:
    virtual void SlotCustomContextMenu(const QPoint& pos) override;
    virtual void OnSelectionChanged(const gui::SelectionChanges& msg) override;

  private:
    PartNavigator* m_nav;
    Connection connectCreateObject;
    Connection connectDeleteObject;
    Connection connectChangedObject;
    gui::DocumentObjectItem* m_root;
    enum ViewColumn
    {
        COLUMN_NAME = 0, /** 名称 */
        COLUMN_VISIABLE,  /** 可见 */
        Column_Layer  /** 图层 */
    };
};

}  // namespace Dev

