/**
 * @file Transactions.h
 * @author 王康 (wkcagd@hotmail.com)
 * @brief 实现一个事务类，通过设置一个事务 ID（transaction ID），可在撤销/重做（undo/redo）系统中，将多个操作合并成一个事务。
 * @version 0.1
 * @date 2024-12-25
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#pragma once
#include <Base/Persistence.h>
#include <memory>

namespace app {

class Property;
class Document;
class TransactionalObject;
class TransactionObject;

/**
 * @brief 对应于一个文档的多个对象的多个快照，可以作为一个整体进行撤销或重做。
 * 
 */
class PFC_APP_API Transaction : public base::Persistence
{
    PFC_TYPESYSTEM_DECL_WITH_OVERRIDE()

  public:
    /**
    * @brief Construct a new Transaction object
    * 
    * @param id 
    * @li 如果传入的 id 为 零，那么系统会自动生成一个唯一的事务 ID。这个 ID 是单调递增的，意味着每个新的事务 ID 都比上一个大，
    *     通常是递增的（比如每次增加 1），确保事务 ID 是连续的。
    * @li 用户可以传入自己的事务 ID，而不必依赖系统自动生成的 ID。这样，用户可以将不同文档中的多个操作分组在一起，
    *     确保这些操作可以作为一个整体进行撤销或重做。也就是说，用户可以将多个独立的操作（比如操作多个文档）归为一个逻辑上的事务，方便一键撤销或重做。
    * @code {.cpp}
    * @endcode
    * 
    */
    explicit Transaction(std::uint32_t id = 0);

    ~Transaction() override;

    void Merge(Transaction& other);

    void Apply(Document& doc, bool forward);

    struct ParametersApply{ Document& doc; bool forward;};
    void Apply(ParametersApply const& params){
        Apply(params.doc, params.forward);
    }

    std::size_t GetEstimatedSize() const override;

    void Store(base::XMLWriter&, std::uint32_t) const override;

    void Restore(base::XMLReader&, std::uint32_t) override;

    std::uint32_t GetID() const;

    static std::uint32_t GetNewID();
    static std::uint32_t GetLastID();

    bool IsEmpty() const;
    bool HasObject(TransactionalObject const* obj) const;
    void AddOrRemoveProperty(const TransactionalObject* obj, const Property* property, bool add);

    void AddObjectNew(std::unique_ptr<TransactionalObject>&& obj);
    void AddObjectDelete(TransactionalObject* obj);
    void AddObjectChange(const TransactionalObject* obj, Property const* property);

    void SetNameUtf8(std::string_view name);
    std::string_view GetNameUtf8() const;

    void Debug();

  private:
    std::string m_name_utf8;//the utf8 name of this transaction
    std::uint32_t m_id;//the id of this transaction

    //这个结构体存储了所有DocumentObject对应的备份
    struct TransactionObjectCollection;
    std::unique_ptr<TransactionObjectCollection> m_transaction_objects;
};

}  // namespace app