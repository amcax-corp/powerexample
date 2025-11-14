#pragma once
#include <App/ExtensionContainer.h>
namespace app {

class Document;

class PFC_APP_API TransactionalObject : public ExtensionContainer
{
    PFC_PROPERTY_DECL_WITH_OVERRIDE()

  public:
    TransactionalObject();
    ~TransactionalObject() override;

    virtual bool IsAttachedToDocument() const;

    //这里用于对象在从Document中分离时，转移对象的名字，因为DocumentObject的name_in_document对应字符串的所有权在
    //Document中，所以需要转移出来，用于DocumentObject的备份，该方法就是转移TransactionalObject在Document中的名字的，
    //对应到于DocumentObject就是name_in_document
    virtual std::string_view DetachFromDocument();

  protected:
    void OnBeforeChangeProperty(Document* doc, Property const* property);
};
}  // namespace app