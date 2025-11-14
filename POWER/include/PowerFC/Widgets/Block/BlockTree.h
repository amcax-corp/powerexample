#pragma once
#include <QAction>
#include <QDrag>
#include <QHeaderView>
#include <QMenu>
#include <QMimeData>
#include <QMouseEvent>
#include <QPainter>
#include <QStandardItemModel>
#include <QStyledItemDelegate>
#include <QTreeWidget>
#include <Widgets/PowerWidgetsConfig.h>

class PW_API BlockTree : public QTreeWidget
{
    Q_OBJECT

    Q_PROPERTY(QSize minimumSize READ minimumSize WRITE setMinimumSize DESIGNABLE false)
    Q_PROPERTY(QSize maximumSize READ maximumSize WRITE setMaximumSize DESIGNABLE false)
    Q_PROPERTY(int columnCount READ columnCount WRITE setColumnCount DESIGNABLE false)
    Q_PROPERTY(bool headerHidden READ isHeaderHidden WRITE setHeaderHidden)
    Q_PROPERTY(SelectionMode selectionMode READ selectionMode WRITE setSelectionMode DESIGNABLE false)
    Q_PROPERTY(bool sortingEnabled READ isSortingEnabled WRITE setSortingEnabled DESIGNABLE false)

    Q_PROPERTY(QSize MinimumSize READ minimumSize WRITE setMinimumSize)
    Q_PROPERTY(QSize MaximumSize READ maximumSize WRITE setMaximumSize)
    Q_PROPERTY(int ColumnCount READ columnCount WRITE setColumnCount)
    Q_PROPERTY(SelectionMode SelectionMode READ selectionMode WRITE setSelectionMode)
    Q_PROPERTY(bool SortRootNodes READ isSortingEnabled WRITE setSortingEnabled)
    Q_PROPERTY(bool HeaderVisibility READ IsHeaderVisibility WRITE SetHeaderVisibility)
    Q_PROPERTY(bool IsMoveAllowed READ GetIsMoveAllowed WRITE SetIsMoveAllowed)

  public:
    /// @brief 构造函数，创建一个 BlockTree 对象
    /// @param parent 父窗口指针，默认为 nullptr
    BlockTree(QWidget* parent = nullptr);

    /// @brief 设置是否允许移动
    /// @param isMoveAllowed 是否允许移动
    void SetIsMoveAllowed(bool isMoveAllowed);

    /// @brief 获取是否允许移动
    /// @return 是否允许移动
    bool GetIsMoveAllowed() const;

    void SetHeaderVisibility(bool visible);
    bool IsHeaderVisibility() const;
    void setAlternatingColors(bool enable);

    void SetCheckedStatus(bool checked);
    bool IsChecked() const;
    
  protected:
    void dropEvent(QDropEvent* event) override;  // 新增重写函数
    void mousePressEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
  private slots:
    void onItemChanged(QTreeWidgetItem* item, int column);

  private:
    void SetCheckStyle();

    void updateChildItems(QTreeWidgetItem* parent, Qt::CheckState state);  // 新增：更新子节点状态
    void updateParentItems(QTreeWidgetItem* item);

    QStandardItemModel *model;
    bool m_canStretchHeight = false;
    bool m_canStretchWidth = false;
    bool m_is_checked = false;
    bool m_checkBoxClick = false;
    QTreeWidgetItem* m_pressedItem = nullptr;
};

class NavigatorTreeViewStyleDelegate : public QStyledItemDelegate
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

class CustomHeaderView : public QHeaderView
{
    Q_OBJECT

  public:
    CustomHeaderView(Qt::Orientation orientation, QWidget* parent = nullptr);

  protected:
    void paintSection(QPainter* painter, const QRect& rect, int logicalIndex) const override;
};