#pragma once

#include <App/DocumentObject.h>
#include <QVector3D>
#include <Widgets/Block/BlockSpecifyPoint.h>
#include <Widgets/Block/BlockSpecifyVector.h>
#include <Widgets/PowerWidgetsConfig.h>

class PW_API BlockSpecifyAxis : public BlockBase
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

    Q_PROPERTY(QString PointLabelText READ GetPointLabelText WRITE SetPointLabelText)
    Q_PROPERTY(QString VectorLabelText READ GetVectorLabelText WRITE SetVectorLabelText)
    Q_PROPERTY(QString PointToolTipText READ GetPointToolTipText WRITE SetPointToolTipText)
    Q_PROPERTY(QPixmap PointToolTipImage READ GetPointToolTipImage WRITE SetPointToolTipImage)
    Q_PROPERTY(QString VectorToolTipText READ GetVectorToolTipText WRITE SetVectorToolTipText)
    Q_PROPERTY(QPixmap VectorToolTipImage READ GetVectorToolTipImage WRITE SetVectorToolTipImage)
    Q_PROPERTY(BlockAbstractGeometry::StepStatus StepStatus READ GetStepStatus WRITE SetStepStatus)

  public:
    explicit BlockSpecifyAxis(QWidget* parent = nullptr);

    QString GetPointToolTipText() const;
    void SetPointToolTipText(const QString& text);
    QPixmap GetPointToolTipImage() const;
    void SetPointToolTipImage(const QPixmap& image);
    QString GetVectorToolTipText() const;
    void SetVectorToolTipText(const QString& text);
    QPixmap GetVectorToolTipImage() const;
    void SetVectorToolTipImage(const QPixmap& image);

    QString GetPointLabelText() const;
    void SetPointLabelText(const QString& text);
    QString GetVectorLabelText() const;
    void SetVectorLabelText(const QString& text);

    BlockAbstractGeometry::StepStatus GetStepStatus() const;
    void SetStepStatus(BlockAbstractGeometry::StepStatus status);

    const std::tuple<QVector3D, QVector3D>& GetAxis() const;

  protected Q_SLOTS:
    void OnToolTipLayoutChanged(BlockBase::TooltipLayout layout);

    void OnPointChanged(const QVector3D& point);
    void OnVectorChanged(const QVector3D& vector);

  private:
    BlockSpecifyPoint* m_point_specify = nullptr;
    BlockSpecifyVector* m_vector_specify = nullptr;

    BlockAbstractGeometry::StepStatus m_step_status = BlockAbstractGeometry::Required;

    std::tuple<QVector3D, QVector3D> m_axis;

    app::DocumentObject* m_doc_object = nullptr;
};