#pragma once

#include <QWidget>
#include <Widgets/Block/BlockBase.h>
#include <Widgets/PowerWidgetsConfig.h>
class PowerDoubleLineEdit;

class PW_API BlockDouble : public BlockBase
{
    Q_OBJECT
    Q_PROPERTY(double Minimal READ GetMinimal WRITE SetMinimal)
    Q_PROPERTY(bool MinInclusive READ IsMinInclusive WRITE SetMinInclusive)
    Q_PROPERTY(double Maximum READ GetMaximum WRITE SetMaximum)
    Q_PROPERTY(bool MaxInclusive READ IsMaxInclusive WRITE SetMaxInclusive)
    Q_PROPERTY(double Tolerance READ GetTolerance WRITE SetTolerance)
    Q_PROPERTY(double Increment READ GetIncrement WRITE SetIncrement)
    Q_PROPERTY(PresentationStyle PresentationStyle READ GetPresentationStyle WRITE SetPresentationStyle)
    Q_PROPERTY(bool ReadOnlyValue READ IsReadOnlyValue WRITE SetReadOnlyValue)
    Q_PROPERTY(bool UnitLabelVisibility READ IsUnitLabelVisibility WRITE SetUnitLabelVisibility)
    Q_PROPERTY(double Value READ GetValue WRITE SetValue)
    Q_PROPERTY(KeyinFiledWidth WidthStyle READ GetWidthStyle WRITE SetWidthStyle)
    
public:
    enum PresentationStyle {
    Keyin,
    Spin,
    };
    Q_ENUM(PresentationStyle);

    enum KeyinFiledWidth {
        Narrow,
        Standard
    };
    Q_ENUM(KeyinFiledWidth);

public:
    /// @brief 构造函数，默认构造函数
    /// @param parent 父窗口指针
    explicit BlockDouble(QWidget *parent = nullptr);

    /// @brief 析构函数
    ~BlockDouble();

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

    /// @brief 获取当前显示风格
    /// @return PresentationStyle类型
    PresentationStyle GetPresentationStyle();

    /// @brief 获取当前是否只读
    /// @return bool类型
    bool IsReadOnlyValue();

    /// @brief 获取当前是否显示单位
    /// @return bool类型
    bool IsUnitLabelVisibility();

    /// @brief 获取当前值
    /// @return double类型
    double GetValue();

    /// @brief 设置当前框的宽度风格
    /// @return KeyinFiledWidth类型
    KeyinFiledWidth GetWidthStyle();

    /// @brief 设置当前增量
    /// @return double类型
    double GetIncrement();

    /// @brief 设置当前增量
    /// @param increment_value double类型
    void SetIncrement(double increment_value);

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

    /// @brief 设置当前显示风格
    /// @param style PresentationStyle类型
    void SetPresentationStyle(PresentationStyle style);

    /// @brief 设置当前是否只读
    /// @param only_read bool类型
    void SetReadOnlyValue(bool only_read);

    /// @brief 设置当前是否显示单位标签
    /// @param show_unit bool类型
    void SetUnitLabelVisibility(bool show_unit);

    /// @brief 设置当前值
    /// @param value double类型
    void SetValue(double value);

    /// @brief 设置当前宽度风格
    /// @param width KeyinFiledWidth类型
    void SetWidthStyle(KeyinFiledWidth width);

    /// @brief 设置是否显示double框
    /// @param show bool类型
    void IsDisplayDouble(bool is_show);
    
signals:
    /// @brief 当值改变时发出信号
    /// @param value double类型
    void SignalDoubleValueChange(double value);

private:
    PowerDoubleLineEdit *m_edit;

};
