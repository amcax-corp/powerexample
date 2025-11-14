/// @file      PluginManage.h
/// @brief     Plugin Management Module
/// @details   
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAXRender
#ifndef PluginManage_h
#define PluginManage_h

#include "Entity.h"
#include <memory>
#include "PluginProperty.h"
#include "InstancedPointData.h"
namespace AMCAXRender {

    /// @brief Plugin Management Class
    /// @details Used for adding, deleting, modifying, and querying plugins, as well as message registration
    class AMCAX_RENDER_API PluginManage {
    public:
        virtual ~PluginManage() {};
    public:

        /// @brief Add Plugin from Entity Geometry Data
        /// @param[in] entity Entity object
        /// @return Plugin id
        /// @note Entity data needs to be created first
        virtual EntityId AddPluginFromMeshEntity(std::shared_ptr<AbstractEntity> entity, bool isInstancedRender = false) = 0;

        /// @brief Update Plugin from Entity Geometry Data
        /// @param[in] id Plugin id
        /// @param[in] entity Entity object
        /// @return Plugin id
        /// @note Entity data needs to be created first
        virtual EntityId UpdateEntityPlugin(std::shared_ptr<AbstractEntity> entity) = 0;

        /// @brief Update Instanced Point Data
        /// @param[in] id Plugin id
        /// @param[in] data Point data
        /// @note Entity plugin data needs to be created first
        virtual void UpdateInstancedPointData(EntityId id, InstancedPointData& data) = 0;

        /// @brief Create Plugin from Plugin Type
        /// @param[in] type Plugin type
        /// @return Plugin id
        /// @note Plugins of type PluginType::kEntity are created through the AddPluginFromMeshEntity interface
        /// @see AddPluginFromMeshEntity
        virtual EntityId AddPluginFromType(PluginType type, EntityId pid = "") = 0;

        /// @brief Remove Plugin
        /// @param[in] id Plugin id
        virtual void RemovePlugin(EntityId id) = 0;
        
        /// @brief Set Plugin Property
        /// @param[in] id Plugin id
        /// @param[in] prop Plugin property
        virtual void SetProperty(EntityId id, std::shared_ptr<PluginProperty> prop, ViewType viewType = ViewType::MAIN) = 0;

        /// @brief Get Plugin Property
        /// @param[in] id Plugin id
        /// @return Plugin property
        virtual std::shared_ptr<PluginProperty> GetProperty(EntityId id, ViewType viewType = ViewType::MAIN) = 0;

        /// @brief Set Batch Plugin Property
        /// @param[in] id Plugin id
        /// @param[in] prop Plugin property
        virtual void BatchSetProperties(EntityId id, std::shared_ptr<PluginProperty> prop) = 0;

        /// @brief Get Plugin Property
        /// @tparam Property type
        /// @param[in] id Plugin id
        /// @return Plugin property
        /// @see Property types can be found in PluginProperty.h
        template<class T>
        std::shared_ptr<T> GetProperty(EntityId id, ViewType viewType = ViewType::MAIN) {
            return std::dynamic_pointer_cast<T>(GetProperty(id, viewType));
        };

        /// @brief Set Plugin Visibility
        /// @param[in] id Plugin id
        /// @param[in] visible Visibility flag
        virtual void SetVisible(EntityId id, bool visible, ViewType viewType = ViewType::MAIN) = 0;

        /// @brief Set Plugin Transformation Matrix
        /// @param[in] id Plugin id
        /// @param[in] matrix Matrix
        /// @note Matrix structure 4*4
        virtual void SetMatrix(EntityId id, double* matrix) = 0;
        
        /// @brief Set Pick Event Filter
        /// @param[in] type Data type, point, line, surface
        /// @note This interface only applies to plugins of type PluginType::kEntity
        virtual void PickEventFilter(PickType type) = 0;

        /// @brief Register Pick Event, Unregister Pick Event
        /// @param[in] event Event type
        /// @param[in] type Callback function
        /// @return Event id
        /// @note This interface only applies to plugins of type PluginType::kEntity, and only supports left mouse click event picking
        virtual EventId RegisterPickEvent(EventType event, PluginCallback command) = 0;
        
        /// @brief Unregister Pick Event
        /// @param[in] id Event id
        /// @note This interface only applies to plugins of type PluginType::kEntity
        virtual void UnregisterPickEvent(EventId id) = 0;

        /// @brief Unregister Pick Event
        /// @param[in] event Event type
        /// @note This interface only applies to plugins of type PluginType::kEntity
        virtual void UnregisterPickEvent(EventType event) = 0;




        virtual void RegisterRectPickEvent(RubberBandPickCallback command) = 0;
        virtual void UnregisterRectPickEvent() = 0;

        /// @brief Set Highlight
        /// @param[in] id Plugin id
        /// @note This interface only applies to plugins of type PluginType::kEntity
        virtual void SetHightLight(EntityId id) = 0;

        /// @brief Clear Highlight
        /// @param[in] id Plugin id
        /// @note This interface only applies to plugins of type PluginType::kEntity
        virtual void ClearHightLight(EntityId id) = 0;

        /// @brief Set Highlight for Specific Plugin Submodule
        /// @details This interface can be used to set the highlight of specific points, lines, and surfaces in the plugin
        /// @param[in] id Plugin id
        /// @param[in] type Data type, (point, line, surface)
        /// @param[in] indexs Submodule numbers
        /// @note This interface only applies to plugins of type PluginType::kEntity
        virtual void SetHightLight(EntityId id, PickType type, std::vector<int> indexs) = 0;

        /// @brief Clear Highlight
        /// @note This interface only applies to plugins of type PluginType::kEntity
        virtual void ClearHightLight() = 0;

        /// @brief Add Highlight to Plugin Submodule
        /// @details This interface can be used to set the highlight of specific points, lines, and surfaces in the plugin
        /// @param[in] id Plugin id
        /// @param[in] type Data type, (point, line, surface)
        /// @param[in] index Submodule number
        /// @note This interface only applies to plugins of type PluginType::kEntity
        virtual void AddHightLight(EntityId id, PickType type, int index) = 0;

        /// @brief Remove Highlight from Plugin Submodule
        /// @details This interface can be used to set the highlight of specific points, lines, and surfaces in the plugin
        /// @param[in] id Plugin id
        /// @param[in] type Data type, (point, line, surface)
        /// @param[in] index Submodule number
        /// @note This interface only applies to plugins of type PluginType::kEntity
        virtual void RemoveHightLight(EntityId id, PickType type, int index) = 0;

        /// @brief Set Highlight Color
        /// @param[in] rgb Color value, color range [0,1]
        /// @note This interface only applies to plugins of type PluginType::kEntity
        virtual void SetHightLightColor(double rgb[3]) = 0;


        /// @brief Set the cell display range for the Entity plugin
        /// @param[in] id Plugin ID
        /// @param[in] type Data type, currently supports line and face
        /// @param[in] min Minimum index
        /// @param[in] max Maximum index
        /// @note  please call "ResetEntityCellRange" before use this function
        /// @note This interface only applies to plugins of type PluginType::kEntity
        virtual void UpdateEntityCellRange(EntityId id, EntityPlugProp::DataType type,unsigned long long min = 0, unsigned long long max = 0) = 0;
        
        /// @brief Resets the range of visible cells. After calling this function, all cells will be hidden.
        /// @param[in] id Plugin ID
        /// @param[in] type Data type, currently supports line and face
        /// @see UpdateEntityCellRange
        /// @note This interface only applies to plugins of type PluginType::kEntity
        virtual void ResetEntityCellRange(EntityId id, EntityPlugProp::DataType type) = 0;

        /// @brief remove all plugins
        virtual void RemoveAll() = 0;

        /// @brief Add Highlight to Plugin Submodule
        /// @param[in] id Plugin id
        /// @note This interface only applies to plugins of type PluginType::kEntity
        virtual void AddHightLight(EntityId id) = 0;
        
        /// @brief Remove Highlight
        /// @param[in] id Plugin id
        /// @note This interface only applies to plugins of type PluginType::kEntity
        virtual void RemoveHightLight(EntityId id) = 0;


        virtual void SetPickerTolerance(double t = 0.005) = 0;

        virtual void SetUsePickOnEntity(bool b) = 0;


    };
}

#endif