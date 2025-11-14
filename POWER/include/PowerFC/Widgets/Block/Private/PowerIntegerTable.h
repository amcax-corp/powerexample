#pragma once

#include <QWidget>
#include <QLabel>
#include <QStringList>
#include <QGridLayout>
#include "PowerInteger.h"

class PowerIntegerTable : public QWidget
{
    Q_OBJECT

public:
    PowerIntegerTable(QWidget *parent = nullptr);
    ~PowerIntegerTable();

    QStringList GetColumnTitles() const;
    void SetColumnTitles(const QStringList &columnTitles);

    QStringList GetRowTitles() const;
    void SetRowTitles(const QStringList &rowTitles);

    bool GetShowSpinFlag() const;
    void SetShowSpinFlag(bool spinFlag);

    int GetIncrement() const;
    void SetIncrement(int increment);

    void UpdateTable();

    QVector<QVector<int>> GetValues() {return m_values;};

signals:
    void SignalValueChanged(QVector<QVector<int>> values);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    QStringList m_column_titles;
    QStringList m_row_titles;
    bool m_show_spin_flag;
    int m_increment;
    QGridLayout *m_layout;
    QVector<QVector<PowerInteger*>> m_table;
    QVector<QLabel*> m_column_headers;
    QVector<QLabel*> m_row_headers; 
    QVector<QVector<int>> m_values;
};    