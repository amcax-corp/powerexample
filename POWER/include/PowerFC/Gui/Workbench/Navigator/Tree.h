
#ifndef GUI_TREE_H
#define GUI_TREE_H

#pragma once
#include <App/Application.h>
#include <App/Document.h>
#include <Base/Parameter.h>
#include <Base/Persistence.h>
#include <Base/Tools.h>
#include <Gui/Selection/Selection.h>
#include <QDrag>
#include <QElapsedTimer>
#include <QHeaderView>
#include <QMenu>
#include <QMimeData>
#include <QMouseEvent>
#include <QPainter>
#include <QStyledItemDelegate>
#include <QTimer>
#include <QTreeWidget>
#include <unordered_map>
#include <unordered_set>

class QLineEdit;

namespace gui {

class ViewProviderDocumentObject;
class DocumentObjectItem;
class DocumentObjectData;
using DocumentObjectDataPtr = std::shared_ptr<DocumentObjectData>;
class TreeModel;

class PFC_GUI_API DocumentObjectData
{
  public:
    const app::DocumentObject* document_object;
    std::string label;
    int type;
    QMap<QString, QVariant> data;

    typedef boost::signals2::scoped_connection Connection;

    DocumentObjectData()
      : type(0)
      , document_object(nullptr)
    {
    }
    DocumentObjectData(const app::DocumentObject* object)
      : document_object(object)
      , type(0)
    {
        label = object ? std::string(object->Label.GetValue()) : "";
    }

    void SetData(QString key, QVariant value)
    {
        data[key] = value;
    }

    QVariant GetData(QString key)
    {
        return data.find(key) != data.end() ? data[key] : QVariant();
    }
};

class PFC_GUI_API TreeWidget : public QTreeWidget, public SelectionObserver
{
    Q_OBJECT

  public:
    TreeWidget(std::string name, QWidget* parent = 0);
    ~TreeWidget();

    std::string GetTreeName() const;
    virtual QTreeWidgetItem* Root();
    void Init(app::Document* doc);
    DocumentObjectItem* FindItem(app::DocumentObject* obj);
    DocumentObjectItem* FindItem(QTreeWidgetItem* parent, const app::DocumentObject* obj);
    DocumentObjectItem* FindItem(QTreeWidgetItem* parent, const std::string& name);
    virtual void InitTree(app::Document* doc);
    virtual DocumentObjectItem* UpdateItem(DocumentObjectItem* item);
    virtual QStringList GetHeaders();
    void CleanRoot();
    void Refresh();

  protected Q_SLOTS:
    virtual void OnItemSelectionChanged();
    virtual void OnItemClick(QTreeWidgetItem* item, int column);
    virtual void OnItemDoubleClick(QTreeWidgetItem* item, int column);
    virtual void OnItemChanged(QTreeWidgetItem*, int index);
    virtual void OnItemEntered(QTreeWidgetItem* item);
    virtual void OnItemCollapsed(QTreeWidgetItem* item);
    virtual void OnItemExpanded(QTreeWidgetItem* item);
    virtual void SlotCustomContextMenu(const QPoint& pos);
    virtual void OnSelectionChanged(const gui::SelectionChanges& msg) override;

    virtual void OnUpdateStatus();
    virtual void OnSelectTimer();

  private:
    virtual void SlotCreateObject(const app::DocumentObject&) {}
    virtual void SlotDeleteObject(const app::DocumentObject&) {}
    virtual void SlotChangeObject(const app::DocumentObject&, const app::Property&) {}
    virtual void SlotBeforeChangeObject(const app::DocumentObject&, const app::Property&) {}
    virtual void OnCreateObject(const gui::ViewProviderDocumentObject&);
    virtual void OnDeleteObject(const gui::ViewProviderDocumentObject&);
    virtual void OnChangeObject(const gui::ViewProviderDocumentObject&, const app::Property&);

  protected:
    QAction* GetAction(const std::string& name);
    QList<QTreeWidgetItem*> GetSelectedWithFilter();

    void UpdateStatus(bool delay = true);
    virtual void ResetSelected();

    void RegistMap(app::DocumentObject* obj, gui::DocumentObjectItem* item);

  protected:
    friend class DocumentObjectItem;
    typedef boost::signals2::connection Connection;
    app::Document* m_doc;
    QTimer* statusTimer;
    QTimer* selectTimer;

    std::map<app::DocumentObject*, gui::DocumentObjectItem*> item_map;

    std::unordered_set<app::DocumentObject*> ChangedObjects;
    std::unordered_set<app::DocumentObject*> NewObjects;

  private:
    Connection connectCreateObject;
    Connection connectDeleteObject;
    Connection connectChangeObject;
    Connection connectBeforeChangeObject;
    Connection connectCreateViewProviderObject;
    Connection connectDeleteViewProviderObject;
    Connection connectChangeViewProviderObject;

    std::string m_name;
};

class PFC_GUI_API DocumentObjectItem : public QTreeWidgetItem
{
  public:
    DocumentObjectItem(DocumentObjectDataPtr data, QTreeWidgetItem* parent = nullptr);
    DocumentObjectItem(const app::DocumentObject* object, QTreeWidgetItem* parent = nullptr);
    ~DocumentObjectItem();

    bool IsChildOfItem(DocumentObjectItem*);
    std::string GetName() const;
    const app::DocumentObject* GetObject();
    gui::ViewProviderDocumentObject* GetViewProvider();
    DocumentObjectItem* GetParentItem() const;
    DocumentObjectDataPtr Data();
    int Row();
    TreeWidget* GetTree() const;

  protected:
    DocumentObjectDataPtr m_data;
    typedef boost::signals2::connection Connection;
    int selected;

    friend class TreeWidget;
};

class PFC_GUI_API NavigatorTreeViewStyleDelegate : public QStyledItemDelegate
{
  public:
    NavigatorTreeViewStyleDelegate(QObject* parent = nullptr);
    // 获取树形控件的缩进量（动态适配）
    int getIndentation() const;

    // 判断是否为最后一个节点
    bool isLastItemInLevel(QTreeWidgetItem* item) const;

    void paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const;

    NavigatorTreeViewStyleDelegate* disableTreeLine();

  private:
    QPen penBackgroup;
    bool showTreeLine = true;
};

}  // namespace gui

#endif  // GUI_TREE_H
