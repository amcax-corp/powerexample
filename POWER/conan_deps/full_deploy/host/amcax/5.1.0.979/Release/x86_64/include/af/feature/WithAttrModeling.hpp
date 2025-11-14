/// @file      WithAttrModeling.hpp
/// @brief     The classes of WithAttrModeling.
/// @details   Support the modeling operations with attributes.
/// @copyright Copyright (c) 2025 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX Kernel.
#pragma once

#include "WithAttrBase.hpp"
#include "af/label/Label.hpp"
#include <common/AxisT.hpp>
#include <common/Macros.hpp>
#include <common/PointT.hpp>
#include <common/TransformationT.hpp>
#include <common/VectorT.hpp>
#include <common/Constants.hpp>
#include <list>
#include <math/CircleT.hpp>
#include <math/EllipseT.hpp>
#include <math/LineT.hpp>
#include <math/ParabolaT.hpp>
#include <math/Plane.hpp>
#include <modeling/MakeBox.hpp>
#include <modeling/MakeCone.hpp>
#include <modeling/MakePrism.hpp>
#include <modeling/MakeCylinder.hpp>
#include <modeling/MakeShape.hpp>
#include <modeling/MakeSphere.hpp>
#include <modeling/MakeTorus.hpp>
#include <modeling/MakeRevol.hpp>
#include <modeling/MakeEdge.hpp>
#include <modeling/MakeEdge2d.hpp>
#include <modeling/MakeFace.hpp>
#include <modeling/MakeHalfSpace.hpp>
#include <modeling/MakePolygon.hpp>
#include <modeling/MakeRevolution.hpp>
#include <modeling/MakeRightPrism.hpp>
#include <modeling/MakeShell.hpp>
#include <modeling/MakeSolid.hpp>
#include <modeling/MakeVertex.hpp>
#include <modeling/MakeWedge.hpp>
#include <modeling/MakeWire.hpp>
#include <modeling/TransformShape.hpp>
#include <modeling/CopyShape.hpp>
#include <modeling/GeneralTransformShape.hpp>
#include <fillet/MakeChamfer.hpp>
#include <fillet/MakeFillet.hpp>
#include <modeling/MakePyramid.hpp>
#include <offset/MakePipe.hpp>
#include <topology/TopoCast.hpp>
#include <vector>

namespace AMCAX
{
/// @brief The class of WithAttr<MakePrism>
template<>
class WithAttr<MakePrism>: public WithAttrBase {
public:
    /// @brief Construct a WithAttr<MakePrism> with a TopoShape and a Vector3
    /// @param s The base shape
	/// @param v The extrusion vector
	/// @param copy Whether copy a base shape
	/// @param canonize Whether canonized to elementary surfaces
    AMCAX_API WithAttr(const TopoShape& s, const Vector3& v, bool copy = false, bool canonize = true);

    /// @brief Perform the build algorithm
    AMCAX_API void Build() override;
    
private:
    TopoShape _s;
    Vector3 _v;
    bool _copy;
    bool _canonize;
};

/// @brief The class of WithAttr<MakeSphere>
template<>
class WithAttr<MakeSphere>: public WithAttrBase {
public:
    /// @brief Construct a WithAttr<Sphere> with r
    /// @param r The radius
    AMCAX_API WithAttr(double r);
        
    /// @brief Construct a WithAttr<Sphere> with r and angle3
    /// @param r The radius
	/// @param angle3 The rotation angle (longitude)
    AMCAX_API WithAttr(double r, double angle3);
    
    /// @brief Construct a WithAttr<Sphere> with r, angle1 and angle2
    /// @param r The radius
	/// @param angle1 The start angle (latitude)
	/// @param angle2 The end angle (latitude)
    AMCAX_API WithAttr(double r, double angle1, double angle2);
    
    /// @brief Construct a WithAttr<Sphere> with r, angle1, angle2 and angle3
    /// @param r The radius
	/// @param angle1 The start angle (latitude)
	/// @param angle2 The end angle (latitude)
	/// @param angle3 The rotation angle (longitude)
    AMCAX_API WithAttr(double r, double angle1, double angle2, double angle3);
    
    /// @brief Set r of the sphere
    /// @details Triggering a Rebuild
    /// @param r The radius to set
    /// @return True if the rebuid is success, otherwise return false.
    AMCAX_API bool SetR(double r);

    /// @brief Set angle1 of the sphere
    /// @details Triggering a Rebuild
    /// @param angle1 The start angle (latitude) to set
    /// @return True if the rebuid is success, otherwise return false.
    AMCAX_API bool SetAngle1(double angle1);

    /// @brief Set angle2 of the sphere
    /// @details Triggering a Rebuild
    /// @param angle2 The end angle (latitude) to set
    /// @return True if the rebuid is success, otherwise return false.
    AMCAX_API bool SetAngle2(double angle2);

    /// @brief Set angle3 of the sphere
    /// @details Triggering a Rebuild 
    /// @param angle3 The rotation angle (longitude) to set
    /// @return True if the rebuid is success, otherwise return false.
    AMCAX_API bool SetAngle3(double angle3);

    /// @brief Perform the sphere build
    AMCAX_API void Build() override;

private:
    enum class ConstructType {
        NONE,
        ANGLE3,
        ANGLE12,
        ANGLE123
    };
    ConstructType _constructType{ConstructType::NONE};
    double _r, _angle1, _angle2, _angle3;
};

/// @brief The class of WithAttr<MakeTorus>
template<>
class WithAttr<MakeTorus>: public WithAttrBase {
public:
    /// @brief Construct a WittAttr<MakeTorus> with r1 and r2
    /// @param r1 The major radius
	/// @param r2 The minor radius
    AMCAX_API WithAttr(double r1, double r2);

    /// @brief Construct a WittAttr<MakeTorus> with r1, r2 and angle3
    /// @param r1 The major radius
	/// @param r2 The minor radius
	/// @param angle3 The rotation angle
    AMCAX_API WithAttr(double r1, double r2, double angle3);

    /// @brief Construct a WittAttr<MakeTorus> with r1, r2, angle1 and angle2
    /// @param r1 The major radius
	/// @param r2 The minor radius
	/// @param angle1 The start angle
	/// @param angle2 The end angle
    AMCAX_API WithAttr(double r1, double r2, double angle1, double angle2);

    /// @brief Construct a WittAttr<MakeTorus> with r1, r2, angle1, angle2 and angle3
    /// @param r1 The major radius
	/// @param r2 The minor radius
	/// @param angle1 The start angle
	/// @param angle2 The end angle
	/// @param angle3 The rotation angle
    AMCAX_API WithAttr(double r1, double r2, double angle1, double angle2, double angle3);

    /// @brief Set r1 of the torus
    /// @details Triggering a Rebuild
    /// @param r1 The major radius to set
    /// @return True if the rebuid is success, otherwise return false.
    AMCAX_API bool SetR1(double r1);

    /// @brief Set r2 of the torus
    /// @details Triggering a Rebuild
    /// @param r2 The minor radius to set
    /// @return True if the rebuid is success, otherwise return false.
    AMCAX_API bool SetR2(double r2);

    /// @brief Set angle1 of the torus
    /// @details Triggering a Rebuild
    /// @param angle1 The start angle to set
    /// @return True if the rebuid is success, otherwise return false.
    AMCAX_API bool SetAngle1(double angle1);

    /// @brief Set angle2 of the torus
    /// @details Triggering a Rebuild
    /// @param angle2 The end angle to set
    /// @return True if the rebuid is success, otherwise return false.
    AMCAX_API bool SetAngle2(double angle2);

    /// @brief Set angle3 of the torus
    /// @details Triggering a Rebuild
    /// @param angle3 The rotation angle to set
    /// @return True if the rebuid is success, otherwise return false.
    AMCAX_API bool SetAngle3(double angle3);

    /// @brief Perform the torus build
    AMCAX_API void Build() override;

private:
    enum class ConstructType {
        NONE,
        ANGLE3,
        ANGLE12,
        ANGLE123
    };
    ConstructType _constructType{ConstructType::NONE};
    double _r1, _r2, _angle1, _angle2, _angle3;
};

/// @brief The class of WithAttr<MakePipe>
template<>
class WithAttr<MakePipe>: public WithAttrBase {
public:
    /// @brief Construct a WithAttr<MakePipe> with spline and profile
    /// @param spine The spine which can be open or closed but must be at least G1 continuity.
	/// @param profile The profile to be swept. It is ok to be 3d or 2d, close or open.
    AMCAX_API WithAttr(const TopoWire& spline, const TopoShape& profile);

    /// @brief Perform the pipe build
    AMCAX_API void Build() override;

private:
    TopoWire _spline;
    TopoShape _profile;
};

/// @brief The class of WithAttr<MakePyramid>
template<>
class WithAttr<MakePyramid>: public WithAttrBase {
public:
    /// @brief Construct a WithAttr<MakePyramid> with basepoints and apex
    /// @param basepoints Points on the base plane
	/// @param apex Apex point
    AMCAX_API WithAttr(const std::vector<Point3>& basepoints, const Point3& apex);
    
    /// @brief Construct a WithAttr<MakePyramid> with p1, p2, p3 and apex
    /// @param p1,p2,p3 Points on the base plane
	/// @param apex Apex point
    AMCAX_API WithAttr(const Point3& p1, const Point3& p2, const Point3& p3, const Point3& apex);

    /// @brief Construct a WithAttr<MakePyramid> with p1, p2, p3, p4 and apex
    /// @param p1,p2,p3,p4 Points on the base plane
	/// @param apex Apex point
    AMCAX_API WithAttr(const Point3& p1, const Point3& p2, const Point3& p3, const Point3& p4, const Point3& apex);
    
    /// @brief Perform the pyramid build
    AMCAX_API void Build();

private:
    std::vector<Point3> _basepoints;
    Point3 _apex;
};

/// @brief The class of WithAttr<MakeRevol>
template<>
class WithAttr<MakeRevol>: public WithAttrBase {
public:
    /// @brief Construct a WithAttr<MakeRevol> with shape and axis
    /// @param shape The base shape
	/// @param axis The rotation axis
	/// @param copy Whether copy the base shape
    AMCAX_API WithAttr(const TopoShape& shape, const Axis3& axis, bool copy = false);

    /// @brief Construct a WithAttr<MakeRevol> with shape, axis and d
    /// @param shape The base shape
	/// @param axis The rotation axis
	/// @param d The rotation angle
	/// @param copy Whether copy the base shape
    AMCAX_API WithAttr(const TopoShape& shape, const Axis3& axis, double d, bool copy = false);

private:
    TopoShape _shape;
    Axis3 _axis;
    double _d;
    bool _copy;
};

/// @brief The class of WithAttr<MakeChamfer>
template<>
class WithAttr<MakeChamfer>: public WithAttrBase {
public:
    /// @brief Construct a WithAttr<MakeChamfer> with s
    /// @param s The given shape
    AMCAX_API WithAttr(const TopoShape& s);

    /// @brief Add an edge used to build chamfers, parameters should be set later
    /// @param dist The distance parameter
	/// @param e The edge used to build chamfers
    AMCAX_API void Add(double dist, const TopoEdge& e);

    /// @brief Add an edge used to build chamfers with two distance parameters on the given face and the face of opposite side
    /// @param dist1 The distance parameter on the given face
	/// @param dist2 The distance parameter on the face of opposite side
	/// @param e The edge used to build chamfers
	/// @param f The face for the first distance parameter
    AMCAX_API void Add(double dist1, double dist2, const TopoEdge& e, const TopoFace& f);

private:
    MakeChamfer _mc;
};

/// @brief The class of WithAttr<MakeFillet>
template<>
class WithAttr<MakeFillet>: public WithAttrBase {
public:
    /// @brief Construct a WithAttr<MakeFillet> with s
    /// @param s The given shape
    AMCAX_API WithAttr(const TopoShape& s);

    /// @brief Add an edge with a radius to the fillet
	/// @param r The radius
	/// @param e The edge
    AMCAX_API void Add(double r, const TopoEdge& e);

    /// @brief Add an edge with a linear varying radius
	/// @param r1 The start radius
	/// @param r2 The end radius
	/// @param e The edge to be fillet
	AMCAX_API void Add(double r1, double r2, const TopoEdge& e);
private:
    MakeFillet _mf;
};

/// @brief The class of WithAttr<TransformShape> 
template<>
class WithAttr<TransformShape>: public WithAttrBase {
public:
    /// @brief Construct a WithAttr<TransformShape> with label and trans
    /// @param label The label's toposhape should be trasformed
    /// @param trans The transformation
    /// @param copyGeom Whether the geometry of the shape is copied
	/// @param copyMesh Whether the mesh of the shape is copied
    AMCAX_API WithAttr(Label& label, Transformation3 trans, bool copyGeom = false, bool copyMesh = false);

    /// @brief Construct a WithAttr<TransformShape> with tr
    /// @param tr The transformation3
    AMCAX_API WithAttr(const Transformation3& tr);

    /// @brief Perform TransformShape
    /// @param s The shape with attr
	/// @param copyGeom Whether the geometry of the shape is copied
	/// @param copyMesh Whether the mesh of the shape is copied
    AMCAX_API void Perform(Label &s, bool copyGeom = false, bool copyMesh = false);

    /// @brief  Perform the transformation build
    AMCAX_API void Build() override;

    /// @brief Get all Labels modified from given label
    /// @param label The shape with attr
    /// @return All modified labels from the given label
    AMCAX_API std::vector<AMCAX::Label> Modified(const Label& label);

    /// @brief Get the label whose shape is modified from label's shape
    /// @param label The shape with attr
    /// @return The modified label whose toposhape is modified by the shape with attr's toposhape
    AMCAX_API Label ModifiedShape(const Label& label);

private:
    void  _BuildAttribute(const Label& label);

private:
    bool _copyGeom;
    bool _copyMesh;
    Label originLabel;
    Transformation3 _trans;
    TransformShape _transformShape;
};

/// @brief The class of WithAttr<GeneralTransformShape>
template<>
class WithAttr<GeneralTransformShape>: public WithAttrBase {
public:
    /// @brief Construct a WithAttr<GeneralTransformShape> with t
    /// @param t The general transformation
    AMCAX_API WithAttr(const GeneralTransformation3 &t);

    /// @brief Construct a WithAttr<GeneralTransformShape> with label and t
    /// @param label The shape with attr
	/// @param t The general transformation
	/// @param copy Whether the geometry of the shape is copied
    AMCAX_API WithAttr(Label& label, const GeneralTransformation3 &t, bool copy=false);

    /// @brief  Perform the general transformShape build
    AMCAX_API void Build() override;

    /// @brief Perform GeneralTransformShape
    /// @param label The shape with attr
	/// @param copy Whether the geometry of the shape is copied
    AMCAX_API void Perform(Label &label, bool copy=false);
    
    /// @brief Get all Labels modified from given label
    /// @param label The shape with attr
    /// @return All modified labels from the given label
    AMCAX_API std::vector<AMCAX::Label> Modified(const Label& label);

    /// @brief Get the label whose shape is modified from label's shape
    /// @param label The shape with attr
    /// @return The modified label whose toposhape is modified by the shape with attr's toposhape
    AMCAX_API Label ModifiedShape(const Label& label);

private:
    void  _BuildAttribute(const Label& label);

private:
    Label originLabel;
    bool _copy;
    GeneralTransformation3 _transformation;
    GeneralTransformShape _generalTransformShape;
};

/// @brief The class of WithAttr<TopoShape>
template<>
class WithAttr<TopoShape>: public WithAttrBase {
public:
    /// @brief Construct a WithAttr<TopoShape> with shape
    /// @param shape The input toposhape
    AMCAX_API WithAttr(const TopoShape& shape);

    /// @brief Set a new TopoShape for the WithAttr<TopoShape>
    /// @param shape The input toposhape
    AMCAX_API void SetTopoShape(TopoShape& shape);

    /// @brief Perform the toposhape buildneihe
    AMCAX_API void Build() override;
private:
    TopoShape myShape;
};


#define DEFINE_CONSTRUCTOR_WITH_INIT(MAKER) \
public: \
    template<typename... Args> \
    explicit WithAttr(Args&&... args): _maker(MAKER(std::forward<Args>(args)...)) { \
        _maker.Build(); \
        if (_maker.IsDone()) \
        { \
            TopoShape shape = _maker.Shape(); \
            _UpdateShape(shape); \
            WithAttrBase::Build(); \
        } \
    }

#define DEFINE_CONSTRUCTOR_WITHOUT_INIT(MAKER) \
public: \
    template<typename... Args> \
    explicit WithAttr(Args&&... args) { \
        TopoShape shape = MAKER(std::forward<Args>(args)...); \
        _UpdateShape(shape); \
        WithAttrBase::Build(); \
    }

#define DEFINE_MODELLING_INIT_FUNC() \
public: \
    template<typename... Args> \
    void Init(Args&&... args) { \
        _maker.Init(std::forward<Args>(args)...); \
        if (_maker.IsDone()) \
        { \
            TopoShape shape = _maker.Shape(); \
            _UpdateShape(shape); \
            WithAttrBase::Build(); \
        } \
    }

/// The class of WithAttr<MakeBox>
template<>
class WithAttr<MakeBox>: public WithAttrBase
{
public:
    /// @brief Default constructor
    AMCAX_API WithAttr() {}
    
    /// @brief Construct a WithAttr<MakeBox> with dx, dy and dz
    /// @param dx The x dimension of the box
    /// @param dy The y dimension of the box
    /// @param dz The z dimension of the box
    AMCAX_API WithAttr(double dx, double dy, double dz);

    /// @brief Construct from a corner point and its size
	/// @param p The corner point
	/// @param dx,dy,dz The size
	AMCAX_API WithAttr(const Point3& p, double dx, double dy, double dz);

	/// @brief Construct from two diagonal corner points
	/// @param p1 The first point
	/// @param p2 The second point
	AMCAX_API WithAttr(const Point3& p1, const Point3& p2);

	/// @brief Construct from a local coordinate system and size
	/// @param frame The local coordinate system
	/// @param dx,dy,dz The size
	AMCAX_API WithAttr(const Frame3& frame, double dx, double dy, double dz);

    /// @brief Initialize and construct from its size in x, y, z directions
	/// @param dx,dy,dz The size
	AMCAX_API void Init(double dx, double dy, double dz);

	/// @brief Initialize and construct from a corner point and its size
	/// @param p The corner point
	/// @param dx,dy,dz The size
	AMCAX_API void Init(const Point3& p, double dx, double dy, double dz);

	/// @brief Initialize and construct from two diagonal corner points
	/// @param p1 The first point
	/// @param p2 The second point
	AMCAX_API void Init(const Point3& p1, const Point3& p2);

	/// @brief Initialize and construct from a local coordinate system and size
	/// @param frame The local coordinate system
	/// @param dx,dy,dz The size
	AMCAX_API void Init(const Frame3& frame, double dx, double dy, double dz);

    /// @brief Set x of the box
    /// @details Triggering a Rebuild when the box is built using x.
    /// @param x The x dimension to set
    /// @return True if the rebuid is success, otherwise return false.
    AMCAX_API bool SetX(double x);

    /// @brief Set y of the box
    /// @details Triggering a Rebuild when the box is built using y.
    /// @param y The y dimension to set
    /// @return True if the rebuid is success, otherwise return false.
    AMCAX_API bool SetY(double y);

    /// @brief Set z of the box
    /// @details Triggering a Rebuild when the box is built using z.
    /// @param z The z dimension to set
    /// @return True if the rebuid is success, otherwise return false.
    AMCAX_API bool SetZ(double z);

    /// @brief Set p of the box
    /// @details Triggering a Rebuild when the box is built using p.
    /// @param p The corner point
    /// @return True if the rebuid is success, otherwise return false.
    AMCAX_API bool SetP(const Point3& p);

    /// @brief Set frame of the box
    /// @details Triggering a Rebuild when the box is built using frame.
    /// @param frame The local coordinate system
    /// @return True if the rebuid is success, otherwise return false.
    AMCAX_API bool SetFrame(const Frame3& frame);

    /// @brief Set p1 of the box
    /// @details Triggering a Rebuild when the box is built using p1.
    /// @param p1 The first point
    /// @return True if the rebuid is success, otherwise return false.
    AMCAX_API bool SetP1(const Point3& p1);

    /// @brief Set p2 of the box
    /// @details Triggering a Rebuild when the box is built using p2.
    /// @param p2 The second point
    /// @return True if the rebuid is success, otherwise return false.
    AMCAX_API bool SetP2(const Point3& p2);


    /// @brief Perform the box build
    AMCAX_API void Build() override;

private:
    enum class ConstructType {
       NONE,
       XYZ,
       PXYZ,
       P1P2,
       FXYZ
    };

    ConstructType _type{ConstructType::NONE};

    MakeBox _maker;
    double _dx, _dy, _dz;

    Point3 _p, _p1, _p2;
    Frame3 _frame;
};

/// @brief The class of WithAttr<MakeCylinder>
template<>
class WithAttr<MakeCylinder>: public WithAttrBase {
public:
    /// @brief Construct a WithAttr<MakeCylinder> with r and h
    /// @param r The radius of the cylinder
    /// @param h The height of the cylinder
    AMCAX_API WithAttr(double r, double h);

    /// @brief Construct a WithAttr<MakeCylinder> with r, h and angle
    /// @param r The radius of the cylinder
    /// @param h The height of the cylinder
    /// @param angle The rotation angle of the cylinder
    AMCAX_API WithAttr(double r, double h, double angle);

    /// @brief Construct a WithAttr<MakeCylinder> with frame, r and h
    /// @param frame The local coordinate system
    /// @param r The radius of the cylinder
    /// @param h The height of the cylinder
    AMCAX_API WithAttr(const Frame3& frame, double r, double h);

    /// @brief Construct a WithAttr<MakeCylinder> with frame, r, h and angle
    /// @param frame The local coordinate system
    /// @param r The radius of the cylinder
    /// @param h The height of the cylinder
    /// @param angle The rotation angle of the cylinder
    AMCAX_API WithAttr(const Frame3& frame, double r, double h, double angle);

    /// @brief Set r of the cylinder
    /// @details Triggering a Rebuild
    /// @param r The radius to set
    /// @return True if the rebuid is success, otherwise return false.
    AMCAX_API bool SetR(double r);
    
    /// @brief Set h of the cylinder
    /// @details Triggering a Rebuild
    /// @param h The height to set
    /// @return True if the rebuid is success, otherwise return false.
    AMCAX_API bool SetH(double h);

    /// @brief Set Angle of the cylinder
    /// @details Triggering a Rebuild
    /// @param angle The rotation angle to set
    /// @return True if the rebuid is success, otherwise return false.
    AMCAX_API bool SetAngle(double angle);

    /// @brief Set frame of the cylinder
    /// @details Triggering a Rebuild
    /// @param frame The local coordinate system
    /// @return True if the rebuid is success, otherwise return false.
    AMCAX_API bool SetFrame(const Frame3& frame);

    /// @brief Perform the cylinder build
    AMCAX_API void Build() override;

private:
    Frame3 _frame;
    bool _useFrame{false};
    bool _useAngle{false};
    double _r, _h, _angle;
};

/// @brief The class of WithAttr<MakeCone>
template<>
class WithAttr<MakeCone>: public WithAttrBase {
public:
    /// @brief Construct a WithAttr<MakeCone> with r1, r2 and h
    /// @details The angle is set to 2 * pi by default
    /// @param r1 The radius of the base of the cone
    /// @param r2 The radius of the top of the cone
    /// @param h The height of the cone
    AMCAX_API WithAttr(double r1, double r2, double h);
    
    /// @brief Construct from a bottom radius, a top radius, a height and a rotation angle
	/// @param r1 The bottom radius
	/// @param r2 The top radius
	/// @param h The height
	/// @param angle The rotation angle to construct a part cone
	AMCAX_API WithAttr(double r1, double r2, double h, double angle);

	/// @brief Construct from a local coordinate system, a bottom radius, a top radius and a height
	/// @param frame The local coordinate system
	/// @param r1 The bottom radius
	/// @param r2 The top radius
	/// @param h The height
	AMCAX_API WithAttr(const Frame3& frame, double r1, double r2, double h);

	/// @brief Construct from a local coordinate system, a bottom radius, a top radius, a height and a rotation angle
	/// @param frame The local coordinate system
	/// @param r1 The bottom radius
	/// @param r2 The top radius
	/// @param h The height
	/// @param angle The rotation angle to construct a part cone
	AMCAX_API WithAttr(const Frame3& frame, double r1, double r2, double h, double angle);

    /// @brief Set r1 of the Cone
    /// @details Triggering a Rebuild
    /// @param r1 The radius of the base of the cone
    /// @return True if the rebuid is success, otherwise return false.
    AMCAX_API bool SetR1(double r1);

    /// @brief Set R2 of the cone
    /// @details Triggering a Rebuild
    /// @param r2 The radius of the top of the cone
    /// @return True if the rebuid is success, otherwise return false.
    AMCAX_API bool SetR2(double r2);

    /// @brief Set h of the cone
    /// @details Triggering a Rebuild
    /// @param h The height of the cone
    /// @return True if the rebuid is success, otherwise return false.
    AMCAX_API bool SetH(double h);

    /// @brief Set angle of the cone
    /// @details Triggering a Rebuild
    /// @param angle The rotation angle of the cone
    /// @return True if the rebuid is success, otherwise return false.
    AMCAX_API bool SetAngle(double angle);

    /// @brief Set frame of the cylinder
    /// @details Triggering a Rebuild
    /// @param frame The local coordinate system
    /// @return True if the rebuid is success, otherwise return false.
    AMCAX_API bool SetFrame(const Frame3& frame);

    /// @brief Perform the cone build
    AMCAX_API void Build() override;

private:
    Frame3 _frame;
    bool _useFrame{false};
    bool _useAngle{false};
    double _r1, _r2, _h, _angle;
};

/// @brief The class of WithAttr<MakeEdge>
template<>
class WithAttr<MakeEdge>: public WithAttrBase {
public:
    /// @brief Construct a default WithAttr<MakeEdge>
    AMCAX_API WithAttr();

    /// @brief Construct a WithAttr<MakeEdge> With v1 and v2
    /// @param v1 The first vertex with attr
    /// @param v2 The second vertex with attr
    AMCAX_API WithAttr(const Label& v1, const Label& v2);

    /// @brief Construct a WithAttr<MakeEdge> With l, v1 and v2
    /// @param l The line
    /// @param v1 The first vertex with attr
    /// @param v2 The second vertex with attr
    AMCAX_API WithAttr(const Line3& l, const Label& v1, const Label& v2);
    
    /// @brief Construct a WithAttr<MakeEdge> With c, v1 and v2
    /// @param c The circle
    /// @param v1 The first vertex with attr
    /// @param v2 The second vertex with attr
    AMCAX_API WithAttr(const Circle3& c, const Label& v1, const Label& v2);

    /// @brief Construct a WithAttr<MakeEdge> With e, v1 and v2
    /// @param e The Ellipse3
    /// @param v1 The first vertex with attr
    /// @param v2 The second vertex with attr
    AMCAX_API WithAttr(const Ellipse3& e, const Label& v1, const Label& v2);

    /// @brief Construct a WithAttr<MakeEdge> With h, v1 and v2
    /// @param h The Hyperbola3
    /// @param v1 The first vertex with attr
    /// @param v2 The second vertex with attr
    AMCAX_API WithAttr(const Hyperbola3& h, const Label& v1, const Label& v2);

    /// @brief Construct a WithAttr<MakeEdge> With p, v1 and v2
    /// @param p The Parabola3
    /// @param v1 The first vertex with attr
    /// @param v2 The second vertex with attr
    AMCAX_API WithAttr(const Parabola3& p, const Label& v1, const Label& v2);

    /// @brief Initialize and Construct from a curve with two end vertices
	/// @param c The curve
	/// @param v1 The first vertex with attr
	/// @param v2 The second vertex with attr
    AMCAX_API void Init(const std::shared_ptr<Geom3Curve>& c, const Label& v1, const Label& v2);

    /// @brief Initialize and construct from a curve with two end vertices and their parameters
	/// @param c The curve
	/// @param v1 The first vertex with attr
	/// @param v2 The second vertex with attr
	/// @param p1 The first parameter
	/// @param p2 The last parameter
	AMCAX_API void Init(const std::shared_ptr<Geom3Curve>& c, const Label& v1, const Label& v2, double p1, double p2);

    /// @brief Initialize and construct from a pcurve on a surface with two end vertices
	/// @param c The pcurve
	/// @param s The surface
	/// @param v1 The first vertex with attr
	/// @param v2 The second vertex with attr
	AMCAX_API void Init(const std::shared_ptr<Geom2Curve>& c, const std::shared_ptr<Geom3Surface>& s, const Label& v1, const Label& v2);

    /// @brief Initialize and construct from a pcurve on a surface with two end vertices and their parameters
	/// @param c The pcurve
	/// @param s The surface
	/// @param v1 The first vertex with attr
	/// @param v2 The second vertex with attr
	/// @param p1 The first parameter
	/// @param p2 The last parameter
	AMCAX_API void Init(const std::shared_ptr<Geom2Curve>& c, const std::shared_ptr<Geom3Surface>& s, const Label& v1, const Label& v2, double p1, double p2);

    /// @brief Build Edge with attr
    AMCAX_API void Build() override;

    /// @brief Get the first vertex with attr
    /// @return The first vertex with attr
    AMCAX_API const Label& Vertex1() const;

    /// @brief Get the second vertex with attr
    /// @return The second vertex with attr
    AMCAX_API const Label& Vertex2() const;
private:
    enum class ConstructorType {
        Line,
        Circle,
        Ellipse,
        Hyperbola,
        Parabola,
        None
    };
    ConstructorType _constructorType{ConstructorType::None};
    bool _default_construct{false};

    template <typename... Args>
    void _BuildEdge(Args&&... args);

    template <typename... Args>
    void _InitEdge(Args&&... args);
    
    Line3 _l;
    Circle3 _c;
    Ellipse3 _e;
    Hyperbola3 _h;
    Parabola3 _p;
    Label _v1, _v2;

    MakeEdge _maker;
};

/// @brief The class of WithAttr<MakeEdge2d>
template<>
class WithAttr<MakeEdge2d>: public WithAttrBase {
public:
    /// @brief Construct a WithAttr<MakeEdge2d> With v1 and v2
    /// @param v1 The first vertex with attr
    /// @param v2 The second vertex with attr
    AMCAX_API WithAttr(const Label& v1, const Label& v2);

    /// @brief Construct a WithAttr<MakeEdge2d> With l, v1 and v2
    /// @param l The line
    /// @param v1 The first vertex with attr
    /// @param v2 The second vertex with attr
    AMCAX_API WithAttr(const Line2& l, const Label& v1, const Label& v2);

    /// @brief Construct a WithAttr<MakeEdge2d> With c, v1 and v2
    /// @param c The circle
    /// @param v1 The first vertex with attr
    /// @param v2 The second vertex with attr
    AMCAX_API WithAttr(const Circle2& c, const Label& v1, const Label& v2);

    /// @brief Construct a WithAttr<MakeEdge2d> With e, v1 and v2
    /// @param e The ellipse
    /// @param v1 The first vertex with attr
    /// @param v2 The second vertex with attr
    AMCAX_API WithAttr(const Ellipse2& e, const Label& v1, const Label& v2);

    /// @brief Construct a WithAttr<MakeEdge2d> With p, v1 and v2
    /// @param p The parabola
    /// @param v1 The first vertex with attr
    /// @param v2 The second vertex with attr
    AMCAX_API WithAttr(const Parabola2& p, const Label& v1, const Label& v2);

    /// @brief Construct a WithAttr<MakeEdge2d> With h, v1 and v2
    /// @param h The hyperbola
    /// @param v1 The first vertex with attr
    /// @param v2 The second vertex with attr
    AMCAX_API WithAttr(const Hyperbola2& h, const Label& v1, const Label& v2);

    /// @brief Construct from a curve with two end vertices
	/// @param c The curve
	/// @param v1 The first vertex with attr
	/// @param v2 The second vertex with attr
	AMCAX_API WithAttr(const std::shared_ptr<Geom2Curve>& c, const Label& v1, const Label& v2);

    /// @brief Construct from a curve with two end vertices and their parameters
    /// @param c The curve
    /// @param v1 The first vertex with attr
    /// @param v2 The second vertex with attr
    /// @param p1 The first parameter
    /// @param p2 The last parameter
    AMCAX_API WithAttr(const std::shared_ptr<Geom2Curve>& c, const Label& v1, const Label& v2, double p1, double p2);

    /// @brief Initialize and construct from a curve with two end vertices with attr
	/// @param c The curve
	/// @param v1 The first vertex with attr
	/// @param v2 The second vertex with attr
	AMCAX_API void Init(const std::shared_ptr<Geom2Curve>& c, const Label& v1, const Label& v2);

    /// @brief Initialize and construct from a curve with two end vertices and their parameters
	/// @param c The curve
	/// @param v1 The first vertex with attr
	/// @param v2 The second vertex with attr
	/// @param param1 The first parameter
	/// @param param2 The last parameter
	AMCAX_API void Init(const std::shared_ptr<Geom2Curve>& c, const Label& v1, const Label& v2, double param1, double param2);

    /// @brief Build Edge2D with attr
    AMCAX_API void Build() override;

    /// @brief Get the first vertex with attr
    /// @return The first vertex with attr
    AMCAX_API const Label& Vertex1() const;

    /// @brief Get the second vertex with attr
    /// @return The second vertex with attr
    AMCAX_API const Label& Vertex2() const;

private:
    enum class ConstructorType {
        Line2,
        Circle2,
        Ellipse2,
        Hyperbola2,
        Parabola2,
        None
    };
    ConstructorType _constructorType{ConstructorType::None};


    template <typename... Args>
    void _BuildEdge2D(Args&&... args);

    template <typename... Args>
    void _InitEdge2D(Args&&... args);

    Line2 _l;
    Circle2 _c;
    Ellipse2 _e;
    Hyperbola2 _h;
    Parabola2 _p;
    Label _v1, _v2;
};

/// @brief The class of WithAttr<MakeFace>
template<>
class WithAttr<MakeFace>: public WithAttrBase {
public:
    /// @brief Construct a default WithAttr<MakeFace>
    AMCAX_API explicit WithAttr();

    /// @brief construct from a face with attr
	/// @param f The face with attr
	AMCAX_API explicit WithAttr(const Label& f);

    /// @brief Initialize and construct from a face with attr
	/// @param f The face with attr
	AMCAX_API void Init(const Label& f);

    /// @brief Add a face with attr to the solid with attr
    /// @param label The face with attr
    AMCAX_API void Add(const Label& label);

    /// @brief Build the face with attr
    AMCAX_API void Build() override;
private:
    Label _f;
    bool _default_construct{false};
    MakeFace _maker;
};

/// @brief The class of WithAttr<MakeHalfSpace> 
template<>
class WithAttr<MakeHalfSpace> : public WithAttrBase {
public:
    /// @brief Construct a half space with a boundary face or shell and reference point
	/// @param shape The boundary face or shell with attribute
	/// @param refPoint The reference point
	AMCAX_API WithAttr(const Label& shape, const Point3& refPoint);

    /// @brief Build the half space with attr
    AMCAX_API void Build() override;

private:
    Label _shapeWithAttr;
    Point3 _refPoint;
};

/// @brief The class of WithAttr<MakePolygon>
template<>
class WithAttr<MakePolygon> : public WithAttrBase {
public:
    /// @brief Construct a default WithAttr<MakePolygon>
    AMCAX_API WithAttr();

    /// @brief Construct a WithAttr<MakePolygon> with two vertices with attr
    /// @param v1 The first vertex with attr
    /// @param v2 The second vertex with attr
    AMCAX_API WithAttr(const Label& v1, const Label& v2);

    /// @brief Construct a WithAttr<MakePolygon> with three vertices with attr
    /// @param v1 The first vertex with attr
    /// @param v2 The second vertex with attr
    /// @param v3 The third vertex with attr
    /// @param close Whether the polygon is closed
    AMCAX_API WithAttr(const Label& v1, const Label& v2, const Label& v3, bool close = false);

    /// @brief Construct a WithAttr<MakePolygon> with four vertices with attr
    /// @param v1 The first vertex with attr
    /// @param v2 The second vertex with attr
    /// @param v3 The third vertex with attr
    /// @param v4 The fourth vertex with attr
    /// @param close Whether the polygon is closed
    AMCAX_API WithAttr(const Label& v1, const Label& v2, const Label& v3, const Label& v4, bool close = false);

    /// @brief Add a vertex with attr to the polygon
    /// @param v The vertex with attr
    AMCAX_API void Add(const Label& v);

    /// @brief Build the polygon with attr
    AMCAX_API void Build() override;

private:
    std::vector<Label> _vertices;
    bool _isClose;
};

/// @brief The class of WithAttr<MakeSolid>
template<>
class WithAttr<MakeSolid> : public WithAttrBase {
public:
    /// @brief Construct a default WithAttr<MakeSolid>
    AMCAX_API WithAttr();

    /// @brief Construct from a list of shapes with attr
    /// @param shapes The list of shapes with attr
    AMCAX_API explicit WithAttr(const std::vector<Label>& shapes);

    /// @brief Add a shell with attr to the solid with attr
    /// @param label The shape with attr
    AMCAX_API void Add(const Label& label);

    /// @brief Build the solid with attr
    AMCAX_API void Build() override;

private:
    std::vector<Label> _shapes;
    std::vector<Label> _addedShapes;
    MakeSolid _maker;
};

/// @brief The class of WithAttr<MakeWire>
template<>
class WithAttr<MakeWire> : public WithAttrBase {
public:
    /// @brief Construct a default WithAttr<MakeWire>
    AMCAX_API WithAttr();

    /// @brief Construct from a list of shapes with attr
    /// @param labels The list of shapes with attr
    AMCAX_API explicit WithAttr(const std::vector<Label>& labels);

    /// @brief Build the wire with attr
    AMCAX_API void Build() override;

    /// @brief Add a wire/edge with attr to the wire with attr
    /// @param label The wire/edge with attr
    AMCAX_API void Add(const Label& label);

    /// @brief Add a list of shapes with attr to the wire with attr
    /// @param labels The list of shapes with attr
    AMCAX_API void Add(const std::vector<Label>& labels);
private:
    void _BuildAttributes();

private:
    std::vector<Label> _labels;
    std::unordered_map<TopoShape, Label> _addedTopoToOrigLabel;
    std::unordered_set<TopoShape> _addedTopo;
    MakeWire _maker;
};
#undef DEFINE_CONSTRUCTOR_WITH_INIT
#undef DEFINE_CONSTRUCTOR_WITHOUT_INIT
#undef DEFINE_MODELLING_INIT_FUNC
} // namespace AMCAX
