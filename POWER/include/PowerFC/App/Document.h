#pragma once
#include <App/Properties/PropertyBool.h>
#include <App/Properties/PropertyEnumeration.h>
#include <App/Properties/PropertyFilePath.h>
#include <App/Properties/PropertyInteger.h>
#include <App/Properties/PropertyMap.h>
#include <App/Properties/PropertyString.h>
#include <App/Properties/PropertyUuid.h>
#include <App/PropertyContainer.h>
#include <boost/signals2.hpp>
#include <memory>

namespace base {
class OStorage;
class IStorage;
}  // namespace base

namespace app {
class Application;
class DocumentObject;
class TransactionalObject;
class Transaction;

class PFC_APP_API Document : public app::PropertyContainer
{
    PFC_PROPERTY_DECL_WITH_OVERRIDE();

  public:
    //用于控制读写的版本，默认为1
    static std::uint32_t GetVersion();

  public:
    // clang-format off
      enum  class Status
      {
          SKIP_RECOMPUTE = 0,
          KEEP_TRAILING_DIGITS = 1,
          CLOSABLE = 2,
          RESTORING = 3,
          RECOMPUTING = 4,
          PARTIAL_RESTORE = 5,
          IMPORTING = 6,
          PARTIAL_DOC = 7,
          ALLOW_PARTIAL_RECOMPUTE = 8,    // allow recomputing editing object if SkipRecompute is set
          TEMP_DOC = 9,                  // Mark as temporary document without prompt for save
          RESTORE_ERROR = 10,
          LINK_STAMP_CHANGED = 11,        // Indicates during restore time if any linked document's time stamp has changed
          IGNORE_ERROR_ON_RECOMPUTE = 12,  // Don't report errors if the recompute failed
          RECOMPUTE_ON_RESTORE = 13,      // Mark pending recompute on restore for migration purposes
      };
    // clang-format on

    PropertyString Label;  //文档名称，显示在Tab上

    PropertyFilePath FileName;  //文档的文件路径，新建的文档，保存之后会确定该属性值

    PropertyString CreatedBy;  //创建者

    PropertyString CreationDate;  //创建时间

    PropertyString LastModifiedBy;  //上次修改用户名

    PropertyString LastModifiedDate;  //上次修改时间

    PropertyString Company;  //组织

    PropertyEnumeration UnitSystem;  //单位制

    PropertyString Comment;  //备注，utf-8多行文本

    PropertyString Id;  //文档id,像Part number

    PropertyUuid Uid;  //文档唯一标识符

    PropertyString License;  //Full name of the licence

    PropertyString LicenseURL;

    PropertyMap Meta;  //元数据，key-value

    PropertyMap Material;  //材质，在Material Module中使用

    PropertyFilePath TransientDirectory;  //文档打开时创建的临时目录，该属性为只读的

    // PropertyLink Top;//Top Object of the Document //文档的根对象

    PropertyString TipName;

    PropertyBool ShowHidden;  //是否在TreeView中显示隐藏的对象

    PropertyBool UseHasher;  //是否使用Hasher命名拓扑对象

    PropertyString Workbench;

    //文档属性发生改变前，发送的信号
    boost::signals2::signal<void(const app::Document&, const app::Property&)> SignalBeforePropertyChanging;
    //文档属性发生改变后，发送的信号
    boost::signals2::signal<void(const app::Document&, const app::Property&)> SignalPropertyChanged;
    //文档的某个对象新建时，发送的信号
    boost::signals2::signal<void(const app::DocumentObject&)> SignalNewObject;
    //文档的某个对象删除时，发送的信号
    boost::signals2::signal<void(const app::DocumentObject&)> SignalDeletingObject;

    //文档的某个对象属性发生改变前，发送的信号
    boost::signals2::signal<void(const app::DocumentObject&, const app::Property&)> SignalBeforeObjectPropertyChanging;

    //文档的某个对象属性发生改变后，发送的信号
    boost::signals2::signal<void(const app::DocumentObject&, const app::Property&)> SignalObjectPropertyChanged;

    //人为调用DocumentObject::Touch时，发送该信号
    boost::signals2::signal<void(const app::DocumentObject&)> SignalObjectTouched;
    //文档的某个对象重命名时，发送的信号
    boost::signals2::signal<void(const app::DocumentObject&)> SignalRelabelObject;

    //文档的某个对象被激活时，发送的信号
    boost::signals2::signal<void(const app::DocumentObject&)> SignalObjectActivated;

    //序列化相关的信号
    boost::signals2::signal<void(std::shared_ptr<base::OStorage>)> SignalDocumentStored;
    boost::signals2::signal<void(std::shared_ptr<base::IStorage>)> SignalDocumentRestored;

    //导出一些对象时，发送的信号
    boost::signals2::signal<void(const std::vector<app::DocumentObject*>&, base::Writer&)> SignalExportObjects;
    boost::signals2::signal<void(const std::vector<app::DocumentObject*>&, base::Writer&)> SignalExportViewObjects;

    boost::signals2::signal<void(const std::vector<app::DocumentObject*>&, base::XMLReader&)> SignalImportObjects;
    boost::signals2::signal<void(const std::vector<app::DocumentObject*>&, base::Reader&, const std::map<std::string, std::string>&)> SignalImportViewObjects;
    //完成对象导入时，发送的信号
    boost::signals2::signal<void(const std::vector<app::DocumentObject*>&)> SignalFinishImportObjects;

    //开始存储文档时，发送的信号
    boost::signals2::signal<void(const app::Document&, std::filesystem::path const&)> SignalStartStoreToFile;
    //完成存储文档时，发送的信号
    boost::signals2::signal<void(const app::Document&, std::filesystem::path const&)> SignalFinishStoreToFile;

    boost::signals2::signal<void(const app::DocumentObject&)> SignalFinishRestoreObject;

    //重新计算前，发送的信号
    boost::signals2::signal<void(const app::Document&)> SignalBeforeRecomputing;

    //一些对象被重新计算后，发送的信号
    boost::signals2::signal<void(const app::Document&, const std::vector<app::DocumentObject*>&)> SignalObjectsRecomputed;

    //对象被重新计算后，发送的信号
    boost::signals2::signal<void(const app::DocumentObject&)> SignalObjectRecomputed;

    //在AddObject进行事务备份时，发送该信号，通知gui::Document对对应的ViewProvider进行事务备份
    boost::signals2::signal<void(app::DocumentObject&, Transaction*)> SignalTransactionAddObject;

    //在RemoveObject进行事务备份时，发送该信号，通知gui::Document对对应的ViewProvider进行事务备份
    boost::signals2::signal<void(app::DocumentObject&, Transaction*)> SignalTransactionRemoveObject;

    //Undo时，发送的信号
    boost::signals2::signal<void(const app::Document&)> SignalUndo;

    //Redo时，发送的信号
    boost::signals2::signal<void(const app::Document&)> SignalRedo;

    //新打开一个事务，发送的信号
    boost::signals2::signal<void(const app::Document&, std::string_view)> SignalTransactionOpened;

    //提交文档的事务，发送的信号
    boost::signals2::signal<void(const app::Document&)> SignalTransactionCommitted;

    //终止文档的事务，发送的信号
    boost::signals2::signal<void(const app::Document&)> SignalTransactionAborted;

    boost::signals2::signal<void(const app::Document&, const app::Property&)> SignalChangePropertyEditor;

    boost::signals2::signal<void(std::string)> SignalLinkXValueSet;

    //执行保存文档到已打开的文件名
    bool DoSave();

    //执行保存文档到指定的文件名
    bool DoSave(std::filesystem::path const& file);

    bool DoSaveAs(std::filesystem::path const& file);

    bool DoSaveCopy(std::filesystem::path const& file) const;

    void RestoreFromFile(std::filesystem::path filepath = {},
                         bool delay_signal = false,
                         std::vector<std::string> const& object_names = {});

    bool AfterRestore(bool check_partial = false);

    bool AfterRestore(const std::vector<app::DocumentObject*>&, bool check_partial = false);

    enum class ExportStatus
    {
        NotExporting,
        Exporting
    };

    bool IsExporting(const app::DocumentObject* object) const;

    void ExportObjects(const std::vector<app::DocumentObject*>& objects, std::ostream&);

    void ExportGraphviz(std::ostream& out);

    std::vector<app::DocumentObject*> ImportObjects(base::XMLReader& reader);

    bool IsSaved() const;

    //!@brief 获取文档的名称
    std::string_view GetName() const;

    //!@brief 获取应用程序的版本
    std::string_view GetProgramVersion() const;

    /**
     * @brief 返回文件名
     * 对于已保存的文档，这将返回存储在属性 'Filename' 中的内容。
     * 对于未保存的临时文件，这将返回属性 'TransientDir' 中的内容。
     * @return std::string_view 
     */
    std::filesystem::path const& GetFileName() const;

    std::size_t GetEstimatedSize() const override;

    void Store(base::XMLWriter& writer, std::uint32_t) const override;

    void Restore(base::XMLReader& reader, std::uint32_t) override;

    //对象操作接口
    /**
     * @brief  向此文档添加一个类型为class_name、名称为object_name（ASCII）的对象，并将其设置为活动对象。
     * 
     * @param class_name 要创建的对象的类型
     * @param object_label 该值会影响object.name_in_document和Label，
     *        如果非空，则基于object_label否则基于class_name生成唯一的，object.name_in_document
     *        如果非空，则设置object_label为Label，否则设置name_in_document为Label
     * @param is_new 如果为false，则不调用 DocumentObject::SetupObject() 回调（默认为 true）
     * @param view_provider_class_name 
     * @param is_partial 指示此对象是否打算被部分加载
     * @return DocumentObject* 
     */
    DocumentObject* AddObject(std::string_view class_name,
                              std::string_view object_label = {},
                              bool is_new = true,
                              std::string_view view_provider_class_name = {},
                              bool is_partial = false);
    /**
     * @brief 批量添加对象
     * 
     * @param class_name 要创建的对象的类型
     * @param object_names 对象名称列表
     * @param is_new 如果为false，则不调用 DocumentObject::SetupObject() 回调（默认为 true）
     * @return std::vector<DocumentObject*> 
     */
    std::vector<DocumentObject*> AddObjects(std::string_view class_name,
                                            std::vector<std::string> object_labels = {},
                                            bool is_new = true);

    //!@brief 根据对象名从文档中移除一个对象
    void RemoveObject(std::string_view object_name);

    /**
     * @brief 将一个已存在的对象（名称为object_name，ASCII）添加到此文档中，并将其设置为活动对象。
     * 这是上述函数的重载版本，可以用于在外部创建一个对象，然后将其添加到文档中。
     * @throw 传递的特征必须尚未添加到任何文档中，否则会抛出异常。
     * @param object 已创建的对象
     */
    DocumentObject* AddObject(std::unique_ptr<DocumentObject> object, std::string_view object_label={});

    /**
     * @brief 将对象从另一个文档复制到此文档中
     * 
     * @param objects 
     * @param recursive 如果为 true，则此对象依赖的所有对象也会被复制。默认情况下，recursive 为 false。
     * @param return_all 如果为 true，则返回所有复制的对象，包括通过递归搜索自动包含的对象。如果为 false，则仅返回与输入对象对应的复制对象。
     * @return std::vector<DocumentObject*> 返回复制的对象列表。
     */
    std::vector<DocumentObject*> CopyObject(const std::vector<DocumentObject*>& objects,
                                            bool recursive = false,
                                            bool return_all = false);
    /**
     * @brief 将一个对象从另一个文档移动到此文档中
     * 
     * @param object 
     * @param recursive 如果 recursive 为 true，则此对象依赖的所有对象也会被移动。默认情况下，recursive 为 false。
     * @return DocumentObject* 
     */
    DocumentObject* MoveObject(DocumentObject* object, bool recursive = false);

    //!@brief 返回当前的活动对象
    DocumentObject* GetActiveObject() const;

    // DocumentObject* GetObject(std::string const& name) const;

    DocumentObject* GetObject(std::string_view name) const;
    // {
    //   // return GetObject(std::string{name});
    // }

    //!@brief 返回文档中具有给定id的对象
    DocumentObject* GetObjectByID(unsigned long id) const;

    //!@brief 返回文档是否包含object
    bool IsIn(const DocumentObject* object) const;

    bool HasObject(const DocumentObject* object) const
    {
        return IsIn(object);
    }

    bool HasObject(std::string const& name) const;

    //!@brief 返回给定对象的名字
    std::string_view GetObjectName(DocumentObject* object) const;

    //!@brief 根据给定的输入返回一个文档中唯一的名字
    std::string GetUniqueObjectName(std::string_view trivial_name) const;

    /**
     * @brief 返回一个格式为 prefix_number（name_number） 的名字。d 指定数字的位数。
     * 生成一个唯一的名称，格式为 前缀_数字，数字部分会根据当前文档中已存在的对象自动递增，以确保名称的唯一性。
     * @param name 前缀的部分
     * @param d 数字部分的位数。例如，d = 3 时，数字部分会填充为 001、002 等。
     * @return std::string 
     */
    std::string GetStandardObjectName(std::string_view name, int d) const;

    //!@brief 返回文档中所有的对象列表，包含依赖的对象
    std::vector<DocumentObject*> GetDependingObjects() const;

    //!@brief 返回对象列表
    std::vector<DocumentObject*> GetObjects() const;

    //!@brief 返回文档中给定类型的对象列表
    std::vector<DocumentObject*> GetObjectsOfType(const base::Type& type_id) const;

    //!@brief 返回文档中给定类型的对象数量
    std::size_t GetNumberOfObjects(base::Type type_id) const;

    //!@brief 返回文档中所有对象的数量
    std::size_t GetNumberOfObjects() const;

    /**
     * @brief 根据类型、名称和标签查找文档中的对象
     * 
     * @param type_id 类型
     * @param object_name 对象名
     * @param label 标签名
     * @return std::vector<DocumentObject*> 
     */
    std::vector<DocumentObject*> FindObjects(const base::Type& type_id,
                                             std::string_view object_name,
                                             std::string_view label) const;

    //状态修改接口
    //!@brief 移除所有修改, 在此调用之后，文档将重新变为有效状态。
    void PurgeTouched();

    //!@brief 检查文档是否有任何一个对象被修改
    bool IsTouched() const;

    //!@brief 检查文档中是否任何一个对象必须要执行
    bool MustExecute() const;

    //!@brief 返回所有被修改的对象
    std::vector<app::DocumentObject*> GetTouched() const;

    //!@brief 设置当前对象是否可关闭，默认是on。
    void SetClosable(bool);

    //!@brief 检查文档是否可关闭
    bool IsClosable() const;

    /**
     * @brief 对于修改的特征进行重新计算，并返回成功重新计算的对象数量
     * 
     * @param objects 指定要重新计算的对象列表，如果为空，则从所有对象中检查哪些对象需要重新计算
     * @param force 
     * @param has_error 
     * @param options 
     * @return int 
     */
    int Recompute(const std::vector<app::DocumentObject*>& objects = {},
                  bool force = false,
                  bool* has_error = nullptr,
                  int options = 0);

    //!@brief 只重新计算一个对象，并返回是否成功
    bool RecomputeObject(app::DocumentObject* object, bool recursive = false);

    //!@brief 返回给定对象的错误描述
    std::string_view GetErrorDescription(const app::DocumentObject* object) const;

    bool TestStatus(Status s) const;

    void SetStatus(Status pos, bool on);

    /** 用于 UNDO（撤销）、REDO（重做）和事务处理的方法
    * 引入事务 ID 的新概念。每个事务在文档内部必须是唯一的。来自不同文档的多个事务可以使用相同的事务 ID 进行分组。
    * 在执行撤销操作时，GUI 组件可以调用 getAvailableUndo(id) 来检查是否可以使用给定 ID 进行撤销。
    * 如果有多个撤销事务（即在给定 ID 之前还有其他事务），GUI 组件应询问用户是否要撤销多个步骤。
    * 如果用户同意，则调用 undo(id) 撤销所有在给定 ID 之前（包括该 ID）的事务。重做操作也是如此。
    * 这里描述的新事务 ID 完全向后兼容。调用 API 时使用默认的 id=0 将保持原始行为。
    */
    //@{
    //!@brief 设置撤销/重做的级别
    void SetUndoMode(int mode);

    //!@brief 返回撤销/重做的级别
    int GetUndoMode() const;

    //!@brief 设置事务模式
    void SetTransactionMode(int mode);

    /**
     * @brief 打开一个新的撤销/重做命令，可以指定一个 UTF-8 格式的名称
     * 此函数调用 App::Application::setActiveTransaction(name) 来设置一个潜在的事务，该事务只有在实际发生更改时才会被创建。
     * @param name 
     */
    void OpenTransaction(std::string_view name = {});
    //!@brief 如果id匹配，则重命名当前事务
    void RenameTransaction(std::string_view name, int id);

    //!@brief 提交Command事务，如果没有打开的Command事务，则什么也不做
    //内部实现仅仅是调用Application::CloseActiveTransaction()接口
    void CommitTransaction();

    //!@brief 终止正在执行的事务
    void AbortTransaction();

    //!@brief 检查文档中是否有打开的事务
    bool HasPendingTransaction() const;

    //!@brief Return the undo/redo transaction ID starting from the back
    int GetTransactionID(bool undo, unsigned pos = 0) const;

    //!@brief 检查是否有一个事务被打开，且其列表是否空，如果没有打开的事务，则返回true
    bool IsTransactionEmpty() const;

    //!@brief 设置undo限制，单位是字节
    void SetUndoLimit(std::uint32_t undo_memeroy_size = 0);

    //!@brief 计算undo/redo任务对内存的消耗
    std::uint32_t GetUndoMemorySize() const;

    //!@brief 设置undo栈大小，默认是20
    void SetMaxUndoStackSize(std::uint32_t undo_max_stack_size = 20);
    //!@brief 返回undo栈大小
    std::uint32_t GetMaxUndoStackSize() const;

    //!@brief 清除所有撤销/重做事务
    void ClearUndos();

    //!@brief 返回存储的撤销操作的数量。如果返回值大于 0，则撤销操作将生效。​
    int GetNumberOfAvailableUndos(int id = 0) const;

    //!@brief 返回所有Undo事务的名字
    std::vector<std::string_view> GetAvailableUndoNames() const;

    //!@brief 执行一次撤销，如果当前没有undo事务，则返回False
    bool Undo(int id = 0);

    int GetNumberOfAvailableRedos(int id = 0) const;

    std::vector<std::string_view> GetAvailableRedoNames() const;

    bool Redo(int id = 0);

    //!@brief 检查文档是否正在执行事务，比如正在执行撤销/重做或者回滚。
    bool IsPerformingTransaction() const;

    //!@internal 用于向一个可事务管理的对象添加或删除属性
    void AddOrRemovePropertyOfObject(TransactionalObject*, Property* property, bool add);

    std::vector<app::DocumentObject*> GetRootObjects() const;

    const std::string_view GetOldLabel() const
    {
        return m_old_label;
    }

    std::string GetFullName() const override
    {
        return m_name;
    }

    /// Indicate if there is any document restoring/importing
    static bool IsAnyRestoring();
    //@}

    ~Document() override;

  protected:
    explicit Document(std::string_view name = {});

    void __RemoveObject(DocumentObject* object);
    DocumentObject* __AddObject(std::unique_ptr<DocumentObject> object, std::string_view object_name);

    /**
     * @brief 从Document.xml中读取Object对象，并返回一个包含所有对象的vector
     * 
     * @param reader 
     * @param version 
     * @return std::vector<app::DocumentObject*> 
     */
    std::vector<app::DocumentObject*> ReadObjects(base::XMLReader& reader, std::uint32_t version);

    void WriteObjects(const std::vector<app::DocumentObject*>&, base::XMLWriter& writer, std::uint32_t version) const;
    bool SaveToFile(std::filesystem::path const& file_path) const;

    void OnBeforePropertyValueChanging(const Property*) override;

    void OnPropertyChanged(const Property*) override;

    /// callback from the Document objects before property will be changed
    void OnBeforeObjectPropertyValueChanging(const TransactionalObject* who, const Property* what);

    void OnObjectPropertyChanged(const DocumentObject* who, const Property* what);

    int __RecomputeFeature(DocumentObject* Feat);

    std::filesystem::path GetTransientDirectory(std::string_view uuid, std::string_view filename) const;

    /**
     * @brief 根据application::GetActiveTransaction返回的name和id信息以及当前文档的上下文判断是否需要创建一个新的事务
     * 如果需要，则调用 @link __OpenTransaction @endlink
     * @param who 事务相关的对象，主要用于删除对象时，作为被删除的对象传入
     * @param what 事务相关的属性
     * @param line 行数
     * 创建事务有5类场景：
     * @li AddObject，此时who为nullptr，what为nullptr
     * @li RemoveObject，此时who为object，what为nullptr
     * @li AddProperty, 此时who为nullptr，what为property
     * @li RemoveProperty，此时who为nullptr，what为property
     * @li Property::SetValue，此时who为nullptr，what为property
     */
    void __CheckTransaction(DocumentObject* who, const Property* what, int line);

    /** Open a new command Undo/Redo, an UTF-8 name can be specified
     *
     * @param name: 事务名字
     * @param id: 事务id, 如果为0，则自动创建
     *
     * @return: 返回新的事务id
     *
     * 这个函数会创建一个真实的事务，不管Application的AutoTransaction设置。
     */
    int __OpenTransaction(std::string_view name = {}, int id = 0);

    //!@internal App::Application内部调用，用于提交一个Command事务
    int __CommitTransaction(bool notify_application = false);

    //!@internal App::Application内部调用，用于终止一个Command事务
    int __AbortTransaction();

    void __ClearRedos();

    friend class TransactionObjectDocumentObject;

  public:
    /// Option bit flags used by getDepenencyList()
    enum DependencyOption
    {
        /// Return topological sorted list
        DepSort = 1,
        /// Do no include object linked by PropertyXLink, as it can handle external link
        DepNoXLinked = 2,
        /// Raise exception on cycles
        DepNoCycle = 4,
    };

    using DependencyOptions = base::Flags<DependencyOption>;

    /** Get a complete list of all objects the given objects depend on.
    *
    * This function is defined as static because it accepts objects from
    * different documents, and the returned list will contain dependent
    * objects from all relevant documents
    *
    * @param objs: input objects to query for dependency.
    * @param options: See DependencyOption
    */
    static std::vector<app::DocumentObject*>
    GetDependencyList(const std::vector<app::DocumentObject*>& objs, DependencyOptions options = {});

    std::vector<app::Document*> GetDependentDocuments(bool sort = true);
    static std::vector<app::Document*> GetDependentDocuments(std::vector<app::Document*> docs, bool sort);

  protected:
    // virtual void OnBeforeChangeProperty(TransactionalObject const* who, Property const* what);

    friend class TransactionalObject;
    friend class DocumentObject;
    friend class Application;

  private:
    std::list<std::unique_ptr<Transaction>> m_undo_transactions;
    std::map<int, Transaction*> m_undo_map;
    std::list<std::unique_ptr<Transaction>> m_redo_transactions;
    std::map<int, Transaction*> m_redo_map;

    std::string m_name;
    std::string m_old_label;

    struct DocumentPrivate* d;
};

}  // namespace app