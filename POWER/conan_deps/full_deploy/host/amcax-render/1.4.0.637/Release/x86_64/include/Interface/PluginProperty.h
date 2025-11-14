/// @file      PluginProperty.h
/// @brief     Plugin Property File
/// @details   
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAXRender
#ifndef PluginProperty_h
#define PluginProperty_h

#include "Entity.h"
#include <map>
#include"Common.h"

namespace AMCAX {
    class TopoFace;
    class TopoShape;
    class TopoEdge;
}

namespace AMCAXRender {

    using Point3D = std::tuple<double, double, double>;
    using Point2D = std::tuple<double, double>;

    using Line3D = std::vector<Point3D>;

    class BaseProp;
    /// @brief Plugin Property Base Class
    class AMCAX_RENDER_API PluginProperty  {
    public:
        PluginProperty();
        virtual ~PluginProperty();

        /// @brief Set Opacity
        /// @param[in] opacity Opacity [0,1]
        virtual void SetOpacity(double opacity);

        /// @brief Set Translation
        /// @param[in] x Translation distance in x direction
        /// @param[in] y Translation distance in y direction
        /// @param[in] z Translation distance in z direction
        virtual void SetTranslate(double x, double y, double z);

        /// @brief Set Rotation
        /// @param[in] angle Rotation angle
        /// @param[in] x,y,z Rotation axis
        virtual void SetRotateWXYZ(double angle, double x, double y, double z);

        /// @brief Set Light On/Off
        /// @param[in] on true: on, false: off
        virtual void SetLightOn(bool on);

        /// @brief Set Visibility
        /// @param[in] visible true: visible, false: hidden
        virtual void SetVisible(bool visible);

        /// @brief Get Visibility
        /// @return  true: visible, false: hidden
        virtual bool GetVisible();
       
        /// @brief Set Matrix
        /// @param[in] 4*4 matrix
        virtual void SetMatrix(double* matrix);

        /// @brief Set Top Render On/Off
        /// @param[in] enable true: on, false: off
        virtual void SetTopRender(bool enable);

        /// @brief Get Top Render Status
        /// @return  true: top, false: normal
        virtual bool IsOnTopRender();

        virtual std::shared_ptr<PluginProperty> DeepClone() const;

    protected:
        BaseProp* mBaseProp; ///< Common property
    };

    /// @brief Entity Plugin
    /// @details This plugin is created through entity data
    class AMCAX_RENDER_API EntityPlugProp : public PluginProperty {
    public:
      
        enum PointStyle
        {
            Sphere,   // Sphere point
            PointX    // X shape
        };

        enum DataType
        {
            kEdge,   // edge
            kFace    // face
        };

        enum LineStyle
        {
            kSolid,    // Sphere point
            kDashed    // X shape
        };

        /// @brief Set the overall color of the plugin
        /// @param[in] color Color component range [0,1]
        virtual void SetColor(double color[3]) = 0;

        /// @brief Clear color
        virtual void ClearColor() = 0;

        /// @brief Set color map
        /// @param[in] colorMap Color map key: scalar value, value: r, g, b color range [0,1]
        /// @param[in] scalars List of scalar values
        /// @param[in] rampToLinear Whether to render colors linearly
        /// @note If rampToLinear==true, scalars and colorMap need to input the scalar and color of all vertices
        virtual void SetColorMap(
            std::map<double, std::vector<double>> colorMap,
            std::vector<double> scalars, 
            ColorMapType type) = 0;

        /// @brief Clear color map
        virtual void ClearColorMap() = 0;

        /// @brief Set line width
        /// @param[in] width Line width
        virtual void SetLineWidth(double width) = 0;

        /// @brief Set point size
        /// @param[in] size Point size
        virtual void SetPointSize(double size = 10) = 0;

        /// @brief Set whether it is pickable
        /// @param[in] enable true: pickable, false: not pickable
        virtual void SetPickable(bool enable) = 0;

        /// @brief Set point style
        /// @param[in] style Refer to PointStyle attribute
        virtual void SetPointStyle(PointStyle style) = 0;

        /// @brief Scale
        virtual void Scale(double x ,double y ,double z) = 0;

        /// @brief SetFixedSize
        /// @param[in] t [0.00001 ~ 1.0]
        virtual void SetFixedSize(bool b ,double t = 1.0) = 0;

        virtual void SetLineStyle(std::map<LineStyle,std::vector<uint64_t>>) = 0;
    };

    /// @brief 3D text plugin
    /// @details
    class AMCAX_RENDER_API TextLabelProp : public PluginProperty {
    public:
        TextLabelProp() {};
        virtual ~TextLabelProp() {};

        /// @brief Add text
        /// @param[in] text Text
        /// @param[in] pos Position x,y,z
        /// @param[in] color Color r,g,b
        virtual void AddText(const std::string& text, const std::vector<double>& pos, const std::vector<double>& color) = 0;
       
        /// @brief Set font size
        /// @param[in] size Font size
        virtual void SetFontSize(int size) = 0;

        /// @brief Clear text
        virtual void Clear() = 0;
    };

    /// @brief 3D arrow
    /// @details
    class AMCAX_RENDER_API ArrowProp : public PluginProperty {
    public:
        /// ArrowOrigin
        enum class ArrowOrigin {
            kStart,
            kCenter,
            kEnd
        };

        ArrowProp() {};
        virtual ~ArrowProp() {};
     
        /// @brief Add arrow data
        /// @param[in] pos Position x,y,z
        /// @param[in] dir Direction vector
        /// @param[in] color Color r,g,b
        /// @param[in] len Arrow length
        virtual void AddArrow(std::vector<double> pos, std::vector<double> dir, std::vector<double> color, double len) = 0;
        
        /// @brief Clear
        virtual void Clear() = 0;

        ///
        virtual void SetFixedSize(bool b) = 0;

        /// set tansform
        virtual void SetTransform(std::shared_ptr<CTransform>trans) = 0;
        virtual std::shared_ptr<CTransform> GetTransform() = 0;

        virtual void SetArrowOrigin(ArrowOrigin o = ArrowOrigin::kStart) = 0;
    };

    /// @brief Coordinate system
    /// @details
    class AMCAX_RENDER_API CoordinateProp : public PluginProperty {
    public:
        CoordinateProp() {};
        virtual ~CoordinateProp() {};

        /// @brief Set coordinate system parameters
        /// @param[in] pos Position x,y,z
        /// @param[in] directionZ Z direction vector
        /// @param[in] directionX X direction vector
        /// @param[in] color_x X-axis color
        /// @param[in] color_y Y-axis color
        /// @param[in] color_z Z-axis color
        /// @note Color range 0~1
        virtual void SetParams(double pos[3], double directionZ[3], double directionX[3], double color_x[3], double color_y[3], double color_z[3]) = 0;
        
        /// @brief Set coordinate system parameters
        /// @param[in] b Whether to render on top
        virtual void SetTotopRender(bool b) = 0;

        /// @brief Set text visibility flag
        /// @param[in] b Whether to display
        virtual void SetTextVisible(bool b) = 0;

        /// @brief Set axis length
        /// @param[in] len Axis length
        virtual void SetLength(double len) = 0;

        /// @brief Set ConeRadius
        virtual void SetConeRadius(double r = 0.1) = 0;

        /// @brief Set CylinderRadius
        virtual void SetCylinderRadius(double r = 0.005) = 0;

        /// @brief Set text color
        /// @note Color range is 0 to 1
        virtual void SetTextColor(double x[3], double y[3], double z[3]) = 0;

        /// @brief Set Coordinate Plugin Style
        virtual void SetCoordinatePluginStyle(CoordinatePluginStyle style) = 0;

        /// @brief Set text size
        virtual void SetTextSize(int size = 12) = 0;

        virtual void SetTransform(std::shared_ptr<CTransform>trans) = 0;

        virtual std::shared_ptr<CTransform> GetTransform() = 0;

        /// @brief Set text
        virtual void SetText(const std::string& x, const std::string& y, const std::string& z) = 0;

    };

    /// @brief Distance ruler
    /// @details Distance ruler plugin
    class AMCAX_RENDER_API DistanceProp : public PluginProperty {
    public:
        enum class EType
        {
            kLinePress, ///< Line press event
            kLabelPress, ///< Label press event
            kLineMove,   ///< Line move event
            kLabelMove,  ///< Line move event
            kHovor,      ///< Hover event
            kHovorOut,   ///< Hover out event
            kClickOut,   ///< Click out event
        };

        using CallBack = std::function<void(EType)>;
        using POINT3D = std::tuple<double, double, double>;
        DistanceProp() {};
        virtual ~DistanceProp() {};

        /// @brief Whether to use json data
        /// @param[in] use 
        virtual void SetUseJson(bool use) = 0;

        /// @brief Update json data
        /// @param[in] json 
        virtual void UpdateJsonData(void* json) = 0;

        /// @brief Register callback
        virtual void RegisterCallBack(CallBack evt) = 0;

        /// @brief Set color
        /// @param[in] lineColor Line color
        /// @param[in] arrowColor Arrow color
        virtual void SetDefaultColor(const POINT3D& lineColor, const POINT3D& arrowColor) = 0;

        /// @brief Set line data
        /// @param[in] lines Line collection
        virtual void SetLines(std::vector<Line3D>& lines) = 0;

        /// @brief Set lines with fixed offset
        /// @param[in] lines Line collection
        /// @param[in] offset Pixel offset (first: start offset, second: end offset)
        /// @note The number of elements in lines must be consistent with the number of elements in offset
        virtual void SetOffsetLines(std::vector<Line3D>& lines, const std::vector<std::tuple<double, double>>& offset) = 0;

        /// @brief Set arrow pairs
        /// @param[in] arrowPos Arrow pair position coordinates, quantity 2
        /// @param[in] arrowDirection Default direction of arrow pairs, quantity 2
        /// @note The arrows set by this interface will switch direction when the two arrows are very close
        virtual void SetArrowPairs(std::vector<Point3D>& arrowPos, const std::vector<Point3D>& arrowDirection) = 0;

        /// @brief Set fixed direction arrows
        /// @param[in] arrowPos Arrow position coordinates
        /// @param[in] arrowDirection Arrow direction
        /// @note The direction of the arrows set by this interface is fixed, and the arrow positions and directions must correspond one-to-one
        virtual void SetFixArrow(std::vector<Point3D>& arrowPos, const std::vector<Point3D>& direction) = 0;

        /// @brief Set text
        /// @param[in] labelPos Text position
        /// @param[in] labels Text content
        /// @note Chinese settings are not supported for now
        virtual void SetLabels(std::vector<Point3D>& labelPos, const std::vector<std::wstring>& labels) = 0;

        /// @brief Pick switch
        virtual void SetPickable(bool enable) = 0;

        /// @brief Set font size
        virtual void SetFontSize(int size = 14) = 0;
    };
 
    /// @brief Bounding box annotation plugin
    /// @details Plugin for drawing dashed lines
    class AMCAX_RENDER_API BoundAnnoProp : public PluginProperty {
    public:
      
        BoundAnnoProp() {};
        virtual ~BoundAnnoProp() {};


        virtual void Clear() = 0;

        /// @brief Set bounding box cube
        /// @param[in] vertex Cube vertices, combined in order
        /// @param[in] tips Label text, the number of texts must be greater than 3
        /// @note 0-1 center point annotation tips[0]; 1-2 center point annotation tips[1], 1-5 center point annotation tips[2]
        virtual void SetBox(const std::vector<Point3D>& vertex ,const std::vector<std::string>& tips) = 0;

        /// @brief Set bounding box sphere
        /// @param[in] circle Collection of arc lines, combined in order
        /// @param[in] annoLine Annotation line, arrow drawn at the end point, the line segment must contain at least 2 points
        /// @param[in] tips Label text, coordinate annotation end point
        virtual void SetCircle(const std::vector<Line3D>& circle, const Line3D& annoLine , const std::string& tip) = 0;

        /// @brief Set bounding box cylinder
        /// @param[in] circle Collection of arc lines, combined in order
        /// @param[in] annoLine Annotation line, arrows drawn at both ends, the line segment must contain at least 3 points
        /// @param[in] tip Label text, coordinate annotation midpoint, the number of texts must be at least 2
        virtual void SetCylinder(const std::vector<Line3D>& circle, const Line3D& annoLine, const std::vector<std::string>& tip) = 0;

        /// @brief Set line color
        virtual void SetLineColor(const Point3D& color) = 0;

        /// @brief Set arrow color
        virtual void SetArrowColor(const Point3D& color) = 0;

        /// @brief Set label color
        virtual void SetLabelColor(const Point3D& color) = 0;

    };

    /// @brief Arrow annotation
    /// @details 
    class AMCAX_RENDER_API ArrowAnnocationProp : public PluginProperty {
    public:
        /// @brief Annotation type
        enum class AnnoType
        {
            kDistance,      ///< Distance
            kRadius,        ///< Radius
        };

        /// @brief Label position
        enum class LabelPos
        {
            kStartPos,      ///< Start point
            kEndPos,        ///< End point
            kCenterPos,     ///< Center
        };

        ArrowAnnocationProp() {};
        virtual ~ArrowAnnocationProp() {};

        /// @brief Set endpoints
        /// @param[in] cPt Start point
        /// @param[in] ePt End point
        /// @param[in] type Annotation type
        virtual void SetPointParameter(const Point3D& cPt, const Point3D& ePt, AnnoType type = AnnoType::kDistance) = 0;

        /// @brief Set text content
        /// @param[in] text Text content
        /// @param[in] pos Text position
        virtual void SetLabel(const std::wstring& text, const LabelPos& pos = LabelPos::kCenterPos) = 0;

        /// @brief Set font size
        virtual void SetFontSize(int size = 14) = 0;

        /// @brief Set color
        virtual void SetColor(const Point3D& color) = 0;

        /// @brief Set point size
        virtual void SetPointSize(double size) = 0;

    };

    /// @brief Bounding box annotation plugin
    /// @details Plugin for drawing dashed lines
    class AMCAX_RENDER_API BoundAnnocationProp : public PluginProperty {
    public:

        /// @brief Cube Annotation
        typedef struct BoxParams_
        {
            double len;     ///< Length, X-axis
            double width;   ///< Width, Y-axis
            double hight;   ///< Height, Z-axis

            Point3D center { 0,0,0 };   ///< Center point
            Point3D directionX{1,0,0};  ///< x-axis direction
            Point3D directionY{ 0,1,0 };///< y-axis direction
        
        }BoxParams;

        /// @brief Sphere Annotation
        typedef struct SphereParams_
        {
            Point3D center{ 0,0,0 };    ///< Center point
            double  radius{ 1 };        ///< Radius
        }SphereParams;

        /// @brief Cylinder Annotation
        typedef struct CylinderParams_
        {
            Point3D center1{ 0,0,0 };   ///< Center point
            Point3D center2{ 0,0,0 };   ///< Center point
            double  radius { 1 };       ///< Radius
            Point3D normal { 0,0,1};    ///< Cylinder central axis direction
        }CylinderParams;

        BoundAnnocationProp() {};
        virtual ~BoundAnnocationProp() {};

        virtual void Clear() = 0;

        /// @brief Cube annotation
        virtual void SetBoxParameter(const BoxParams& param) = 0;

        /// @brief Spherical bounding box
        virtual void SetSphereParameter(const SphereParams& param) = 0;

        /// @brief Cylinder annotation parameters
        virtual void SetCylinderParameter(const CylinderParams& param) = 0;

        /// @brief Set overall color
        /// @param[in] color RGB channels, range [0,1]
        virtual void SetColor(const Point3D& color) = 0;

        /// @brief Set annotation font size
        virtual void SetPointSize(double size = 14) = 0;

        /// @brief Set annotation unit
        /// @param[in] unit Unit
        virtual void SetUnit(const std::string& unit = "mm") = 0;
    };

    /// @brief Measure plugin
    /// @details 
    class AMCAX_RENDER_API MeasureProp : public PluginProperty {
    public:

        /// @brief Line style
        /// Line types
        enum LineStyle
        {
            kSolid,     ///< Solid line
            kBoldSolid, ///< Bold solid line
            kDashed,    ///< Dashed line
            kBoldDashed ///< Bold dashed line
        };

        /// @brief Draggable label
        struct LeaderLabel
        {
            Point3D anchorPoint;    // Anchor point of the label (double)
            Point3D floatingPoint;  // Floating point of the label, modifiable by the render control
            std::wstring label;     // The label text
            std::wstring value;     // The value associated with the label
            Point3D color;          // The label's color (double)
        };

        /// @brief Strip line
        struct StripLine
        {
            Line3D    line;         // The line object
            LineStyle style;        // The line style
            Point3D   color;        // The color of the line
        };

        /// @brief Offset line segment
        struct OffsetLine
        {
            Point3D   p0;           ///< Endpoint 0
            Point3D   p1;           ///< Endpoint 1
            Point2D   offset;       ///< Pixel offset between endpoint 0 and endpoint 1
            LineStyle style;        // The style of the offset line
            Point3D   color;        // The color of the offset line
        };

        /// @brief Arrow pair
        /// Arrows automatically switch direction based on the distance
        struct ArrowPair
        {
            Point3D  pos1;          ///< The center of arrow 1
            Point3D  direction1;    ///< The direction of arrow 1
            Point3D  pos2;          ///< The center of arrow 2
            Point3D  direction2;    ///< The direction of arrow 2
            Point3D  color;         // The color of the arrows
        };

        /// @brief Directional arrow
        struct DirectionArrow
        {
            Point3D  pos;           // The position of the directional arrow
            Point3D  direction;     // The direction of the arrow
            Point3D  color;         // The color of the arrow
        };

        MeasureProp() {};          // Default constructor
        virtual ~MeasureProp() {}; // Virtual destructor

        /// @brief Set the leader labels 
        /// Function to set the leader labels
        virtual void SetLeaderLabel(const std::vector<LeaderLabel>& label) = 0;

        /// @brief Set the strip lines
        /// Function to set the strip lines
        virtual void SetStripLine(const std::vector<StripLine>& line) = 0;

        /// @brief Set the offset lines
        /// Function to set the offset lines
        virtual void SetOffsetLine(const std::vector<OffsetLine>& offsetLine) = 0;

        /// @brief Set the arrow pair
        /// Function to set the arrow pair
        virtual void SetArrowPair(const std::vector <ArrowPair>& arrow) = 0;

        /// @brief Set the directional arrows
        /// Function to set the directional arrows
        virtual void SetDirectionArrow(const std::vector<DirectionArrow>& arrow) = 0;

    };


    /// @brief 2D text plugin
    /// @details
    class AMCAX_RENDER_API TextLabel2dProp : public PluginProperty {
    public:
        TextLabel2dProp() {};
        virtual ~TextLabel2dProp() {};

        /// @brief SetText
        /// @param[in] text Text
        /// @param[in] pos Position x,y,z
        /// @param[in] color Color r,g,b
        virtual void SetText(const std::wstring& text, const Point3D& pos, const Point3D& color) = 0;

        /// @brief Set point size
        /// @param[in] size Point size
        virtual void SetPointSize(double size = 12) = 0;

    };

    /// @brief EntityClip by clipping plane
    /// @details
    class AMCAX_RENDER_API EntityClipProp : public PluginProperty {
    public:
        EntityClipProp() {};
        virtual ~EntityClipProp() {};

        /// @brief AttachEntity
        /// @param[in] entity The entity object
        virtual void AttachEntity(std::vector<std::shared_ptr<AbstractEntity>> entityList) = 0;

        /// @brief Set/Get the normal vector of the clipping plane
        virtual void SetNormal(const Point3D& n) = 0;
        virtual void GetNormal(Point3D& n) = 0;

        /// @brief Set/Get the origin point of the clipping plane
        virtual void SetOrigin(const Point3D& o) = 0;
        virtual void GetOrigin(Point3D& o) = 0;

        /// @brief Reset the clipping plane
        virtual void Reset() = 0;
    };

    /// @brief TextureProp
    /// @details
    class AMCAX_RENDER_API TextureProp3D : public PluginProperty {
    public:

        /// @brief Texture Data
        struct  TextureData {
            std::vector<double> points;    //position
            std::vector<double> scales;    //xyz scale
            std::vector<float>  angles;    //Spin angle
            std::vector<uint8_t> colors;   //rgb 0-255
            std::vector<double>  normals;  //normal direction      
        };
        TextureProp3D() {};
        virtual ~TextureProp3D() {};
   
        virtual void CreateTexture(std::shared_ptr<AbstractEntity> entity, AMCAXRender::TextureProp3D::TextureData& data) = 0;

        virtual void ClipByRegion(const std::vector<AMCAX::TopoEdge>& region) = 0;
        
        /// @brief Gets the intersecting texture IDs
       /// @param[in] interIds Texture IDs with intersection points (textures intersecting the boundary)
       /// @param[in] insideIds Texture IDs completely inside the specified region
       /// @param[in] outsideIds Texture IDs completely outside the specified region
        virtual void GetIntersectionIds(std::vector<uint32_t>& interIds, std::vector<uint32_t>& insideIds, std::vector<uint32_t>& outsideIds) = 0;

        virtual void SetRegionColor(Point3D rgb) = 0;

    };

#ifdef USE_AMCAX_KERNEL

    /// @brief TextureProp
    /// @details
    class AMCAX_RENDER_API TextureProp2D : public PluginProperty {
    public:
      
        /// Shape type
        enum Type {
            kNone,
            kRect,
            kEllipse,
            kCircle,
        };
        class Shape {
        public:
            virtual ~Shape() {}
            Type t = kNone;
        };

        ///rect
        class RectShape : public Shape{
        public:
            RectShape()     
            {
               t = Type::kRect;
            }
            double w = 0.0;
            double h = 0.0;
        };

        // Circle or ellipse shape
        class EllipseShape : public Shape {
        public:
            EllipseShape() {
                t = Type::kEllipse;
            }
            double majorRadius = 0.1;  // Major radius (semi-major axis)
            double minorRadius = 0.0;  // Minor radius (semi-minor axis)
            Point2D d = { 1, 0 };        // Orientation direction vector
        };

        // Circle
        class CircleShape : public Shape {
        public:
            CircleShape() {
                t = Type::kCircle;
            }
            double radius = 0.1;  // radius
        };
        struct TextureData {
            std::shared_ptr<Shape> shape;    // Texture geometry representation
            std::vector<Point2D> uvPos;     // UV coordinate mapping
            std::vector<Point2D> scales;    // UV scaling factors (s,t)
            std::vector<Point3D> colors;    // RGB color values (0-255 per channel)
            std::vector<float> angle;       // Texture rotation angles (degrees)
        };

        TextureProp2D() {};
        virtual ~TextureProp2D() {};

        // @brief Create texture array
        virtual void CreateTexture(AMCAX::TopoFace face, AMCAXRender::TextureProp2D::TextureData& data) = 0;

        /// @brief Clip by polygonal region
        /// @param[in] region The edge defining the clipping region polygon
        virtual void ClipByRegion(const std::vector<AMCAX::TopoEdge>& region) = 0;

        /// @brief Clip with dual planes
        /// @param[in] c_0      Origin point of the first clipping plane
        /// @param[in] normal_0  Normal vector of the first clipping plane
        /// @param[in] c_1      Origin point of the second clipping plane
        /// @param[in] normal_1  Normal vector of the second clipping plane
        virtual void ClipByPlane(const Point3D& c_0, const Point3D& normal_0, const Point3D& c_1, const Point3D& normal_1) = 0;

        /// @brief Control visibility of clipping tools
        /// @param[in] visible Toggle visibility state for clipping regions/planes
        virtual void SetClipToolsVisible(bool visible) = 0;

        /// @brief Gets the intersecting texture IDs
        /// @param[in] interIds Texture IDs with intersection points (textures intersecting the boundary)
        /// @param[in] insideIds Texture IDs completely inside the specified region
        /// @param[in] outsideIds Texture IDs completely outside the specified region
        virtual void GetIntersectionIds(std::vector<uint32_t>& interIds, std::vector<uint32_t>& insideIds, std::vector<uint32_t>& outsideIds) = 0;

        virtual void SetRegionColor(Point3D rgb) = 0;

    };

#endif


    /// @brief Distance Dimension
    /// @details
    class AMCAX_RENDER_API LinearDimensionProp : public PluginProperty {
    public:
        using CallBack = std::function<void(double)>;

        LinearDimensionProp() {};
        virtual ~LinearDimensionProp() {};

        /// @brief Set the base plane
        /// @param[in] origin The origin point of the plane
        /// @param[in] normal The normal vector of the plane
        virtual void SetBasePlane(const Point3D& origin, const Point3D& normal) = 0;

        /// @brief Set callback,get distance value
        virtual void SetCallBack(CallBack callback) = 0;

    };

    /// @brief Angle Dimension
    /// @details
    class AMCAX_RENDER_API AngleDimensionProp : public PluginProperty {
    public:
        using CallBack = std::function<void(double)>;

        AngleDimensionProp() {};
        virtual ~AngleDimensionProp() {};

        /// @brief Set the base plane
        /// @param[in] origin The origin point of the plane
        /// @param[in] normal The normal vector of the plane
        virtual void SetBasePlane(const Point3D& origin, const Point3D& normal) = 0;
        
        /// @brief Set callback,get angle value
        virtual void SetCallBack(CallBack callback) = 0;

    };

    /// @brief MoveAxes system
    /// @details
    class AMCAX_RENDER_API MoveAxesProp : public PluginProperty {
    public:

        using CallBack = std::function<void(double* matrix)>;

        MoveAxesProp() {};
        virtual ~MoveAxesProp() {};

        /// @brief Set Axes parameters
        /// @param[in] pos Position x,y,z
        /// @param[in] callback call back fuction
        virtual void SetCallBack(CallBack callback) = 0;

        /// @brief move center 
        /// @param[in] center Position x,y,z
        virtual void MoveTo(const Point3D& center) = 0;
    };
}

#endif