#pragma once

#include <QWidget>
#include <Widgets/Block/BlockBase.h>
class PowerInteger;

class PW_API BlockInteger : public BlockBase
{
    Q_OBJECT

    Q_PROPERTY(int Minimal READ GetMinimal WRITE SetMinimal)
    Q_PROPERTY(bool MinInclusive READ IsMinInclusive WRITE SetMinInclusive)
    Q_PROPERTY(int Maximum READ GetMaximum WRITE SetMaximum)
    Q_PROPERTY(bool MaxInclusive READ IsMaxInclusive WRITE SetMaxInclusive)
    Q_PROPERTY(PresentationStyle PresentationStyle READ GetPresentationStyle WRITE SetPresentationStyle)
    Q_PROPERTY(bool ReadOnlyValue READ IsReadOnlyValue WRITE SetReadOnlyValue)
    Q_PROPERTY(int Value READ GetValue WRITE SetValue)
    Q_PROPERTY(KeyinFiledWidth WidthStyle READ GetWidthStyle WRITE SetWidthStyle)

public:

    enum PresentationStyle {
        Keyin,
        Spin,
        // Scale,
        // ScaleKeyin,
        // Combo
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
    explicit BlockInteger(QWidget *parent = nullptr);

    /// @brief 析构函数
    ~BlockInteger();

    /// @brief 获取当前最小值
    /// @return int类型
    int GetMinimal();

    /// @brief 当前是否包含最小值
    /// @return bool类型
    bool IsMinInclusive();

    /// @brief 获取当前最大值
    /// @return int类型
    int GetMaximum();

    /// @brief 当前是否包含最大值
    /// @return bool类型
    bool IsMaxInclusive();

    /// @brief 获取当前显示风格
    /// @return PresentationStyle类型
    PresentationStyle GetPresentationStyle();

    /// @brief 获取当前是否只读
    /// @return bool类型
    bool IsReadOnlyValue();

    /// @brief 获取当前值
    /// @return int类型
    int GetValue();

    /// @brief 设置当前框的宽度风格
    /// @return KeyinFiledWidth类型
    KeyinFiledWidth GetWidthStyle();
signals:

    /// @brief 当值改变时发出信号
    /// @param value int类型
    void SignalIntValueChange(int value);

public Q_SLOTS:

    /// @brief 设置当前最小值
    /// @param min_value int类型
    void SetMinimal(int min_value);

    /// @brief 设置当前是否包含最小值
    /// @param min_inclusive_value bool类型
    void SetMinInclusive(bool min_inclusive_value);

    /// @brief 设置当前最大值
    /// @param max_value int类型
    void SetMaximum(int max_value);

    /// @brief 设置当前是否包含最大值
    /// @param max_inclusive_value bool类型
    void SetMaxInclusive(bool max_inclusive_value);

    /// @brief 设置当前显示风格
    /// @param style PresentationStyle类型
    void SetPresentationStyle(PresentationStyle style);

    /// @brief 设置当前是否只读
    /// @param only_read bool类型
    void SetReadOnlyValue(bool only_read);

    /// @brief 设置当前值
    /// @param value int类型
    void SetValue(int value);

    /// @brief 设置当前宽度风格
    /// @param width KeyinFiledWidth类型
    void SetWidthStyle(KeyinFiledWidth width);

private:
    PowerInteger *m_edit;
    // PowerIntegerSpin *m_edit;

};
