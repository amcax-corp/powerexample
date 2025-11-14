#pragma once

#include <QWidget>
#include <Widgets/PowerWidgetsConfig.h>

class PowerFileOrFolderSelection;
class PW_API BlockFolderSelection : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QString Path READ GetPath WRITE SetPath)
    Q_PROPERTY(QString LabelText READ GetLabelText WRITE SetLabelText)
public:
    /// @brief 构造函数
    /// @param parent 
    BlockFolderSelection(QWidget *parent = nullptr);

    /// @brief 析构函数
    ~BlockFolderSelection();

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


signals:
    /// @brief 路径改变信号，返回当前路径
    void SignalPathChanged(const QString &path);

private slots:
    /// @brief 路径改变槽函数
    void OnPathChanged(const QString &path);

private:
    PowerFileOrFolderSelection *m_folder_selection;
};