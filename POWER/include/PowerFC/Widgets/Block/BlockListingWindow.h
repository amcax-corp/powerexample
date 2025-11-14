#pragma once

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTimer>
#include <QPoint>
#include <QMouseEvent>
#include <QTextEdit>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QFile>
#include <QVector>
#include <QTextCursor>
#include <QTextDocument>
#include <Widgets/PowerWidgetsConfig.h>
#include <QDialog>
#include <Widgets/Block/Private/PowerTitleBar.h>
#include <Widgets/ContainerBlock/BlockDialog.h>
#include <Widgets/Block/Private/PowerDialogButtonBox.h>

class PW_API BlockListingWindow : public BlockDialog
{
    Q_OBJECT
public:
    
    enum DeviceType {
        DeviceTypeWindow = 0,        // 输出到信息窗口（仅窗口输出）
        DeviceTypeFile = 1,          // 仅输出到文件
        DeviceTypeFileAndWindow = 2, // 同时输出到文件和窗口
        DeviceTypeNone = 3          // 不输出（丢弃所有数据）
    };

    BlockListingWindow(QWidget *parent = nullptr);
    ~BlockListingWindow();

    void InitUI();
    void InitConnect();

    void Open();              
    void Close();             
    void CloseWindow();       
    void WriteLine(const QString &msg);   
    void WriteFullline(const QString &msg); 
    bool IsOpen();           
    void SelectDevice(DeviceType deviceType, const QString &fileName); 
    DeviceType Device() const; 

    void UpdateMatches();
    void HighlightCurrentMatch();
    void ClearColor();

    QTextEdit* GetTextEdit() { return m_textedit; }

private slots:
    void OnTextChanged();
    void Onfindclicked();
    void Onclosefindclicked();
    void Onfindstringclicked();
    void OnLeftArrowClicked();
    void OnRightArrowClicked();
    void OnSaveButtonClicked();
    void OnPrintButtonClicked();

private:
    
    QVBoxLayout* m_mainLayout;
    QHBoxLayout* m_iconLayout;
    QVBoxLayout* m_textLayout;
    QTextEdit* m_textedit;
    QLabel* find_label;
    QLabel* empty_label;
    QLabel* title_label;
    QFrame *find_frame;
    QLineEdit* find_lineedit;
    QPushButton* m_savebutton;
    QPushButton* m_printbutton;
    QPushButton* m_findbutton;
    QPushButton* m_close_find_button;
    QPushButton* m_left_arrow_button;
    QPushButton* m_right_arrow_button;
    bool first_click_find_button = true;  // 第一次点击查找按钮的标识
    QString lineedit_context;  // 查找时使用的字符串
    bool m_needupdate = false;
    QTextDocument *document;
    QTextCursor m_findCursor;          // 当前匹配的文本游标
    QVector<QTextCursor> m_matches;      // 存储所有匹配的文本游标
    int m_currentMatchIndex = -1;        // 当前匹配项的索引

    DeviceType m_current_device = DeviceTypeWindow; 
    QString m_file_name = "";        
    QFile *m_file = nullptr;              
    bool m_is_open = false;              
};
  