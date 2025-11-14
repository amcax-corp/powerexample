#pragma once

#include <QWizard>
#include <QListWidget>
#include <QPixmap>
#include <Widgets/PowerWidgetsConfig.h>
#include <QLabel>

class PW_API BlockWizard : public QWizard
{
    Q_OBJECT

    // Q_PROPERTY(bool Initialize READ GetInitialize WRITE SetInitialize DESIGNABLE false USER false)
    // Q_PROPERTY(PowerDialogButtonBox::DialogButton dialogButtons READ dialogButtons WRITE setDialogButtons DESIGNABLE false USER false)
    Q_PROPERTY(QWizard::WizardStyle wizardStyle READ wizardStyle WRITE setWizardStyle DESIGNABLE false)
    Q_PROPERTY(QWizard::WizardOptions options READ options WRITE setOptions DESIGNABLE false)
    Q_PROPERTY(Qt::TextFormat titleFormat READ titleFormat WRITE setTitleFormat DESIGNABLE false)
    Q_PROPERTY(Qt::TextFormat subTitleFormat READ subTitleFormat WRITE setSubTitleFormat DESIGNABLE false)

    // Q_PROPERTY(int CurrentPage READ GetCurrentStep WRITE SetCurrentStep)
    Q_PROPERTY(bool ShowBannerArea READ ShowBannerArea WRITE SetShowBannerArea)
    Q_PROPERTY(bool ShowTaskNavigator READ ShowTaskNavigator WRITE SetShowTaskNavigator)
    Q_PROPERTY(QPixmap CurrentBannerImage READ GetCurrentBannerImage WRITE SetCurrentBannerImage)
    Q_PROPERTY(QPixmap CurrentStepIcon READ GetCurrentStepIcon WRITE SetCurrentStepIcon)
    Q_PROPERTY(QString CurrentStepText READ GetCurrentStepText WRITE SetCurrentStepText)

public:
    BlockWizard(QWidget *parent = nullptr);

    // int GetCurrentStep() const;
    // void SetCurrentStep(int step);
    bool ShowBannerArea() const;
    void SetShowBannerArea(bool show);
    bool ShowTaskNavigator() const;    
    void SetShowTaskNavigator(bool show);
    QPixmap GetCurrentBannerImage() const;
    void SetCurrentBannerImage(const QPixmap &image);
    QPixmap GetCurrentStepIcon() const;
    void SetCurrentStepIcon(const QPixmap &icon);
    QString GetCurrentStepText() const;
    void SetCurrentStepText(const QString &text);

public:
    // Container

signals:
    void SignalCurrentStepChanged(int step);

public slots:
    void OnPageAdded(int id);
    void OnPageRemoved(int id);

private:
    bool m_show_banner_area = true;
    bool m_show_task_navigator = true;

    // QWizard *m_wizard = nullptr;

    QList<QPixmap> m_banner_images = {QPixmap(), QPixmap()};
    QList<QPixmap> m_step_icons = {QPixmap(), QPixmap()};
    QStringList m_step_texts = {"", ""};
    QListWidget *m_task_navigator = nullptr;
};