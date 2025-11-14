#ifndef POWERMULTILINESTRING_H
#define POWERMULTILINESTRING_H
#include <QTextEdit>
#include <QStringList>

class PowerMultilineString : public QTextEdit {
    Q_OBJECT
public:
    PowerMultilineString(QWidget *parent = nullptr);

    // 将 QStringList 复制到 BlockMultilineString
    void SetText(const QStringList &text_list);

    // 从 BlockMultilineString 获取值返回到 QStringList
    QStringList GetText() const;

    // 设置每行的最大字符数量
    void SetMaxCharsPerLine(int max_chars);
    // 获取每行的最大字符数量
    int GetMaxCharsPerLine() const;

    // 设置每行的高度
    void SetRowHeight(int height);
    // 获取每行的高度
    int GetRowHeight() const;

    // 设置整个 BlockMultilineString 显示的行数
    void SetVisibleRows(int rows);
    // 获取整个 BlockMultilineString 显示的行数
    int GetVisibleRows() const;

    void SetResizeHeightWithDialog(bool resizeHeightWithDialog);
    bool GetResizeHeightWithDialog() const;    

protected:
    void keyPressEvent(QKeyEvent *event) override;
    void resizeHeight();

private:
    int m_max_chars_perLine = 0;
    int m_row_height = 0;
    int m_visible_rows = 0;
    bool m_resize_height_with_dialog = false;

    // 截断文本以符合最大字符数量
    QString TruncateText(const QString &text, int max_chars);
    // 处理文本列表，进行截断和拼接
    QString ProcessTextList(const QStringList &text_List);
};

#endif // POWERMULTILINESTRING_H