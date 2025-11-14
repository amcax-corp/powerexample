#pragma once

#include <App/DocumentObject.h>
#include <Widgets/Block/BlockSpecifyAxis.h>
#include <Widgets/ContainerBlock/BlockDialog.h>
#include <Widgets/PowerWidgetsConfig.h>

namespace standard {
    class ViewProviderObjectAxis;
}

class PW_API PowerAxisSettingDialog : public BlockDialog
{
    Q_OBJECT

    friend class standard::ViewProviderObjectAxis;

  public:
    ~PowerAxisSettingDialog() = default;

  protected:
    explicit PowerAxisSettingDialog(app::DocumentObject* origin_doc, QWidget* parent = nullptr);

  public:
    QSize sizeHint() const override;

  protected:
    bool OnConfirmed() override;
    void OnResetted() override;
    void OnCanceled() override;

  private:
    void InitUI();

  private:
    app::DocumentObject* m_origin_doc = nullptr;

    double m_original_origin_x;
    double m_original_origin_y;
    double m_original_origin_z;

    double m_original_direction_i;
    double m_original_direction_j;
    double m_original_direction_k;

    BlockSpecifyAxis* m_axis_widget = nullptr;
};