/// @file      EntityFactory.h
/// @brief     Entity Factory
/// @details   
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAXRender
#ifndef EntityFactory_h
#define EntityFactory_h
#include "Entity.h"
#include <memory>
#include <array>
#include "CAXMeshInfo.h"
#include "SlimTriangleMeshInfo.h"
#include "Common.h"

namespace AMCAXRender
{
    /// @brief	Entity Factory Class
    class AMCAX_RENDER_API EntityFactory {
    public:
        virtual ~EntityFactory() {};

    public:
        /// @brief Read .mesh binary file to Entity
        /// @param[in] file Absolute file path
        /// @return Entity object
        virtual std::shared_ptr<AbstractEntity> FromFileBin(std::string file) = 0;

        /// @brief Write to .mesh binary file
        /// @param[in] entity Entity object
        /// @param[in] file Absolute file path
        virtual void WriteToFileBin(std::shared_ptr<AbstractEntity> entity, std::string file) = 0;

        /// @brief Read json to Entity
        /// @param[in] vdata json data
        /// @return Entity object
        virtual std::shared_ptr<AbstractEntity> FromJson(void* vdata) = 0;


        /// @brief Generate Entity from CAXMeshInfo
        /// @param[in] meshInfo Custom mesh
        /// @return Entity object
        virtual std::shared_ptr<AbstractEntity> FromCAXMeshInfo(const CAXMeshInfo& meshInfo) = 0;

        /// @brief Generate Entity from CAXMeshInfo
        /// @param[in] meshInfo Custom mesh
        /// @return Entity object
        /// @note Lightweight creation of Entity, no scalar attached
        virtual std::shared_ptr<AbstractEntity> FromCAXMeshInfoSlim(const CAXMeshInfo& meshInfo) = 0;

        /// @brief Generate Entity from SlimTriangleMeshInfo
        /// @param[in] meshInfo Lightweight custom mesh
        /// @return Entity object
        /// @note Lightweight creation of Entity, no scalar attached
        virtual std::shared_ptr<AbstractEntity> FromSlimTriangleMeshInfo(SlimTriangleMeshInfo& meshInfo) = 0;

        /// @brief Create Coordinate System Entity
        /// @param[in] directionZ Z-axis direction
        /// @param[in] directionX X-axis direction
        /// @param[in] entityId Specified id
        /// @return Entity object
        virtual std::shared_ptr<AbstractEntity> CreateCoordinate(double directionZ[3], double directionX[3], EntityId entityId = "") = 0;

        /// @brief Create Move Axes Entity
        /// @param[in] bound Bounding box
        /// @return Entity object
        virtual std::shared_ptr<AbstractEntity> CreateMoveAxes(double bound[6]) = 0;

        /// @brief Create Sketch Coordinate System Entity
        /// @param[in] vdata json data
        /// @return Array of Entity objects
        virtual std::vector<std::shared_ptr<AbstractEntity>> ConvertSketch(void* vdata) = 0;

        // @brief Generate Entity from other Entity
        /// @param[in] originEntity The original entity
        /// @param[in] transform The transformation
        /// @return Entity object
        virtual std::shared_ptr<AbstractEntity> CreateEntity(std::shared_ptr<AbstractEntity> originEntity, std::shared_ptr<CTransform> transform) = 0;

#ifdef USE_AMCAX_KERNEL
        /// @brief Read toshape to Entity
        /// @param[in] shape toposhape data
        /// @param linDeflection The linear deflection
	    /// @param isRelative Determine whether the deflection is computed relatively
	    /// @param angDeflection The angle deflection
        /// @param array bounding box point used when shpae has infinity value 
        /// @return Entity object
        virtual std::shared_ptr<AbstractEntity> FromShape(const AMCAX::TopoShape& shape, double linDeflection = 0.005, bool isRelative = true, double angDeflection = 0.5, const std::array<double, 6>& array = {-10.0, -10.0, -10.0, 10.0, 10.0, 10.0}, bool isRemoveClosedEdge = true) = 0;

        /// @brief Read toposhapes to Entities
        /// @param[in] shapes toposhape data
        /// @param linDeflection The linear deflection
        /// @param isRelative Determine whether the deflection is computed relatively
        /// @param angDeflection The angle deflection
        /// @return Entity objects
        virtual std::vector<std::shared_ptr<AbstractEntity>> FromShapes(const std::vector<AMCAX::TopoShape>& shapes, double linDeflection = 0.005, bool isRelative = true, double angDeflection = 0.5, const std::array<double, 6>& array = { -10.0, -10.0, -10.0, 10.0, 10.0, 10.0 }, bool isRemoveClosedEdge = true) = 0;

        /// @brief Update entity data
        /// @param[in] id Entity id
        /// @param[in] shape toposhape data
        /// @return Entity object
        virtual std::shared_ptr<AbstractEntity> UpdateShape(EntityId id, AMCAX::TopoShape& shape) = 0;

        /// @brief Check toposhape has infinity value or not
        /// @param[in] shape toposhape data
        /// @return has infinity value or not
        virtual bool IsInfinity(const AMCAX::TopoShape& shape) = 0;
#endif
    };
}
#endif