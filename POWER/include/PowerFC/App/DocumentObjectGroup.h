#ifndef PFC_APP_DOCUMENTOBJECTGROUP_H
#define PFC_APP_DOCUMENTOBJECTGROUP_H
#pragma once

#include <App/DocumentObject.h>
#include <App/GroupExtension.h>


namespace app {

class PFC_APP_API DocumentObjectGroup : public DocumentObject, public GroupExtension
{
    PFC_PROPERTY_DECL_WITH_OVERRIDE();

  public:
    DocumentObjectGroup();
    ~DocumentObjectGroup() override;

    std::string_view GetViewProviderClassName() const override
    {
        return "App::ViewProviderDocumentObjectGroup";
    }

    //TODO PyObject* GetPyObject() override;
};

//TODO: using DocumentObjectGroupPy = app::FeaturePythonT<DocumentObjectGroup>;

}  // namespace app

#endif