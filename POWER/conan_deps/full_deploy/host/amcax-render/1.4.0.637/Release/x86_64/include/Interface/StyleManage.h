/// @file      StyleManage.h
/// @brief     Style Management
/// @details   
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAXRender
#ifndef StyleManage_h
#define StyleManage_h

#include "Macros.h"
#include "Constants.h"
#include<map>
#include "RubberBandPickConfig.h"
namespace AMCAXRender {

    /// @brief Style Management Class
    /// @details Mainly used for switching mouse styles, such as: whether the right mouse button rotates or the middle mouse button rotates, etc.
    class AMCAX_RENDER_API StyleManage {
    public:
        virtual ~StyleManage() {};
    public:

        /// @brief Coordinate System Direction Indicator Style Setting
        /// @param[in] style Coordinate system style (cube, sail, etc.)
        virtual void SetMarkerStyle(CoordStyle style) = 0;
        
        /// @brief Coordinate System Direction Indicator Style Setting
        /// @param[in] style Coordinate system position
        virtual void SetMarkerPosition(double x1, double y1, double x2, double y2) = 0;

        /// @brief 
        virtual void SetHoverStyle() = 0;

        /// @brief Set Interaction Style
        /// @param[in] style Interaction style
        /// @note InteractonStyle
        virtual void SetIneractoinStyle(InteractonStyle style) = 0;

        virtual void SetIneractoinStyleHotKey(InteractionOperation op, InteractionHotKey key) = 0;

        virtual void SetRotationCenter(RotationCenter rotationCenter) = 0;
        /// @brief Whether the direction indicator supports mouse interaction
        /// @param[in] enable true: enable, false: disable
        virtual void SetMarkerInteractive(bool enable) = 0;

        /// @brief Set Standard Plane Style
        /// @param[in] style
        virtual void SetPlaneStyle(PlaneStyle style) = 0;

        /// @brief Set Background Color 1
        /// @param[in] r,g,b Color component values
        virtual void SetBackground(double r, double g, double b) = 0;

        /// @brief Set Background Color 2
        /// @param[in] r,g,b Color component values
        virtual void SetBackground2(double r, double g, double b) = 0;

        /// @brief Background Gradient Color Switch
        /// @param[in] true: enable gradient color, false: disable gradient color
        /// @note Gradient color will only take effect when both SetBackground and SetBackground2 colors are set
        virtual void SetGradientBackground(bool enable) = 0;

        /// @brief Set Color Bar Position and Orientation
        /// @param[in] pos: bottom left position
        /// @param[in] orientationToVertical true: vertical direction, false: horizontal direction
        virtual void SetColorBarPosition(double pos[4],bool orientationToVertical = true)= 0;

        /// @brief Set Color Bar Visibility
        /// @param[in] visible true: visible, false: hidden
        virtual void SetColorBarVisible(bool visible) = 0;

        /// @brief Set Color Bar Data
        /// @param[in] colorList Color list value: r,g,b
        /// @param[in] labels Label values
        virtual void SetColorBarColorMap(const std::vector<std::vector<double>>& colorList, const std::vector<std::string>& labels) = 0;

        /// @brief Set Color Bar Data
        /// @param[in] colorMap  key: scalar value, value: color value
        /// @param[in] labels  custom labels
        /// @param[in] linear  should linear mapping be used
        virtual void SetColorBarColorMap2(const std::map<double, std::vector<double>>& colorMap, const std::vector<std::string>& labels, bool linear) = 0;

        /// @brief Set Pick Color Enable
        /// @param[in] enable  true: enable, false: disable
        virtual void SetPickColorEnable(bool enable) = 0;

        /// @brief Set Rubber Band Pick Configuration
        /// @param[in] isLeft2Right  true: set parameters for left-to-right selection, false: set parameters for right-to-left selection
        /// @param[in] config  Rubber band pick configuration
        virtual void SetRubberBandPickConfig(bool isLeft2Right, const RubberBandPickConfig& config) = 0;
        virtual RubberBandPickConfig& GetRubberBandPickConfig(bool isLeft2Right) = 0;

        /// @brief Set widget title menu
        /// @param[in] enable
        virtual void ShowTitleMenu(bool enable) = 0;

        /// @brief Set render mode
        /// @param[in] mode 
        virtual void SetRenderMode(RenderMode mode) = 0;

        /// @brief Get render mode
        /// @return render mode 
        virtual RenderMode GetRenderMode() = 0;

        /// @brief Set render mode
        /// @param[in] id
        /// @param[in] mode 
        /// @note Cannot support setting shaded mode for single entity
        virtual void SetRenderMode(EntityId id, RenderMode mode) = 0;

        /// @brief Get render mode
        /// @param[in] id
        /// @return render mode 
        virtual RenderMode GetRenderMode(EntityId id) = 0;

        /// @brief Set FAXX anti - aliasing
        /// @param[in] enable Turn on / off FXAA anti - aliasing,
        virtual void SetUseFAXX(bool enable) = 0;

        virtual void SetDefaultTransparentValue(double val) = 0;
    };
}
#endif