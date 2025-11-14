/// @file      BRepAdaptorCurve3.hpp
/// @brief     Class of adaptor of 3D curves in B-Rep
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <geometry/AdaptorGeom3Curve.hpp>
#include <topology/TopoEdge.hpp>

namespace AMCAX
{
class Adaptor3CurveOnSurface;
class TopoFace;

/// @brief Class of adaptor of 3D curves in B-Rep
class AMCAX_CLASS_API BRepAdaptorCurve3 : public Adaptor3Curve
{
public:
	/// @brief Default constructor
	BRepAdaptorCurve3() noexcept = default;

	/// @brief Construct form an edge
	/// @param e The edge
	AMCAX_API explicit BRepAdaptorCurve3(const TopoEdge& e);

	/// @brief Construct from an edge and a face
	/// @param e The edge
	/// @param f The face
	AMCAX_API BRepAdaptorCurve3(const TopoEdge& e, const TopoFace& f);

	[[nodiscard]] AMCAX_API std::shared_ptr<Adaptor3Curve> ShallowCopy() const override;

	/// @brief Clean the information of edge and face
	AMCAX_API void Reset();

	/// @brief Initialize from an edge
	/// @param e The edge
	AMCAX_API void Initialize(const TopoEdge& e);

	/// @brief Initialize from an edge and a face
	/// @param e The edge
	/// @param f The face
	AMCAX_API void Initialize(const TopoEdge& e, const TopoFace& f);

	/// @brief Get the transformation
	/// @return The transformation
	[[nodiscard]] AMCAX_API const Transformation3& Transformation() const noexcept;

	/// @brief Is the curve a 3D curve
	/// @return True if the curve is a 3D curve
	[[nodiscard]] AMCAX_API bool Is3DCurve() const noexcept;

	/// @brief Is the curve a curve on surface
	/// @return True if the curve is a curve on surface
	[[nodiscard]] AMCAX_API bool IsCurveOnSurface() const noexcept;

	/// @brief Get the 3D curve
	/// @return The 3D curve
	[[nodiscard]] AMCAX_API const AdaptorGeom3Curve& Curve() const noexcept;

	/// @brief Get the curve on surface
	/// @return The curve on surface
	[[nodiscard]] AMCAX_API const Adaptor3CurveOnSurface& CurveOnSurface() const noexcept;

	/// @brief Get the edge
	/// @return The edge
	[[nodiscard]] AMCAX_API const TopoEdge& Edge() const noexcept;

	/// @brief Get the tolerance of the edge
	/// @return The tolerance
	[[nodiscard]] AMCAX_API double Tolerance() const;

	[[nodiscard]] AMCAX_API double FirstParameter() const override;
	[[nodiscard]] AMCAX_API double LastParameter() const override;
	[[nodiscard]] AMCAX_API ContinuityType Continuity() const override;
	[[nodiscard]] AMCAX_API int NIntervals(ContinuityType c) const override;
	AMCAX_API void Intervals(std::vector<double>& t, ContinuityType c) const override;
	[[nodiscard]] AMCAX_API std::shared_ptr<Adaptor3Curve> Trim(double first, double last, double tol) const override;
	[[nodiscard]] AMCAX_API bool IsClosed() const override;
	[[nodiscard]] AMCAX_API bool IsPeriodic() const override;
	[[nodiscard]] AMCAX_API double Period() const override;
	[[nodiscard]] AMCAX_API Point3 Value(double u) const override;
	AMCAX_API void D0(double u, Point3& p) const override;
	AMCAX_API void D1(double u, Point3& p, Vector3& v) const override;
	AMCAX_API void D2(double u, Point3& p, Vector3& v1, Vector3& v2) const override;
	AMCAX_API void D3(double u, Point3& p, Vector3& v1, Vector3& v2, Vector3& v3) const override;
	[[nodiscard]] AMCAX_API Vector3 DN(double u, int n) const override;
	[[nodiscard]] AMCAX_API double Resolution(double r3d) const override;
	[[nodiscard]] AMCAX_API CurveType Type() const override;
	[[nodiscard]] AMCAX_API Line3 Line() const override;
	[[nodiscard]] AMCAX_API Circle3 Circle() const override;
	[[nodiscard]] AMCAX_API Ellipse3 Ellipse() const override;
	[[nodiscard]] AMCAX_API Hyperbola3 Hyperbola() const override;
	[[nodiscard]] AMCAX_API Parabola3 Parabola() const override;
	[[nodiscard]] AMCAX_API int Degree() const override;
	[[nodiscard]] AMCAX_API bool IsRational() const override;
	[[nodiscard]] AMCAX_API int NPoles() const override;
	[[nodiscard]] AMCAX_API int NKnots() const override;
	[[nodiscard]] AMCAX_API std::shared_ptr<Geom3BezierCurve> Bezier() const override;
	[[nodiscard]] AMCAX_API std::shared_ptr<Geom3BSplineCurve> BSpline() const override;
	[[nodiscard]] AMCAX_API std::shared_ptr<Geom3OffsetCurve> OffsetCurve() const override;

private:
	/// @brief Transformation of the curve
	Transformation3 transformation;

	/// @brief Base curve of an edge
	AdaptorGeom3Curve curve;

	/// @brief Curve on surface if the edge has no 3D curve
	std::shared_ptr<Adaptor3CurveOnSurface> curveOnSurface;

	/// @brief Edge
	TopoEdge edge;
};
} // namespace AMCAX
