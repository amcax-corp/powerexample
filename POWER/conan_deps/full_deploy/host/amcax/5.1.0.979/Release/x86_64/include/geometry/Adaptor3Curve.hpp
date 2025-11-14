/// @file      Adaptor3Curve.hpp
/// @brief     Base class of adaptor of 3D curves
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <memory>
#include <vector>

#include <math/CircleT.hpp>
#include <math/EllipseT.hpp>
#include <math/GeometryMacros.hpp>
#include <math/HyperbolaT.hpp>
#include <math/LineT.hpp>
#include <math/ParabolaT.hpp>

namespace AMCAX
{
class Geom3BezierCurve;
class Geom3BSplineCurve;
class Geom3OffsetCurve;

/// @brief Base class of adaptor of 3D curves
class AMCAX_CLASS_API Adaptor3Curve
{
public:
	/// @brief Default constructor
	Adaptor3Curve() noexcept = default;

	/// @brief Copy constructor
	Adaptor3Curve(const Adaptor3Curve&) noexcept = default;

	/// @brief Move constructor
	Adaptor3Curve(Adaptor3Curve&&) noexcept = default;

	/// @brief Destructor
	virtual ~Adaptor3Curve() noexcept = default;

	/// @brief Copy assignment operator
	/// @return The reference to self
	Adaptor3Curve& operator=(const Adaptor3Curve&) noexcept = default;

	/// @brief Move assignment operator
	/// @return The reference to self
	Adaptor3Curve& operator=(Adaptor3Curve&&) noexcept = default;

	/// @brief Get the shallow copied adaptor
	/// @return The copied adaptor
	AMCAX_API virtual std::shared_ptr<Adaptor3Curve> ShallowCopy() const = 0;

	/// @brief Get the first parameter
	/// @return The first parameter
	AMCAX_API virtual double FirstParameter() const = 0;

	/// @brief Get the last parameter
	/// @return The last parameter
	AMCAX_API virtual double LastParameter() const = 0;

	/// @brief Get the type of continuity
	/// @return The type of continuity
	AMCAX_API virtual ContinuityType Continuity() const = 0;

	/// @brief Get the number of intervals based on a given continuity
	/// @param c The continuity
	/// @return The number of intervals
	AMCAX_API virtual int NIntervals(ContinuityType c) const = 0;

	/// @brief Get the intervals based on a given continuity
	/// @param[in,out] t The resulting intervals, must be resized before
	/// @param[in] c The continuity
	AMCAX_API virtual void Intervals(std::vector<double>& t, ContinuityType c) const = 0;

	/// @brief Get the trimmed curve
	/// @param first The first parameter
	/// @param last The last parameter
	/// @param tol The tolerance for point confusion
	/// @return The trimmed curve
	AMCAX_API virtual std::shared_ptr<Adaptor3Curve> Trim(double first, double last, double tol) const = 0;

	/// @brief Is the curve closed
	/// @return True if the curve is closed
	AMCAX_API virtual bool IsClosed() const = 0;

	/// @brief Is the curve periodic
	/// @return True if the curve is periodic
	AMCAX_API virtual bool IsPeriodic() const = 0;

	/// @brief Get the period of the curve
	/// @return The period
	AMCAX_API virtual double Period() const = 0;

	/// @brief Compute the point at a parameter
	/// @param u The parameter
	/// @return The point
	AMCAX_API virtual Point3 Value(double u) const = 0;

	/// @brief Compute the point at a parameter
	/// @param[in] u The parameter
	/// @param[out] p The point
	AMCAX_API virtual void D0(double u, Point3& p) const = 0;

	/// @brief Compute the point and the first derivative at a parameter
	/// @param[in] u The parameter
	/// @param[out] p The point
	/// @param[out] v The first derivative
	AMCAX_API virtual void D1(double u, Point3& p, Vector3& v) const = 0;

	/// @brief Compute the point and the first and second derivatives at a parameter
	/// @param[in] u The parameter
	/// @param[out] p The point
	/// @param[out] v1 The first derivative
	/// @param[out] v2 The second derivative
	AMCAX_API virtual void D2(double u, Point3& p, Vector3& v1, Vector3& v2) const = 0;

	/// @brief Compute the point and the first, second and third derivatives at a parameter
	/// @param[in] u The parameter
	/// @param[out] p The point
	/// @param[out] v1 The first derivative
	/// @param[out] v2 The second derivative
	/// @param[out] v3 The third derivative
	AMCAX_API virtual void D3(double u, Point3& p, Vector3& v1, Vector3& v2, Vector3& v3) const = 0;

	/// @brief Compute the n-th derivative at a parameter
	/// @param u The parameter
	/// @param n The order of derivative
	/// @return The n-th derivative
	AMCAX_API virtual Vector3 DN(double u, int n) const = 0;

	/// @brief Compute the parametric tolerance from a 3D tolerance
	/// @param r3d The 3D tolerance
	/// @return The parametric tolerance
	AMCAX_API virtual double Resolution(double r3d) const = 0;

	/// @brief Get the type of curve
	/// @return The type of curve
	AMCAX_API virtual CurveType Type() const = 0;

	/// @brief Get a line if the curve type is line
	/// @return The line
	AMCAX_API virtual Line3 Line() const = 0;

	/// @brief Get a circle if the curve type is circle
	/// @return The circle
	AMCAX_API virtual Circle3 Circle() const = 0;

	/// @brief Get an ellipse if the curve type is ellipse
	/// @return The ellipse
	AMCAX_API virtual Ellipse3 Ellipse() const = 0;

	/// @brief Get a hyperbola if the curve type is hyperbola
	/// @return The hyperbola
	AMCAX_API virtual Hyperbola3 Hyperbola() const = 0;

	/// @brief Get a parabola if the curve type is parabola
	/// @return The parabola
	AMCAX_API virtual Parabola3 Parabola() const = 0;

	/// @brief Get the degree of the curve
	/// @return The degree of the curve
	AMCAX_API virtual int Degree() const = 0;

	/// @brief Is the B spline curve rational
	/// @return True if the B spline curve is rational
	AMCAX_API virtual bool IsRational() const = 0;

	/// @brief Get the number of poles
	/// @return The number of poles
	AMCAX_API virtual int NPoles() const = 0;

	/// @brief Get the number of knots
	/// @return The number of knots
	AMCAX_API virtual int NKnots() const = 0;

	/// @brief Get a bezier curve if the curve type is bezier curve
	/// @return The bezier curve
	AMCAX_API virtual std::shared_ptr<Geom3BezierCurve> Bezier() const = 0;

	/// @brief Get a B spline curve if the curve type is B spline curve
	/// @return The B spline curve
	AMCAX_API virtual std::shared_ptr<Geom3BSplineCurve> BSpline() const = 0;

	/// @brief Get an offset curve if the curve type is offset curve
	/// @return The offset curve
	AMCAX_API virtual std::shared_ptr<Geom3OffsetCurve> OffsetCurve() const = 0;
};
} // namespace AMCAX
