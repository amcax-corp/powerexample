/// @file      CurveCalculation.hpp
/// @brief     Class of basic calculation for elementary curves
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <math/CircleT.hpp>
#include <math/EllipseT.hpp>
#include <math/HyperbolaT.hpp>
#include <math/LineT.hpp>
#include <math/ParabolaT.hpp>

namespace AMCAX
{
/// @brief Functions for basic geometric computations on elementary curves such as lines and conics.
/// @details The calculation includes parameters, values, derivatives, periods, and 3D conversions.
///          The curves include lines, circles, ellipses, parabolas, and hyperbolas, in both 2D and 3D.
class CurveCalculation
{
public:
	/// @brief Put a parameter into a period defined by the first and last parameters
	/// @details If either of the input parameters is infinity or the period is less than a small epsilon, then this function returns u without any changes.
	/// @param u The input parameter
	/// @param ufirst The lower bound of the first period
	/// @param ulast The upper bound of the first period
	/// @return The output parameter that in the range [ufirst, ulast]
	[[nodiscard]] AMCAX_API static double InPeriod(double u, double ufirst, double ulast) noexcept;

	/// @brief Adjust u1 and u2 to be in the period range.
	/// @details The parameter u1 is set in the range [ufirst, ulast]
	///          The parameter u2 is set in the range [u1, u1 + ulast - ufirst]
	/// @param[in] ufirst The lower bound of the period
	/// @param[in] ulast The upper bound of the period
	/// @param[in] precision The precision for checking equality
	/// @param[in,out] u1 The first parameter to be adjust
	/// @param[in,out] u2 The second parameter to be adjust
	AMCAX_API static void AdjustPeriodic(double ufirst, double ulast, double precision, double& u1, double& u2) noexcept;

	/// @brief Compute the point on a 3D line at a parameter
	/// @param u The parameter
	/// @param line The line
	/// @return The resulting point
	[[nodiscard]] AMCAX_API static Point3 Value(double u, const Line3& line) noexcept;

	/// @brief Compute the point on a 3D line at a parameter
	/// @param u The parameter
	/// @param line The line
	/// @return The resulting point
	[[nodiscard]] AMCAX_API static Point3 D0(double u, const Line3& line) noexcept;

	/// @brief Compute the first derivative on a 3D line at a parameter
	/// @param u The parameter
	/// @param line The line
	/// @return The first derivative
	[[nodiscard]] AMCAX_API static Vector3 D1(double u, const Line3& line) noexcept;

	/// @brief Compute the second derivative on a 3D line at a parameter
	/// @param u The parameter
	/// @param line The line
	/// @return The second derivative
	[[nodiscard]] AMCAX_API static Vector3 D2(double u, const Line3& line) noexcept;

	/// @brief Compute the third derivative on a 3D line at a parameter
	/// @param u The parameter
	/// @param line The line
	/// @return The third derivative
	[[nodiscard]] AMCAX_API static Vector3 D3(double u, const Line3& line) noexcept;

	/// @brief Compute the n-th derivative on a 3D line at a parameter
	/// @param u The parameter
	/// @param line The line
	/// @param n The order of derivative
	/// @return The n-th derivative
	[[nodiscard]] AMCAX_API static Vector3 DN(double u, const Line3& line, int n) noexcept;

	/// @brief Compute the point and the first derivative on a 3D line at a parameter
	/// @param[in] u The parameter
	/// @param[in] line The line
	/// @param[out] p The point
	/// @param[out] v1 The first derivative
	AMCAX_API static void D1(double u, const Line3& line, Point3& p, Vector3& v1) noexcept;

	/// @brief Compute the point and the first two derivatives on a 3D line at a parameter
	/// @param[in] u The parameter
	/// @param[in] line The line
	/// @param[out] p The point
	/// @param[out] v1 The first derivative
	/// @param[out] v2 The second derivative
	AMCAX_API static void D2(double u, const Line3& line, Point3& p, Vector3& v1, Vector3& v2) noexcept;

	/// @brief Compute the point and the first three derivatives on a 3D line at a parameter
	/// @param[in] u The parameter
	/// @param[in] line The line
	/// @param[out] p The point
	/// @param[out] v1 The first derivative
	/// @param[out] v2 The second derivative
	/// @param[out] v3 The third derivative
	AMCAX_API static void D3(double u, const Line3& line, Point3& p, Vector3& v1, Vector3& v2, Vector3& v3) noexcept;

	/// @brief Compute the parameter of a given point on a 3D line
	/// @param line The line
	/// @param p The given point
	/// @return The parameter of point
	[[nodiscard]] AMCAX_API static double Parameter(const Line3& line, const Point3& p) noexcept;

	/// @brief Compute the point on a 3D line represented by an axis at a parameter
	/// @param u The parameter
	/// @param pos The axis where the line lies
	/// @return The point
	[[nodiscard]] AMCAX_API static Point3 LineValue(double u, const Axis3& pos) noexcept;

	/// @brief Compute the point on a 3D line represented by an axis at a parameter
	/// @param u The parameter
	/// @param pos The axis where the line lies
	/// @return The point
	[[nodiscard]] AMCAX_API static Point3 LineD0(double u, const Axis3& pos) noexcept;

	/// @brief Compute the first derivative on a 3D line represented by an axis at a parameter
	/// @param u The parameter
	/// @param pos The axis where the line lies
	/// @return The first derivative
	[[nodiscard]] AMCAX_API static Vector3 LineD1(double u, const Axis3& pos) noexcept;

	/// @brief Compute the second derivative on a 3D line represented by an axis at a parameter
	/// @param u The parameter
	/// @param pos The axis where the line lies
	/// @return The second derivative
	[[nodiscard]] AMCAX_API static Vector3 LineD2(double u, const Axis3& pos) noexcept;

	/// @brief Compute the third derivative on a 3D line represented by an axis at a parameter
	/// @param u The parameter
	/// @param pos The axis where the line lies
	/// @return The third derivative
	[[nodiscard]] AMCAX_API static Vector3 LineD3(double u, const Axis3& pos) noexcept;

	/// @brief Compute the n-th derivative on a 3D line represented by an axis at a parameter
	/// @param u The parameter
	/// @param pos The axis where the line lies
	/// @param n The order of derivative
	/// @return The n-th derivative
	[[nodiscard]] AMCAX_API static Vector3 LineDN(double u, const Axis3& pos, int n) noexcept;

	/// @brief Compute the point and the first derivative on a 3D line represented by an axis at a parameter
	/// @param[in] u The parameter
	/// @param[in] pos The axis where the line lies
	/// @param[out] p The point
	/// @param[out] v1 The first derivative
	AMCAX_API static void LineD1(double u, const Axis3& pos, Point3& p, Vector3& v1) noexcept;

	/// @brief Compute the point and the first two derivatives on a 3D line represented by an axis at a parameter
	/// @param[in] u The parameter
	/// @param[in] pos The axis where the line lies
	/// @param[out] p The point
	/// @param[out] v1 The first derivative
	/// @param[out] v2 The second derivative
	AMCAX_API static void LineD2(double u, const Axis3& pos, Point3& p, Vector3& v1, Vector3& v2) noexcept;

	/// @brief Compute the point and the first three derivatives on a 3D line represented by an axis at a parameter
	/// @param[in] u The parameter
	/// @param[in] pos The axis where the line lies
	/// @param[out] p The point
	/// @param[out] v1 The first derivative
	/// @param[out] v2 The second derivative
	/// @param[out] v3 The third derivative
	AMCAX_API static void LineD3(double u, const Axis3& pos, Point3& p, Vector3& v1, Vector3& v2, Vector3& v3) noexcept;

	/// @brief Compute the parameter of a given point on a 3D line represented by an axis
	/// @param pos The axis where the line lies
	/// @param p The given point
	/// @return The parameter of point
	[[nodiscard]] AMCAX_API static double LineParameter(const Axis3& pos, const Point3& p) noexcept;

	/// @brief Compute the point on a 3D circle at a parameter
	/// @param u The parameter
	/// @param circle The circle
	/// @return The resulting point
	[[nodiscard]] AMCAX_API static Point3 Value(double u, const Circle3& circle) noexcept;

	/// @brief Compute the point on a 3D circle at a parameter
	/// @param u The parameter
	/// @param circle The circle
	/// @return The resulting point
	[[nodiscard]] AMCAX_API static Point3 D0(double u, const Circle3& circle) noexcept;

	/// @brief Compute the first derivative on a 3D circle at a parameter
	/// @param u The parameter
	/// @param circle The circle
	/// @return The first derivative
	[[nodiscard]] AMCAX_API static Vector3 D1(double u, const Circle3& circle) noexcept;

	/// @brief Compute the second derivative on a 3D circle at a parameter
	/// @param u The parameter
	/// @param circle The circle
	/// @return The second derivative
	[[nodiscard]] AMCAX_API static Vector3 D2(double u, const Circle3& circle) noexcept;

	/// @brief Compute the third derivative on a 3D circle at a parameter
	/// @param u The parameter
	/// @param circle The circle
	/// @return The third derivative
	[[nodiscard]] AMCAX_API static Vector3 D3(double u, const Circle3& circle) noexcept;

	/// @brief Compute the n-th derivative on a 3D circle at a parameter
	/// @param u The parameter
	/// @param circle The circle
	/// @param n The order of derivative
	/// @return The n-th derivative
	[[nodiscard]] AMCAX_API static Vector3 DN(double u, const Circle3& circle, int n) noexcept;

	/// @brief Compute the point and the first derivative on a 3D circle at a parameter
	/// @param[in] u The parameter
	/// @param[in] circle The circle
	/// @param[out] p The point
	/// @param[out] v1 The first derivative
	AMCAX_API static void D1(double u, const Circle3& circle, Point3& p, Vector3& v1) noexcept;

	/// @brief Compute the point and the first two derivatives on a 3D circle at a parameter
	/// @param[in] u The parameter
	/// @param[in] circle The circle
	/// @param[out] p The point
	/// @param[out] v1 The first derivative
	/// @param[out] v2 The second derivative
	AMCAX_API static void D2(double u, const Circle3& circle, Point3& p, Vector3& v1, Vector3& v2) noexcept;

	/// @brief Compute the point and the first three derivatives on a 3D circle at a parameter
	/// @param[in] u The parameter
	/// @param[in] circle The circle
	/// @param[out] p The point
	/// @param[out] v1 The first derivative
	/// @param[out] v2 The second derivative
	/// @param[out] v3 The third derivative
	AMCAX_API static void D3(double u, const Circle3& circle, Point3& p, Vector3& v1, Vector3& v2, Vector3& v3) noexcept;

	/// @brief Compute the parameter of a given point on a 3D circle
	/// @param circle The circle
	/// @param p The given point
	/// @return The parameter of point
	[[nodiscard]] AMCAX_API static double Parameter(const Circle3& circle, const Point3& p) noexcept;

	/// @brief Compute the point on a 3D circle represented by a local frame and a radius at a parameter
	/// @param u The parameter
	/// @param pos The local frame where the circle lies
	/// @param radius The radius
	/// @return The point
	[[nodiscard]] AMCAX_API static Point3 CircleValue(double u, const Frame3& pos, double radius) noexcept;

	/// @brief Compute the point on a 3D circle represented by a local frame and a radius at a parameter
	/// @param u The parameter
	/// @param pos The local frame where the circle lies
	/// @param radius The radius
	/// @return The point
	[[nodiscard]] AMCAX_API static Point3 CircleD0(double u, const Frame3& pos, double radius) noexcept;

	/// @brief Compute the first derivative on a 3D circle represented by a local frame and a radius at a parameter
	/// @param u The parameter
	/// @param pos The local frame where the circle lies
	/// @param radius The radius
	/// @return The first derivative
	[[nodiscard]] AMCAX_API static Vector3 CircleD1(double u, const Frame3& pos, double radius) noexcept;

	/// @brief Compute the second derivative on a 3D circle represented by a local frame and a radius at a parameter
	/// @param u The parameter
	/// @param pos The local frame where the circle lies
	/// @param radius The radius
	/// @return The second derivative
	[[nodiscard]] AMCAX_API static Vector3 CircleD2(double u, const Frame3& pos, double radius) noexcept;

	/// @brief Compute the third derivative on a 3D circle represented by a local frame and a radius at a parameter
	/// @param u The parameter
	/// @param pos The local frame where the circle lies
	/// @param radius The radius
	/// @return The third derivative
	[[nodiscard]] AMCAX_API static Vector3 CircleD3(double u, const Frame3& pos, double radius) noexcept;

	/// @brief Compute the n-th derivative on a 3D circle represented by a local frame and a radius at a parameter
	/// @param u The parameter
	/// @param pos The local frame where the circle lies
	/// @param radius The radius
	/// @param n The order of derivative
	/// @return The n-th derivative
	[[nodiscard]] AMCAX_API static Vector3 CircleDN(double u, const Frame3& pos, double radius, int n) noexcept;

	/// @brief Compute the point and the first derivative on a 3D circle represented by a local frame and a radius at a parameter
	/// @param[in] u The parameter
	/// @param[in] pos The local frame where the circle lies
	/// @param[in] radius The radius
	/// @param[out] p The point
	/// @param[out] v1 The first derivative
	AMCAX_API static void CircleD1(double u, const Frame3& pos, double radius, Point3& p, Vector3& v1) noexcept;

	/// @brief Compute the point and the first two derivatives on a 3D circle represented by a local frame and a radius at a parameter
	/// @param[in] u The parameter
	/// @param[in] pos The local frame where the circle lies
	/// @param[in] radius The radius
	/// @param[out] p The point
	/// @param[out] v1 The first derivative
	/// @param[out] v2 The second derivative
	AMCAX_API static void CircleD2(double u, const Frame3& pos, double radius, Point3& p, Vector3& v1, Vector3& v2) noexcept;

	/// @brief Compute the point and the first three derivatives on a 3D circle represented by a local frame and a radius at a parameter
	/// @param[in] u The parameter
	/// @param[in] pos The local frame where the circle lies
	/// @param[in] radius The radius
	/// @param[out] p The point
	/// @param[out] v1 The first derivative
	/// @param[out] v2 The second derivative
	/// @param[out] v3 The third derivative
	AMCAX_API static void CircleD3(double u, const Frame3& pos, double radius, Point3& p, Vector3& v1, Vector3& v2, Vector3& v3) noexcept;

	/// @brief Compute the parameter of a given point on a 3D circle represented by a local frame
	/// @param pos The local frame where the circle lies
	/// @param p The given point
	/// @return The parameter of point
	[[nodiscard]] AMCAX_API static double CircleParameter(const Frame3& pos, const Point3& p) noexcept;

	/// @brief Compute the point on a 3D ellipse at a parameter
	/// @param u The parameter
	/// @param ellipse The ellipse
	/// @return The resulting point
	[[nodiscard]] AMCAX_API static Point3 Value(double u, const Ellipse3& ellipse) noexcept;

	/// @brief Compute the point on a 3D ellipse at a parameter
	/// @param u The parameter
	/// @param ellipse The ellipse
	/// @return The resulting point
	[[nodiscard]] AMCAX_API static Point3 D0(double u, const Ellipse3& ellipse) noexcept;

	/// @brief Compute the first derivative on a 3D ellipse at a parameter
	/// @param u The parameter
	/// @param ellipse The ellipse
	/// @return The first derivative
	[[nodiscard]] AMCAX_API static Vector3 D1(double u, const Ellipse3& ellipse) noexcept;

	/// @brief Compute the second derivative on a 3D ellipse at a parameter
	/// @param u The parameter
	/// @param ellipse The ellipse
	/// @return The second derivative
	[[nodiscard]] AMCAX_API static Vector3 D2(double u, const Ellipse3& ellipse) noexcept;

	/// @brief Compute the third derivative on a 3D ellipse at a parameter
	/// @param u The parameter
	/// @param ellipse The ellipse
	/// @return The third derivative
	[[nodiscard]] AMCAX_API static Vector3 D3(double u, const Ellipse3& ellipse) noexcept;

	/// @brief Compute the n-th derivative on a 3D ellipse at a parameter
	/// @param u The parameter
	/// @param ellipse The ellipse
	/// @param n The order of derivative
	/// @return The n-th derivative
	[[nodiscard]] AMCAX_API static Vector3 DN(double u, const Ellipse3& ellipse, int n) noexcept;

	/// @brief Compute the point and the first derivative on a 3D ellipse at a parameter
	/// @param[in] u The parameter
	/// @param[in] ellipse The ellipse
	/// @param[out] p The point
	/// @param[out] v1 The first derivative
	AMCAX_API static void D1(double u, const Ellipse3& ellipse, Point3& p, Vector3& v1) noexcept;

	/// @brief Compute the point and the first two derivatives on a 3D ellipse at a parameter
	/// @param[in] u The parameter
	/// @param[in] ellipse The ellipse
	/// @param[out] p The point
	/// @param[out] v1 The first derivative
	/// @param[out] v2 The second derivative
	AMCAX_API static void D2(double u, const Ellipse3& ellipse, Point3& p, Vector3& v1, Vector3& v2) noexcept;

	/// @brief Compute the point and the first three derivatives on a 3D ellipse at a parameter
	/// @param[in] u The parameter
	/// @param[in] ellipse The ellipse
	/// @param[out] p The point
	/// @param[out] v1 The first derivative
	/// @param[out] v2 The second derivative
	/// @param[out] v3 The third derivative
	AMCAX_API static void D3(double u, const Ellipse3& ellipse, Point3& p, Vector3& v1, Vector3& v2, Vector3& v3) noexcept;

	/// @brief Compute the parameter of a given point on a 3D ellipse
	/// @param ellipse The ellipse
	/// @param p The given point
	/// @return The parameter of point
	[[nodiscard]] AMCAX_API static double Parameter(const Ellipse3& ellipse, const Point3& p) noexcept;

	/// @brief Compute the point on a 3D ellipse represented by a local frame, a major radius and a minor radius at a parameter
	/// @param u The parameter
	/// @param pos The local frame where the ellipse lies
	/// @param majorRadius The major radius
	/// @param minorRadius The minor radius
	/// @return The point
	[[nodiscard]] AMCAX_API static Point3 EllipseValue(double u, const Frame3& pos, double majorRadius, double minorRadius) noexcept;

	/// @brief Compute the point on a 3D ellipse represented by a local frame, a major radius and a minor radius at a parameter
	/// @param u The parameter
	/// @param pos The local frame where the ellipse lies
	/// @param majorRadius The major radius
	/// @param minorRadius The minor radius
	/// @return The point
	[[nodiscard]] AMCAX_API static Point3 EllipseD0(double u, const Frame3& pos, double majorRadius, double minorRadius) noexcept;

	/// @brief Compute the first derivative on a 3D ellipse represented by a local frame, a major radius and a minor radius at a parameter
	/// @param u The parameter
	/// @param pos The local frame where the ellipse lies
	/// @param majorRadius The major radius
	/// @param minorRadius The minor radius
	/// @return The first derivative
	[[nodiscard]] AMCAX_API static Vector3 EllipseD1(double u, const Frame3& pos, double majorRadius, double minorRadius) noexcept;

	/// @brief Compute the second derivative on a 3D ellipse represented by a local frame, a major radius and a minor radius at a parameter
	/// @param u The parameter
	/// @param pos The local frame where the ellipse lies
	/// @param majorRadius The major radius
	/// @param minorRadius The minor radius
	/// @return The second derivative
	[[nodiscard]] AMCAX_API static Vector3 EllipseD2(double u, const Frame3& pos, double majorRadius, double minorRadius) noexcept;

	/// @brief Compute the third derivative on a 3D ellipse represented by a local frame, a major radius and a minor radius at a parameter
	/// @param u The parameter
	/// @param pos The local frame where the ellipse lies
	/// @param majorRadius The major radius
	/// @param minorRadius The minor radius
	/// @return The third derivative
	[[nodiscard]] AMCAX_API static Vector3 EllipseD3(double u, const Frame3& pos, double majorRadius, double minorRadius) noexcept;

	/// @brief Compute the n-th derivative on a 3D ellipse represented by a local frame, a major radius and a minor radius at a parameter
	/// @param u The parameter
	/// @param pos The local frame where the ellipse lies
	/// @param majorRadius The major radius
	/// @param minorRadius The minor radius
	/// @param n The order of derivative
	/// @return The n-th derivative
	[[nodiscard]] AMCAX_API static Vector3 EllipseDN(double u, const Frame3& pos, double majorRadius, double minorRadius, int n) noexcept;

	/// @brief Compute the point and the first derivative on a 3D ellipse represented by a local frame, a major radius and a minor radius at a parameter
	/// @param[in] u The parameter
	/// @param[in] pos The local frame where the ellipse lies
	/// @param[in] majorRadius The major radius
	/// @param[in] minorRadius The minor radius
	/// @param[out] p The point
	/// @param[out] v1 The first derivative
	AMCAX_API static void EllipseD1(double u, const Frame3& pos, double majorRadius, double minorRadius, Point3& p, Vector3& v1) noexcept;

	/// @brief Compute the point and the first two derivatives on a 3D ellipse represented by a local frame, a major radius and a minor radius at a parameter
	/// @param[in] u The parameter
	/// @param[in] pos The local frame where the ellipse lies
	/// @param[in] majorRadius The major radius
	/// @param[in] minorRadius The minor radius
	/// @param[out] p The point
	/// @param[out] v1 The first derivative
	/// @param[out] v2 The second derivative
	AMCAX_API static void EllipseD2(double u, const Frame3& pos, double majorRadius, double minorRadius, Point3& p, Vector3& v1, Vector3& v2) noexcept;

	/// @brief Compute the point and the first three derivatives on a 3D ellipse represented by a local frame, a major radius and a minor radius at a parameter
	/// @param[in] u The parameter
	/// @param[in] pos The local frame where the ellipse lies
	/// @param[in] majorRadius The major radius
	/// @param[in] minorRadius The minor radius
	/// @param[out] p The point
	/// @param[out] v1 The first derivative
	/// @param[out] v2 The second derivative
	/// @param[out] v3 The third derivative
	AMCAX_API static void EllipseD3(double u, const Frame3& pos, double majorRadius, double minorRadius, Point3& p, Vector3& v1, Vector3& v2, Vector3& v3) noexcept;

	/// @brief Compute the parameter of a given point on a 3D ellipse represented by a local frame, a major radius and a minor radius
	/// @param pos The local frame where the ellipse lies
	/// @param majorRadius The major radius
	/// @param minorRadius The minor radius
	/// @param p The given point
	/// @return The parameter of point
	[[nodiscard]] AMCAX_API static double EllipseParameter(const Frame3& pos, double majorRadius, double minorRadius, const Point3& p) noexcept;

	/// @brief Compute the point on a 3D parabola at a parameter
	/// @param u The parameter
	/// @param parabola The parabola
	/// @return The resulting point
	[[nodiscard]] AMCAX_API static Point3 Value(double u, const Parabola3& parabola) noexcept;

	/// @brief Compute the point on a 3D parabola at a parameter
	/// @param u The parameter
	/// @param parabola The parabola
	/// @return The resulting point
	[[nodiscard]] AMCAX_API static Point3 D0(double u, const Parabola3& parabola) noexcept;

	/// @brief Compute the first derivative on a 3D parabola at a parameter
	/// @param u The parameter
	/// @param parabola The parabola
	/// @return The first derivative
	[[nodiscard]] AMCAX_API static Vector3 D1(double u, const Parabola3& parabola) noexcept;

	/// @brief Compute the second derivative on a 3D parabola at a parameter
	/// @param u The parameter
	/// @param parabola The parabola
	/// @return The second derivative
	[[nodiscard]] AMCAX_API static Vector3 D2(double u, const Parabola3& parabola) noexcept;

	/// @brief Compute the third derivative on a 3D parabola at a parameter
	/// @param u The parameter
	/// @param parabola The parabola
	/// @return The third derivative
	[[nodiscard]] AMCAX_API static Vector3 D3(double u, const Parabola3& parabola) noexcept;

	/// @brief Compute the n-th derivative on a 3D parabola at a parameter
	/// @param u The parameter
	/// @param parabola The parabola
	/// @param n The order of derivative
	/// @return The n-th derivative
	[[nodiscard]] AMCAX_API static Vector3 DN(double u, const Parabola3& parabola, int n) noexcept;

	/// @brief Compute the point and the first derivative on a 3D parabola at a parameter
	/// @param[in] u The parameter
	/// @param[in] parabola The parabola
	/// @param[out] p The point
	/// @param[out] v1 The first derivative
	AMCAX_API static void D1(double u, const Parabola3& parabola, Point3& p, Vector3& v1) noexcept;

	/// @brief Compute the point and the first two derivatives on a 3D parabola at a parameter
	/// @param[in] u The parameter
	/// @param[in] parabola The parabola
	/// @param[out] p The point
	/// @param[out] v1 The first derivative
	/// @param[out] v2 The second derivative
	AMCAX_API static void D2(double u, const Parabola3& parabola, Point3& p, Vector3& v1, Vector3& v2) noexcept;

	/// @brief Compute the point and the first three derivatives on a 3D parabola at a parameter
	/// @param[in] u The parameter
	/// @param[in] parabola The parabola
	/// @param[out] p The point
	/// @param[out] v1 The first derivative
	/// @param[out] v2 The second derivative
	/// @param[out] v3 The third derivative
	AMCAX_API static void D3(double u, const Parabola3& parabola, Point3& p, Vector3& v1, Vector3& v2, Vector3& v3) noexcept;

	/// @brief Compute the parameter of a given point on a 3D parabola
	/// @param parabola The parabola
	/// @param p The given point
	/// @return The parameter of point
	[[nodiscard]] AMCAX_API static double Parameter(const Parabola3& parabola, const Point3& p) noexcept;

	/// @brief Compute the point on a 3D parabola represented by a local frame and a focal length at a parameter
	/// @param u The parameter
	/// @param pos The local frame where the parabola lies
	/// @param focal The focal length
	/// @return The point
	[[nodiscard]] AMCAX_API static Point3 ParabolaValue(double u, const Frame3& pos, double focal) noexcept;

	/// @brief Compute the point on a 3D parabola represented by a local frame and a focal length at a parameter
	/// @param u The parameter
	/// @param pos The local frame where the parabola lies
	/// @param focal The focal length
	/// @return The point
	[[nodiscard]] AMCAX_API static Point3 ParabolaD0(double u, const Frame3& pos, double focal) noexcept;

	/// @brief Compute the first derivative on a 3D parabola represented by a local frame and a focal length at a parameter
	/// @param u The parameter
	/// @param pos The local frame where the parabola lies
	/// @param focal The focal length
	/// @return The first derivative
	[[nodiscard]] AMCAX_API static Vector3 ParabolaD1(double u, const Frame3& pos, double focal) noexcept;

	/// @brief Compute the second derivative on a 3D parabola represented by a local frame and a focal length at a parameter
	/// @param u The parameter
	/// @param pos The local frame where the parabola lies
	/// @param focal The focal length
	/// @return The second derivative
	[[nodiscard]] AMCAX_API static Vector3 ParabolaD2(double u, const Frame3& pos, double focal) noexcept;

	/// @brief Compute the third derivative on a 3D parabola represented by a local frame and a focal length at a parameter
	/// @param u The parameter
	/// @param pos The local frame where the parabola lies
	/// @param focal The focal length
	/// @return The third derivative
	[[nodiscard]] AMCAX_API static Vector3 ParabolaD3(double u, const Frame3& pos, double focal) noexcept;

	/// @brief Compute the n-th derivative on a 3D parabola represented by a local frame and a focal length at a parameter
	/// @param u The parameter
	/// @param pos The local frame where the parabola lies
	/// @param focal The focal length
	/// @param n The order of derivative
	/// @return The n-th derivative
	[[nodiscard]] AMCAX_API static Vector3 ParabolaDN(double u, const Frame3& pos, double focal, int n) noexcept;

	/// @brief Compute the point and the first derivative on a 3D parabola represented by a local frame and a focal length at a parameter
	/// @param[in] u The parameter
	/// @param[in] pos The local frame where the parabola lies
	/// @param[in] focal The focal length
	/// @param[out] p The point
	/// @param[out] v1 The first derivative
	AMCAX_API static void ParabolaD1(double u, const Frame3& pos, double focal, Point3& p, Vector3& v1) noexcept;

	/// @brief Compute the point and the first two derivatives on a 3D parabola represented by a local frame and a focal length at a parameter
	/// @param[in] u The parameter
	/// @param[in] pos The local frame where the parabola lies
	/// @param[in] focal The focal length
	/// @param[out] p The point
	/// @param[out] v1 The first derivative
	/// @param[out] v2 The second derivative
	AMCAX_API static void ParabolaD2(double u, const Frame3& pos, double focal, Point3& p, Vector3& v1, Vector3& v2) noexcept;

	/// @brief Compute the point and the first three derivatives on a 3D parabola represented by a local frame and a focal length at a parameter
	/// @param[in] u The parameter
	/// @param[in] pos The local frame where the parabola lies
	/// @param[in] focal The focal length
	/// @param[out] p The point
	/// @param[out] v1 The first derivative
	/// @param[out] v2 The second derivative
	/// @param[out] v3 The third derivative
	AMCAX_API static void ParabolaD3(double u, const Frame3& pos, double focal, Point3& p, Vector3& v1, Vector3& v2, Vector3& v3) noexcept;

	/// @brief Compute the parameter of a given point on a 3D parabola represented by a local frame and a focal length
	/// @param pos The local frame where the parabola lies
	/// @param focal The focal length
	/// @param p The given point
	/// @return The parameter of point
	[[nodiscard]] AMCAX_API static double ParabolaParameter(const Frame3& pos, double focal, const Point3& p) noexcept;

	/// @brief Compute the point on a 3D hyperbola at a parameter
	/// @param u The parameter
	/// @param hyperbola The hyperbola
	/// @return The resulting point
	[[nodiscard]] AMCAX_API static Point3 Value(double u, const Hyperbola3& hyperbola) noexcept;

	/// @brief Compute the point on a 3D hyperbola at a parameter
	/// @param u The parameter
	/// @param hyperbola The hyperbola
	/// @return The resulting point
	[[nodiscard]] AMCAX_API static Point3 D0(double u, const Hyperbola3& hyperbola) noexcept;

	/// @brief Compute the first derivative on a 3D hyperbola at a parameter
	/// @param u The parameter
	/// @param hyperbola The hyperbola
	/// @return The first derivative
	[[nodiscard]] AMCAX_API static Vector3 D1(double u, const Hyperbola3& hyperbola) noexcept;

	/// @brief Compute the second derivative on a 3D hyperbola at a parameter
	/// @param u The parameter
	/// @param hyperbola The hyperbola
	/// @return The second derivative
	[[nodiscard]] AMCAX_API static Vector3 D2(double u, const Hyperbola3& hyperbola) noexcept;

	/// @brief Compute the third derivative on a 3D hyperbola at a parameter
	/// @param u The parameter
	/// @param hyperbola The hyperbola
	/// @return The third derivative
	[[nodiscard]] AMCAX_API static Vector3 D3(double u, const Hyperbola3& hyperbola) noexcept;

	/// @brief Compute the n-th derivative on a 3D hyperbola at a parameter
	/// @param u The parameter
	/// @param hyperbola The hyperbola
	/// @param n The order of derivative
	/// @return The n-th derivative
	[[nodiscard]] AMCAX_API static Vector3 DN(double u, const Hyperbola3& hyperbola, int n) noexcept;

	/// @brief Compute the point and the first derivative on a 3D hyperbola at a parameter
	/// @param[in] u The parameter
	/// @param[in] hyperbola The hyperbola
	/// @param[out] p The point
	/// @param[out] v1 The first derivative
	AMCAX_API static void D1(double u, const Hyperbola3& hyperbola, Point3& p, Vector3& v1) noexcept;

	/// @brief Compute the point and the first two derivatives on a 3D hyperbola at a parameter
	/// @param[in] u The parameter
	/// @param[in] hyperbola The hyperbola
	/// @param[out] p The point
	/// @param[out] v1 The first derivative
	/// @param[out] v2 The second derivative
	AMCAX_API static void D2(double u, const Hyperbola3& hyperbola, Point3& p, Vector3& v1, Vector3& v2) noexcept;

	/// @brief Compute the point and the first three derivatives on a 3D hyperbola at a parameter
	/// @param[in] u The parameter
	/// @param[in] hyperbola The hyperbola
	/// @param[out] p The point
	/// @param[out] v1 The first derivative
	/// @param[out] v2 The second derivative
	/// @param[out] v3 The third derivative
	AMCAX_API static void D3(double u, const Hyperbola3& hyperbola, Point3& p, Vector3& v1, Vector3& v2, Vector3& v3) noexcept;

	/// @brief Compute the parameter of a given point on a 3D hyperbola
	/// @param hyperbola The hyperbola
	/// @param p The given point
	/// @return The parameter of point
	[[nodiscard]] AMCAX_API static double Parameter(const Hyperbola3& hyperbola, const Point3& p) noexcept;

	/// @brief Compute the point on a 3D hyperbola represented by a local frame, a major radius and a minor radius at a parameter
	/// @param u The parameter
	/// @param pos The local frame where the hyperbola lies
	/// @param majorRadius The major radius
	/// @param minorRadius The minor radius
	/// @return The point
	[[nodiscard]] AMCAX_API static Point3 HyperbolaValue(double u, const Frame3& pos, double majorRadius, double minorRadius) noexcept;

	/// @brief Compute the point on a 3D hyperbola represented by a local frame, a major radius and a minor radius at a parameter
	/// @param u The parameter
	/// @param pos The local frame where the hyperbola lies
	/// @param majorRadius The major radius
	/// @param minorRadius The minor radius
	/// @return The point
	[[nodiscard]] AMCAX_API static Point3 HyperbolaD0(double u, const Frame3& pos, double majorRadius, double minorRadius) noexcept;

	/// @brief Compute the first derivative on a 3D hyperbola represented by a local frame, a major radius and a minor radius at a parameter
	/// @param u The parameter
	/// @param pos The local frame where the hyperbola lies
	/// @param majorRadius The major radius
	/// @param minorRadius The minor radius
	/// @return The first derivative
	[[nodiscard]] AMCAX_API static Vector3 HyperbolaD1(double u, const Frame3& pos, double majorRadius, double minorRadius) noexcept;

	/// @brief Compute the second derivative on a 3D hyperbola represented by a local frame, a major radius and a minor radius at a parameter
	/// @param u The parameter
	/// @param pos The local frame where the hyperbola lies
	/// @param majorRadius The major radius
	/// @param minorRadius The minor radius
	/// @return The second derivative
	[[nodiscard]] AMCAX_API static Vector3 HyperbolaD2(double u, const Frame3& pos, double majorRadius, double minorRadius) noexcept;

	/// @brief Compute the third derivative on a 3D hyperbola represented by a local frame, a major radius and a minor radius at a parameter
	/// @param u The parameter
	/// @param pos The local frame where the hyperbola lies
	/// @param majorRadius The major radius
	/// @param minorRadius The minor radius
	/// @return The third derivative
	[[nodiscard]] AMCAX_API static Vector3 HyperbolaD3(double u, const Frame3& pos, double majorRadius, double minorRadius) noexcept;

	/// @brief Compute the n-th derivative on a 3D hyperbola represented by a local frame, a major radius and a minor radius at a parameter
	/// @param u The parameter
	/// @param pos The local frame where the hyperbola lies
	/// @param majorRadius The major radius
	/// @param minorRadius The minor radius
	/// @param n The order of derivative
	/// @return The n-th derivative
	[[nodiscard]] AMCAX_API static Vector3 HyperbolaDN(double u, const Frame3& pos, double majorRadius, double minorRadius, int n) noexcept;

	/// @brief Compute the point and the first derivative on a 3D hyperbola represented by a local frame, a major radius and a minor radius at a parameter
	/// @param[in] u The parameter
	/// @param[in] pos The local frame where the hyperbola lies
	/// @param[in] majorRadius The major radius
	/// @param[in] minorRadius The minor radius
	/// @param[out] p The point
	/// @param[out] v1 The first derivative
	AMCAX_API static void HyperbolaD1(double u, const Frame3& pos, double majorRadius, double minorRadius, Point3& p, Vector3& v1) noexcept;

	/// @brief Compute the point and the first two derivatives on a 3D hyperbola represented by a local frame, a major radius and a minor radius at a parameter
	/// @param[in] u The parameter
	/// @param[in] pos The local frame where the hyperbola lies
	/// @param[in] majorRadius The major radius
	/// @param[in] minorRadius The minor radius
	/// @param[out] p The point
	/// @param[out] v1 The first derivative
	/// @param[out] v2 The second derivative
	AMCAX_API static void HyperbolaD2(double u, const Frame3& pos, double majorRadius, double minorRadius, Point3& p, Vector3& v1, Vector3& v2) noexcept;

	/// @brief Compute the point and the first three derivatives on a 3D hyperbola represented by a local frame, a major radius and a minor radius at a parameter
	/// @param[in] u The parameter
	/// @param[in] pos The local frame where the hyperbola lies
	/// @param[in] majorRadius The major radius
	/// @param[in] minorRadius The minor radius
	/// @param[out] p The point
	/// @param[out] v1 The first derivative
	/// @param[out] v2 The second derivative
	/// @param[out] v3 The third derivative
	AMCAX_API static void HyperbolaD3(double u, const Frame3& pos, double majorRadius, double minorRadius, Point3& p, Vector3& v1, Vector3& v2, Vector3& v3) noexcept;

	/// @brief Compute the parameter of a given point on a 3D hyperbola represented by a local frame, a major radius and a minor radius
	/// @param pos The local frame where the hyperbola lies
	/// @param majorRadius The major radius
	/// @param minorRadius The minor radius
	/// @param p The given point
	/// @return The parameter of point
	[[nodiscard]] AMCAX_API static double HyperbolaParameter(const Frame3& pos, double majorRadius, double minorRadius, const Point3& p) noexcept;

	/// @brief Compute the point on a 2D line at a parameter
	/// @param u The parameter
	/// @param line The line
	/// @return The resulting point
	[[nodiscard]] AMCAX_API static Point2 Value(double u, const Line2& line) noexcept;

	/// @brief Compute the point on a 2D line at a parameter
	/// @param u The parameter
	/// @param line The line
	/// @return The resulting point
	[[nodiscard]] AMCAX_API static Point2 D0(double u, const Line2& line) noexcept;

	/// @brief Compute the first derivative on a 2D line at a parameter
	/// @param u The parameter
	/// @param line The line
	/// @return The first derivative
	[[nodiscard]] AMCAX_API static Vector2 D1(double u, const Line2& line) noexcept;

	/// @brief Compute the second derivative on a 2D line at a parameter
	/// @param u The parameter
	/// @param line The line
	/// @return The second derivative
	[[nodiscard]] AMCAX_API static Vector2 D2(double u, const Line2& line) noexcept;

	/// @brief Compute the third derivative on a 2D line at a parameter
	/// @param u The parameter
	/// @param line The line
	/// @return The third derivative
	[[nodiscard]] AMCAX_API static Vector2 D3(double u, const Line2& line) noexcept;

	/// @brief Compute the n-th derivative on a 2D line at a parameter
	/// @param u The parameter
	/// @param line The line
	/// @param n The order of derivative
	/// @return The n-th derivative
	[[nodiscard]] AMCAX_API static Vector2 DN(double u, const Line2& line, int n) noexcept;

	/// @brief Compute the point and the first derivative on a 2D line at a parameter
	/// @param[in] u The parameter
	/// @param[in] line The line
	/// @param[out] p The point
	/// @param[out] v1 The first derivative
	AMCAX_API static void D1(double u, const Line2& line, Point2& p, Vector2& v1) noexcept;

	/// @brief Compute the point and the first two derivatives on a 2D line at a parameter
	/// @param[in] u The parameter
	/// @param[in] line The line
	/// @param[out] p The point
	/// @param[out] v1 The first derivative
	/// @param[out] v2 The second derivative
	AMCAX_API static void D2(double u, const Line2& line, Point2& p, Vector2& v1, Vector2& v2) noexcept;

	/// @brief Compute the point and the first three derivatives on a 2D line at a parameter
	/// @param[in] u The parameter
	/// @param[in] line The line
	/// @param[out] p The point
	/// @param[out] v1 The first derivative
	/// @param[out] v2 The second derivative
	/// @param[out] v3 The third derivative
	AMCAX_API static void D3(double u, const Line2& line, Point2& p, Vector2& v1, Vector2& v2, Vector2& v3) noexcept;

	/// @brief Compute the parameter of a given point on a 2D line
	/// @param line The line
	/// @param p The given point
	/// @return The parameter of point
	[[nodiscard]] AMCAX_API static double Parameter(const Line2& line, const Point2& p) noexcept;

	/// @brief Compute the point on a 2D line represented by an axis at a parameter
	/// @param u The parameter
	/// @param pos The axis where the line lies
	/// @return The point
	[[nodiscard]] AMCAX_API static Point2 LineValue(double u, const Axis2& pos) noexcept;

	/// @brief Compute the point on a 2D line represented by an axis at a parameter
	/// @param u The parameter
	/// @param pos The axis where the line lies
	/// @return The point
	[[nodiscard]] AMCAX_API static Point2 LineD0(double u, const Axis2& pos) noexcept;

	/// @brief Compute the first derivative on a 2D line represented by an axis at a parameter
	/// @param u The parameter
	/// @param pos The axis where the line lies
	/// @return The first derivative
	[[nodiscard]] AMCAX_API static Vector2 LineD1(double u, const Axis2& pos) noexcept;

	/// @brief Compute the second derivative on a 2D line represented by an axis at a parameter
	/// @param u The parameter
	/// @param pos The axis where the line lies
	/// @return The second derivative
	[[nodiscard]] AMCAX_API static Vector2 LineD2(double u, const Axis2& pos) noexcept;

	/// @brief Compute the third derivative on a 2D line represented by an axis at a parameter
	/// @param u The parameter
	/// @param pos The axis where the line lies
	/// @return The third derivative
	[[nodiscard]] AMCAX_API static Vector2 LineD3(double u, const Axis2& pos) noexcept;

	/// @brief Compute the n-th derivative on a 2D line represented by an axis at a parameter
	/// @param u The parameter
	/// @param pos The axis where the line lies
	/// @param n The order of derivative
	/// @return The n-th derivative
	[[nodiscard]] AMCAX_API static Vector2 LineDN(double u, const Axis2& pos, int n) noexcept;

	/// @brief Compute the point and the first derivative on a 2D line represented by an axis at a parameter
	/// @param[in] u The parameter
	/// @param[in] pos The axis where the line lies
	/// @param[out] p The point
	/// @param[out] v1 The first derivative
	AMCAX_API static void LineD1(double u, const Axis2& pos, Point2& p, Vector2& v1) noexcept;

	/// @brief Compute the point and the first two derivatives on a 2D line represented by an axis at a parameter
	/// @param[in] u The parameter
	/// @param[in] pos The axis where the line lies
	/// @param[out] p The point
	/// @param[out] v1 The first derivative
	/// @param[out] v2 The second derivative
	AMCAX_API static void LineD2(double u, const Axis2& pos, Point2& p, Vector2& v1, Vector2& v2) noexcept;

	/// @brief Compute the point and the first three derivatives on a 2D line represented by an axis at a parameter
	/// @param[in] u The parameter
	/// @param[in] pos The axis where the line lies
	/// @param[out] p The point
	/// @param[out] v1 The first derivative
	/// @param[out] v2 The second derivative
	/// @param[out] v3 The third derivative
	AMCAX_API static void LineD3(double u, const Axis2& pos, Point2& p, Vector2& v1, Vector2& v2, Vector2& v3) noexcept;

	/// @brief Compute the parameter of a given point on a 2D line represented by an axis
	/// @param pos The axis where the line lies
	/// @param p The given point
	/// @return The parameter of point
	[[nodiscard]] AMCAX_API static double LineParameter(const Axis2& pos, const Point2& p) noexcept;

	/// @brief Compute the point on a 2D circle at a parameter
	/// @param u The parameter
	/// @param circle The circle
	/// @return The resulting point
	[[nodiscard]] AMCAX_API static Point2 Value(double u, const Circle2& circle) noexcept;

	/// @brief Compute the point on a 2D circle at a parameter
	/// @param u The parameter
	/// @param circle The circle
	/// @return The resulting point
	[[nodiscard]] AMCAX_API static Point2 D0(double u, const Circle2& circle) noexcept;

	/// @brief Compute the first derivative on a 2D circle at a parameter
	/// @param u The parameter
	/// @param circle The circle
	/// @return The first derivative
	[[nodiscard]] AMCAX_API static Vector2 D1(double u, const Circle2& circle) noexcept;

	/// @brief Compute the second derivative on a 2D circle at a parameter
	/// @param u The parameter
	/// @param circle The circle
	/// @return The second derivative
	[[nodiscard]] AMCAX_API static Vector2 D2(double u, const Circle2& circle) noexcept;

	/// @brief Compute the third derivative on a 2D circle at a parameter
	/// @param u The parameter
	/// @param circle The circle
	/// @return The third derivative
	[[nodiscard]] AMCAX_API static Vector2 D3(double u, const Circle2& circle) noexcept;

	/// @brief Compute the n-th derivative on a 2D circle at a parameter
	/// @param u The parameter
	/// @param circle The circle
	/// @param n The order of derivative
	/// @return The n-th derivative
	[[nodiscard]] AMCAX_API static Vector2 DN(double u, const Circle2& circle, int n) noexcept;

	/// @brief Compute the point and the first derivative on a 2D circle at a parameter
	/// @param[in] u The parameter
	/// @param[in] circle The circle
	/// @param[out] p The point
	/// @param[out] v1 The first derivative
	AMCAX_API static void D1(double u, const Circle2& circle, Point2& p, Vector2& v1) noexcept;

	/// @brief Compute the point and the first two derivatives on a 2D circle at a parameter
	/// @param[in] u The parameter
	/// @param[in] circle The circle
	/// @param[out] p The point
	/// @param[out] v1 The first derivative
	/// @param[out] v2 The second derivative
	AMCAX_API static void D2(double u, const Circle2& circle, Point2& p, Vector2& v1, Vector2& v2) noexcept;

	/// @brief Compute the point and the first three derivatives on a 2D circle at a parameter
	/// @param[in] u The parameter
	/// @param[in] circle The circle
	/// @param[out] p The point
	/// @param[out] v1 The first derivative
	/// @param[out] v2 The second derivative
	/// @param[out] v3 The third derivative
	AMCAX_API static void D3(double u, const Circle2& circle, Point2& p, Vector2& v1, Vector2& v2, Vector2& v3) noexcept;

	/// @brief Compute the parameter of a given point on a 2D circle
	/// @param circle The circle
	/// @param p The given point
	/// @return The parameter of point
	[[nodiscard]] AMCAX_API static double Parameter(const Circle2& circle, const Point2& p) noexcept;

	/// @brief Compute the point on a 2D circle represented by a local frame and a radius at a parameter
	/// @param u The parameter
	/// @param pos The local frame where the circle lies
	/// @param radius The radius
	/// @return The point
	[[nodiscard]] AMCAX_API static Point2 CircleValue(double u, const Frame2& pos, double radius) noexcept;

	/// @brief Compute the point on a 2D circle represented by a local frame and a radius at a parameter
	/// @param u The parameter
	/// @param pos The local frame where the circle lies
	/// @param radius The radius
	/// @return The point
	[[nodiscard]] AMCAX_API static Point2 CircleD0(double u, const Frame2& pos, double radius) noexcept;

	/// @brief Compute the first derivative on a 2D circle represented by a local frame and a radius at a parameter
	/// @param u The parameter
	/// @param pos The local frame where the circle lies
	/// @param radius The radius
	/// @return The first derivative
	[[nodiscard]] AMCAX_API static Vector2 CircleD1(double u, const Frame2& pos, double radius) noexcept;

	/// @brief Compute the second derivative on a 2D circle represented by a local frame and a radius at a parameter
	/// @param u The parameter
	/// @param pos The local frame where the circle lies
	/// @param radius The radius
	/// @return The second derivative
	[[nodiscard]] AMCAX_API static Vector2 CircleD2(double u, const Frame2& pos, double radius) noexcept;

	/// @brief Compute the third derivative on a 2D circle represented by a local frame and a radius at a parameter
	/// @param u The parameter
	/// @param pos The local frame where the circle lies
	/// @param radius The radius
	/// @return The third derivative
	[[nodiscard]] AMCAX_API static Vector2 CircleD3(double u, const Frame2& pos, double radius) noexcept;

	/// @brief Compute the n-th derivative on a 2D circle represented by a local frame and a radius at a parameter
	/// @param u The parameter
	/// @param pos The local frame where the circle lies
	/// @param radius The radius
	/// @param n The order of derivative
	/// @return The n-th derivative
	[[nodiscard]] AMCAX_API static Vector2 CircleDN(double u, const Frame2& pos, double radius, int n) noexcept;

	/// @brief Compute the point and the first derivative on a 2D circle represented by a local frame and a radius at a parameter
	/// @param[in] u The parameter
	/// @param[in] pos The local frame where the circle lies
	/// @param[in] radius The radius
	/// @param[out] p The point
	/// @param[out] v1 The first derivative
	AMCAX_API static void CircleD1(double u, const Frame2& pos, double radius, Point2& p, Vector2& v1) noexcept;

	/// @brief Compute the point and the first two derivatives on a 2D circle represented by a local frame and a radius at a parameter
	/// @param[in] u The parameter
	/// @param[in] pos The local frame where the circle lies
	/// @param[in] radius The radius
	/// @param[out] p The point
	/// @param[out] v1 The first derivative
	/// @param[out] v2 The second derivative
	AMCAX_API static void CircleD2(double u, const Frame2& pos, double radius, Point2& p, Vector2& v1, Vector2& v2) noexcept;

	/// @brief Compute the point and the first three derivatives on a 2D circle represented by a local frame and a radius at a parameter
	/// @param[in] u The parameter
	/// @param[in] pos The local frame where the circle lies
	/// @param[in] radius The radius
	/// @param[out] p The point
	/// @param[out] v1 The first derivative
	/// @param[out] v2 The second derivative
	/// @param[out] v3 The third derivative
	AMCAX_API static void CircleD3(double u, const Frame2& pos, double radius, Point2& p, Vector2& v1, Vector2& v2, Vector2& v3) noexcept;

	/// @brief Compute the parameter of a given point on a 2D circle represented by a local frame
	/// @param pos The local frame where the circle lies
	/// @param p The given point
	/// @return The parameter of point
	[[nodiscard]] AMCAX_API static double CircleParameter(const Frame2& pos, const Point2& p) noexcept;

	/// @brief Compute the point on a 2D ellipse at a parameter
	/// @param u The parameter
	/// @param ellipse The ellipse
	/// @return The resulting point
	[[nodiscard]] AMCAX_API static Point2 Value(double u, const Ellipse2& ellipse) noexcept;

	/// @brief Compute the point on a 2D ellipse at a parameter
	/// @param u The parameter
	/// @param ellipse The ellipse
	/// @return The resulting point
	[[nodiscard]] AMCAX_API static Point2 D0(double u, const Ellipse2& ellipse) noexcept;

	/// @brief Compute the first derivative on a 2D ellipse at a parameter
	/// @param u The parameter
	/// @param ellipse The ellipse
	/// @return The first derivative
	[[nodiscard]] AMCAX_API static Vector2 D1(double u, const Ellipse2& ellipse) noexcept;

	/// @brief Compute the second derivative on a 2D ellipse at a parameter
	/// @param u The parameter
	/// @param ellipse The ellipse
	/// @return The second derivative
	[[nodiscard]] AMCAX_API static Vector2 D2(double u, const Ellipse2& ellipse) noexcept;

	/// @brief Compute the third derivative on a 2D ellipse at a parameter
	/// @param u The parameter
	/// @param ellipse The ellipse
	/// @return The third derivative
	[[nodiscard]] AMCAX_API static Vector2 D3(double u, const Ellipse2& ellipse) noexcept;

	/// @brief Compute the n-th derivative on a 2D ellipse at a parameter
	/// @param u The parameter
	/// @param ellipse The ellipse
	/// @param n The order of derivative
	/// @return The n-th derivative
	[[nodiscard]] AMCAX_API static Vector2 DN(double u, const Ellipse2& ellipse, int n) noexcept;

	/// @brief Compute the point and the first derivative on a 2D ellipse at a parameter
	/// @param[in] u The parameter
	/// @param[in] ellipse The ellipse
	/// @param[out] p The point
	/// @param[out] v1 The first derivative
	AMCAX_API static void D1(double u, const Ellipse2& ellipse, Point2& p, Vector2& v1) noexcept;

	/// @brief Compute the point and the first two derivatives on a 2D ellipse at a parameter
	/// @param[in] u The parameter
	/// @param[in] ellipse The ellipse
	/// @param[out] p The point
	/// @param[out] v1 The first derivative
	/// @param[out] v2 The second derivative
	AMCAX_API static void D2(double u, const Ellipse2& ellipse, Point2& p, Vector2& v1, Vector2& v2) noexcept;

	/// @brief Compute the point and the first three derivatives on a 2D ellipse at a parameter
	/// @param[in] u The parameter
	/// @param[in] ellipse The ellipse
	/// @param[out] p The point
	/// @param[out] v1 The first derivative
	/// @param[out] v2 The second derivative
	/// @param[out] v3 The third derivative
	AMCAX_API static void D3(double u, const Ellipse2& ellipse, Point2& p, Vector2& v1, Vector2& v2, Vector2& v3) noexcept;

	/// @brief Compute the parameter of a given point on a 2D ellipse
	/// @param ellipse The ellipse
	/// @param p The given point
	/// @return The parameter of point
	[[nodiscard]] AMCAX_API static double Parameter(const Ellipse2& ellipse, const Point2& p) noexcept;

	/// @brief Compute the point on a 2D ellipse represented by a local frame, a major radius and a minor radius at a parameter
	/// @param u The parameter
	/// @param pos The local frame where the ellipse lies
	/// @param majorRadius The major radius
	/// @param minorRadius The minor radius
	/// @return The point
	[[nodiscard]] AMCAX_API static Point2 EllipseValue(double u, const Frame2& pos, double majorRadius, double minorRadius) noexcept;

	/// @brief Compute the point on a 2D ellipse represented by a local frame, a major radius and a minor radius at a parameter
	/// @param u The parameter
	/// @param pos The local frame where the ellipse lies
	/// @param majorRadius The major radius
	/// @param minorRadius The minor radius
	/// @return The point
	[[nodiscard]] AMCAX_API static Point2 EllipseD0(double u, const Frame2& pos, double majorRadius, double minorRadius) noexcept;

	/// @brief Compute the first derivative on a 2D ellipse represented by a local frame, a major radius and a minor radius at a parameter
	/// @param u The parameter
	/// @param pos The local frame where the ellipse lies
	/// @param majorRadius The major radius
	/// @param minorRadius The minor radius
	/// @return The first derivative
	[[nodiscard]] AMCAX_API static Vector2 EllipseD1(double u, const Frame2& pos, double majorRadius, double minorRadius) noexcept;

	/// @brief Compute the second derivative on a 2D ellipse represented by a local frame, a major radius and a minor radius at a parameter
	/// @param u The parameter
	/// @param pos The local frame where the ellipse lies
	/// @param majorRadius The major radius
	/// @param minorRadius The minor radius
	/// @return The second derivative
	[[nodiscard]] AMCAX_API static Vector2 EllipseD2(double u, const Frame2& pos, double majorRadius, double minorRadius) noexcept;

	/// @brief Compute the third derivative on a 2D ellipse represented by a local frame, a major radius and a minor radius at a parameter
	/// @param u The parameter
	/// @param pos The local frame where the ellipse lies
	/// @param majorRadius The major radius
	/// @param minorRadius The minor radius
	/// @return The third derivative
	[[nodiscard]] AMCAX_API static Vector2 EllipseD3(double u, const Frame2& pos, double majorRadius, double minorRadius) noexcept;

	/// @brief Compute the n-th derivative on a 2D ellipse represented by a local frame, a major radius and a minor radius at a parameter
	/// @param u The parameter
	/// @param pos The local frame where the ellipse lies
	/// @param majorRadius The major radius
	/// @param minorRadius The minor radius
	/// @param n The order of derivative
	/// @return The n-th derivative
	[[nodiscard]] AMCAX_API static Vector2 EllipseDN(double u, const Frame2& pos, double majorRadius, double minorRadius, int n) noexcept;

	/// @brief Compute the point and the first derivative on a 2D ellipse represented by a local frame, a major radius and a minor radius at a parameter
	/// @param[in] u The parameter
	/// @param[in] pos The local frame where the ellipse lies
	/// @param[in] majorRadius The major radius
	/// @param[in] minorRadius The minor radius
	/// @param[out] p The point
	/// @param[out] v1 The first derivative
	AMCAX_API static void EllipseD1(double u, const Frame2& pos, double majorRadius, double minorRadius, Point2& p, Vector2& v1) noexcept;

	/// @brief Compute the point and the first two derivatives on a 2D ellipse represented by a local frame, a major radius and a minor radius at a parameter
	/// @param[in] u The parameter
	/// @param[in] pos The local frame where the ellipse lies
	/// @param[in] majorRadius The major radius
	/// @param[in] minorRadius The minor radius
	/// @param[out] p The point
	/// @param[out] v1 The first derivative
	/// @param[out] v2 The second derivative
	AMCAX_API static void EllipseD2(double u, const Frame2& pos, double majorRadius, double minorRadius, Point2& p, Vector2& v1, Vector2& v2) noexcept;

	/// @brief Compute the point and the first three derivatives on a 2D ellipse represented by a local frame, a major radius and a minor radius at a parameter
	/// @param[in] u The parameter
	/// @param[in] pos The local frame where the ellipse lies
	/// @param[in] majorRadius The major radius
	/// @param[in] minorRadius The minor radius
	/// @param[out] p The point
	/// @param[out] v1 The first derivative
	/// @param[out] v2 The second derivative
	/// @param[out] v3 The third derivative
	AMCAX_API static void EllipseD3(double u, const Frame2& pos, double majorRadius, double minorRadius, Point2& p, Vector2& v1, Vector2& v2, Vector2& v3) noexcept;

	/// @brief Compute the parameter of a given point on a 2D ellipse represented by a local frame, a major radius and a minor radius
	/// @param pos The local frame where the ellipse lies
	/// @param majorRadius The major radius
	/// @param minorRadius The minor radius
	/// @param p The given point
	/// @return The parameter of point
	[[nodiscard]] AMCAX_API static double EllipseParameter(const Frame2& pos, double majorRadius, double minorRadius, const Point2& p) noexcept;

	/// @brief Compute the point on a 2D parabola at a parameter
	/// @param u The parameter
	/// @param parabola The parabola
	/// @return The resulting point
	[[nodiscard]] AMCAX_API static Point2 Value(double u, const Parabola2& parabola) noexcept;

	/// @brief Compute the point on a 2D parabola at a parameter
	/// @param u The parameter
	/// @param parabola The parabola
	/// @return The resulting point
	[[nodiscard]] AMCAX_API static Point2 D0(double u, const Parabola2& parabola) noexcept;

	/// @brief Compute the first derivative on a 2D parabola at a parameter
	/// @param u The parameter
	/// @param parabola The parabola
	/// @return The first derivative
	[[nodiscard]] AMCAX_API static Vector2 D1(double u, const Parabola2& parabola) noexcept;

	/// @brief Compute the second derivative on a 2D parabola at a parameter
	/// @param u The parameter
	/// @param parabola The parabola
	/// @return The second derivative
	[[nodiscard]] AMCAX_API static Vector2 D2(double u, const Parabola2& parabola) noexcept;

	/// @brief Compute the third derivative on a 2D parabola at a parameter
	/// @param u The parameter
	/// @param parabola The parabola
	/// @return The third derivative
	[[nodiscard]] AMCAX_API static Vector2 D3(double u, const Parabola2& parabola) noexcept;

	/// @brief Compute the n-th derivative on a 2D parabola at a parameter
	/// @param u The parameter
	/// @param parabola The parabola
	/// @param n The order of derivative
	/// @return The n-th derivative
	[[nodiscard]] AMCAX_API static Vector2 DN(double u, const Parabola2& parabola, int n) noexcept;

	/// @brief Compute the point and the first derivative on a 2D parabola at a parameter
	/// @param[in] u The parameter
	/// @param[in] parabola The parabola
	/// @param[out] p The point
	/// @param[out] v1 The first derivative
	AMCAX_API static void D1(double u, const Parabola2& parabola, Point2& p, Vector2& v1) noexcept;

	/// @brief Compute the point and the first two derivatives on a 2D parabola at a parameter
	/// @param[in] u The parameter
	/// @param[in] parabola The parabola
	/// @param[out] p The point
	/// @param[out] v1 The first derivative
	/// @param[out] v2 The second derivative
	AMCAX_API static void D2(double u, const Parabola2& parabola, Point2& p, Vector2& v1, Vector2& v2) noexcept;

	/// @brief Compute the point and the first three derivatives on a 2D parabola at a parameter
	/// @param[in] u The parameter
	/// @param[in] parabola The parabola
	/// @param[out] p The point
	/// @param[out] v1 The first derivative
	/// @param[out] v2 The second derivative
	/// @param[out] v3 The third derivative
	AMCAX_API static void D3(double u, const Parabola2& parabola, Point2& p, Vector2& v1, Vector2& v2, Vector2& v3) noexcept;

	/// @brief Compute the parameter of a given point on a 2D parabola
	/// @param parabola The parabola
	/// @param p The given point
	/// @return The parameter of point
	[[nodiscard]] AMCAX_API static double Parameter(const Parabola2& parabola, const Point2& p) noexcept;

	/// @brief Compute the point on a 2D parabola represented by a local frame and a focal length at a parameter
	/// @param u The parameter
	/// @param pos The local frame where the parabola lies
	/// @param focal The focal length
	/// @return The point
	[[nodiscard]] AMCAX_API static Point2 ParabolaValue(double u, const Frame2& pos, double focal) noexcept;

	/// @brief Compute the point on a 2D parabola represented by a local frame and a focal length at a parameter
	/// @param u The parameter
	/// @param pos The local frame where the parabola lies
	/// @param focal The focal length
	/// @return The point
	[[nodiscard]] AMCAX_API static Point2 ParabolaD0(double u, const Frame2& pos, double focal) noexcept;

	/// @brief Compute the first derivative on a 2D parabola represented by a local frame and a focal length at a parameter
	/// @param u The parameter
	/// @param pos The local frame where the parabola lies
	/// @param focal The focal length
	/// @return The first derivative
	[[nodiscard]] AMCAX_API static Vector2 ParabolaD1(double u, const Frame2& pos, double focal) noexcept;

	/// @brief Compute the second derivative on a 2D parabola represented by a local frame and a focal length at a parameter
	/// @param u The parameter
	/// @param pos The local frame where the parabola lies
	/// @param focal The focal length
	/// @return The second derivative
	[[nodiscard]] AMCAX_API static Vector2 ParabolaD2(double u, const Frame2& pos, double focal) noexcept;

	/// @brief Compute the third derivative on a 2D parabola represented by a local frame and a focal length at a parameter
	/// @param u The parameter
	/// @param pos The local frame where the parabola lies
	/// @param focal The focal length
	/// @return The third derivative
	[[nodiscard]] AMCAX_API static Vector2 ParabolaD3(double u, const Frame2& pos, double focal) noexcept;

	/// @brief Compute the n-th derivative on a 2D parabola represented by a local frame and a focal length at a parameter
	/// @param u The parameter
	/// @param pos The local frame where the parabola lies
	/// @param focal The focal length
	/// @param n The order of derivative
	/// @return The n-th derivative
	[[nodiscard]] AMCAX_API static Vector2 ParabolaDN(double u, const Frame2& pos, double focal, int n) noexcept;

	/// @brief Compute the point and the first derivative on a 2D parabola represented by a local frame and a focal length at a parameter
	/// @param[in] u The parameter
	/// @param[in] pos The local frame where the parabola lies
	/// @param[in] focal The focal length
	/// @param[out] p The point
	/// @param[out] v1 The first derivative
	AMCAX_API static void ParabolaD1(double u, const Frame2& pos, double focal, Point2& p, Vector2& v1) noexcept;

	/// @brief Compute the point and the first two derivatives on a 2D parabola represented by a local frame and a focal length at a parameter
	/// @param[in] u The parameter
	/// @param[in] pos The local frame where the parabola lies
	/// @param[in] focal The focal length
	/// @param[out] p The point
	/// @param[out] v1 The first derivative
	/// @param[out] v2 The second derivative
	AMCAX_API static void ParabolaD2(double u, const Frame2& pos, double focal, Point2& p, Vector2& v1, Vector2& v2) noexcept;

	/// @brief Compute the point and the first three derivatives on a 2D parabola represented by a local frame and a focal length at a parameter
	/// @param[in] u The parameter
	/// @param[in] pos The local frame where the parabola lies
	/// @param[in] focal The focal length
	/// @param[out] p The point
	/// @param[out] v1 The first derivative
	/// @param[out] v2 The second derivative
	/// @param[out] v3 The third derivative
	AMCAX_API static void ParabolaD3(double u, const Frame2& pos, double focal, Point2& p, Vector2& v1, Vector2& v2, Vector2& v3) noexcept;

	/// @brief Compute the parameter of a given point on a 2D parabola represented by a local frame and a focal length
	/// @param pos The local frame where the parabola lies
	/// @param focal The focal length
	/// @param p The given point
	/// @return The parameter of point
	[[nodiscard]] AMCAX_API static double ParabolaParameter(const Frame2& pos, double focal, const Point2& p) noexcept;

	/// @brief Compute the point on a 2D hyperbola at a parameter
	/// @param u The parameter
	/// @param hyperbola The hyperbola
	/// @return The resulting point
	[[nodiscard]] AMCAX_API static Point2 Value(double u, const Hyperbola2& hyperbola) noexcept;

	/// @brief Compute the point on a 2D hyperbola at a parameter
	/// @param u The parameter
	/// @param hyperbola The hyperbola
	/// @return The resulting point
	[[nodiscard]] AMCAX_API static Point2 D0(double u, const Hyperbola2& hyperbola) noexcept;

	/// @brief Compute the first derivative on a 2D hyperbola at a parameter
	/// @param u The parameter
	/// @param hyperbola The hyperbola
	/// @return The first derivative
	[[nodiscard]] AMCAX_API static Vector2 D1(double u, const Hyperbola2& hyperbola) noexcept;

	/// @brief Compute the second derivative on a 2D hyperbola at a parameter
	/// @param u The parameter
	/// @param hyperbola The hyperbola
	/// @return The second derivative
	[[nodiscard]] AMCAX_API static Vector2 D2(double u, const Hyperbola2& hyperbola) noexcept;

	/// @brief Compute the third derivative on a 2D hyperbola at a parameter
	/// @param u The parameter
	/// @param hyperbola The hyperbola
	/// @return The third derivative
	[[nodiscard]] AMCAX_API static Vector2 D3(double u, const Hyperbola2& hyperbola) noexcept;

	/// @brief Compute the n-th derivative on a 2D hyperbola at a parameter
	/// @param u The parameter
	/// @param hyperbola The hyperbola
	/// @param n The order of derivative
	/// @return The n-th derivative
	[[nodiscard]] AMCAX_API static Vector2 DN(double u, const Hyperbola2& hyperbola, int n) noexcept;

	/// @brief Compute the point and the first derivative on a 2D hyperbola at a parameter
	/// @param[in] u The parameter
	/// @param[in] hyperbola The hyperbola
	/// @param[out] p The point
	/// @param[out] v1 The first derivative
	AMCAX_API static void D1(double u, const Hyperbola2& hyperbola, Point2& p, Vector2& v1) noexcept;

	/// @brief Compute the point and the first two derivatives on a 2D hyperbola at a parameter
	/// @param[in] u The parameter
	/// @param[in] hyperbola The hyperbola
	/// @param[out] p The point
	/// @param[out] v1 The first derivative
	/// @param[out] v2 The second derivative
	AMCAX_API static void D2(double u, const Hyperbola2& hyperbola, Point2& p, Vector2& v1, Vector2& v2) noexcept;

	/// @brief Compute the point and the first three derivatives on a 2D hyperbola at a parameter
	/// @param[in] u The parameter
	/// @param[in] hyperbola The hyperbola
	/// @param[out] p The point
	/// @param[out] v1 The first derivative
	/// @param[out] v2 The second derivative
	/// @param[out] v3 The third derivative
	AMCAX_API static void D3(double u, const Hyperbola2& hyperbola, Point2& p, Vector2& v1, Vector2& v2, Vector2& v3) noexcept;

	/// @brief Compute the parameter of a given point on a 2D hyperbola
	/// @param hyperbola The hyperbola
	/// @param p The given point
	/// @return The parameter of point
	[[nodiscard]] AMCAX_API static double Parameter(const Hyperbola2& hyperbola, const Point2& p) noexcept;

	/// @brief Compute the point on a 2D hyperbola represented by a local frame, a major radius and a minor radius at a parameter
	/// @param u The parameter
	/// @param pos The local frame where the hyperbola lies
	/// @param majorRadius The major radius
	/// @param minorRadius The minor radius
	/// @return The point
	[[nodiscard]] AMCAX_API static Point2 HyperbolaValue(double u, const Frame2& pos, double majorRadius, double minorRadius) noexcept;

	/// @brief Compute the point on a 2D hyperbola represented by a local frame, a major radius and a minor radius at a parameter
	/// @param u The parameter
	/// @param pos The local frame where the hyperbola lies
	/// @param majorRadius The major radius
	/// @param minorRadius The minor radius
	/// @return The point
	[[nodiscard]] AMCAX_API static Point2 HyperbolaD0(double u, const Frame2& pos, double majorRadius, double minorRadius) noexcept;

	/// @brief Compute the first derivative on a 2D hyperbola represented by a local frame, a major radius and a minor radius at a parameter
	/// @param u The parameter
	/// @param pos The local frame where the hyperbola lies
	/// @param majorRadius The major radius
	/// @param minorRadius The minor radius
	/// @return The first derivative
	[[nodiscard]] AMCAX_API static Vector2 HyperbolaD1(double u, const Frame2& pos, double majorRadius, double minorRadius) noexcept;

	/// @brief Compute the second derivative on a 2D hyperbola represented by a local frame, a major radius and a minor radius at a parameter
	/// @param u The parameter
	/// @param pos The local frame where the hyperbola lies
	/// @param majorRadius The major radius
	/// @param minorRadius The minor radius
	/// @return The second derivative
	[[nodiscard]] AMCAX_API static Vector2 HyperbolaD2(double u, const Frame2& pos, double majorRadius, double minorRadius) noexcept;

	/// @brief Compute the third derivative on a 2D hyperbola represented by a local frame, a major radius and a minor radius at a parameter
	/// @param u The parameter
	/// @param pos The local frame where the hyperbola lies
	/// @param majorRadius The major radius
	/// @param minorRadius The minor radius
	/// @return The third derivative
	[[nodiscard]] AMCAX_API static Vector2 HyperbolaD3(double u, const Frame2& pos, double majorRadius, double minorRadius) noexcept;

	/// @brief Compute the n-th derivative on a 2D hyperbola represented by a local frame, a major radius and a minor radius at a parameter
	/// @param u The parameter
	/// @param pos The local frame where the hyperbola lies
	/// @param majorRadius The major radius
	/// @param minorRadius The minor radius
	/// @param n The order of derivative
	/// @return The n-th derivative
	[[nodiscard]] AMCAX_API static Vector2 HyperbolaDN(double u, const Frame2& pos, double majorRadius, double minorRadius, int n) noexcept;

	/// @brief Compute the point and the first derivative on a 2D hyperbola represented by a local frame, a major radius and a minor radius at a parameter
	/// @param[in] u The parameter
	/// @param[in] pos The local frame where the hyperbola lies
	/// @param[in] majorRadius The major radius
	/// @param[in] minorRadius The minor radius
	/// @param[out] p The point
	/// @param[out] v1 The first derivative
	AMCAX_API static void HyperbolaD1(double u, const Frame2& pos, double majorRadius, double minorRadius, Point2& p, Vector2& v1) noexcept;

	/// @brief Compute the point and the first two derivatives on a 2D hyperbola represented by a local frame, a major radius and a minor radius at a parameter
	/// @param[in] u The parameter
	/// @param[in] pos The local frame where the hyperbola lies
	/// @param[in] majorRadius The major radius
	/// @param[in] minorRadius The minor radius
	/// @param[out] p The point
	/// @param[out] v1 The first derivative
	/// @param[out] v2 The second derivative
	AMCAX_API static void HyperbolaD2(double u, const Frame2& pos, double majorRadius, double minorRadius, Point2& p, Vector2& v1, Vector2& v2) noexcept;

	/// @brief Compute the point and the first three derivatives on a 2D hyperbola represented by a local frame, a major radius and a minor radius at a parameter
	/// @param[in] u The parameter
	/// @param[in] pos The local frame where the hyperbola lies
	/// @param[in] majorRadius The major radius
	/// @param[in] minorRadius The minor radius
	/// @param[out] p The point
	/// @param[out] v1 The first derivative
	/// @param[out] v2 The second derivative
	/// @param[out] v3 The third derivative
	AMCAX_API static void HyperbolaD3(double u, const Frame2& pos, double majorRadius, double minorRadius, Point2& p, Vector2& v1, Vector2& v2, Vector2& v3) noexcept;

	/// @brief Compute the parameter of a given point on a 2D hyperbola represented by a local frame, a major radius and a minor radius
	/// @param pos The local frame where the hyperbola lies
	/// @param majorRadius The major radius
	/// @param minorRadius The minor radius
	/// @param p The given point
	/// @return The parameter of point
	[[nodiscard]] AMCAX_API static double HyperbolaParameter(const Frame2& pos, double majorRadius, double minorRadius, const Point2& p) noexcept;

	/// @brief Convert a 2D point to a 3D point
	/// @param pos The 3D local frame
	/// @param p The 2D point
	/// @return The 3D point
	[[nodiscard]] AMCAX_API static Point3 To3d(const Frame3& pos, const Point2& p) noexcept;

	/// @brief Convert a 2D vector to a 3D vector
	/// @param pos The 3D local frame
	/// @param v The 2D vector
	/// @return The 3D vector
	[[nodiscard]] AMCAX_API static Vector3 To3d(const Frame3& pos, const Vector2& v) noexcept;

	/// @brief Convert a 2D direction to a 3D direction
	/// @param pos The 3D local frame
	/// @param d The 2D direction
	/// @return The 3D direction
	[[nodiscard]] AMCAX_API static Direction3 To3d(const Frame3& pos, const Direction2& d) noexcept;

	/// @brief Convert a 2D axis to a 3D axis
	/// @param pos The 3D local frame
	/// @param a The 2D axis
	/// @return The 3D axis
	[[nodiscard]] AMCAX_API static Axis3 To3d(const Frame3& pos, const Axis2& a) noexcept;

	/// @brief Convert a 2D frame to a 3D frame
	/// @param pos The 3D local frame
	/// @param f The 2D frame
	/// @return The 3D frame
	[[nodiscard]] AMCAX_API static Frame3 To3d(const Frame3& pos, const Frame2& f) noexcept;

	/// @brief Convert a 2D line to a 3D line
	/// @param pos The 3D local frame
	/// @param l The 2D line
	/// @return The 3D line
	[[nodiscard]] AMCAX_API static Line3 To3d(const Frame3& pos, const Line2& l) noexcept;

	/// @brief Convert a 2D circle to a 3D circle
	/// @param pos The 3D local frame
	/// @param c The 2D circle
	/// @return The 3D circle
	[[nodiscard]] AMCAX_API static Circle3 To3d(const Frame3& pos, const Circle2& c);

	/// @brief Convert a 2D ellipse to a 3D ellipse
	/// @param pos The 3D local frame
	/// @param e The 2D ellipse
	/// @return The 3D ellipse
	[[nodiscard]] AMCAX_API static Ellipse3 To3d(const Frame3& pos, const Ellipse2& e);

	/// @brief Convert a 2D parabola to a 3D parabola
	/// @param pos The 3D local frame
	/// @param p The 2D parabola
	/// @return The 3D parabola
	[[nodiscard]] AMCAX_API static Parabola3 To3d(const Frame3& pos, const Parabola2& p);

	/// @brief Convert a 2D hyperbola to a 3D hyperbola
	/// @param pos The 3D local frame
	/// @param h The 2D hyperbola
	/// @return The 3D hyperbola
	[[nodiscard]] AMCAX_API static Hyperbola3 To3d(const Frame3& pos, const Hyperbola2& h);
};
} // namespace AMCAX
