#pragma once
#include <common/PointT.hpp>
#include <geometry/Geom3Curve.hpp>
#include <topology/TopoShape.hpp>
#include <vector>

class CurveContinuity
{
  public:
      struct struct_continuity
    {
        AMCAX::Point3 point;                   //连续性点
        std::string continuity_type;           //连续性类型
        std::string distance_endpoints;        //两点距离
        std::string tangent_vector_angle;      //切线向量夹角
        std::string curvature_length;          //曲率长度
        std::string curvature_vector_angle;    //曲率向量夹角
    };
    struct Input
    {
        AMCAX::TopoShape topo_edge1;
        AMCAX::TopoShape topo_edge2;
    };

    struct OutPut
    {
        std::vector<struct_continuity> vector_continuity_edges;
        std::string error_message;
    };

    enum ContinuityEdgesType
    {
        NoContinuity,
        G0,
        G1,
        G2,
    };
  public:
    bool JudgeCurveContinuity();
    bool Run(const Input& input);
    bool JudgeContinuity(std::shared_ptr<AMCAX::Geom3Curve> curve3_1, std::shared_ptr<AMCAX::Geom3Curve> curve3_2,std::vector<struct_continuity>& vector_continuity_edges);

  public:
    void SetInput(const Input& input)
    {
        this->m_input = input;
    }
    auto GetOutput() const
    {
        return m_output;
    }

  private:
    Input m_input;
    OutPut m_output;
};