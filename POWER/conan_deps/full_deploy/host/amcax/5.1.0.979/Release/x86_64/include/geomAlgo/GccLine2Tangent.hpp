/// @file      GccLine2Tangent.hpp
/// @brief     Class of constructing a 2D line tangent to two curves or points
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <vector>

#include <geomAlgo/GccMacros.hpp>
#include <math/LineT.hpp>

namespace AMCAX
{
#ifndef DOXYGEN_SKIP
class AdaptorGeom2Curve;
class GccIterLine2Tangent;
class GccQualifiedCurve;
#endif

/// @brief Class of constructing a 2D line tangent to two curves or points
class GccLine2Tangent
{
public:
	/// @brief Construct a 2D line tangent to two curves
	/// @param qualified1 The first curve
	/// @param qualified2 The second curve
	/// @param tolerance The tolerance
	AMCAX_API GccLine2Tangent(const GccQualifiedCurve& qualified1, const GccQualifiedCurve& qualified2, double tolerance);

	/// @brief Construct a 2D line tangent to a curve and passing through a point
	/// @param qualified1 The tangent curve
	/// @param point The point that the 2D line passes through
	/// @param tolerance The tolerance
	AMCAX_API GccLine2Tangent(const GccQualifiedCurve& qualified1, const Point2& point, double tolerance);

	/// @brief Construct a 2D line passing through two points
	/// @param point1 The first point
	/// @param point2 The second point
	/// @param tolerance The tolerance
	AMCAX_API GccLine2Tangent(const Point2& point1, const Point2& point2, double tolerance);

	/// @brief Construct a 2D line tangent to two curves with initial parameters
	/// @param qualified1 The first curve
	/// @param qualified2 The second curve
	/// @param tolerance The tolerance
	/// @param parameter1 The initial guess of the parameter on the first curve
	/// @param parameter2 The initial guess of the parameter on the second curve
	AMCAX_API GccLine2Tangent(const GccQualifiedCurve& qualified1, const GccQualifiedCurve& qualified2, double tolerance, double parameter1, double parameter2);

	/// @brief Construct a 2D line tangent to a curve and passing through a point with initial parameters
	/// @param qualified1 The tangent curve
	/// @param point The point that the 2D line passes through
	/// @param tolerance The tolerance
	/// @param parameter1 The initial guess of the parameter on the tangent curve
	AMCAX_API GccLine2Tangent(const GccQualifiedCurve& qualified1, const Point2& point, double tolerance, double parameter1);

	/// @brief Is the algorithm done
	/// @return True if the algorithm has no failure
	[[nodiscard]] AMCAX_API bool IsDone() const noexcept;

	/// @brief Get the number of the resulting 2D line
	/// @return The number of the resulting 2D line
	[[nodiscard]] AMCAX_API int NSolutions() const noexcept;

	/// @brief Get the resulting 2D line at a given index
	/// @param index The index
	/// @return The resulting 2D line
	[[nodiscard]] AMCAX_API Line2 Solution(int index) const;

	/// @brief Get the qualifiers of the tangency at a given index
	/// @param[in] index The index
	/// @param[out] qualif1 The qualifier of the first tangent curve
	/// @param[out] qualif2 The qualifier of the second tangent curve
	AMCAX_API void Qualifier(int index, GccPosition& qualif1, GccPosition& qualif2) const;

	/// @brief Get the information of the tangential relationship between the resulting 2D line at a given index and the first curve
	/// @param[in] index The index
	/// @param[out] parSol The parameter of the tangent point on the resulting 2D line
	/// @param[out] parArg The parameter of the tangent point on the tangent curve
	/// @param[out] pointSol The tangent point
	AMCAX_API void Tangency1(int index, double& parSol, double& parArg, Point2& pointSol) const;

	/// @brief Get the information of the tangential relationship between the resulting 2D line at a given index and the second curve
	/// @param[in] index The index
	/// @param[out] parSol The parameter of the tangent point on the resulting 2D line
	/// @param[out] parArg The parameter of the tangent point on the tangent curve
	/// @param[out] pointSol The tangent point
	AMCAX_API void Tangency2(int index, double& parSol, double& parArg, Point2& pointSol) const;

private:
	bool Add(int index, const GccIterLine2Tangent& gccLine, double tolerance, const AdaptorGeom2Curve& curve1, const AdaptorGeom2Curve& curve2);

	bool isDone = false;
	int nSol = 0;
	std::vector<Line2> linsol;
	std::vector<GccPosition> qualifier1;
	std::vector<GccPosition> qualifier2;
	std::vector<Point2> pointTangent1;
	std::vector<Point2> pointTangent2;
	std::vector<double> param1;
	std::vector<double> param2;
	std::vector<double> paramArg1;
	std::vector<double> paramArg2;
};
} // namespace AMCAX
