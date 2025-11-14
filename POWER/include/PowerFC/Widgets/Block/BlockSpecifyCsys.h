#pragma once

#include <QVector3D>
#include <Widgets/Block/BlockAbstractGeometry.h>
#include <Widgets/Block/BlockSelectionEnum.h>
#include <Widgets/PowerWidgetsConfig.h>

class PowerShowDetailSettingButton;
class PowerButton;
class PowerEnumeration;

class PW_API BlockSpecifyCsys : public BlockAbstractGeometry
{
    Q_OBJECT

    Q_PROPERTY(QString LabelText READ GetLabelText WRITE SetLabelText DESIGNABLE false)
    Q_PROPERTY(bool LabelTextVisibility READ IsLabelTextVisibility WRITE SetLabelTextVisibility DESIGNABLE false)
    Q_PROPERTY(QPixmap LabelBitmap READ GetLabelBitmap WRITE SetLabelBitmap DESIGNABLE false)
    Q_PROPERTY(bool LabelBitmapVisibility READ IsLabelBitmapVisibility WRITE SetLabelBitmapVisibility DESIGNABLE false)
    Q_PROPERTY(bool LabelVisibility READ IsLabelVisibility WRITE SetLabelVisibility FINAL DESIGNABLE false)
    Q_PROPERTY(QString TooltipTitle READ GetTooltipTitle WRITE SetTooltipTitle DESIGNABLE false)
    Q_PROPERTY(QString TooltipText READ GetTooltipText WRITE SetTooltipText DESIGNABLE false)
    Q_PROPERTY(QPixmap TooltipImage READ GetTooltipImage WRITE SetTooltipImage DESIGNABLE false)
    Q_PROPERTY(TooltipLayout TooltipLayout READ GetTooltipLayout WRITE SetTooltipLayout DESIGNABLE false)

    Q_PROPERTY(BlockAbstractGeometry::StepStatus StepStatus READ GetStepStatus WRITE SetStepStatus)
    // Q_PROPERTY(CsysType OutputType READ GetCsysType WRITE SetCsysType)

  public:
    explicit BlockSpecifyCsys(QWidget* parent = nullptr);

  public:
    enum CsysType
    {
        Cartesian,
        Cylindrical,
        Spherical
    };
    Q_ENUM(CsysType)

    const QList<QVector3D>& GetCsys() const;
    void SetCsys(const QVector3D& origin, const QVector3D& x_axis, const QVector3D& z_axis);

  Q_SIGNALS:
    void SignalGetCsys(const QList<QVector3D>&);
    void SignalSettingButtonClicked();

  public Q_SLOTS:
    void OnGetSettingDone(const QList<QVector3D>&);
    void Clear() override;

  protected:
    void SetFocusedDirectly(bool focused) override;
    void showEvent(QShowEvent* event) override;
  private:
    PowerButton* m_title;
    PowerShowDetailSettingButton* m_dialog_button;
    PowerEnumeration* m_csys_types;

    CsysType m_csys_type = Cartesian;

    QList<QVector3D> m_csys;
};