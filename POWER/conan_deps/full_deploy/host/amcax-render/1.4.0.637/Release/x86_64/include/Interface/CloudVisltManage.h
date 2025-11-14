/// @file      CloudVisltManage.h
/// @brief     Cloud Object Management
/// @details   
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAXRender

#ifndef CloudVisltManage_h
#define CloudVisltManage_h

#include "CloudVislt.h"
#include "ClipAttributes.h"
#include <memory>
#include <map>

namespace AMCAXRender {
    /// @brief Cloud Rendering Properties
    /// @details Interface class for cloud rendering properties, can be used to set and get related properties
    class AMCAX_RENDER_API VisltProperty {
    public:
        /// @brief Scale Mode
        enum Scaling
        {
            Linear, ///< Linear scaling
            Log     ///< Logarithmic scaling
        };

        /// @brief Opacity Type
        enum OpacityType
        {
            FullyOpaque,  ///< Fully opaque rendering (no transparency)
            Constant,     ///< Constant transparency applied uniformly
            Ramp          ///< Transparency varies linearly with data values
        };

        virtual ~VisltProperty() {};

        /// @brief Set Cloud Object Slicer Display
        /// @param[in] type Display flag, 0: X-axis, 1: Y-axis, 2: Z-axis
        /// @param[in] value Slicer percentage, range 0 - 100
        virtual void SetSlicer(int type, int value) = 0;

        /// @brief Remove Slicer from Rendering Scene
        virtual void RemoveSlicer() = 0;

        /// @brief Remove Slicer from Rendering Scene
        /// @param[in] type Display flag, 0: X-axis, 1: Y-axis, 2: Z-axis
        virtual void RemoveSlicer(int type) = 0;

        /// @brief Set Color Map
        /// @param[in] colorMap Color map, element structure: scalar, color r,g,b
        /// @note Color range [0,1]
        virtual void SetColorMap(const std::vector <std::pair<double, std::tuple<double, double, double>>>& colorMap) = 0;

        /// @brief Compute Cloud Clip Plane
        /// @param[in] atts Clip attributes
        virtual void ComputeClip(ClipAttributes& atts) = 0;

        /// @brief Remove Clip Plane
        virtual void RemoveClip() = 0;

        /// @brief Set Color Table
        /// @param[in] index Index in the color map list
        virtual void SetColorTable(int index) = 0;

        /// @brief Sets the scaling mode for mapping scalar values to colors.
        /// @param[in] mode The scaling mode to use (Linear, Log).
        virtual void SetScaleMode(Scaling mode) = 0;

        /// @brief Sets the opacity mode for the plot.
        /// @param opacityType The type of opacity to apply (FullyOpaque, Constant, or Ramp).
        virtual void SetOpcityMode(OpacityType opacityType) = 0;

        /// @brief Sets the opacity value
        /// @param opacity The opacity value in the range [0, 1]
        virtual void SetOpcityVaule(double opacity) = 0;
    };

    /// @brief Volume Rendering Properties
    /// @details Interface class for volume rendering properties, can be used to set and get related properties
    class AMCAX_RENDER_API VisltVolumeProperty : public VisltProperty {
    public:
        
        /// @brief Set Volume Rendering to Use GPU
        /// @param[in] enable Whether to use GPU
        virtual void SetVolumeGPUEnable(bool enable) = 0;

        /// @brief Get Volume Rendering GPU Usage
        /// @return bool Whether GPU is used
        virtual bool GetVolumeGPUEnable() = 0;

        /// @brief Set Opacity Map
        /// @param[in] opacityMap Opacity map, element structure: scalar, opacity
        /// @note Opacity range [0,1]
        virtual void SetOpacityMap(const std::vector<std::pair<double, double>>& opacityMap) = 0;

        /// @brief Set Slicer Window Width and Level
        /// @param[in] window Window width 
        /// @param[in] level Window level
        virtual void SetSlicerWindowLevel(double window, double level) = 0;

        /// @brief Get Slicer Window Width and Level
        /// @see SetSlicerWindowLevel
        virtual void GetSlicerWindowLevel(double* window, double* level) = 0;

        /// @brief Get Slicer Window Width and Level Range
        /// @param[in] min Minimum value 
        /// @param[in] max Maximum value
        virtual void GetSlicerWindowLevelRange(double& min, double& max) = 0;

        /// @brief Set Threshold Switch
        /// @param[in] enable Threshold segmentation switch
        virtual void SetThresholdEnable(bool enable) = 0;

        /// @brief Set Slicer Threshold
        /// @param[in] min Minimum value 
        /// @param[in] max Maximum value
        virtual void SetSlicerThreshold(double min, double max) = 0;

        /// @brief Get Slicer Threshold Range
        /// @see SetSlicerThreshold
        virtual void GetSlicerThreshold(double* min, double* max) = 0;

        /// @brief Add Opacity Mapping Parameter
        /// @param[in] pos Voxel value
        /// @param[in] opacity Opacity, range [0,1]
        virtual void AddPointScalarOpacityMapping(double pos, double opacity) = 0;

        /// @brief Remove Opacity Mapping Parameter
        /// @param pos Voxel value
        virtual void DelPointScalarOpacityMapping(double pos) = 0;

        /// @brief Remove All Opacity Mapping Parameters
        virtual void RemoveAllPointScalarOpacityMapping() = 0;

        /// @brief Add Color Mapping Parameter
        /// @param[in] pos Voxel value
        /// @param[in] r,g,b Represent color, range 0-1.0
        virtual void AddPointScalarColorMapping(double pos, double r, double g, double b) = 0;

        /// @brief Remove Color Mapping Parameter
        virtual void DelPointScalarColorMapping(double pos) = 0;

        /// @brief Remove All Color Mapping Parameters
        virtual void RemoveAllPointScalarColorMapping() = 0;

        /// @brief Add Gradient Opacity Mapping Parameter
        /// @param[in] pos Voxel value
        /// @param[in] opacity Opacity, range [0,1]
        virtual void AddPointGradientOpacity(double pos, double opacity) = 0;

        /// @brief Remove Gradient Opacity Mapping Parameter
        virtual void DelPointGradientOpacity(double pos) = 0;

        /// @brief Remove All Gradient Opacity Mapping Parameters
        virtual void RemoveAllPointGradientOpacity() = 0;

        /// @brief ROI Callback
        using ROI_CALLBACK = std::function<void(double roi[6])>;

        /// @brief Register ROI Callback
        /// @param[in] ROI_CALLBACK Callback function
        virtual void RegisterRoiCallBack(ROI_CALLBACK) = 0;

        /// @brief Set Camera ROI
        /// @param[in] Array parameters are: -x,+x,-y,+y,-z,+z
        virtual void SetRoI(double roi[6]) = 0;

        /// @brief Get Camera ROI
        /// @see   SetRoI
        virtual void GetRoI(double roi[6]) = 0;

        /// @brief Set ROI Support
        /// @param[in] enable ROI enable flag, true: enable, false: disable
        virtual void SetROIEnable(bool enable) = 0;

        /// @brief Get ROI Enable Flag
        /// @return ROI switch
        virtual bool GetROIEnable() = 0;
    };
    /// @brief	CloudVisltManage Class
    class AMCAX_RENDER_API CloudVisltManage {
    public:
        virtual ~CloudVisltManage() {};

        /// @brief Add Cloud Object to Rendering Scene
        /// @param[in] vislt Cloud object
        /// @param[in] name Scalar name
        /// @param[in] renderType Cloud rendering type, 0: Pseudo color, 1: Volume rendering, ...
        /// @return EntityId Cloud object id
        virtual EntityId AddCloudVislt(std::shared_ptr<CloudVislt> vislt, std::string name, int renderType = 0) = 0;

        /// @brief Remove Specified Cloud Object from Rendering Scene
        /// @param[in] id Cloud object id
        virtual void Remove(EntityId id) = 0;

        /// @brief Set Cloud Object Visibility in Rendering Scene
        /// @param[in] id Cloud object id
        /// @param[in] visible Visibility flag, true: visible, false: hidden
        virtual void SetVisible(EntityId id, bool visible) = 0;

        /// @brief Get Cloud Object Visibility in Rendering Scene
        /// @param[in] id Cloud object id
        /// @return visible Visibility flag, true: visible, false: hidden
        virtual bool GetVisible(EntityId id) = 0;

        /// @brief Set Cloud Color Map Visibility in Rendering Scene
        /// @param[in] visible Visibility flag, true: visible, false: hidden
        virtual void SetVisibleColorMap(bool visible) = 0;

        /// @brief Set Edge Visibility in Rendering Scene
        /// @param[in] id Cloud object id
        /// @param[in] visible Visibility flag, true: visible, false: hidden
        virtual void SetVisibleForEdge(EntityId id, bool visible) = 0;

        /// @brief Get Cloud Properties
        /// @param[in] id Cloud object id
        /// @return Cloud properties
        virtual std::shared_ptr<VisltProperty> GetProperty(EntityId id) = 0;

        /// @brief Get Cloud Properties
        /// @tparam Property type
        /// @param[in] id Cloud object id
        /// @return Cloud properties
        template<class T>
        std::shared_ptr<T> GetProperty(EntityId id) {
            return std::dynamic_pointer_cast<T> (GetProperty(id));
        };

        /// @brief Get Color Table List
        /// @return std::vector<std::pair<std::string, int>> Color map list
        /// @note std::map<int, std::string> Index and color name
        virtual std::map<int, std::string> GetColorTableList() = 0;

        /// @brief Sets the position and size of a vtkVisItScalarBarActor in normalized viewport coordinates.
        /// @param x The x-coordinate of the bottom-left corner (in [0, 1]).
        /// @param y The y-coordinate of the bottom-left corner (in [0, 1]).
        /// @param width The width of the scalar bar (in [0, 1]).
        /// @param height The height of the scalar bar (in [0, 1]).
        ///  @return True if the settings were applied successfully, false if invalid inputs were provided.
        virtual bool SetScalarBarPositionAndSize(double x, double y, double width, double height) = 0;
    };
}

#endif