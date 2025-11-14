#pragma once
#include <App/TransactionObject.h>
namespace app {

class PFC_APP_API TransactionObjectDocumentObject : public app::TransactionObject
{
    PFC_TYPESYSTEM_DECL_WITH_OVERRIDE()

  public:
    TransactionObjectDocumentObject()=default;
    ~TransactionObjectDocumentObject() override=default;
    
    //document就是documentobject的Caretaker
    void ApplyNew(Document& document, std::unique_ptr<TransactionalObject>&& object) override;
    
    //document就是documentobject的Caretaker
    void ApplyDelete(Document& document, TransactionalObject* object) override;
};
}  // namespace app