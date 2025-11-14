#pragma once

#include "DocumentObject3D.h"
#include "Properties/PropertyTopoShape.h"
#include <App/Properties/PropertyColorMap.h>
#include <App/Properties/PropertyColor.h>
#include <App/Properties/PropertyMap.h>
#include <Base/Exception.h>
#include <topology/TopoExplorerTool.hpp>
#include <topology/TopoFace.hpp>
#include <topology/TopoShape.hpp>
#include <topology/TopoTool.hpp>
#include <topology/TopoVertex.hpp>

namespace app {

class DocumentObjectLayer;

class PFC_APP_API DocumentObjectTopoShape : public DocumentObject3D
{
    PFC_PROPERTY_DECL_WITH_OVERRIDE()

  public:
    PropertyString Layer;
    PropertyTopoShape Shape;

    PropertyColorMap FaceColors;
    PropertyColor SolidColor;

    PropertyMap FaceNames;

    DocumentObjectTopoShape();
    ~DocumentObjectTopoShape() override;

    //获取子Shape的full Id
    //doc#object..shape_type[face,vert,edge].shape_index
    //不允许在一个对象中有多个PropertyTopoShape的属性，因为id上未区分Property
    std::string GetSubShapeID(const AMCAX::TopoShape& shape) const;

    //根据full id获取Shape，doc.object.[Face,Vertex,Edge,*]shape_index
    static AMCAX::TopoShape GetTopoShape(std::string_view full_id);

    DocumentObjectLayer* GetLayer() const;

    std::string_view GetViewProviderClassName() const override
    {
        return "gui::ViewProviderDocumentObjectTopoShape";
    }

    static std::string_view GetShapeTypeName(AMCAX::ShapeType shape_type);

    void SetFaceColors(std::vector<std::pair<AMCAX::TopoShape, app::Color>> const& colors);
    void SetFaceNames(std::map<std::string, std::string> const& names);

    /**
     * @brief 此接口查找所有符合指定颜色的面，如果存在多个符合指定颜色的面，则返回所有面，如果没有，返回空。
     * 
     * @param color 
     * @return std::vector<AMCAX::TopoShape> 
     */
    std::vector<AMCAX::TopoShape> FindFacesByColor(app::Color const& color);

    /**
     * @brief 此接口查找所有符合指定名称的面，如果存在多个符合指定颜色的面，则返回所有面，如果没有，返回空。
     * 
     * @param face_name
     * @return std::vector<AMCAX::TopoShape> 
     */
    std::vector<AMCAX::TopoShape> FindFacesByName(std::string_view face_name);

    std::string_view GetNameByFace(AMCAX::TopoShape const& face) const;

    /**
     * @brief 此接口查找第一个符合指定颜色的面，如果存在多个符合指定颜色的面，则返回第一个面，如果没有，返回空。
     * 
     * @param color 
     * @return std::vector<AMCAX::TopoShape> 
     */
    std::vector<AMCAX::TopoShape> FindOneFaceByColor(app::Color const& color);

    bool HasTopoShape() const{
      return !Shape.IsNull();
    }

  protected:
    void OnPropertyChanged(const app::Property*) override;
    void OnDocumentRestored() override;

  private:
    void UpdateShapeIndex();
    AMCAX::IndexSet<AMCAX::TopoShape> m_vertices, m_edges, m_faces;
    DocumentObjectLayer* m_layer;
};

}  // namespace app
