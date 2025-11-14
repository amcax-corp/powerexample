#ifndef PFC_APP_DOCUMENTOBJECTEXTENSION_H
#define PFC_APP_DOCUMENTOBJECTEXTENSION_H
#pragma once

#include <App/Extension.h>

namespace base {
class Matrix4D;
}

namespace app {

class DocumentObject;
class DocumentObjectExecReturn;

class PFC_APP_API DocumentObjectExtension : public Extension
{
    PFC_EXTENSION_PROPERTY_DECL_WITH_OVERRIDE();

  public:
    DocumentObjectExtension() = default;
    ~DocumentObjectExtension() override = default;

    app::DocumentObject* GetExtendedObject();

    const app::DocumentObject* GetExtendedObject() const;

    //!@copydoc DocumentObject::MustExecute
    virtual int ExtensionMustExecute()
    {
        return 0;
    }

    //!@copydoc DocumentObject::Execute
    virtual app::DocumentObjectExecReturn* ExtensionExecute()
    {
        return nullptr;
    }

    //!@brief 在被扩展的对象SettingDocument之后调用
    virtual void OnExtendedSettingDocument() {}

    //!@brief 在被扩展的Object文档完全Restored之后调用
    virtual void OnExtendednDocumentResotred() {}

    //!@brief 在被扩展的Object Setup之后调用
    virtual void OnExtendedSetupObject() {}

    //!@brief 在被扩展的Object Unsetup之后调用
    virtual void OnExtendedUnsetupObject() {}

    //PyObject* GetExtensionPyObject();

    //!@return 返回对应的ViewProvider扩展名，用于自动创建ViewProvider扩展
    virtual std::string_view GetViewProviderExtensionName() const
    {
        return {};
    }

    //!@copydoc DocumentObject::GetSubObject
    virtual bool ExtensionGetSubObject(DocumentObject*& object_out,
                                       std::string_view subname,
                                       void** py_object_out,
                                       base::Matrix4D* matrix_out,
                                       bool need_transform,
                                       int depth) const
    {
        return false;
    }

    //!@copydoc DocumentObject::GetSubObjects
    virtual bool ExtensionGetSubObjects(std::vector<std::string>& objects_out, std::string_view reason) const
    {
        return false;
    }

    virtual bool ExtensionGetLinkedObject(DocumentObject*& object_out,
                                          bool recursive,
                                          base::Matrix4D* matrix_out,
                                          bool need_transform,
                                          int depth) const
    {
        return false;
    }

    virtual int ExtensionSetElementVisible(std::string_view, bool)
    {
        return -1;
    }

    virtual int ExtensionIsElementVisible(std::string_view) const
    {
        return -1;
    }

    //!@copydoc DocumentObject::HasChildElement
    virtual bool ExtensionHasChildElement() const
    {
        return false;
    }
};

}  // namespace app
#endif