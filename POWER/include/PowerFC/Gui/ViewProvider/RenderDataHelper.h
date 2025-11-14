#pragma once

#include "Logging/Logging.h"
#include <AMCAXRender.h>
#include <PFCGlobal.h>
#include <geometry/ComputePointsTangentialDeflection.hpp>
#include <geometry/Geom3BSplineCurve.hpp>
#include <geometry/Geom3Curve.hpp>
#include <interface/Constants.h>
#include <math/GeometryMacros.hpp>
#include <math/PolygonOnTriangularMesh.hpp>
#include <math/TriangularMesh.hpp>
#include <memory>
#include <modeling/MakeShapeTool.hpp>
#include <topology/BRepAdaptorCompCurve3.hpp>
#include <topology/BRepAdaptorCurve3.hpp>
#include <topology/BRepAdaptorSurface.hpp>
#include <topology/TopoExplorerTool.hpp>
#include <topology/TopoFace.hpp>
#include <topology/TopoShape.hpp>
#include <topology/TopoTool.hpp>
#include <topology/TopoVertex.hpp>
#include <topomesh/BRepMeshIncrementalMesh.hpp>

namespace gui {
class PFC_GUI_API RenderDataHelper
{
  private:
    struct FaceInfo
    {
        AMCAX::OrientationType ori;
        std::shared_ptr<AMCAX::TriangularMesh> triMesh;
        AMCAX::TopoLocation loc;
        AMCAX::SurfaceType type;
        AMCAX::Point3 center;
    };
    struct EdgeInfo
    {
        std::shared_ptr<AMCAX::TriangularMesh> triMesh;
        std::shared_ptr<AMCAX::PolygonOnTriangularMesh> polyMesh;
        AMCAX::TopoLocation loc;
    };

  public:
    /*
    {
        "category": "SHAPE",
        "id": "modelname", 
        "points": [[x,y,z], [x,y,z]...],
        "vertices": {
            "topoType": "index" / "point",
            "topo": [0, 1...]  // 拓扑点, 对 points 索引 或 [x,y,z]
        },
        "edges": [
            {
                "meshType": "index" / "point",
                "mesh": [0, 1...] // 对 points 索引 或 [x,y,z]
            }
        ],
        "faces": [
            {
                "facets": [[1,2,3], [4,5,6]...],
                "normals": [[x,y,z], [x,y,z]...]
            }
        ]
    }
    */
    AMCAXRender::CAXMeshInfo parseShapeToData(const std::string& objId,
                                              const AMCAX::TopoShape& shape,
                                              bool isVertex = true,
                                              bool isEdge = true,
                                              bool isFace = true) const
    {
        AMCAXRender::CAXMeshInfo data;

        AMCAX::IndexSet<AMCAX::TopoShape> shapeVerts_, shapeEdges_, shapeFaces_;
        std::vector<FaceInfo> faceInfos_;
        std::vector<EdgeInfo> edgeInfos_;

        AMCAX::TopoExplorerTool::MapShapes(shape, AMCAX::ShapeType::Vertex, shapeVerts_);
        AMCAX::TopoExplorerTool::MapShapes(shape, AMCAX::ShapeType::Face, shapeFaces_);
        AMCAX::TopoExplorerTool::MapShapes(shape, AMCAX::ShapeType::Edge, shapeEdges_);

        bool isPoint = false;
        bool isCurve = false;

        if (shapeFaces_.size() == 0)
        {
            if (shapeEdges_.size() == 0)
            {
                isPoint = true;
            }
            else
            {
                isCurve = true;
            }
        }

        if (shapeFaces_.size() > 0)
        {
            auto face = static_cast<AMCAX::TopoFace const&>(shapeFaces_[0]);
            AMCAX::TopoLocation location;
            auto mesh = AMCAX::TopoTool::Triangulation(face, location);
            if (!mesh)
            {
                AMCAX::BRepMeshIncrementalMesh IMesh(shape, 0.01, true, 0.2);
                if (!IMesh.IsDone())
                {
                    LOGGING_DEBUG << objId << " :updateRenderData BRepMeshIncrementalMesh not Done";
                    return data;
                }
            }
        }
        AMCAX::MakeShapeTool::EnsureNormalConsistency(shape);

        faceInfos_.resize(shapeFaces_.size());
        for (int i = 0; i < shapeFaces_.size(); ++i)
        {
            const AMCAX::TopoFace& f = static_cast<const AMCAX::TopoFace&>(shapeFaces_[i]);
            AMCAX::BRepAdaptorSurface adapt(f);
            double uFirst = adapt.FirstUParameter();
            double uLast = adapt.LastUParameter();
            double vFirst = adapt.FirstVParameter();
            double vLast = adapt.LastVParameter();
            adapt.D0((uFirst + uLast) / 2.0, (vFirst + vLast) / 2.0, faceInfos_[i].center);
            faceInfos_[i].type = adapt.Type();
            AMCAX::TopoLocation loc;
            faceInfos_[i].triMesh = AMCAX::TopoTool::Triangulation(f, loc);
            faceInfos_[i].loc = loc;
            faceInfos_[i].ori = f.Orientation();
        }

        edgeInfos_.resize(shapeEdges_.size());
        for (int i = 0; i < shapeEdges_.size(); ++i)
        {
            const AMCAX::TopoEdge& e = static_cast<const AMCAX::TopoEdge&>(shapeEdges_[i]);
            AMCAX::TopoLocation loc;
            AMCAX::TopoTool::PolygonOnTriangulation(e, edgeInfos_[i].polyMesh, edgeInfos_[i].triMesh, loc);
            edgeInfos_[i].loc = loc;
        }

        if (isPoint)
        {
            data.category = "POINT";
            data.id = objId;
            for (int i = 0; i < shapeVerts_.size(); ++i)
            {
                AMCAX::Point3 vp1 = AMCAX::TopoTool::Point(static_cast<const AMCAX::TopoVertex&>(shapeVerts_[i]));
                data.points.push_back({vp1.X(), vp1.Y(), vp1.Z()});
            }
            return data;
        }

        data.category = "SHAPE";
        data.id = objId;

        data.vertex.topoType = "point";
        if (isVertex)
        {
            for (int i = 0; i < shapeVerts_.size(); ++i)
            {
                AMCAX::Point3 vp1 = AMCAX::TopoTool::Point(static_cast<const AMCAX::TopoVertex&>(shapeVerts_[i]));
                data.vertex.vertices.push_back(vp1.X());
                data.vertex.vertices.push_back(vp1.Y());
                data.vertex.vertices.push_back(vp1.Z());
            }
        }

        if (isEdge)
        {
            for (int i = 0; i < shapeEdges_.size(); ++i)
            {
                AMCAXRender::Edge eitem;
                eitem.meshType = "point";

                const AMCAX::TopoEdge& aEdge = static_cast<const AMCAX::TopoEdge&>(shapeEdges_[i]);
                double First, Last;
                std::shared_ptr<AMCAX::Geom3Curve> hCurve = AMCAX::TopoTool::Curve(aEdge, First, Last);

                if (!isCurve)
                {
                    std::shared_ptr<AMCAX::TriangularMesh> mesh = edgeInfos_[i].triMesh;
                    std::shared_ptr<AMCAX::PolygonOnTriangularMesh> poly = edgeInfos_[i].polyMesh;
                    AMCAX::Transformation3 tr = edgeInfos_[i].loc.Transformation();
                    if (poly)
                    {
                        for (int pid = 0; pid < poly->NVertices(); ++pid)
                        {
                            const AMCAX::Point3& ev = mesh->Vertex(poly->Vertex(pid)).Transformed(tr);
                            eitem.mesh.push_back(ev.X());
                            eitem.mesh.push_back(ev.Y());
                            eitem.mesh.push_back(ev.Z());
                        }
                    }
                    else
                    {
                        AMCAX::BRepAdaptorCurve3 ad(aEdge);
                        if (ad.Type() == AMCAX::CurveType::BSplineCurve)
                        {
                            std::shared_ptr<AMCAX::Geom3BSplineCurve> splineCrv = ad.BSpline();
                            int nPoints = (splineCrv->NPoles() + 2) * 50;
                            double gap = (Last - First) / nPoints;
                            for (int i = 0; i <= nPoints; i++)
                            {
                                AMCAX::Point3 pt = splineCrv->Value(First + i * gap);
                                eitem.mesh.push_back(pt.X());
                                eitem.mesh.push_back(pt.Y());
                                eitem.mesh.push_back(pt.Z());
                            }
                        }
                        else
                        {
                            AMCAX::ComputePointsTangentialDeflection smart(ad, 0.2, 0.1);
                            for (int i = 0; i < smart.NPoints(); i++)
                            {
                                const AMCAX::Point3& p0 = smart.Value(i);
                                eitem.mesh.push_back(p0.X());
                                eitem.mesh.push_back(p0.Y());
                                eitem.mesh.push_back(p0.Z());
                            }
                        }
                    }
                }
                else
                {
                    AMCAX::BRepAdaptorCurve3 ad(aEdge);
                    double angulardef = 0.2;
                    if (ad.Type() == AMCAX::CurveType::BSplineCurve)
                        angulardef = 0.05;
                    AMCAX::ComputePointsTangentialDeflection smart(ad, angulardef, 0.1);

                    for (int i = 0; i < smart.NPoints(); i++)
                    {
                        const AMCAX::Point3& p0 = smart.Value(i);
                        eitem.mesh.push_back(p0.X());
                        eitem.mesh.push_back(p0.Y());
                        eitem.mesh.push_back(p0.Z());
                    }
                }

                data.edges.push_back(eitem);
            }
        }

        if (isFace)
        {
            int baseVerticeIndex = 0;

            for (uint i = 0; i < faceInfos_.size(); ++i)
            {
                AMCAXRender::Face fitem;

                std::shared_ptr<AMCAX::TriangularMesh> mesh = faceInfos_[i].triMesh;
                AMCAX::Transformation3 tr = faceInfos_[i].loc.Transformation();
                AMCAX::OrientationType fOri = faceInfos_[i].ori;

                if (!mesh)
                {
                    data.faces.push_back(fitem);
                    continue;
                }

                fitem.pointSize = mesh->NVertices();
                for (int vid = 0; vid < mesh->NVertices(); ++vid)
                {
                    const AMCAX::Point3& p = mesh->Vertex(vid).Transformed(tr);
                    data.points.push_back({p.X(), p.Y(), p.Z()});
                    if (mesh->HasNormals())
                    {
                        const AMCAX::Direction3& norm = mesh->Normal(vid).Transformed(tr);
                        if (fOri == AMCAX::OrientationType::Reversed)
                            data.normals.push_back({-norm.X(), -norm.Y(), -norm.Z()});
                        else
                            data.normals.push_back({norm.X(), norm.Y(), norm.Z()});
                    }
                    else
                    {
                        data.normals.push_back({0, 0, 1});
                    }
                }

                for (int fid = 0; fid < mesh->NTriangles(); ++fid)
                {
                    AMCAX::Triangle tri = mesh->Face(fid);
                    if (fOri == AMCAX::OrientationType::Reversed)
                        std::swap(tri[1], tri[2]);

                    fitem.facets.push_back({tri[0] + baseVerticeIndex, tri[1] + baseVerticeIndex, tri[2] + baseVerticeIndex});
                }

                data.faces.push_back(fitem);
                baseVerticeIndex += mesh->NVertices();
            }
        }
        return data;
    }
};
}  // namespace gui
