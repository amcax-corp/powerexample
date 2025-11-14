/// @file      InstancedPointData.h
/// @brief     Instanced Rendering Point Data
/// @details   Used to construct instanced rendering point data
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAXRender
#ifndef InstancedPointData_h
#define InstancedPointData_h

#include "Macros.h"
#include <array>
namespace AMCAXRender {
    /// @brief Instanced Rendering Point Data
    struct AMCAX_RENDER_API InstancedPointData{
        std::string blockId;
        std::vector<double> points;
        std::vector<double> scales;
        std::vector<double> quaternions;    // wxyz
        std::vector<unsigned char> colors;  // rgba 0-255

        InstancedPointData()
        {

        }
        InstancedPointData(
            std::string blockId,
            std::vector<double>& points,
            std::vector<double>& scales,
            std::vector<double>& quaternions,
            std::vector<unsigned char>& colors)
            :
            blockId(blockId),
            points(std::move(points)),
            scales(std::move(scales)),
            quaternions(std::move(quaternions)),
            colors(std::move(colors))
        {

        }
    };
 

    AMCAX_RENDER_API InstancedPointData CreateInstancedPointData(std::string filename);
    AMCAX_RENDER_API void WriteInstancedPointData(const InstancedPointData& info, std::string filename);

}
#endif