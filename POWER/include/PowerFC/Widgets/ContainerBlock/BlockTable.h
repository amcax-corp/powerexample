#pragma once

#include <Widgets/Block/BlockBase.h>
#include <Widgets/PowerWidgetsConfig.h>

class PW_API BlockTable : public BlockBase
{
    Q_OBJECT
    // Q_PROPERTY(bool HasColumnLabels READ HasColumnLabels WRITE SetHasColumnLabels NOTIFY SignalHasColumnLabelsChanged);
    // Q_PROPERTY(QStringList ColumnLabels READ GetColumnLabels WRITE SetColumnLabels NOTIFY SignalNumberOfColumnChanged);

public:
    explicit BlockTable(QWidget *parent = nullptr);

    // // READ
    // bool HasColumnLabels() const;
    // QStringList GetColumnLabels() const;

    // // WRITE
    // void SetHasColumnLabels(bool has_column_labels);
    // void SetColumnLabels(const QStringList column_labels);

protected:

signals:
    void SignalHasColumnLabelsChanged(bool);
    void SignalNumberOfColumnChanged(QStringList);

private:
    bool m_has_column_labels = false;
    QStringList m_column_labels = {"Column1"};
    QWidget *m_header = nullptr;
};