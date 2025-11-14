#ifndef PREFERENCEDIALOG_H
#define PREFERENCEDIALOG_H

#include "Widgets/ContainerBlock/BlockDialog.h"
#include "Widgets/Block/BlockTree.h"
#include <QStackedWidget>
#include <QMap>
#include <Base/Parameter.h>


class PreferenceDialog : public BlockDialog {
    Q_OBJECT
public:
    PreferenceDialog(QWidget *parent = nullptr);
    ~PreferenceDialog();

    void InitUI();
    void InitWorkBench();
    bool HasTreeNode(BlockTree* treeWidget, const QString& nodeName);
    QTreeWidgetItem* AddParentNode(const QString& pnode);
    void AddChildNode(QTreeWidgetItem* parent, const QMap<QString, QWidget*> map);
    void AddBaseTab();
    void AddWorkBenchTab(const QString& workbench, const QMap<QString, QWidget*> map);

signals:
    //复位信号
    void SignalResetClicked();

public slots:
    bool OnConfirmed() override;
    bool OnApplied() override;
    void OnResetted() override;
    void OnCanceled() override;

    void OnTreeItemClicked(QTreeWidgetItem *item, int column);

private:
    BlockTree* m_tree;
    QStackedWidget* m_widget;
    QStringList m_workbench = {};
    QMap<QString, QWidget*> m_widget_map;
    QMap<QString, QWidget*> m_base_map;
};
#endif // PREFERENCEDIALOG_H
