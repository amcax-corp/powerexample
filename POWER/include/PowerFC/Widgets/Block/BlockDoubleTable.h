#pragma once

#include <QWidget>
#include <Widgets/PowerWidgetsConfig.h>

class PowerDoubleTable;
class PW_API BlockDoubleTable: public QWidget
{
    Q_OBJECT

    Q_PROPERTY(QStringList ColumnTitles READ GetColumnTitles WRITE SetColumnTitles)
    Q_PROPERTY(QStringList RowTitles READ GetRowTitles WRITE SetRowTitles)
    Q_PROPERTY(int Increment READ GetIncrement WRITE SetIncrement)
    Q_PROPERTY(bool SpinVisibility READ IsSpinVisibility WRITE SetSpinVisibility)

public:
    /// @brief 构造函数，默认构造函数
    /// @param parent 父窗口指针
    explicit BlockDoubleTable(QWidget *parent = nullptr);

    /// @brief 析构函数
    ~BlockDoubleTable();

    /// @brief 获取列标题
    /// @return QStringList类型 列标题
    QStringList GetColumnTitles();

    /// @brief 设置列标题
    /// @param column_titles QStringList类型 列标题
    void SetColumnTitles(QStringList column_titles);

    /// @brief 获取行标题
    /// @return QStringList类型 行标题
    QStringList GetRowTitles();

    /// @brief 设置行标题
    /// @param row_titles QStringList类型 行标题
    void SetRowTitles(QStringList row_titles);

    /// @brief 获取增量
    /// @return double类型 增量
    double GetIncrement();

    /// @brief 设置增量
    /// @param increment double类型 增量
    void SetIncrement(double increment);
    
    /// @brief 获取是否启用微调
    /// @return bool类型 是否启用微调
    bool IsSpinVisibility();

    /// @brief 设置是否启用微调
    /// @param spin bool类型 是否启用微调
    void SetSpinVisibility(bool spin);

signals:
    /// @brief 信号，当表格值发生变化时发出
    /// @param values QVector<QVector<double>>类型 表格值
    void SignalDoubleTableValueChanged(QVector<QVector<double>> values);

public slots:
    /// @brief 信号槽，当表格值发生变化时调用
    void OnDoubleTableValueChanged();

private:
    PowerDoubleTable *m_edit_table;
};
