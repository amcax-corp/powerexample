#pragma once
#include <App/DynamicPropertyTable.h>
#include <App/TransactionalObject.h>
#include <Base/Persistence.h>
#include <unordered_map>


namespace app {
class Document;

/**
 * @brief 由于一个Transaction通常由多个子操作构成，对应于子操作，app::TransactionObject则是用于记录对象创建、对象删除、属性修改等操作历史。
 * 
 */
class PFC_APP_API TransactionObject : public base::Persistence
{
    PFC_TYPESYSTEM_DECL_WITH_OVERRIDE()

  public:
    TransactionObject();
    ~TransactionObject() override;

    TransactionObject(const TransactionObject&) = delete;
    TransactionObject& operator=(const TransactionObject&) = delete;
    TransactionObject(TransactionObject&&);
    TransactionObject& operator=(TransactionObject&&);

    virtual void ApplyNew(Document& doc, std::unique_ptr<TransactionalObject>&& obj);
    virtual void ApplyDelete(Document& doc, TransactionalObject* obj);
    virtual void ApplyChange(Document& doc, TransactionalObject* obj, bool forward);

    void SetProperty(const Property* property);
    void AddOrRemoveProperty(const Property* property, bool add);

    std::size_t GetEstimatedSize() const override;

    void Store(base::XMLWriter&, std::uint32_t) const override;
    void Restore(base::XMLReader&, std::uint32_t) override;

    //合并两个TransactionObject
    //如果当前状态为DELETE，other状态为NEW，返回false
    bool Merge(TransactionObject & other);

  protected:

    enum class Status { New, Delete, Change };

    Status m_status{Status::New};


    struct PropertyBackupData{
      std::unique_ptr<app::Property> property = nullptr;
      std::string name{};
      std::string group{};
      std::string description{};
      PropertyFlags flags{};

      base::Type property_type{};
      const Property* origin_property = nullptr;

      void CopyDynamicPropertyData(const Property* property);
      ~PropertyBackupData();
      PropertyBackupData();

      PropertyBackupData(const PropertyBackupData&) = delete;
      PropertyBackupData& operator=(const PropertyBackupData&) = delete;
      PropertyBackupData(PropertyBackupData&&);

    };

    std::unordered_map<int64_t, PropertyBackupData> m_property_backup_map;
    std::string m_name_in_document;

    friend class Transaction;

    
};

}  // namespace app