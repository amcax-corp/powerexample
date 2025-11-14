#pragma once

#include "Gui/TreeItemModel.h"
#include "PFCGlobal.h"
#include <map>
#include <string>

namespace app {
class DocumentObject;
}

namespace gui {

class Document;
class ViewProviderDocumentObject;

class PFC_GUI_API ActiveObjectList
{
  public:
    explicit ActiveObjectList(Document* doc)
      : m_doc(doc)
    {}

    template<typename _T>
    inline _T GetObject(const char* name, app::DocumentObject** parent = nullptr, std::string* subname = nullptr) const
    {
        auto it = m_object_map.find(name);
        if (it == m_object_map.end())
            return 0;
        return dynamic_cast<_T>(GetObject(it->second, true, parent, subname));
    }
    void SetObject(app::DocumentObject*, const char*, const char* subname = nullptr, const gui::HighlightMode& m = HighlightMode::UserDefined);
    bool HasObject(const char*) const;
    void ObjectDeleted(const ViewProviderDocumentObject& viewProviderIn);
    bool HasObject(app::DocumentObject* obj, const char*, const char* subname = nullptr) const;

  private:
    struct ObjectInfo;
    void SetHighlight(const ObjectInfo& info, gui::HighlightMode mode, bool enable);
    app::DocumentObject* GetObject(const ObjectInfo& info, bool resolve, app::DocumentObject** parent = nullptr, std::string* subname = nullptr) const;
    ObjectInfo GetObjectInfo(app::DocumentObject* obj, const char* subname) const;

  private:
    struct ObjectInfo
    {
        app::DocumentObject* obj;
        std::string subname;
    };
    std::map<std::string, ObjectInfo> m_object_map;
    Document* m_doc;
};
}  // namespace gui