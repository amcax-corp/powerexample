/// @file      EntityManage.h
/// @brief     Entity Management
/// @details   
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAXRender
#ifndef EntityManage_h
#define EntityManage_h

#include "Entity.h"
#include <memory>
#include <map>
#include "zebraConfig.h"
#include "Common.h"
#include "Material.h"

namespace AMCAXRender {

    /// @brief Entity Management Class
    class AMCAX_RENDER_API EntityManage {
    public:
        virtual ~EntityManage() {};
    public:
        /// @brief Add Entity to Rendering Scene
        /// @param[in] entity Entity object
        /// @return Unique entity identifier
        virtual EntityId AddEntity(std::shared_ptr<AbstractEntity> entity) = 0;

        /// @brief Add Coordinate System Entity to Rendering Scene
        /// @param[in] entity Entity object
        /// @param[in] center Coordinate system origin
        /// @return Entity identifier
        virtual EntityId AddCoordinateEntity(std::shared_ptr<AbstractEntity> entity, double center[3]) = 0;

        /// @brief Add Move Axes Entity to Rendering Scene
        /// @param[in] entity Entity object
        /// @return Entity identifier
        virtual EntityId AddMoveAxesEntity(std::shared_ptr<AbstractEntity> entity) = 0;

        /// @brief Add 2D Entity to Rendering Scene
        /// @param[in] entity Entity object
        /// @return Entity identifier
        virtual EntityId AddEntity2D(std::shared_ptr<AbstractEntity> entity) = 0;

        /// @brief Get Entity from Scene
        /// @param[in] id Entity id
        /// @return Entity object
        virtual std::shared_ptr<AbstractEntity> GetEntityById(EntityId id) = 0;

        /// @brief Remove Specified Entity from Rendering Scene
        /// @param[in] id Entity id
        virtual void Remove(EntityId id) = 0;

        /// @brief Remove Specified Entity from Rendering Scene
        /// @param[in] id Entity ids
        virtual void Remove(std::vector<EntityId> ids) = 0;

        /// @brief Remove All Entities from Rendering Scene
        virtual void RemoveAll() = 0;

        /// @brief Remove All 2D Entities from Sketch in Rendering Scene
        virtual void Remove2D() = 0;

        /// @brief Update Entity Data
        /// @param[in] id Entity id
        /// @param[in] entity Entity object
        virtual void UpdateEntity(EntityId id, std::shared_ptr<AbstractEntity> entity) = 0;

        /// @brief Set Entity Visibility
        /// @param[in] id Entity id
        /// @param[in] visible Visibility flag, true: visible, false: hidden
        virtual void SetEntityVisble(EntityId id, bool visible, ViewType viewType = ViewType::MAIN) = 0;

        /// @brief Set Visibility of Entity Submodule
        /// @param[in] id Entity id
        /// @param[in] type Submodule type
        /// @param[in] visible Visibility flag, true: visible, false: hidden
        /// @param[in] index Submodule index
        /// @note Submodule index may represent: the index-th face, point, line, etc.
        virtual void SetEntityPartVisible(EntityId id, PickType type, bool visible, int index) = 0;

        /// @brief Set Visibility of Entity Submodule
        /// @param[in] id Entity id
        /// @param[in] type Submodule type
        /// @param[in] visible Visibility flag, true: visible, false: hidden
        /// @param[in] indexs Submodule index array
        /// @see setEntityPartVisible
        virtual void SetEntityPartVisible(EntityId id, PickType type, bool visible, std::vector<int> indexs) = 0;

        /// @brief Set Entity Opacity
        /// @param[in] id Entity id
        /// @param[in] opacity Opacity, range [0,1]
        virtual void SetEntityOpacity(EntityId id, double opacity) = 0;

        /// @brief Set Submodule Entity Opacity
        /// @param[in] id Entity id
        /// @param[in] opacity Opacity, range [0,1]
        /// @param[in] faceIndex face Submodule index 
        virtual void SetEntityOpacity(EntityId id, double opacity, int faceIndex) = 0;

        /// @brief Add Preview Entity
        /// @param[in] id Entity id
        /// @param[in] IsEntity2D Is it a 2D entity
        /// @return Entity id
        virtual EntityId AddPreviewEntity(std::shared_ptr<AbstractEntity> entity, bool IsEntity2D = false) = 0;

        /// @brief Add Preview Coordinate System to Rendering Scene
        /// @param[in] entity Entity object
        /// @param[in] center Coordinate system origin
        /// @return Entity identifier
        virtual EntityId AddPreviewCoordinateEntity(std::shared_ptr<AbstractEntity> entity, double center[3]) = 0;

        /// @brief Clear Preview Entities
        virtual void ClearPreview() = 0;

        /// @brief Refresh Window
        virtual void DoRepaint() = 0;

        /// @brief Set Entity Selected
        /// @param[in] id Entity id
        virtual void SetEntitySelected(EntityId id) = 0;

        /// @brief Async Set Entity Selected
        /// @param[in] id Entity id
        /// @param[in] type Entity data type
        /// @param[in] index Submodule index, e.g. point, line, face, etc.
        /// @param[in] callback Complete 
        virtual void AsyncSetEntitySelected(EntityId id, PickType type, int index, std::function<void()> callback) = 0;

        /// @brief Entity Selected Color
        /// @param[in] rgb Color
        /// @note Color range [0,1]
        virtual void SetEntitySelectedColor(double rgb[3]) = 0;

        /// @brief Clear Entity Selected
        virtual void ClearEntitySelected() = 0;

        /// @brief Clear Entity Hovered
        virtual void ClearEntityHovered() = 0;

        /// @brief Set Multiple Entities Selected Color
        /// @param[in] rgb Color
        /// @note Color range [0,1]
        virtual void SetMulitEntitySelectedColor(double rgb[3]) = 0;

        /// @brief Append Multiple Entities Selected
        /// @param[in] id Entity id
        /// @note Note the difference with setEntitySelected
        virtual void AppendMulitEntitySelected(EntityId id) = 0;

        /// @brief Remove Multiple Entities Selected
        /// @param[in] id Entity id
        virtual void RemoveMulitEntitySelected(EntityId id) = 0;

        /// @brief Clear All Multiple Entities Selected
        virtual void ClearMulitEntitySelected() = 0;

        /// @brief Set Highlight
        /// @param[in] id Entity id
        /// @param[in] type Entity data type
        /// @param[in] indexs Submodule index, e.g. point, line, face, etc.
        virtual void SetHightLight(EntityId id, PickType type, std::vector<int> indexs) = 0;

        /// @brief Set Highlight
        /// @param[in] id Entity id
        /// @param[in] selectInfos Entity data type and Submodule index 
        virtual void SetHightLight(std::unordered_map<AMCAXRender::EntityId, std::unordered_map<AMCAXRender::PickType, std::vector<int>>> selectInfos) = 0;

        /// @brief Clear Highlight
        virtual void ClearHightLight() = 0;

        /// @brief Add Highlight
        /// @param[in] id Entity id
        /// @param[in] type Entity data type
        /// @param[in] index Submodule index, e.g. point, line, face, etc.
        virtual void AddHightLight(EntityId id, PickType type, int index) = 0;

        /// @brief Add Highlight
        /// @param[in] id Entity id
        virtual void AddHightLight(EntityId id) = 0;

        /// @brief Async Add Highlight
        /// @param[in] id Entity id
        /// @param[in] type Entity data type
        /// @param[in] index Submodule index, e.g. point, line, face, etc.
        /// @param[in] callback Complete 
        virtual void AsyncAddHightLight(EntityId id, PickType type, int index, std::function<void()> callback) = 0;

        /// @brief Remove Highlight
        /// @param[in] id Entity id
        /// @param[in] type Entity data type
        /// @param[in] index Submodule index, e.g. point, line, face, etc.
        virtual void RemoveHightLight(EntityId id, PickType type, int index) = 0;

        /// @brief Remove Highlight
        /// @param[in] id Entity id
        virtual void RemoveHightLight(EntityId id) = 0;

        /// @brief Async Remove Highlight
        /// @param[in] id Entity id
        /// @param[in] type Entity data type
        /// @param[in] index Submodule index, e.g. point, line, face, etc.
        virtual void AsyncRemoveHightLight(EntityId id, PickType type, int index, std::function<void()> callback) = 0;

        /// @brief Set Highlight Color
        /// @param[in] rgb Color
        /// @note Color range [0,1]
        virtual void SetHightLightColor(double rgb[3]) = 0;

        /// @brief Get Highlight Color
        /// @param[in] rgb Color
        /// @note Color range [0,1]
        virtual void GetHightLightColor(double rgb[3]) = 0;

        /// @brief Set Entity Color for Points, Lines, and Faces
        /// @param[in] id Entity id
        /// @param[in] type Entity data type
        /// @param[in] list Color table, list data parsing: key point, line, face index, value color
        virtual void SetEntityColor(EntityId id, PickType type, std::map<int, std::tuple<double,double,double>> list) = 0;

        /// @brief Set Entity Color for Points, Lines, and Faces
        /// @param[in] id Entity id
        /// @param[in] type Entity data type
        /// @param[in] rgb Color 
        /// @note Color range [0,1]
        virtual void SetEntityColor(EntityId id, PickType type, double rgb[3]) = 0;

        /// @brief Set Entity Color for Points, Lines, and Faces
        /// @param[in] id Entity id
        /// @param[in] rgb Color 
        /// @note Color range [0,1]
        virtual void SetEntityColor(EntityId id, double rgb[3]) = 0;

        /// @brief Set Entity Pick Enable
        /// @param[in] id Entity id
        /// @param[in] enable Is it pickable
        virtual void SetPickEntityEnable(EntityId id, bool enable) = 0;

        /// @brief Hide Face of Entity 
        /// @param[in] id Entity id
        virtual void HideEntityFace(EntityId id) = 0;

        /// @brief Set Zebra Stripes Enable
        /// @param[in] id Entity id
        /// @param[in] enable Is it enabled
        virtual void SetEntityZebra(EntityId id, bool enable) = 0;

        /// @brief Set Zebra Stripes by index
        /// @param[in] id Entity id
        /// @param[in] index Submodule index
        /// @param[in] enable Is it enabled
        virtual void SetEntityZebraByIndex(EntityId id, int index, bool enable) = 0;

        /// @brief clear Zebra Stripes
        virtual void ClearZebra() = 0;

        /// @brief Set Zebra Stripes Configuration
        /// @param[in] config Configuration
        virtual void SetZebraConfig(const ZebraConfig& config) = 0;

        /// @brief Set Transfrom
        /// @param[in] id Entity id
        /// @param[in] transform model matrix
        virtual void SetTransfrom(EntityId id, CTransform* transform) = 0;

        /// @brief Set Global Transfrom
        /// @param[in] transform model matrix
        virtual void SetTransfrom( CTransform* transform) = 0;

        /// @brief Get all entity IDs  
        /// @param[in] ids Array of entity IDs  
        virtual void GetAllEntityIds(std::vector<EntityId>& ids) = 0;

        /// @brief Set Entity Ray flag ,set ray lineWidth
        virtual void SetRayFlag(EntityId id, bool isRay,float lineWidth = 1.0f) = 0;

        /// @brief Set Entity Material, include Ambient, Diffuse, Specular, SpecularPower
        virtual void SetMaterial(EntityId id, std::shared_ptr<Material> material) = 0;

        /// @brief Set Entity face Material, include Ambient, Diffuse, Specular, SpecularPower
        virtual void SetMaterial(EntityId id, int faceId, std::shared_ptr<Material> material) = 0;
    };
}
#endif