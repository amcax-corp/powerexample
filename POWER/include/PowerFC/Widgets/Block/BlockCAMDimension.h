#pragma once
#include <Widgets/Block/BlockBase.h>
class PowerDoubleLineEdit;
class PowerEnumeration;
class PW_API BlockCAMDimension : public BlockBase
{
    Q_OBJECT
    Q_PROPERTY(double Value READ GetValue WRITE SetValue)
    Q_PROPERTY(double Minimal READ GetMinimal WRITE SetMinimal)
    Q_PROPERTY(bool MinInclusive READ IsMinInclusive WRITE SetMinInclusive)
    Q_PROPERTY(double Maximum READ GetMaximum WRITE SetMaximum)
    Q_PROPERTY(bool MaxInclusive READ IsMaxInclusive WRITE SetMaxInclusive)
    Q_PROPERTY(double Tolerance READ GetTolerance WRITE SetTolerance)
    Q_PROPERTY(bool ReadOnlyValue READ IsReadOnlyValue WRITE SetReadOnlyValue)
    Q_PROPERTY(int CurrentIndex READ GetCurrentIndex WRITE SetCurrentIndex)

public:
    /**
     * @brief 构造函数，用于创建一个 BlockCAMDimension 对象。
     *
     * @param parent 指向父窗口部件的指针，默认为 nullptr。
     */
    explicit BlockCAMDimension(QWidget *parent = nullptr);

    /**
     * @brief 析构函数，用于销毁一个 BlockCAMDimension 对象。
     */
    ~BlockCAMDimension();

    /// @brief 获取当前值
    /// @return double类型
    double GetValue();

    /// @brief 获取当前最小值
    /// @return double类型
    double GetMinimal();

    /// @brief 当前是否包含最小值
    /// @return bool类型
    bool IsMinInclusive();

    /// @brief 获取当前最大值
    /// @return double类型
    double GetMaximum();

    /// @brief 当前是否包含最大值
    /// @return bool类型
    bool IsMaxInclusive();

    /// @brief 获取当前误差值
    /// @return double类型
    double GetTolerance();

    /// @brief 获取当前是否只读
    /// @return bool类型
    bool IsReadOnlyValue();

    /// @brief 获取当前单位的索引
    /// @return bool类型
    int GetCurrentIndex();

    /// @brief 设置当前值
    /// @param value double类型
    void SetValue(double value);

    /// @brief 设置当前最小值
    /// @param min_value double类型
    void SetMinimal(double min_value);

    /// @brief 设置当前是否包含最小值
    /// @param min_inclusive_value double类型
    void SetMinInclusive(bool min_inclusive_value);

    /// @brief 设置当前最大值
    /// @param max_value double类型
    void SetMaximum(double max_value);

    /// @brief 设置当前是否包含最大值
    /// @param max_inclusive_value double类型
    void SetMaxInclusive(bool max_inclusive_value);

    /// @brief 设置当前误差
    /// @param tolerance_value double类型
    void SetTolerance(double tolerance_value);

    /// @brief 设置当前是否只读
    /// @param only_read bool类型
    void SetReadOnlyValue(bool only_read);

    /// @brief 获取当前单位的索引
    /// @return bool类型
    void SetCurrentIndex(int index);

Q_SIGNALS:
    /// @brief 信号，当索引改变时发出
    /// @param index 索引值
    void SignalIndexChanged(int index);

    /// @brief 当值改变时发出信号
    /// @param value double类型
    void SignalDoubleValueChange(double value);

private:
    PowerDoubleLineEdit *m_double;
    PowerEnumeration *m_unit;
};
