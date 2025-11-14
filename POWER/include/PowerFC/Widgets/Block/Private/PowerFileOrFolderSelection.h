#pragma once

#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>

class PowerFileOrFolderSelection : public QWidget
{
    Q_OBJECT
public:

    PowerFileOrFolderSelection(QWidget *parent = nullptr);

    ~PowerFileOrFolderSelection();

    QString GetInitPath() const;

    void SetInitPath(const QString& path);

    QStringList GetFilter() const;

    void SetFilter(const QStringList& filter);

    int GetFilterIndex() const;

    void SetFilterIndex(int filter_index);

    void SetFileOrFolder(bool folder_flag);

    void SetLabelText(const QString& text);

    QString GetLabelText() const;

    void SetSaveFlag(bool save_flag);

    void SetEnabled(bool enabled);

    bool GetEnabled() const;

signals:
    void SignalFileSelected(const QString& selected_path);
    void SignalFolderSelected(const QString& path);
    void SignalSaveSelected(const QString& selected_path);
    void SignalLabelChanged();
    void SignalSaveChanged(const QString& save_path);

public slots:
    void OnFileOrFolderSelected();
    void OnLineEditEditingFinished();
    void OnClickSaved();

private:
    QLineEdit *m_lineedit;
    QPushButton *m_button;
    QStringList m_filter;
    int m_filter_index;
    QString m_init_path;
    QString m_selected_path;
    QLabel *m_file_label;
    bool m_folder_flag;
    bool m_save_flag = false;
};
