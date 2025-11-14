#pragma once

#include <QWidget>
#include <QLabel>
#include <QStringList>
#include <QGridLayout>
#include "PowerDoubleLineEdit.h"

class PowerDoubleTable : public QWidget
{
    Q_OBJECT

public:
    PowerDoubleTable(QWidget *parent = nullptr);
    ~PowerDoubleTable();

    QStringList GetColumnTitles() const;
    void SetColumnTitles(const QStringList &columnTitles);

    QStringList GetRowTitles() const;
    void SetRowTitles(const QStringList &rowTitles);

    bool GetShowSpinFlag() const;
    void SetShowSpinFlag(bool spinFlag);

    double GetIncrement() const;
    void SetIncrement(double increment);

    void UpdateTable();

    QVector<QVector<double>> GetValues() {return m_values;};

signals:
    void SignalValueChanged(QVector<QVector<double>> values);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    QStringList m_column_titles;
    QStringList m_row_titles;
    bool m_show_spin_flag;
    double m_increment;
    QGridLayout *m_layout;
    QVector<QVector<PowerDoubleLineEdit*>> m_table;
    QVector<QLabel*> m_column_headers;
    QVector<QLabel*> m_row_headers; 
    QVector<QVector<double>> m_values;
};    