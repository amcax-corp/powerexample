#pragma once

#include <PFCGlobal.h>
#include <QAbstractItemModel>
#include <qtreewidget.h>

namespace gui {

class TreeWidget;
class PFC_GUI_API TreeModel : public QAbstractItemModel
{
    Q_OBJECT

  public:  // used or implement by super clased
    virtual QVariant CustomData(const QModelIndex& index, int role) const = 0;

    void SetHeaders(QStringList headers)
    {
        m_headers = headers;
    }

  public:
    TreeModel(TreeWidget* parent = 0);
    ~TreeModel();
    QTreeWidgetItem* ItemFromIndex(const QModelIndex& index);
    QTreeWidgetItem* Root();
    void Clear();
    void SetRoot(QTreeWidgetItem* root);

  protected:
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
    QVariant data(const QModelIndex& index, int role) const override;
    virtual Qt::ItemFlags flags(const QModelIndex& index) const override;
    QModelIndex index(int row, int column, const QModelIndex& parent) const override;
    QModelIndex parent(const QModelIndex& index) const override;
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;
    bool removeRows(int row, int count, const QModelIndex& parent) override;

    /// drag support ///
    Qt::DropActions supportedDropActions() const override;
    virtual QMimeData* mimeData(const QModelIndexList& indexes) const override;
    bool dropMimeData(const QMimeData* data, Qt::DropAction action, int row, int column, const QModelIndex& parent) override;

  private:
    QStringList m_headers;       /**< 表头内容 */
    QTreeWidgetItem* m_rootItem; /**< 根节点 */
    TreeWidget* m_tree;
};

}  // namespace gui