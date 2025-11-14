#pragma once

#include <App/DocumentObject.h>
#include <QVector3D>
#include <Widgets/Block/BlockDouble.h>
#include <Widgets/Block/BlockEnumeration.h>
#include <Widgets/ContainerBlock/BlockDialog.h>
#include <Widgets/PowerWidgetsConfig.h>
#include <common/PointT.hpp>
#include <AMCAXRender.h>

class BlockSpecifyPoint;
class BlockSelectObject;
namespace standard {
class ViewProviderVector3D;
}

class PW_API PowerVectorSettingDialog : public BlockDialog
{
    Q_OBJECT

    friend class standard::ViewProviderVector3D;

  public:
    explicit PowerVectorSettingDialog(QVector3D vector, bool has_preview, QWidget* parent = nullptr);

  public:
    QSize sizeHint() const override;
    void SetVector(QVector3D vector);

    void SetEnumIndex(int index);
    std::string_view GetDocumentObjectName() const;
    const QVector3D GetCurrentVector() const;
    QVector3D GetEndPoint() const;

  protected:
    explicit PowerVectorSettingDialog(app::DocumentObject* origin_doc, QWidget* parent = nullptr);

  signals:
    void SignalConfirmed(const QVector3D& vector);

  protected Q_SLOTS:
    bool OnConfirmed() override;
    void OnResetted() override;
    void OnCanceled() override;

  private Q_SLOTS:
    void OnIValueChanged(double value);
    void OnJValueChanged(double value);
    void OnKValueChanged(double value);

  private:
    void InitGate();
    void InitUI();
    void ClearOutsideSelection();
    void SetDeimensionReadOnly(bool read_only);

  private:
    BlockDouble* m_specify_i;
    BlockDouble* m_specify_j;
    BlockDouble* m_specify_k;
    BlockSpecifyPoint *specify_point_first;
    BlockSpecifyPoint *specify_point_second;
    BlockSelectObject *specify_face;
    bool m_first_point_specified = false;
    bool m_second_point_specified = false;
   
    PowerEnumeration* m_enum_select_types;

    app::DocumentObject* m_specify_doc = nullptr;
    app::DocumentObject* m_tmp_doc = nullptr;

    double m_original_i = 0.0;
    double m_original_j = 0.0;
    double m_original_k = 0.0;

    QVector3D m_end_point;
    std::optional<AMCAXRender::EntityId> m_plugin_id;

    bool m_pickup_complete = false;
};