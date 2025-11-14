#pragma once

#include <QWidget>
#include <Widgets/PowerWidgetsConfig.h>

class PowerIntegerTable;

class PW_API BlockIntegerTable: public QWidget
{
    Q_OBJECT

    Q_PROPERTY(QStringList ColumnTitles READ GetColumnTitles WRITE SetColumnTitles)
    Q_PROPERTY(QStringList RowTitles READ GetRowTitles WRITE SetRowTitles)
    Q_PROPERTY(int Increment READ GetIncrement WRITE SetIncrement)
    Q_PROPERTY(bool Spin READ GetSpin WRITE SetSpin)

public:
    /// @brief 构造函数，默认构造函数
    /// @param parent 父窗口指针
    explicit BlockIntegerTable(QWidget *parent = nullptr);

    /// @brief 析构函数
    ~BlockIntegerTable();

    /// @brief 获取列标题
    /// @return 列标题
    QStringList GetColumnTitles();

    /// @brief 设置列标题
    /// @param column_titles 
    void SetColumnTitles(QStringList column_titles);

    /// @brief 获取行标题
    /// @return QStringList
    QStringList GetRowTitles();

    /// @brief 设置行标题
    /// @param row_titles
    void SetRowTitles(QStringList row_titles);

    /// @brief 获取增量
    /// @return 增量
    int GetIncrement();

    /// @brief 设置增量
    /// @param increment 增量
    void SetIncrement(int increment);
    
    /// @brief 获取是否启用微调器
    /// @return 是否启用微调器
    bool GetSpin();

    /// @brief 设置是否启用微调器
    /// @param spin 是否启用微调器
    void SetSpin(bool spin);

signals:
    /// @brief 信号，当表格值发生变化时发出,值为从左到右，从上到下的值存储在容器中
    /// @param values 值
    void SignalIntTableValueChanged(QVector<QVector<int>> values);

public slots:
    /// @brief 当表格值发生变化时调用
    void OnIntTableValueChanged();

private:
    PowerIntegerTable *m_edit_table;
};
