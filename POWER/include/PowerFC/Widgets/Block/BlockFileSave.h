#pragma once

#include <QWidget>
#include <Widgets/PowerWidgetsConfig.h>

class PowerFileOrFolderSelection;
class PW_API BlockFileSave : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QStringList Filter READ GetFilter WRITE SetFilter)
    Q_PROPERTY(int FilterIndex READ GetFilterIndex WRITE SetFilterIndex)
    Q_PROPERTY(QString Path READ GetPath WRITE SetPath)
    Q_PROPERTY(QString LabelText READ GetLabelText WRITE SetLabelText)

public:
    /// @brief 构造函数
    /// @param parent 
    BlockFileSave(QWidget *parent = nullptr);

    /// @brief 析构函数
    ~BlockFileSave();

    /// @brief 获取过滤器
    /// @return QStringList类型
    QStringList GetFilter() const;

    /// @brief 设置过滤器
    /// @param filter 例{.txt, .docx....}
    void SetFilter(const QStringList &filter);

    /// @brief 获取过滤器索引
    /// @return QString类型 0表示第一个过滤器，1表示第二个，依次类推，小于0默认第一个
    int GetFilterIndex() const;

    /// @brief 设置过滤器索引
    /// @param index
    void SetFilterIndex(int index);

    /// @brief 获取路径
    /// @return QString类型
    QString GetPath() const;

    /// @brief 设置路径
    /// @param path
    void SetPath(const QString &path);

    /// @brief 获取标签文本
    /// @return QString类型
    QString GetLabelText() const;

    /// @brief 设置标签文本
    /// @param text
    void SetLabelText(const QString &text);

    void SetEnable(bool enable);

    bool GetEnable() const;

signals:
    /// @brief 路径改变信号，返回当前路径
    void SignalPathChanged(const QString &path);

private slots:
    /// @brief 路径改变槽函数
    void OnPathChanged(const QString &path);

private:
    PowerFileOrFolderSelection *m_file_selection;




};