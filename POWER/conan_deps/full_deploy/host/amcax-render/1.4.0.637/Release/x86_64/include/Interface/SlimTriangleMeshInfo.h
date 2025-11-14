/// @file      SlimTriangleMeshInfo.h
/// @brief     Lightweight Custom Mesh Structure
/// @details   Used to construct mesh data
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAXRender
#ifndef SlimTriangleMeshInfo_h
#define SlimTriangleMeshInfo_h
#include "Macros.h"

namespace AMCAXRender {
    /// @brief Custom Mesh Data Structure
    struct AMCAX_RENDER_API SlimTriangleMeshInfo {
        std::string id;			///< Unique data id
        std::vector<double> slimPointData;
        std::vector<double> slimNormalData;
        std::vector<int> slimCellData;
        std::vector<double> slimCellScalarData;

        SlimTriangleMeshInfo()
        {

        }
        SlimTriangleMeshInfo(std::string id,
            std::vector<double>& pointData,
            std::vector<double>& normalData,
            std::vector<int>& cellData,
            std::vector<double>& cellScalarData)
            : id(std::move(id)),
            slimPointData(std::move(pointData)),
            slimNormalData(std::move(normalData)),
            slimCellData(std::move(cellData)),
            slimCellScalarData(std::move(cellScalarData))
        {

        }
    };
 

    AMCAX_RENDER_API SlimTriangleMeshInfo CreateSlimTriangleMeshInfo(std::string filename);
    AMCAX_RENDER_API void WriteSlimTriangleMeshInfo(const SlimTriangleMeshInfo& info, std::string filename);

}
#endif