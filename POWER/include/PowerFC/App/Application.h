#ifndef POWERFC_APP_APPLICATION_H_
#define POWERFC_APP_APPLICATION_H_
#include <stack>
#pragma once

#include <Base/Parameter.h>
#include <Base/XMLReader.h>
#include <Base/XMLWriter.h>
#include <PFCGlobal.h>
#include <boost/signals2.hpp>
#include <map>
#include <string>
#include <vector>

namespace app {

class Document;
class DocumentObject;
class Property;

/**
  * @name 导入导出类型相关接口管理，通过此机制，应用程序模块可以注册
  *  其能够处理的文件扩展名（文件类型）。
  *  文件扩展名和模块名称会被存储，当打开
  *  该类型文件时，对应的模块会被加载，并需要
  *  在OpenHandlerFactorySingleton中注册一个OpenHandler类。
  *  工作台加载完成后，会创建该类型的OpenHandler
  *  实例来加载文件。
  */
class PFC_APP_API ImportExportManager
{
  public:
    //@{
    //注册一个导入的文件类型和其对应的模块名称
    void AddImportType(std::string_view type, std::string_view module_name);
    //改变一个已注册的文件类型的模块名称
    void ChangeImportModuleName(std::string_view type, std::string_view old_module_name, std::string_view new_module_name);

    //获取支持导入file_type类型的模块名称列表
    std::vector<std::string> GetImportModules(std::string const& file_type) const;
    //获取所有模块名称列表
    std::vector<std::string> GetAllImportModules() const;

    //获取模块module_name支持的导入文件类型列表
    std::vector<std::string> GetImportTypes(std::string const& module_name) const;
    //获取所有导入文件类型列表
    std::vector<std::string> GetAllImportTypes() const;

    //获取导入file_type类型的文件过滤器，以及对应的模块名称
    std::map<std::string, std::string> GetImportFilters(std::string const& file_type) const;
    //获取所有导入文件类型的文件过滤器，以及对应的模块名称
    std::map<std::string, std::string> GetAllImportFilters() const;
    //@}

    //注册一个导出的文件类型和其对应的模块名称
    void AddExportType(std::string_view type, std::string_view module_name);
    //改变一个已注册导出的文件类型的模块名称
    void ChangeExportModuleName(std::string_view type, std::string_view old_module_name, std::string_view new_module_name);

    //获取支持导出file_type类型的模块名称列表
    std::vector<std::string> GetExportModules(std::string const& file_type) const;
    //获取所有支持导出的模块名称列表
    std::vector<std::string> GetAllExportModules() const;

    //获取模块module_name支持的导出文件类型列表
    std::vector<std::string> GetExportTypes(std::string const& module_name) const;
    //获取所有导出文件类型列表
    std::vector<std::string> GetAllExportTypes() const;

    //获取导出file_type类型的文件过滤器，以及对应的模块名称
    std::map<std::string, std::string> GetExportFilters(std::string const& file_type) const;

    //获取所有导出文件类型的文件过滤器，以及对应的模块名称
    std::map<std::string, std::string> GetAllExportFilters() const;

    ImportExportManager();
    ~ImportExportManager();

  private:
    struct Implementation;
    std::unique_ptr<Implementation> pimpl;
};

class PFC_APP_API Application : public ImportExportManager
{
  public:
    virtual ~Application();

  private:
    //向m_document_map中插入一个新的文档，内部会构建std::unique_ptr<app::Document>
    Document* InsertDocument(std::string_view name);

  public:
    // 创建一个新的文档
    Document* NewDocument(std::string_view name = {}, std::string_view user_name = {}, bool need_create_view = true, std::string_view workbench = "StandardWorkbench", bool is_temporary = false);
    // Document* NewDocument(std::string_view name, bool createView, bool tempDoc = false);
    // 关闭文档
    bool CloseDocument(const std::string_view name);
    // 打开指定文档
    Document* OpenDocument(std::filesystem::path const& file_name, bool create_view = true);
    // 获取当前激活文档
    Document* GetActiveDocument() const;

    /** 打开多个文档
      * @param file_names: 输入文件名列表
      * @param paths: 可选的输入文件路径列表，当路径与文件名不同时使用（主要用于恢复场景）
      * @param labels: 可选的文档标签列表（主要用于恢复场景）
      * @param errs: 可选的错误信息输出列表。如果提供此参数，函数将捕获所有Base::Exception异常
      * 并将错误信息存入该列表；否则遇到异常时将直接抛出
      * @param create_view: 是否在恢复时通知Gui模块创建视图
      *
      * @return 返回与每个输入文件对应的已打开文档对象列表（可能包含NULL表示打开失败）
      *
      * 此函数还会自动打开所有外部引用的文件
      */
    std::vector<Document*> OpenDocuments(const std::vector<std::filesystem::path>& file_names,
                                         const std::vector<std::filesystem::path>* paths = nullptr,
                                         const std::vector<std::string>* labels = nullptr,
                                         std::vector<std::string>* errs = nullptr,
                                         bool create_view = true);

  private:
    /// Path matching mode for getDocumentByPath()
    enum class PathMatchMode
    {

        /// 通过解析为绝对文件路径进行匹配
        MatchAbsolute = 0,
        /**
          * 首先尝试绝对路径匹配。若未找到，则解析为规范文件路径进行匹配，
          * 其中会解析所有中间的 '.'、'..' 和符号链接。
          */
        MatchCanonical = 1,
        /**
          * 与 MatchCanonical 相同，但如果通过规范路径找到文档（意味着该文档
          * 可以通过两个不同的绝对路径解析），则会打印警告且不返回找到的文档。
          * 这允许调用方有意将同一物理文件作为不同文档加载。
          */
        MatchCanonicalWarning = 2,
    };

    /** 尝试从已有文档中找到与给定路径匹配的文档
     *
     * @param path: file path
     * @param check_canonical: file path matching mode, @sa PathMatchMode.
     * @return Return the document found by matching with the given path
     */
    app::Document* GetDocumentByPath(std::filesystem::path const& path, PathMatchMode check_canonical = PathMatchMode::MatchAbsolute) const;

    /// open single document only
    app::Document* __OpenDocument(std::filesystem::path const& file_name,
                                  std::filesystem::path const& property_file_name,
                                  std::string_view label,
                                  bool is_main_doc,
                                  bool create_view,
                                  std::vector<std::string>&& object_names);

  public:
    // 根据名称检索文档
    Document* GetDocument(const std::string_view name) const;

    // gets the (internal) name of the document
    std::string_view GetDocumentName(const app::Document*) const;

    // 获取文档列表
    std::vector<Document*> GetDocuments() const;
    std::string GetUniqueDocumentName(std::string_view name, bool tempDoc);

    /// Add pending document to open together with the current opening document
    // 1表示成功添加，0表示当前不在Restoring状态，-1未添加
    int AddPendingDocument(std::string_view file_name, std::string_view object_name, bool allow_partial);

    // 设置当前活跃文档
    void SetActiveDocument(Document* pDoc);
    void SetActiveDocument(std::string_view name);
    // 关闭所有文档
    void CloseAllDocuments();
    // 是否正在打开/还原文档
    bool IsRestoring() const;
    /// 是否正在关闭所有文档
    bool IsClosingAll() const;

    /** @name Link handling */
    //@{

    enum GetLinkOption
    {
        /// Get all links (both directly and in directly) linked to the given object
        GetLinkRecursive = 1,
        /// Get link array element instead of the array
        GetLinkArrayElement = 2,
        /// Get linked object instead of the link, no effect if GetLinkRecursive
        GetLinkedObject = 4,
        /// Get only external links, no effect if GetLinkRecursive
        GetLinkExternal = 8,
    };

    enum class MessageOption
    {
        Quiet, /**< Suppress error. */
        Error, /**< Print an error message. */
        Throw, /**< Throw an exception. */
    };

    /** Check for link recursion depth
    *
    * @param depth: current depth
    * @param option: whether to throw exception, print an error message or quieten any output.
    * In the latter case the caller must check the returned value.
    *
    * @return Return the maximum remaining depth.
    *
    * The function uses an internal count of all objects in all documents as
    * the limit of recursion depth.
    */
    // int CheckLinkDepth(int depth, MessageOption option = MessageOption::Error);

    /** Return the links to a given object
    *
    * @param obj: the linked object. If NULL, then all links are returned.
    * @param option: @sa App::GetLinkOption
    * @param maxCount: limit the number of links returned, 0 means no limit
    */
    std::set<DocumentObject*> CollectLinksTo(
        const DocumentObject*,
        int options,
        int maxCount = 0) const;

    /// Check if there is any link to the given object
    bool HasLinksTo(const DocumentObject* obj) const;
    //@}

    base::ParameterManager& GetUserParameter();
    base::ParameterManager& GetSystemParameter();

    /**通过完整路径获取参数组
    * 这是一个便捷的方法来获取参数组：
    * \code
    * // 获取标准参数,User parameter对应GetUserParameter(),System parameter对应GetSystemParameter()
    * auto grp = app::GetApplication().GetUserParameter().GetGroup("BaseApp/Preferences/Document");
    * std::string dir             = grp->GetString("ProjectPath", "");
    * std::string camera_name     = grp->GetString("CameraName", "TempCamera.inc");
    * \endcode
    */
    base::ParameterGroup* GetParameterGroupByPath(const std::string& path);

    /**
     * @brief 从m_parameter_manager_map中获取参数集
     * 
     * @param name 
     * @return base::ParameterManager* 
     */
    base::ParameterManager* GetParameterSet(std::string const& name) const;

    const std::map<std::string, std::shared_ptr<base::ParameterManager>>& GetParameterSetList() const;

    base::ParameterManager* AddParameterSet(std::string const& name);
    void RemoveParameterSet(std::string const& name);

  private:
    void SaveParameterSetList();
    void LoadParameterSetList();
    std::filesystem::path GetParameterSetFilePath(std::string const& parameter_set_name) const;

  public:
    static std::string GetExecutableName();
    static std::string GetHomePath();
    static std::string GetTempPath();

    static std::string GetUserCachePath();
    static std::string GetUserConfigPath();
    static std::string GetUserAppDataDir();
    static std::string GetUserMacroDir();
    static std::string GetResourceDir();
    static std::string GetLibraryDir();
    static std::string GetHelpDir();
    static std::string GetWorkbenchDir();

    static std::string GetAppName();

    int64_t ApplicationPid() const;

    boost::signals2::signal<void(const Document&, bool)> SignalNewDocument;       // signal on new Document
    boost::signals2::signal<void(const Document&)> SignalBeforeDeletingDocument;  // signal on document getting deleted
    boost::signals2::signal<void()> SignalDocumentDeleted;                        // signal on already deleted Document
    boost::signals2::signal<void(const Document&)> SignalRelabelDocument;         // signal on relabeling Document (user name)
    boost::signals2::signal<void(const Document&)> SignalRenameDocument;          // signal on renaming Document (internal name)
    boost::signals2::signal<void(const Document&)> SignalActiveDocument;          // signal on activating Document
    boost::signals2::signal<void(const Document&)> SignalStoreDocument;           // signal on saving Document
    boost::signals2::signal<void(const Document&)> SignalRestoreDocument;         // signal on restoring Document
    boost::signals2::signal<void(const Document&)> SignalStartRestoreDocument;    // signal on starting to restore Document
    boost::signals2::signal<void(const Document&)> SignalFinishRestoreDocument;   // signal on restoring Document
    boost::signals2::signal<void(const Document&)> SignalPendingReloadDocument;
    boost::signals2::signal<void(const Document&, const std::filesystem::path&)> SignalStartStoreDocumentToFile;   // signal on starting to save Document
    boost::signals2::signal<void(const Document&, const std::filesystem::path&)> SignalFinishStoreDocumentToFile;  // signal on saved Document
    boost::signals2::signal<void(const Document&)> SignalUndoDocument;                                             // signal on undo in document
    boost::signals2::signal<void()> SignalUndo;                                                                    // signal on application wide undo
    boost::signals2::signal<void(const Document&)> SignalRedoDocument;                                             // signal on redo in document
    boost::signals2::signal<void()> SignalRedo;                                                                    // signal on application wide redo
    boost::signals2::signal<void(bool)> SignalBeforeCloseTransaction;                                              // signal before close/abort active transaction
    boost::signals2::signal<void(bool)> SignalCloseTransaction;                                                    // signal after close/abort active transaction
    boost::signals2::signal<void(const Document&)> SignalShowHidden;                                               // signal on show hidden items
    boost::signals2::signal<void()> SignalStartOpenDocument;                                                       // signal on start opening document(s)
    boost::signals2::signal<void()> SignalFinishOpenDocument;                                                      // signal on finished opening document(s)
    boost::signals2::signal<void(const app::Document&, const app::Property&)> SignalBeforeChangeDocument;          // signal before change of doc property
    boost::signals2::signal<void(const app::Document&, const app::Property&)> SignalChangedDocument;               // signal on changed doc property
    boost::signals2::signal<void(const app::DocumentObject&)> SignalNewObject;                                     // signal on new Object
    boost::signals2::signal<void(const app::DocumentObject&)> SignalDeletedObject;                                 // signal on deleted Object
    boost::signals2::signal<void(const app::DocumentObject&, const app::Property&)> SignalBeforeChangeObject;      // signal on changed Object
    boost::signals2::signal<void(const app::DocumentObject&, const app::Property&)> SignalChangedObject;           // signal on changed Object
    boost::signals2::signal<void(const app::DocumentObject&)> SignalRelabelObject;                                 // signal on relabeled Object
    boost::signals2::signal<void(const app::DocumentObject&)> SignalActivatedObject;                               // signal on activated Object
    boost::signals2::signal<void(const app::Document&)> SignalBeforeRecomputeDocument;                             // signal before recomputed document
    boost::signals2::signal<void(const app::Document&)> SignalRecomputed;                                          // signal on recomputed document
    boost::signals2::signal<void(const app::DocumentObject&)> SignalObjectRecomputed;                              // signal on recomputed document object
    boost::signals2::signal<void(const app::Document&, std::string_view)> SignalOpenTransaction;                   // signal on opened transaction
    boost::signals2::signal<void(const app::Document&)> SignalCommitTransaction;                                   // signal a committed transaction
    boost::signals2::signal<void(const app::Document&)> SignalAbortTransaction;                                    // signal an aborted transaction

    /** @name Signals of property changes
     * These signals are emitted on property additions or removal.
     * The changed object can be any sub-class of PropertyContainer.
     */
    //@{
    /// signal on adding a dynamic property
    boost::signals2::signal<void(const app::Property&)> SignalAppendDynamicProperty;
    /// signal on about removing a dynamic property
    boost::signals2::signal<void(const app::Property&)> SignalRemoveDynamicProperty;
    /// signal on about changing the editor mode of a property
    boost::signals2::signal<void(const app::Document&, const app::Property&)> SignalChangePropertyEditor;
    //@}

    public:
    /**
     * @brief 该方法用于检查link的深度，使用当前应用程序的对象数量估计一个深度限制，如果当前深度超出了，则报错。
     * 
     * @param depth 当前深度
     * @return int 
     */
    int CheckLinkDepth(int depth);

  protected:
    // 处理文档对象发射的信号
    void SlotBeforeChangeDocument(const app::Document&, const app::Property&);
    void SlotChangedDocument(const app::Document&, const app::Property&);
    void SlotNewObject(const app::DocumentObject&);
    void SlotDeletedObject(const app::DocumentObject&);
    void SlotBeforeChangeObject(const app::DocumentObject&, const app::Property& Prop);
    void SlotChangedObject(const app::DocumentObject&, const app::Property& Prop);
    void SlotRelabelObject(const app::DocumentObject&);
    void SlotActivatedObject(const app::DocumentObject&);
    void SlotUndoDocument(const app::Document&);
    void SlotRedoDocument(const app::Document&);
    void SlotRecomputedObject(const app::DocumentObject&);
    void SlotRecomputed(const app::Document&);
    void SlotBeforeRecompute(const app::Document&);
    void SlotOpenTransaction(const app::Document&, std::string_view);
    void SlotCommitTransaction(const app::Document&);
    void SlotAbortTransaction(const app::Document&);

    //处理Document::SignalStartStore信号，转发Application::
    void SlotStartSaveDocument(const app::Document&, const std::filesystem::path&);
    void SlotFinishSaveDocument(const app::Document&, const std::filesystem::path&);

    void SlotChangePropertyEditor(const app::Document&, const app::Property&);

  public:
    static void Init(int argc, char** argv);
    static void InitTypes();
    static void InitConfig(int argc, char** argv);
    static void InitAppliaction();
    static void Destruct();
    static void LogStatus();
    
    static std::list<std::string> ProcessFiles(const std::list<std::string>&);
    static void RunApplication();
    static int GetARGC();
    static char** GetARGV();
    static std::map<std::string, std::string>& Config();
    static bool HasARGV(const char* argv);

    static Application* Singleton();

    /** Setup a pending application-wide active transaction
    *
    * @param name: new transaction name
    * @param persist: by default, if the calling code is inside any invocation
    * of a command, it will be auto closed once all command within the current
    * stack exists. To disable auto closing, set persist=true
    *
    * @return The new transaction ID.
    *
    * Call this function to setup an application-wide transaction. All current
    * pending transactions of opening documents will be committed first.
    * However, no new transaction is created by this call. Any subsequent
    * changes in any current opening document will auto create a transaction
    * with the given name and ID. If more than one document is changed, the
    * tr*/
    int SetActiveTransaction(std::string_view name, bool persist = false);

    std::string_view GetActiveTransaction(int* transaction_id = nullptr) const;

    enum class TransactionClosingMode
    {
        Abort = 0,
        Commit = 1,
    };

    /**
    * 提交/中止当前活动事务
    * 
    * @param is_abort_else_commit 是否中止事务（true=中止，false=提交，默认为提交）
    * @param transaction_id 指定事务ID（0表示使用当前活动事务ID）
    * 
    * 除直接调用外，在以下情况会自动触发本函数：
    * 1. 新建具有不同ID的事务时
    * 2. 任何具有当前活动事务ID的事务被提交或中止时
    * 
    * 注意：当transaction_id=0时，默认处理最近的活动事务
    */
    void CloseActiveTransaction(bool is_abort_else_commit = false, int transaction_id = 0);

    void CloseActiveTransaction(TransactionClosingMode mode, int transaction_id = 0)
    {
        CloseActiveTransaction(mode == TransactionClosingMode::Abort, transaction_id);
    }

  private:
    Application(std::map<std::string, std::string>& config);

    static void LoadParameters();

    static std::unique_ptr<Application> s_app_singleton;
    static std::map<std::string, std::string> s_config;
    static int s_argc;
    static char** s_argv;

  private:
    std::map<std::string, std::string> m_config;

    static std::shared_ptr<base::ParameterManager> s_user_parameter_manager;
    static std::shared_ptr<base::ParameterManager> s_system_parameter_manager;
    std::map<std::string, std::shared_ptr<base::ParameterManager>> m_parameter_manager_map;

    std::map<std::string_view, std::unique_ptr<Document>> m_document_map;
    mutable std::map<std::filesystem::path, Document*> m_document_file_map;
    app::Document* m_active_document{nullptr};

    //挂起的文档
    std::deque<std::filesystem::path> m_pending_docs;
    std::deque<std::filesystem::path> m_pending_docs_to_reopen;
    std::map<std::filesystem::path, std::vector<std::string>> m_pending_doc_map;

    // To prevent infinite recursion of reloading a partial document due a truly
    // missing object
    // 字典，存储每个文档的重新加载尝试中加载的对象名，采用set，防止重复对象名
    std::map<std::filesystem::path, std::set<std::string>> m_document_reload_attempts;

    bool m_is_restoring{false};    //是否正在打开文档
    bool m_is_closing_all{false};  //是否正在关闭所有文档
    bool m_is_allow_partial{false};

    int m_objects_counts{-1};  //用于估计最大链接深度

    friend class AutoTransaction;

    std::string m_active_transaction_name;
    // int m_active_transaction_id{0};
    std::stack<int> m_transaction_id_stack{};
    // std::map<app::Document*, std::stack<int>> m_transaction_ids;
    int m_active_transaction_guard{0};
    bool m_active_transaction_use_temporary_name{false};

    friend class Document;
    friend class DocumentObject;

    /** @brief Helper class for App::Document to signal on close/abort transaction
     * 在构造时发送SignalBeforeCloseTransaction信号，在析构时发送SignalCloseTransaction信号。
     * 因此在准备关闭或中止事务前，创建一个TransactionSignaller对象即可。
     */
    class PFC_APP_API TransactionSignaller
    {
      public:
        struct ConstructParameters
        {
            TransactionClosingMode mode{TransactionClosingMode::Abort};
            bool need_signal{false};
        };

        TransactionSignaller(ConstructParameters const& params)
          : TransactionSignaller(params.mode, params.need_signal)
        {}

        TransactionSignaller(bool abort_or_commit, bool need_signal);
        TransactionSignaller(TransactionClosingMode mode, bool need_signal)
          : TransactionSignaller(mode == TransactionClosingMode::Abort, need_signal)
        {}
        ~TransactionSignaller();

      private:
        bool abort_or_commit;
    };
};

inline app::Application& GetApplication()
{
    return *app::Application::Singleton();
}

inline void OpenCommand(std::string_view cmd_name)
{
    app::GetApplication().SetActiveTransaction(cmd_name);
}
inline void CommitCommand()
{
    app::GetApplication().CloseActiveTransaction();
}
inline void AbortCommand()
{
    app::GetApplication().CloseActiveTransaction(true);
}

}  // namespace app

#endif