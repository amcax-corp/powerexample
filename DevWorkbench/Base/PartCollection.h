#pragma once

#include <memory>
#include <vector>
#include <boost/signals2.hpp>
#include <App/DocumentObjectTopoShape.h>

namespace app {
class DocumentObject;
}

namespace Dev {

class DevSetup;

class PartCollection
{
  public:
    PartCollection(DevSetup* owner = nullptr);
    ~PartCollection();

    void Clear();
    DevSetup* GetSetup();

    std::vector<app::DocumentObjectTopoShape*> PartList();

    bool IsLabelUnique(std::string_view label);
    std::string GetUniqueName(std::string_view name);

    void Setup(app::Document* doc, std::vector<app::DocumentObjectTopoShape*> parts);
    app::DocumentObjectTopoShape* FindObject(std::string_view name);

    void SetSortList(const std::map<std::string, std::vector<std::string>>& map);
    std::map<std::string, std::vector<std::string>>& GetSortList();

    void RemovePart(std::string_view name);
    void RemovePart(app::DocumentObjectTopoShape* obj);

    void SlotNewObject(const app::DocumentObject&);
    void SlotObjectDeleted(const app::DocumentObject&);
    void SlotObjectBeforePropertyChanged(const app::DocumentObject&, const app::Property&);
    void SlotObjectPropertyChanged(const app::DocumentObject&, const app::Property&);

    boost::signals2::signal<void(const app::DocumentObject&)> SignalNewObject;
    boost::signals2::signal<void(const app::DocumentObject&)> SignalDeletedObject;
    boost::signals2::signal<void(const app::DocumentObject&, const app::Property&)> SignalObjectPropertyChanged;

  private:
    DevSetup* m_owner;

    std::vector<app::DocumentObjectTopoShape*> m_parts;

    using Connection = boost::signals2::connection;
    Connection connectNewObject;
    Connection connectDeletedObject;
    Connection connectBeforeObjectPropertyChanged;
    Connection connectObjectPropertyChanged;

    std::map<std::string, std::vector<std::string>> sort_list;
};

}  // namespace cam