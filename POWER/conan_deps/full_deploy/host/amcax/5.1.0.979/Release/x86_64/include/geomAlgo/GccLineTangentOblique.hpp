/// @file      GccLineTangentOblique.hpp
/// @brief     Class of constructing a 2D line tangent to a curve or point and having a given oblique angle with a line
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
class GccIterLineTangentOblique;
class GccQualifiedCurve;
#endif

/// @brief Class of constructing a 2D line tangent to a curve or point and having a given oblique angle with a line
class GccLineTangentOblique
{
public:
	/// @brief Construct a 2D line tangent to a curve and having a given oblique angle with a line
	/// @param qualified1 The tangent curve
	/// @param line The reference line
	/// @param tolerance The tolerance
	/// @param angle The oblique angle
	AMCAX_API GccLineTangentOblique(const GccQualifiedCurve& qualified1, const Line2& line, double tolerance, double angle);

	/// @brief Construct a 2D line passing through a point and having a given oblique angle with a line
	/// @param point The point which the 2D line passes through
	/// @param line The reference line
	/// @param angle The oblique angle
	AMCAX_API GccLineTangentOblique(const Point2& point, const Line2& line, double angle);

	/// @brief Construct a 2D line tangent to a curve and having a given oblique angle with a line with a initial parameter
	/// @param qualified1 The tangent curve
	/// @param line The reference line
	/// @param tolerance The tolerance
	/// @param parameter1 The initial guess of the parameter on the tangent curve
	/// @param angle The oblique angle
	AMCAX_API GccLineTangentOblique(const GccQualifiedCurve& qualified1, const Line2& line, double tolerance, double parameter1, double angle);

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
	/// @param index The index
	/// @return The qualifier of the tangent curve
	[[nodiscard]] AMCAX_API GccPosition Qualifier(int index) const;

	/// @brief Get the information of the tangential relationship between the resulting 2D line at a given index and the curve
	/// @param[in] index The index
	/// @param[out] parSol The parameter of the tangent point on the resulting 2D line
	/// @param[out] parArg The parameter of the tangent point on the tangent curve
	/// @param[out] pointSol The tangent point
	AMCAX_API void Tangency1(int index, double& parSol, double& parArg, Point2& pointSol) const;

	/// @brief Get the information of the intersection at a given index
	/// @param[in] index The index
	/// @param[out] parSol The parameter of the intersection point on the resulting 2D line
	/// @param[out] parArg The parameter of the intersection point on the reference line
	/// @param[out] pointSol The intersection point
	AMCAX_API void Intersection2(int index, double& parSol, double& parArg, Point2& pointSol) const;

	/// @brief Is the resulting 2D line parallel to the reference line
	/// @return True if the line and the resulting 2D line are parallel
	[[nodiscard]] AMCAX_API bool IsParallel2() const noexcept;

private:
	bool Add(int index, const GccIterLineTangentOblique& line, double tolerance, const AdaptorGeom2Curve& curve);

	bool isDone = false;
	bool Paral2 = false;
	int nSol = 0;
	std::vector<Line2> linsol;
	std::vector<GccPosition> qualifier1;
	std::vector<Point2> pointTangent1;
	std::vector<Point2> pointInter2;
	std::vector<double> param1;
	std::vector<double> param2;
	std::vector<double> paramArg1;
	std::vector<double> paramArg2;
};
} // namespace AMCAX
