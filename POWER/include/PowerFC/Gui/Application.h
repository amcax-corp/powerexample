#pragma once

#include "PFCGlobal.h"
#include <App/Application.h>
#include <Base/Type.h>
#include <PFCGlobal.h>
#include <QCloseEvent>
#include <list>
#include <memory>
#include <qtmetamacros.h>
#include <string>
#include <vector>

namespace gui {

class Document;
class MainWindow;
class CommandManager;
class BaseView;
class MdiView;
class ViewProvider;
class ViewProviderDocumentObject;

class PFC_GUI_API Application
{
  public:
    Application();
    ~Application();

    boost::signals2::signal<void(const gui::Document&, bool)> SignalNewDocument;                             // signal on new Document
    boost::signals2::signal<void(const gui::Document&)> SignalDeleteDocument;                                // signal on deleted Document
    boost::signals2::signal<void(const gui::Document&)> SignalRelabelDocumenct;                              // signal on relabeling Document
    boost::signals2::signal<void(const gui::Document&)> SignalRenameDocument;                                // signal on rename Document
    boost::signals2::signal<void(const gui::Document&)> SignalActiveDocument;                                // signal on activating Document
    boost::signals2::signal<void(const gui::ViewProvider&)> SignalNewObject;                                 // signal on new Object
    boost::signals2::signal<void(const gui::ViewProvider&)> SignalDeletedObject;                             // signal on deleted Object
    boost::signals2::signal<void(const gui::ViewProvider&, const app::Property&)> SignalBeforeChangeObject;  // signal on changed Object
    boost::signals2::signal<void(const gui::ViewProvider&, const app::Property&)> SignalChangedObject;       // signal on changed object property
    boost::signals2::signal<void(const gui::ViewProvider&)> SignalRelabelObject;                             // signal on renamed Object
    boost::signals2::signal<void(const gui::ViewProvider&)> SignalActivatedObject;                           // signal on activated Object
    boost::signals2::signal<void(const std::string&)> SignalActivateWorkbench;                               // signal on activated workbench
    boost::signals2::signal<void(const std::string&)> SignalAddWorkbench;                                    // signal on added workbench
    boost::signals2::signal<void(const std::string&)> SignalRemoveWorkbench;                                 // signal on removed workbench
    boost::signals2::signal<void(const gui::Document&)> SignalShowHidden;                                    // signal on show hidden items
    boost::signals2::signal<void(const gui::MdiView*)> SignalActivateView;                                   // signal on activating view
    boost::signals2::signal<void(const gui::MdiView*)> SignalCloseView;                                   // signal on close view

    boost::signals2::signal<void(const gui::ViewProviderDocumentObject&)> SignalInEdit;                      // signal on entering in edit mode
    boost::signals2::signal<void(const gui::ViewProviderDocumentObject&)> SignalResetEdit;                   // signal on leaving edit mode

  protected:
    // 处理APP发射过来的信号
    void SlotNewDocument(const app::Document&, bool);
    void SlotDeleteDocument(const app::Document&);
    void SlotRelabelDocument(const app::Document&);
    void SlotRenameDocument(const app::Document&);
    void SlotActiveDocument(const app::Document&);
    void SlotShowHidden(const app::Document&);
    void SlotNewObject(const ViewProvider&);
    void SlotDeletedObject(const ViewProvider&);
    void SlotChangedObject(const ViewProvider&, const app::Property& Prop);
    void SlotRelabelObject(const ViewProvider&);
    void SlotActivatedObject(const ViewProvider&);
    void SlotInEdit(const gui::ViewProviderDocumentObject&);
    void SlotResetEdit(const gui::ViewProviderDocumentObject&);

  public:
    static void InitTypes();
    static void InitAppliaction();
    static void RunApplication();

    static gui::Application& Instance();


    friend PFC_GUI_API gui::Application* GetGuiApplication();

    gui::Document* GetDocument(const app::Document* appDoc) const;
    gui::Document* GetDocument(const std::string& doc_name) const;
    gui::ViewProvider* GetViewProvider(const app::DocumentObject*) const;
    gui::ViewProvider* GetViewProvider(const std::string& doc_name, const std::string& doc_object_name) const;
    void SetStyleSheet(const std::string& path);
    void ViewActivated(MdiView* view);
    gui::Document* ActiveDocument() const;
    void TryClose(QCloseEvent* e);
    bool ActivateWorkbench(const std::string& name);
    void ActivateView(const base::Type& type, bool create = false);

    void CheckoutWorkbench();

    //视图操作接口
    bool DispatchMsgToActiveView(std::string_view msg, const QVariant & input={}, QVariant* output=nullptr);

    // void AttachView(gui::BaseView* pcView);
    // void DetachView(gui::BaseView* pcView);

    void ViewClosed(MdiView* view);

    Document* EditDocment() const;
    void SetEditDocument(Document* doc);
    void SetActiveDocument(Document* doc);

    void UpdateActions(bool delay = false);

    void OnUpdate();
    void OnDocuemntClose(gui::Document* doc);

  private:
    static Application* gui_singleton;
    std::unique_ptr<struct ApplicationPrivate> d;
};

PFC_GUI_API gui::Application* GetGuiApplication();

}  // namespace gui