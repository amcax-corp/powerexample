#pragma once

#include <QDialogButtonBox>
#include <QPushButton>
#include <QHBoxLayout>
#include <Widgets/ContainerBlock/BlockDialog.h>

class PowerDialogButtonBox : public QDialogButtonBox
{
    Q_OBJECT

public:
    explicit PowerDialogButtonBox(QWidget *parent = nullptr);

    void SetButtonEnabled(QDialogButtonBox::StandardButton button, bool enabled);
    void SetButtonText(QDialogButtonBox::StandardButton button, const QString &text);
    void SetButtonFormat(BlockDialog::DialogButton format);

    QPushButton *GetButton(QDialogButtonBox::StandardButton button);

private:
    void InitButtonStyle();
};