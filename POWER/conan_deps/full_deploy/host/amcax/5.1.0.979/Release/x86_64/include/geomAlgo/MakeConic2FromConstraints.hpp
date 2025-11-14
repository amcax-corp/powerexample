/// @file      MakeConic2FromConstraints.hpp
/// @brief     The class of creating 2d conic curve from geometric constraints
/// @details   This class computes the 2d conic curve from 5 geometric constraints including points and tangents
/// @copyright Copyright (c) 2024 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <memory>
#include <vector>

#include <common/FrameT.hpp>
#include <common/VectorT.hpp>
#include <math/GeometryMacros.hpp>

namespace AMCAX
{
class Geom2Curve;

/// @brief Struct of constraint settings for making conic curve
struct Conic2Constraint
{
	/// @brief Construct from a point constraint
	/// @param point The point constraint
	explicit Conic2Constraint(const Point2& point) noexcept
		: point(point),
		  withTangent(false)
	{
	}

	/// @brief Construct from point and tangent constraints
	/// @param point The point constraint
	/// @param tangent The tangent vector constraint
	Conic2Constraint(const Point2& point, const Vector2& tangent) noexcept
		: point(point),
		  withTangent(true),
		  tangent(tangent)
	{
	}

	/// @brief Construct from point and tangent constraints
	/// @param point The point constraint
	/// @param tangent The tangent direction constraint
	Conic2Constraint(const Point2& point, const Direction2& tangent) noexcept
		: point(point),
		  withTangent(true),
		  tangent(tangent)
	{
	}

	/// @brief The point
	Point2 point;

	/// @brief Does the constraint contain tangent
	bool withTangent;

	/// @brief Vector of tangent constraint
	Vector2 tangent;
};

/// @brief Build 2d conic curve from geometric constraints
class MakeConic2FromConstraints
{
public:
	/// @brief Build by ending points and tangents and a parameter
	/// @param startConstraint The start point and tangent
	/// @param endConstraint The end point and tangent
	/// @param parameter The parameter to determine type and shape of the conic. For not parallel tangent vectors, valid range is (0.0, 1.0): ellipse if (0.0, 0.5), parabola if {0.5}, hyperbola if (0.5, 1.0); For parallel tangent vectors, valid range is (0.0, inf), circle if {0.5} and ellipse if else.
	AMCAX_API MakeConic2FromConstraints(const Conic2Constraint& startConstraint, const Conic2Constraint& endConstraint, double parameter);

	/// @brief Build by point and tangent constraints. The number of constraints must be 5 in total and the start and the end point constraints are required
	/// @param constraints The constraints of the conic. It is supported that the constraints contain 5 points, 4 points and 1 tangent, 3 points and 2 tangent
	AMCAX_API explicit MakeConic2FromConstraints(const std::vector<Conic2Constraint>& constraints);

	/// @brief Whether the conic is successfully built
	/// @return Whether the conic is successfully built
	[[nodiscard]] AMCAX_API bool IsDone() const;

	/// @brief a0*x^2 + a1*xy + a2*y^2 + a3*x + a4*y + a5 = 0
	/// @return Coefficient array with size of 6
	[[nodiscard]] AMCAX_API const std::vector<double>& Coefficients() const;

	/// @brief Conic curve type
	/// @return Circle, ellipse, parabola or hyperbola
	[[nodiscard]] AMCAX_API CurveType Type() const;

	/// @brief Get the curve between the start point and the end point
	/// @return A trimmed 2d conic
	[[nodiscard]] AMCAX_API std::shared_ptr<Geom2Curve> Curve2d() const;

private:
	void BuildConic(const Point2& pointA, const Vector2& tangentA, const Point2& pointB, const Point2& pointC, const Vector2& tangentC);

	void BuildConic(const Point2& pointA, const Vector2& tangentA, const Point2& pointB, const Point2& pointC, const Point2& pointD);

	void BuildConic(const Point2& pointA, const Point2& pointB, const Point2& pointC, const Point2& pointD, const Point2& pointE);

	void EquationToGeom();

private:
	bool isDone = false;
	CurveType type = CurveType::Undefined;
	std::vector<double> coefficients;
	std::shared_ptr<Geom2Curve> curve2d;
	Point2 startPoint2d;
	Point2 endPoint2d;
	std::vector<Point2> judgePoint2d;
	std::vector<Point2> points2d;
};
} // namespace AMCAX
