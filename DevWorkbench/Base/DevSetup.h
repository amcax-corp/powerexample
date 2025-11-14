#pragma once

#include <AMCAXRender.h>
#include <Base/Object/DevObject.h>
#include <Base/PartCollection.h>
#include <Base/Navigator/PartNavigator.h>
#include <Base/Object/BoxObject.h>
#include <Base/Object/CurvesLoftObject.h>
#include <Base/Object/RenderDistanceObject.h>

namespace app
{
  class Document;
  class DocumentObjectTopoShape;
} // namespace app

namespace Dev
{

  class DevSetup : public Dev::DevObject
  {
    PFC_TYPESYSTEM_DECL_WITH_OVERRIDE()
  public:
    DevSetup();
    ~DevSetup() override;

    template <typename T>
    std::vector<T *> GetObjects(app::Document *doc);
    static DevSetup *GetCurDevSetup();

    PartCollection *DevPartCollection();
    app::DocumentObjectTopoShape *AddPart(std::string_view name, bool isWireframedMark = false);
    BoxObject *AddBoxObject(std::string_view name);
    CurvesLoftObject *AddCurvesLoft(std::string_view name);
    RenderDistanceObject *AddRenderDistanceObject(std::string_view name);
    PartNavigator *GetPartNavigator();
    void UpdatePartNavigator();

    void Setup();

    void Store(base::XMLWriter &, std::uint32_t version) const override;
    void Restore(base::XMLReader &, std::uint32_t version) override;

    void SetNavSortList(int index, std::map<std::string, std::vector<std::string>> &map);
    std::map<std::string, std::vector<std::string>> &GetNavSortList(int index);

  private:
    void AddToSelection(DevObject *obj);
    void OnFinishRestoreDocument(const app::Document &);
    void OnBeforeDeletingDocument(const app::Document &doc);

  private:
    PartCollection *part_collection;
    std::map<int, std::map<std::string, std::vector<std::string>>> nav_sort_list;
    std::vector<std::string> selecteds;
  };

} // namespace cam