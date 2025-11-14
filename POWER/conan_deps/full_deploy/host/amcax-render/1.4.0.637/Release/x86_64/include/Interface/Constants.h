/// @file      Constants.h
/// @brief     Constants Class File
/// @details   This file defines the Constants class
/// @copyright Copyright (c) 2023 Hefei Jiushuo Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAXRender
#ifndef Constants_h
#define Constants_h

#include "Macros.h"
#include <string>
#include <vector>
#include <functional>

namespace AMCAX {
    class TopoShape;
}

namespace AMCAXRender
{
    typedef std::string EntityId;
    typedef int EventId;
    
    /// @brief CTR Window Type
    enum class ViewType
    {
        MAIN,	///< MAIN Rendering Window
        TOP,	///< TOP Rendering Window
        FRONT,	///< FRONT Rendering Window
        RIGHT	///< RIGHT Rendering Window   
    };

    /// @brief Entity Data Type
    enum class EntityDimension {
        UNKNOWN,
        D0, ///< Point
        D1, ///< Curve, Lines 
        D2, ///< Face
        D3,	///< Body
        GROUP ///< Group
    };

    /// @brief Coordinate System Style
    enum class CoordStyle {
        none,		
        cubeView,	///< Cube Style
        sailView,	///< Sail Style
        cubeView2,	///< Cube Style 2
        cubeView3	///< Cube Style 3
    };

    /// @brief Mouse Interaction Style
    enum class InteractonStyle {
        interaction_1,    ///< Style 1
        interaction_2,    ///< Style 2
        imageStyle,       ///< ImageStyle
        interaction_3,    ///< Style 3

        unknown           ///< unknown
    };


    enum class InteractionOperation {
        None,
        Rotate,
        Pan,
        Zoom
    };

    enum class InteractionHotKey {
        LeftButton,
        MiddleButton,
        RightButton
    };

    enum class RotationCenter {
        Default,
        Origin,
        BoundingBoxCenter
    };

    /// @brief Pick Event Type
    enum class EventType
    {
        mouse_hovered,		///< Hovered
        mouse_hovered_out,	///< Hovered Out
        mouse_click,		///< Left Click
        mouse_double_click,	///< Left Double Click
        mouse_click_null	///< Null Click
    };

    /// @brief Mouse Event Type
    enum class MouseEventType
    {
        mouse_move,		///< Mouse Move
        mouse_leftDown,	///< Left Button Down
        mouse_leftUp	///< Left Button Up
    };

    /// @brief Pick Type
    enum class PickType
    {
        unknown = 1 << 0,
        vert = 1 << 1,					  ///< Vertex Pick
        point = 1 << 2,					  ///< Point Pick
        edge = 1 << 3,					  ///< Edge Pick
        face = 1 << 4,					  ///< Face Pick
        body = vert | point | edge | face,///< Body Pick
        all = 1 << 5 | body				  ///< All Pick
    };

    inline PickType operator|(PickType lhs, PickType rhs) {
        return static_cast<PickType>(static_cast<int>(lhs) | static_cast<int>(rhs));
    }

    inline PickType& operator|=(PickType& lhs, PickType rhs) {
        lhs = lhs | rhs;
        return lhs;
    }

    inline PickType operator&(PickType lhs, PickType rhs) {
        return static_cast<PickType>(static_cast<int>(lhs) & static_cast<int>(rhs));
    }

    inline PickType& operator&=(PickType& lhs, PickType rhs) {
        lhs = lhs & rhs;
        return lhs;
    }

    inline PickType operator~(PickType lhs) {
        return static_cast<PickType>(~static_cast<int>(lhs));
    }

    /// @brief Coordinate System Marker Event Type
    enum class MarkerEvent
    {
        sailViewEvent, ///< Sail
        cubeViewEvent  ///< Cube
    };

    /// @brief Marker Type
    enum class MarkerType
    {
        unknown,
        sailXY,
        sailXZ,
        sailYZ,

        CUBE_UP,
        CUBE_DOWN,
        CUBE_RIGHT,
        CUBE_LEFT,
        CUBE_FRONT,
        CUBE_BACK,

        CUBE_FRONT_RIGHT_UP,
        CUBE_RIGHT_BACK_UP,
        CUBE_LEFT_FRONT_UP,
        CUBE_BACK_LEFT_UP,
        CUBE_FRONT_RIGHT_DOWN,
        CUBE_RIGHT_BACK_DOWN,
        CUBE_LEFT_FRONT_DOWN,
        CUBE_BACK_LEFT_DOWN,
        CUBE_FRONT_RIGHT,
        CUBE_RIGHT_BACK,
        CUBE_LEFT_FRONT,
        CUBE_BACK_LEFT,
        CUBE_FRONT_UP,
        CUBE_BACK_UP,
        CUBE_FRONT_DOWN,
        CUBE_BACK_DOWN,
        CUBE_RIGHT_UP,
        CUBE_LEFT_UP,
        CUBE_RIGHT_DOWN,
        CUBE_LEFT_DOWN
    };

    /// @brief Camera Mode
    enum class CameraMode
    {
        k3d,///< 3D Mode
        k2d ///< 2D Mode
    };

    /// @brief Standard Plane Style
    enum class PlaneStyle {
        none,
        standardPlane
    };

    /// @brief Camera View
    enum class CameraView
    {
        UP = 0,
        DOWN,
        RIGHT,
        LEFT,
        FRONT,
        BACK,

        FRONT_RIGHT_UP,
        RIGHT_BACK_UP,
        LEFT_FRONT_UP,
        BACK_LEFT_UP,
        FRONT_RIGHT_DOWN,
        RIGHT_BACK_DOWN,
        LEFT_FRONT_DOWN,
        BACK_LEFT_DOWN,

        FRONT_RIGHT,
        RIGHT_BACK,
        LEFT_FRONT,
        BACK_LEFT,
        FRONT_UP,
        BACK_UP,
        FRONT_DOWN,
        BACK_DOWN,
        RIGHT_UP,
        LEFT_UP,
        RIGHT_DOWN,
        LEFT_DOWN
    };

    /// @brief Plugin Type
    enum class PluginType
    {
        kUnkown = 0,
        kEntity ,			///< Entity	
        kTextLabel,			///< Text
        kArrow,				///< Arrow
        kCoordinate,		///< Coordinate System
        kDistance,			///< Distance Ruler
        kBoundAnno,			///< Bounding Box Plugin
        kArrowAnnocation,   ///< Arrow Annotation, Supports Single and Double Arrow
        kBoundsAnnocation,  ///< Bounding Box Annotation Plugin
        kMeasureMent,       ///< Measure Plugin
        k2dTextLabel,       ///< 2dTextLabel
        kEntityClip,        ///< EntityClip
        kTextureProp,       ///< TextureProp
        kTexture2D,         ///< Texture2D
        kLinearDimension,   ///< LinearDimension
        kAngleDimension,    ///< AngleDimension
        kMoveAxes,          ///< MoveAxes




    };

    /// @brief Coordinate Plugin Style
    enum class CoordinatePluginStyle
    {
        Default = 0,            ///< Default
        NoArrowHead,			///< NoArrowHead	
        OpenArrowHead,			///< OpenArrowHead
        SolidArrowHead,			///< SolidArrowHead
        Planes,		            ///< Planes
    };

    /// @brief Rubber Band Status
    enum class RubberBandStatus
    {
        Disable = 0,
        ZoomPermanent,	///< Zoom Permanent
        ZoomOnce,		///< Zoom Once
        PickPermanent,	///< Pick Permanent
        PickOnce,		///< Pick Once
    };

    /// @brief Zebra Line Thickness
    enum class LineThickness {
        Thickest = 6, // Thickest
        Thick = 5,    // Thicker
        Medium = 4,   // Thick
        Normal = 3,   // Normal
        Thin = 2,     // Thin
        Thinner = 1,  // Thinner
        Thinnest = 0  // Thinnest
    };

    /// @brief Color Map Type
    enum class ColorMapType {
        CellLinearColorByCellScalar = 0,        ///< Apply color to cells based on cell scalars, with linear color mapping. Formerly known as: rampToLinear
        CellStepColorByCellScalar,              ///< Apply color to cells based on cell scalars, with step color mapping. Formerly known as: rampToStep

        CellLinearColorByPointScalar,           ///< Apply color to cells based on point scalars, with linear color mapping. Formerly known as: beforeRrampToLinear
        CellStepColorByPointScalar,             ///< Apply color to cells based on point scalars, with step color mapping. Formerly known as: beforeRampToStep

    };

    /// @brief Render Mode Type
    enum class RenderMode {
        Normal = 0,     ///< Normal Mode
        Shaded,         ///< Shading Mode
        Edge,           ///< Edge Mode
        Wireframe,      ///< Wireframe Mode
        NoFrame,        ///< No Frame Mode
        Transparent,    ///< Transparent Mode
        HiddenLinesRemoved  ///< Hidden Lines Removed Mode
    };

    /// @brief Light type
    enum class LightType
    {
        Directional = 0,    ///< directional light
        Point,      ///< point light
        Spot            ///< spot light
    };

    /// @brief Pick Callback Function
    /// @param EntityId Parent Entity ID
    /// @param EntityId Child Entity ID
    /// @param PickType Pick Type, e.g., Point, Line, Face...
    /// @param int Pick Index, e.g., Which Face, Which Point...
    /// @param int* Mouse Pixel Coordinates
    using Command = std::function<void(EntityId, EntityId, PickType, int, int*)>;

    /// @brief Marker Callback
    /// @param MarkerType Returns Current Direction
    using MarkerCommand = std::function<void(MarkerType)>;

    /// @brief Movable Coordinate System Component Callback
    /// @param EntityId Entity ID
    /// @param matrix Transformation Matrix, The Matrix Structure is 4x4
    using MoveAxesCommand = std::function<void(EntityId,double* matrix)>;

    /// @brief TopoShape Pick Callback Function
    /// @param EntityId Parent Entity ID
    /// @param EntityId Child Entity ID
    /// @param PickType Pick Type, e.g., Point, Line, Face...
    /// @param shape TopoShape Data
    /// @param int* Mouse Pixel Coordinates
    using ShapeCommand = std::function<void(EntityId, EntityId, PickType, const AMCAX::TopoShape& shape, int*)>;

    /// @brief Plugin Pick Callback Function
    /// @param EntityId Plugin ID
    /// @param PickType Pick Type, e.g., Point, Line, Face...
    /// @param int Pick Index, e.g., Which Face, Which Point...
    /// @param double* Specific World Coordinates Closest to Mouse Position (Located on the Currently Selected Plugin)
    using PluginCallback = std::function<void(EntityId, PickType, int, double*)>;

    /// @brief Rubber Band Zoom Callback
    using RubberBandZoomCallback = std::function<void()>;

    /// @brief Rubber Band Pick Callback
    using RubberBandPickCallback = std::function<void(std::unordered_map<EntityId, std::unordered_map<PickType, std::vector<int>>>)>;

    /// @brief Mouse Event Callback
    using MouseCommand = std::function<void(MouseEventType)>;

    /// @brief Focus Event Callback
    using FocusCommand = std::function<void()>;

}

#define renderGetMacro(name, type) \
public: \
  type Get##name() const { return this->name; }

#define renderSetMacro(name, type) \
public: \
  void Set##name(type value) { this->name = value; }

#define renderGetSetMacro(name, type) \
  renderGetMacro(name, type) \
  renderSetMacro(name, type)


#endif