/// @file      InstanceData.h
/// @brief     Instanced Rendering Data
/// @details   Used to construct instanced rendering point data
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAXRender
#ifndef InstanceData_h
#define InstanceData_h

#include "Macros.h"
#include <string>
#include <vector>
#include <array>

namespace AMCAXRender
{
    /// @brief Instanced Rendering Data
    class AMCAX_RENDER_API InstancedData {
        friend class EntityManageImpl;
    public:
       
        InstancedData();
        ~InstancedData();
        
        /// @brief Add a new instance to the instancing data.
        /// 
        /// This method adds a new transform instance with its own unique ID, position, rotation, scale, and color.
        /// The instance will be used during instanced rendering where each one shares the same geometry but has
        /// its own transform and appearance.
        ///
        /// @param[in] subId   A unique string identifier for the instance.
        /// @param[in] position A 3D position array {x, y, z} in world space.
        /// @param[in] rotation A 3D rotation array {x, y, z} in degrees. Rotation is applied in X-Y-Z order.
        /// @param[in] scale    A 3D scale array {x, y, z}. Use {1,1,1} for no scaling.
        /// @param[in] color    A 3D color array {r, g, b}, each component in [0,1] range.
        void AddInstance(
            const std::string subId,
            const double position[3],
            const double rotation[3],
            const double scale[3],
            const double color[3]
        );

        /// @brief Add multiple instances in batch.
        ///
        /// Adds a list of instances in a single call. All input arrays must have the same length.
        /// Each element corresponds to one instance’s parameters.
        ///
        /// @param[in] subIds   Vector of unique string identifiers.
        /// @param[in] positions Vector of positions, each as array {x, y, z}.
        /// @param[in] rotations Vector of rotations, each as array {x, y, z} in degrees.
        /// @param[in] scales    Vector of scales, each as array {x, y, z}.
        /// @param[in] colors    Vector of colors, each as array {r, g, b}, values in [0,1].
        void AddInstances(
            const std::vector<std::string>& subIds,
            const std::vector<std::array<double, 3>>& positions,
            const std::vector<std::array<double, 3>>& rotations,
            const std::vector<std::array<double, 3>>& scales,
            const std::vector<std::array<double, 3>>& colors
        );

        /// @brief Build the internal data structure for instanced rendering.
        ///
        /// This method should be called after all instances are added. It prepares the geometry, color,
        /// and transformation arrays for the GPU instancing pipeline.
        void Build();

    private:
        std::vector<std::string> SubIds;
        std::vector<double> flatPositions;
        std::vector<double> flatOrientations;
        std::vector<double> flatScales;
        std::vector<unsigned char> flatColors;
        std::vector<unsigned char> idColors;

        void ComputeOrientationMatrix(const std::array<double, 3>& rotDeg,
            const std::array<double, 3>& scale,
            float outMatrix[9]);

    protected:
        class Impl;
        Impl* pImpl;
        void* GetRenderBuffer();
    };
}

#endif