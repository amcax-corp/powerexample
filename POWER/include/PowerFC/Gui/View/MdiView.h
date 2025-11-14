#pragma once

#include "ActiveObjectList.h"
#include <Base/BaseClass.h>
#include <PFCGlobal.h>
#include <QMainWindow>
#include <QString>

#include "View.h"

namespace gui {

class ActiveObjectList;
class MainWindow;

class PFC_GUI_API MdiView : public QMainWindow, public BaseView
{
    Q_OBJECT

    PFC_TYPESYSTEM_DECL_WITH_OVERRIDE()
  public:
    /** View constructor
     * Attach the view to the given document. If the document is zero
     * the view will attach to the active document. Be aware, there isn't
     * always an active document.
     */
    MdiView(gui::Document* pcDocument, QWidget* parent, Qt::WindowFlags wflags = Qt::WindowFlags());
    /** View destructor
     * Detach the view from the document, if attached.
     */
    ~MdiView() override;
    void OnRelabel(gui::Document* pDoc) override;
    virtual void ViewAll();
    QSize minimumSizeHint() const override;
    virtual QStringList UndoActions() const;
    virtual QStringList RedoActions() const;

    /// access getter for the active object list
    template<typename _T>
    inline _T GetActiveObject(const char* name, app::DocumentObject** parent = nullptr, std::string* subname = nullptr) const
    {
        return m_active_objects.GetObject<_T>(name, parent, subname);
    }
    void SetActiveObject(app::DocumentObject* doc, const char* n, const char* subname = nullptr)
    {
        m_active_objects.SetObject(doc, n, subname);
    }
    bool HasActiveObject(const char* n) const
    {
        return m_active_objects.HasObject(n);
    }
    bool IsActiveObject(app::DocumentObject* doc, const char* n, const char* subname = nullptr) const
    {
        return m_active_objects.HasObject(doc, n, subname);
    }

    /// MDI view mode enum
    enum ViewMode
    {
        Child,     /**< Child viewing, view is docked inside the MDI application window */
        TopLevel,  /**< The view becomes a top level window and can be moved outsinde the application window */
        FullScreen /**< The view goes to full screen viewing */
    };

    virtual void SetCurrentViewMode(ViewMode mode);
    ViewMode CurrentViewMode() const
    {
        return m_current_mode;
    }

    /// Message handler
    bool OnMessage(std::string_view msg, const QVariant & input={}, QVariant* output=nullptr) override;
    /// Message handler test
    bool OnHasMessage(const char* pMsg) const override;
    bool CanClose() override;

    QString BuildWindowTitle() const;

  Q_SIGNALS:
    void Message(const QString&, int);

  protected Q_SLOTS:
    virtual void SlotWindowStateChanged(MdiView* view);

  protected:
    void closeEvent(QCloseEvent* e) override;
    /** \internal */
    void changeEvent(QEvent* e) override;

  private:
    ActiveObjectList m_active_objects;
    ViewMode m_current_mode;
    Qt::WindowStates m_window_state;
    friend class MainWindow;
};

}  // namespace gui