#pragma once

#include "MdiView.h"
#include <App/Properties/PropertyString.h>
#include <PFCGlobal.h>
#include <QImage>
#include <QOpenGLWidget>
#include <QWidget>

namespace gui {

struct View3DInventorPrivate;
class View3DInventorViewer;

class PFC_GUI_API View3DInventor : public MdiView
{
    Q_OBJECT

    PFC_TYPESYSTEM_DECL_WITH_OVERRIDE()

  public:
    // app::PropertyString CameraString;  // Path to the transient directory

    View3DInventor(gui::Document* pcDocument, QWidget* parent, Qt::WindowFlags wflags = Qt::WindowFlags());
    ~View3DInventor() override;

    /// Message handler
    bool OnMessage(std::string_view msg, const QVariant& input={}, QVariant* output=nullptr) override;
    /// Message handler test
    bool OnHasMessage(const char* pMsg) const override;

    void DeleteSelf() override;
    void OnRename(gui::Document* doc) override;
    void OnUpdate() override;
    void ViewAll() override;

    View3DInventorViewer* GetViewer() const;
  private slots:
    void SlotRefresh();
    void SlotViewAll();

  signals:
    void SigRefresh();
    void SigViewAll();

  private:
    struct View3DInventorPrivate* m_data;

    friend class View3DMessageProcessCenter;

    bool m_is_refresh;
    bool m_is_view_all;
    bool m_is_projection = true;
};

}  // namespace gui