/// @file      CAXMeshInfo.h
/// @brief     Custom Mesh Structure
/// @details   Used to construct mesh data
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAXRender
#ifndef CAXMeshInfo_h
#define CAXMeshInfo_h
#include "Macros.h"
#include <array>

namespace AMCAXRender {

    /// @brief Vertex
    struct AMCAX_RENDER_API Vertex
    {
        std::string topoType; ///< Type, e.g., "point"
        std::vector<double> vertices;
        std::vector<std::vector<double>> pick;
        std::vector<std::vector<double>> sktpoint;
    };

    /// @brief Edge
    struct AMCAX_RENDER_API Edge
    {
        std::string meshType; ///< Type, e.g., "index", "point"
        std::vector<double> mesh;
    };

    /// @brief Face
    struct AMCAX_RENDER_API Face {
        std::vector<std::vector<int>> facets;
        std::vector<int> edges;
        int pointSize;
        std::vector<std::vector<double>> normals;
        std::vector<std::vector<double>> uvs;
    };

    /// @brief Custom Mesh Data Structure
    struct AMCAX_RENDER_API CAXMeshInfo{
        std::string category; ///< Data type, e.g., "SHAPE", "POINT"
        std::string id; ///< Unique data ID
        std::vector<std::vector<double>> points; ///< Point collection
        std::vector<std::vector<double>> normals; ///< Normal vector collection
        Vertex vertex; ///< Vertex data collection
        std::vector<Edge> edges; ///< Edge data collection
        std::vector<Face> faces; ///< Face data collection

        std::vector<std::vector<float>> poly_points; ///< polyline Point collection
        int ray_points_sum{0};
    };
 
    AMCAX_RENDER_API CAXMeshInfo CreateCAXMeshInfo(std::string filename);
    AMCAX_RENDER_API void WriteCAXMeshInfo(const CAXMeshInfo& info, std::string filename);

    /// @brief Mesh Data For Point
    struct AMCAX_RENDER_API RenderPoint
    {
        std::array<float, 3> Position;
        std::array<float, 3> Normal;
    };

    /// @brief Mesh Data For Edge
    struct AMCAX_RENDER_API RenderEdge
    {
        std::array<float, 3> pt1;
        std::array<float, 3> pt2;
        int index;
    };
    /// @brief Mesh Data
    struct AMCAX_RENDER_API RenderMesh
    {
        std::vector<RenderPoint> points;
        std::unordered_map<int, std::vector<std::array<int, 3>>> faces;
        std::vector<RenderEdge> edges;
        std::vector<std::array<float, 3>> topoPoints;
        std::string id;
    };

}
#endif