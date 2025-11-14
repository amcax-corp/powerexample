/// @file      Entity.h
/// @brief     Entity Class File
/// @details   This file defines the entity class
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAXRender
#ifndef Entity_h
#define Entity_h
#include "Macros.h"
#include "Constants.h"
#include <memory>

namespace AMCAXRender {

    /// @brief Entity Base Class
    class AMCAX_RENDER_API AbstractEntity {
    protected:
        AbstractEntity() {};
    public:
        virtual ~AbstractEntity() {}
    public:
        /// @brief Get Entity Type
        /// @return Type
        /// @see EntityDimension
        virtual EntityDimension GetDimension() = 0;

        /// @brief Get Entity ID
        /// @return Unique ID
        virtual EntityId GetEntityId() { return entityId; };

        /// @brief Set Mouse Hover Color
        /// @param[in] rgb Color 
        /// @note Color component range [0,255]
        virtual void SetHoveredColor(double rgb[3]) = 0;

        /// @brief Get Mouse Hover Color
        /// @return Color
        virtual double* GetHoveredColor() = 0;

        /// @brief Set Entity Color
        /// @param[in] rgb Color 
        /// @note Color component range [0,255]
        virtual void SetNormalColor(double rgb[3]) = 0;

        /// @brief Get Entity Color
        virtual double* GetNormalColor() = 0;

        /// @brief Get Visibility Flag
        /// @return Visibility flag
        /// @retval true Visible
        /// @retval false Hidden
        virtual bool GetVisible(ViewType viewType = ViewType::MAIN) = 0;

        /// @brief Set the pick type of an entity
        /// @param[in] type PickType
        virtual void SetPickType(PickType type) = 0;

        /// @brief Get the pick type of an entity
        /// @return PickType
        virtual PickType GetPickType() = 0;
    protected:
        EntityId entityId; ///< Unique entity identifier ID
    };

}
#endif