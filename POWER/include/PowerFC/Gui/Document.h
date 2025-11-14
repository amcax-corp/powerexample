#pragma once
#include <App/Properties/PropertyString.h>
#include <Base/Persistence.h>
#include <Gui/View/MdiView.h>
#include <QString>
#include <boost/signals2.hpp>

namespace base {
class XMLReader;
class XMLWriter;
}  // namespace base

namespace app {
class Document;
class DocumentObject;
class Property;
class Transaction;
}  // namespace app

namespace gui {
enum class HighlightMode;
enum class TreeItemMode;
class BaseView;
class ViewProvider;
class Application;
class ViewProviderDocumentObject;
class ViewProviderDocumentObject3D;
}  // namespace gui

namespace gui {

class PFC_GUI_API Document : public base::Persistence
{
  public:
    // app::PropertyString CameraString;  // Path to the transient directory

    Document(app::Document* doc, Application* app);
    ~Document() override;

    /** @name I/O of the document */
    //@{
    virtual std::size_t GetEstimatedSize() const override;

    bool DoSave();
    bool DoSaveAs();
    bool DoSaveCopy();

    static void DoSaveAll();

    //!@brief 重载该方法，把属性数据保存到xml文档中
    virtual void Store(base::XMLWriter&, std::uint32_t version) const override;

    //!@brief 重载该方法，把属性数据从xml文档中恢复
    virtual void Restore(base::XMLReader&, std::uint32_t version) override;

    void ExportObjects(std::vector<app::DocumentObject*>&,
                       base::XMLWriter&,
                       std::uint32_t version);

    void ImportObjects(std::vector<app::DocumentObject*>&,
                       base::XMLReader&,
                       std::map<std::string, std::string> const& name_mapping,
                       std::uint32_t version);

    /// Add all root objects of the given array to a group
    //TODO void AddRootObjectsToGroup(const std::vector<app::DocumentObject*>&, app::DocumentObjectGroup& group_name);

    static bool CheckCanonicalPath(const std::map<app::Document*, bool>& doc_map);

    bool AskIfSavingFailed(const QString&);
    //@}

    /// Attach a view (get called by the MdiView constructor)
    void AttachView(gui::BaseView* view);
    /// Detach a view (get called by the MdiView destructor)
    void DetachView(gui::BaseView* view);

    app::Document* GetDocument() const;

    std::vector<ViewProviderDocumentObject3D*> GetViewProvider3DList() const;

    gui::ViewProviderDocumentObject* GetViewProvider(const app::DocumentObject*) const;
    gui::ViewProviderDocumentObject* GetViewProvider(std::string_view doc_object_name) const;
    std::vector<gui::ViewProviderDocumentObject*> GetViewProviders(std::string_view type) const;
    /// Get an Undo string vector with the Undo names
    std::vector<std::string_view> GetUndoVector() const;
    /// Get an Redo string vector with the Redo names
    std::vector<std::string_view> GetRedoVector() const;

    void Undo(int steps);
    void Redo(int steps);

    bool IsPerformingTransaction() const;

    /// Observer message from the App doc
    void SetModified(bool);
    bool IsModified() const;

    MdiView* GetActiveView() const;
    BaseView* GetView() const;
    
    /**
     * @brief 在View关闭时是否检查文档的修改，
     * 
     * @param check_modify 
     * @param check_link 
     * @return true 
     * @return false 
     */
    bool CanClose(bool check_modify = true, bool check_link = false);

    MdiView* CreateView(const base::Type& typeId);
    MdiView* CloneView(MdiView* view);

    void BeforeDelete();

    void OnUpdate();
    void OnRelabel();

    void SetEditViewProvider(ViewProvider* provider);
    void SetWorkbench(std::string& workbench);
    std::string GetCurWorkbench();

    // std::list<MdiView*> GetMDIViews() const;
    // std::list<MdiView*> GetMDIViewsOfType(const base::Type& typeId) const;

    // void AddViewProvider(gui::ViewProviderDocumentObject*);

  protected:
    /// This slot is connected to the App::Document::signalNewObject(...)
    void SlotNewObject(const app::DocumentObject&);
    void SlotDeletedObject(const app::DocumentObject&);
    void SlotChangedObject(const app::DocumentObject&, const app::Property&);
    void SlotRelabelObject(const app::DocumentObject&);
    
    /**
     * @brief app::Document::AddObject时发过来的信号，此函数中处理对应ViewProvider的事务备份
     * 
     * @param the_object 添加到doc中的对象
     * @param current_transaction 当前的事务
     */
    void SlotTransactionAddObject(const app::DocumentObject& the_object, app::Transaction* current_transaction);

    /**
     * @brief app::Document::RemoveObject时发过来的信号，此函数中处理对应ViewProvider的事务备份
     * 
     * @param the_object 移除的对象
     * @param current_transaction 当前的事务
     */
    void SlotTransactionRemoveObject(const app::DocumentObject& the_object, app::Transaction* current_transaction);

    void SlotActivatedObject(const app::DocumentObject&);
    void SlotStartRestoreDocument(const app::Document&);
    void SlotFinishRestoreDocument(const app::Document&);
    void SlotUndoDocument(const app::Document&);
    void SlotRedoDocument(const app::Document&);
    void SlotShowHidden(const app::Document&);
    void SlotFinishImportObjects(const std::vector<app::DocumentObject*>&);
    void SlotFinishRestoreObject(const app::DocumentObject& obj);
    void SlotRecomputed(const app::Document&);
    void SlotSkipRecompute(const app::Document& doc, const std::vector<app::DocumentObject*>& objs);
    void SlotTouchedObject(const app::DocumentObject&);
    void SlotChangePropertyEditor(const app::Document&, const app::Property&);

  public:
    mutable boost::signals2::signal<void(const gui::ViewProviderDocumentObject&)> SignalNewObject;                                                                                            // signal on new Object
    mutable boost::signals2::signal<void(const gui::ViewProviderDocumentObject&)> SignalDeletedObject;                                                                                        // signal on deleted Object
    mutable boost::signals2::signal<void(const gui::ViewProviderDocumentObject&, const app::Property&)> SignalChangedObject;                                                                  // signal on changed Object, the 2nd argument is the changed property of the referenced document object, not of the view provider */
    mutable boost::signals2::signal<void(const gui::ViewProviderDocumentObject&)> SignalRelabelObject;                                                                                        // signal on renamed Object
    mutable boost::signals2::signal<void(const gui::ViewProviderDocumentObject&)> SignalActivatedObject;                                                                                      // signal on activated Object
    mutable boost::signals2::signal<void(const gui::ViewProviderDocumentObject&)> SignalInEdit;                                                                                               // signal on entering in edit Mode
    mutable boost::signals2::signal<void(const gui::ViewProviderDocumentObject&)> SignalResetEdit;                                                                                            // signal on leaving edit Mode
    mutable boost::signals2::signal<void(const gui::ViewProviderDocumentObject&, const gui::HighlightMode&, bool, app::DocumentObject* parent, std::string& subname)> SignalHighlightObject;  // signal on changed Object, the 2nd argument is the highlite mode to Use
    mutable boost::signals2::signal<void(const gui::ViewProviderDocumentObject&, const gui::TreeItemMode&, app::DocumentObject* parent, std::string& subname)> SignalExpandObject;            // signal on changed Object, the 2nd argument is the highlite mode to Use
    mutable boost::signals2::signal<void(const gui::ViewProviderDocumentObject&)> SignalShowItem;                                                                                             // signal on changed ShowInTree property in view Provider
    mutable boost::signals2::signal<void(const gui::ViewProviderDocumentObject&)> SignalScrollToObject;                                                                                       // signal on scrolling to an Object
    mutable boost::signals2::signal<void(const gui::Document& doc)> SignalUndoDocument;                                                                                                       // signal on undo Document
    mutable boost::signals2::signal<void(const gui::Document& doc)> SignalRedoDocument;                                                                                                       // signal on redo Document
    mutable boost::signals2::signal<void(const gui::Document& doc)> SignalDeleteDocument;                                                                                                     // signal on deleting Document

  private:
    //检查其他文档中相同的事务ID
    bool CheckTransactionID(bool undo, int steps);

    void AddViewProvider(std::unique_ptr<ViewProviderDocumentObject>&& vp);

    friend class TransactionObjectViewProvider;

  private:
    std::unique_ptr<struct DocumentPrivate> d;
};

}  // namespace gui