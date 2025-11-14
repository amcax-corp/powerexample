/// @file      GccCircleTangentOnRadius.hpp
/// @brief     Class of constructing a 2D circle tangent to a curve or point and having a center on a curve with a given radius
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <vector>

#include <geomAlgo/GccMacros.hpp>
#include <math/CircleT.hpp>

namespace AMCAX
{
#ifndef DOXYGEN_SKIP
class AdaptorGeom2Curve;
class GccAnaCircleTangentOnRadius;
class GccGeoCircleTangentOnRadius;
class GccQualifiedCurve;
#endif

/// @brief Class of constructing a 2D circle tangent to a curve or point and having a center on a curve with a given radius
class GccCircleTangentOnRadius
{
public:
	/// @brief Construct a 2D circle tangent to a curve and having a center on a curve with a given radius
	/// @param qualified1 The tangent curve
	/// @param curve The curve where the center lies
	/// @param radius The given radius
	/// @param tolerance The tolerance
	AMCAX_API GccCircleTangentOnRadius(const GccQualifiedCurve& qualified1, const AdaptorGeom2Curve& curve, double radius, double tolerance);

	/// @brief Construct a 2D circle passing through a point and having a center on a curve with a given radius
	/// @param point1 The point that the 2D circle passes through
	/// @param curve The curve where the center lies
	/// @param radius The given radius
	/// @param tolerance The tolerance
	AMCAX_API GccCircleTangentOnRadius(const Point2& point1, const AdaptorGeom2Curve& curve, double radius, double tolerance);

	/// @brief Is the algorithm done
	/// @return True if the algorithm has no failure
	[[nodiscard]] AMCAX_API bool IsDone() const noexcept;

	/// @brief Get the number of the resulting 2D circle
	/// @return The number of the resulting 2D circle
	[[nodiscard]] AMCAX_API int NSolutions() const noexcept;

	/// @brief Get the resulting 2D circle at a given index
	/// @param index The index
	/// @return The resulting 2D circle
	[[nodiscard]] AMCAX_API Circle2 Solution(int index) const;

	/// @brief Get the qualifier of the tangency at a given index
	/// @param index The index
	/// @return The qualifier of the tangent curve
	[[nodiscard]] AMCAX_API GccPosition Qualifier(int index) const;

	/// @brief Get the information of the tangential relationship between the resulting 2D circle at a given index and the curve
	/// @param[in] index The index
	/// @param[out] parSol The parameter of the tangent point on the resulting 2D circle
	/// @param[out] parArg The parameter of the tangent point on the tangent curve
	/// @param[out] pointSol The tangent point
	AMCAX_API void Tangency1(int index, double& parSol, double& parArg, Point2& pointSol) const;

	/// @brief Get the information of the center point at a given index
	/// @param[in] index The index
	/// @param[out] parArg The parameter of the center point on the curve
	/// @param[out] pointSol The center point
	AMCAX_API void CenterOn3(int index, double& parArg, Point2& pointSol) const;

	/// @brief Is the resulting 2D circle at a given index is the same as the tangent curve
	/// @param index The index
	/// @return True if the resulting 2D circle and the tangent curve are the same
	[[nodiscard]] AMCAX_API bool IsSame1(int index) const;

private:
	void Results(const GccAnaCircleTangentOnRadius& gccCircle);
	void Results(const GccGeoCircleTangentOnRadius& gccCircle);

	bool isDone = false;
	int nSol = 0;
	std::vector<Circle2> cirsol;
	std::vector<GccPosition> qualifier1;
	std::vector<int> same1;
	std::vector<Point2> pointTangent1;
	std::vector<double> param1;
	std::vector<double> paramArg1;
	std::vector<Point2> pointCenter3;
	std::vector<double> paramCenter3;
};
} // namespace AMCAX
