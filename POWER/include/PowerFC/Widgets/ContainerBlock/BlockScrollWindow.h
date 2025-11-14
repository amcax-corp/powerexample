#pragma once

#include <QScrollArea>
#include <Widgets/PowerWidgetsConfig.h>
class PW_API BlockScrollWindow : public QScrollArea
{
    Q_OBJECT
    Q_PROPERTY(int Height READ GetHeight WRITE SetHeight)
    Q_PROPERTY(bool ResizeHeightWithDialog READ GetResizeHeightWithDialog WRITE SetResizeHeightWithDialog)
public:
    BlockScrollWindow(QWidget *parent = nullptr);
    ~BlockScrollWindow();
    void AddContent(QWidget *widget);
    QWidget *GetContent();

    int GetHeight() const;
    bool GetResizeHeightWithDialog() const;

    void SetHeight(int height);
    void SetResizeHeightWithDialog(bool resizeHeightWithDialog);

signals:
    void SignalAddContent();

private:
    void ResizeBlock();

private:
    QWidget *m_center_widget;
    bool m_first_widget = false;
    int m_height = 3;
    bool m_resize_height_with_dialog = false;
};
