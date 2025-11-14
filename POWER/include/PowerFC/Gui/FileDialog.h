#ifndef POWERFC_GUI_FILEDIALOG_H
#define POWERFC_GUI_FILEDIALOG_H
#pragma once
#include <PFCGlobal.h>
#include <QCompleter>
#include <QFileDialog>
#include <QFileIconProvider>
#include <QFileSystemModel>
#include <QPointer>


class QButtonGroup;
class QDialogButtonBox;
class QGridLayout;
class QGroupBox;
class QHBoxLayout;
class QLineEdit;
class QSpacerItem;

namespace gui {

class PFC_GUI_API FileDialog : public QFileDialog
{
    Q_OBJECT
  public:
    static QString getOpenFileName(QWidget* parent = nullptr,
                                   const QString& caption = {},
                                   const QString& dir = {},
                                   const QString& filter = {},
                                   QString* selected_filter = nullptr,
                                   QFileDialog::Options options = {});
    static QStringList getOpenFileNames(QWidget* parent = nullptr,
                                        const QString& caption = {},
                                        const QString& dir = {},
                                        const QString& filter = {},
                                        QString* selected_filter = nullptr,
                                        QFileDialog::Options options = {});

    static QString getSaveFileName(QWidget* parent = nullptr,
                                   const QString& caption = {},
                                   const QString& dir = {},
                                   const QString& filter = {},
                                   QString* selected_filter = nullptr,
                                   QFileDialog::Options options = {});
    static QString getExistingDirectory(QWidget* parent = nullptr,
                                        const QString& caption = {},
                                        const QString& dir = {},
                                        QFileDialog::Options options = QFileDialog::ShowDirsOnly);

    static QString GetWorkingDirectory();
    static void SetWorkingDirectory(const QString& dir);

    static QString RestoreLocation();
    static void StoreLocation(const QString& dir);

    explicit FileDialog(QWidget* parent = nullptr);
    ~FileDialog();

    void accept() override;

  private Q_SLOTS:
    void OnSelectedFilter(const QString&);

  private:
    bool HasSuffix(const QString&) const;
    
    //获取侧边栏要显示的目录
    static QList<QUrl> FetchSidebarUrls();
};

}  // namespace gui


namespace gui{

/**FileOptionsDialog 类提供了一个可扩展的文件对话框，可在右侧或底部添加额外的小部件，
 * 并通过"扩展"按钮显示或隐藏该部件。
 */
class PFC_GUI_API FileOptionsDialog : public QFileDialog
{
    Q_OBJECT

public:
    // 扩展部件位置枚举
    enum ExtensionPosition {
        ExtensionRight    = 0,  // 右侧扩展
        ExtensionBottom   = 1   // 底部扩展
    };

    // 构造函数
    FileOptionsDialog(QWidget* parent, Qt::WindowFlags);
    // 析构函数
    ~FileOptionsDialog() override;

    // 重写接受按钮行为
    void accept() override;

    // 设置选项部件
    void SetOptionsWidget(ExtensionPosition pos, QWidget*, bool show = false);
    // 获取选项部件
    QWidget* GetOptionsWidget() const;

protected Q_SLOTS:
    // 切换扩展部件显示状态
    void ToggleExtension();

private:
    QSize m_old_size;                   // 保存原始尺寸
    ExtensionPosition m_extension_position{ExtensionRight};  // 扩展部件位置
    QPushButton* m_extension_button{nullptr};    // 扩展按钮
    QPointer<QWidget> m_extension_widget{nullptr}; // 扩展部件指针
};
}

namespace gui{
//该类提供FileDialog的文件图标
class FileIconProvider : public QFileIconProvider
{
public:
    FileIconProvider();
    ~FileIconProvider() override;

    QIcon icon(IconType type) const override;
    QIcon icon(const QFileInfo & info) const override;
    QString type(const QFileInfo & info) const override;
};
}

namespace gui{
/**
 * @brief FileChooser 类提供了一个带右侧按钮的文本输入框，用于选择文件或目录。
 */
class PFC_GUI_API FileChooser : public QWidget
{
    Q_OBJECT

public:
    // 模式枚举：文件或目录
    enum Mode { File, Directory };
    // 接受模式枚举：打开或保存
    enum AcceptMode { AcceptOpen, AcceptSave };

    Q_ENUM( Mode )
    Q_PROPERTY(Mode mode READ GetMode WRITE SetMode NOTIFY ModeChanged)  // 模式属性
    Q_ENUM( AcceptMode )
    Q_PROPERTY(AcceptMode m_accept_mode READ GetAcceptMode WRITE SetAcceptMode NOTIFY AcceptModeChanged)  // 接受模式属性
    Q_PROPERTY(QString m_file_name READ GetFileName WRITE SetFileName NOTIFY FileNameChanged)  // 文件名属性
    Q_PROPERTY(QString m_filter READ GetFilter WRITE SetFilter NOTIFY FilterChanged)  // 过滤器属性
    Q_PROPERTY(QString m_button_text READ GetButtonText WRITE SetButtonText NOTIFY ButtonTextChanged)  // 按钮文本属性

public:
    explicit FileChooser(QWidget * parent = nullptr);  // 构造函数
    ~FileChooser() override;  // 析构函数

    
    //@return 获取当前设置的过滤器。
    QString GetFilter() const;

    
    //@return 获取当前选择的文件名/路径。
    QString GetFileName() const;

    
    //@return 获取当前模式：文件模式返回true，目录模式返回false。
    Mode GetMode() const;

    
    //@return 获取按钮上显示的文本。

    QString GetButtonText() const;

    
    //@return* 设置接受模式（打开/保存）。
    void SetAcceptMode(AcceptMode mode);
    
    //@return* 获取当前接受模式。
    AcceptMode GetAcceptMode() const {
        return m_accept_mode;
    }

    public Q_SLOTS:
    virtual void SetFileName( const QString &fn );
    virtual void SetMode( gui::FileChooser::Mode m );
    virtual void SetFilter ( const QString & );
    virtual void SetButtonText ( const QString & );

Q_SIGNALS:
    void FileNameChanged( const QString & );
    void FileNameSelected( const QString & );
    void FilterChanged(const QString&);
    void ButtonTextChanged(const QString&);
    void ModeChanged(gui::FileChooser::Mode);
    void AcceptModeChanged(gui::FileChooser::AcceptMode);

private Q_SLOTS:
    void OnChooseFile();
    void OnEditingFinished();

protected:
    void resizeEvent(QResizeEvent*) override;

private:
    QLineEdit *m_line_edit{nullptr};
    QCompleter *m_completer{nullptr};
    QFileSystemModel *m_filesystem_model{nullptr};
    QPushButton *m_button{nullptr};
    Mode m_mode{Mode::File};
    AcceptMode m_accept_mode{AcceptMode::AcceptOpen};
    QString m_filter{};
};
}


namespace gui{
/**
 * SelectModule 类提供了一组单选按钮，用于选择应该处理特定文件类型的模块。
 */
class PFC_GUI_API DialogSelectModule : public QDialog
{
    Q_OBJECT

public:
    DialogSelectModule(const QString& type, const QMap<QString, QString>&, QWidget* parent);  // 构造函数
    ~DialogSelectModule() override;  // 析构函数
    QString GetModule() const;  // 获取选择的模块

    /**@name 导入/导出处理器
     * 这些方法接受一个文件名或文件名列表，并返回一个文件名与对应Python模块的映射表，该模块将用于打开文件。
     */
    //@{
    static QMap<QString, QString> ExportHandler(const QString& file_name, const QString& filter=QString());  // 导出处理器(单个文件)
    static QMap<QString, QString> ExportHandler(const QStringList& file_names, const QString& filter=QString());  // 导出处理器(多个文件)
    static QMap<QString, QString> ImportHandler(const QString& file_name, const QString& filter=QString());  // 导入处理器(单个文件)
    static QMap<QString, QString> ImportHandler(const QStringList& file_names, const QString& filter=QString());  // 导入处理器(多个文件)
    //@}

    void accept() override;  // 重写接受操作
    void reject() override;  // 重写拒绝操作

private Q_SLOTS:
    void OnButtonClicked();  // 按钮点击槽函数

private:
    struct Private;
    QScopedPointer<Private> d;

};
}

#endif
