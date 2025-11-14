#pragma once

#include <QWidget>
#include <Widgets/Block/BlockBase.h>

class PowerMultilineString;

class PW_API BlockMultilineString : public BlockBase
{
    Q_OBJECT
    Q_PROPERTY(QStringList Value READ GetValue WRITE SetValue)
    Q_PROPERTY(int Width READ GetWidth WRITE SetWidth)
    Q_PROPERTY(int Height READ GetHeight WRITE SetHeight)
    Q_PROPERTY(bool ResizeHeightWithDialog READ GetResizeHeightWithDialog WRITE SetResizeHeightWithDialog)
    Q_PROPERTY(bool ValueReadOnly READ IsValueReadOnly WRITE SetValueReadOnly)


public:
    /// @brief 构造函数，创建一个BlockMultilineString对象
    /// @param parent 父QWidget指针，默认为nullptr
    explicit BlockMultilineString(QWidget *parent = nullptr);
    ~BlockMultilineString();

    /// @brief 初始化UI
    void InitUi();

    /// @brief 获取文本列表
    /// @return QStringList类型的文本列表
    QStringList GetValue();

    /// @brief 获取每行文本的最大宽度
    /// @return int类型的每行文本的最大宽度
    int GetWidth();

    /// @brief 获取多行字符串显示的行数
    /// @return int类型的多行字符串显示的行数
    int GetHeight();

    /// @brief 获取高度是否随Dialog调整
    /// @return int类型的多行字符串显示的行数
    bool GetResizeHeightWithDialog();

    /// @brief 设置文本列表
    /// @param textList QStringList类型的文本列表
    void SetValue(const QStringList &textList);

    /// @brief 设置每行文本的最大宽度
    /// @param width int类型的每行文本的最大宽度
    void SetWidth(int width);

    /// @brief 设置多行字符串显示的行数
    /// @param height int类型的多行字符串显示的行数
    void SetHeight(int width);

    /// @brief 设置高度是否随Dialog调整
    /// @param height int类型的多行字符串显示的行数
    void SetResizeHeightWithDialog(bool resizeHeightWithDialog);

    bool IsValueReadOnly();

    void SetValueReadOnly(bool valueReadOnly);

signals:
    /// @brief 信号，当值改变时发出
    /// @param value QStringList类型的值
    void SignalValueChanged(QStringList value);
    
private:
    void ResizeHeight();

private:
    PowerMultilineString *m_edit;
};
