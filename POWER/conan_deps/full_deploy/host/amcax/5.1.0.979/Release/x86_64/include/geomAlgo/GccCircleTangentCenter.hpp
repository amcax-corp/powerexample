/// @file      GccCircleTangentCenter.hpp
/// @brief     Class of constructing a 2D circle tangent to a curve or point at a given center
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <vector>

#include <geomAlgo/GccMacros.hpp>
#include <math/CircleT.hpp>

namespace AMCAX
{
class GccQualifiedCurve;

/// @brief Class of constructing a 2D circle tangent to a curve or point at a given center
class GccCircleTangentCenter
{
public:
	/// @brief Construct a 2D circle tangent to a curve at a given center
	/// @param qualified1 The tangent curve
	/// @param center The center point
	/// @param tolerance The tolerance
	AMCAX_API GccCircleTangentCenter(const GccQualifiedCurve& qualified1, const Point2& center, double tolerance);

	/// @brief Construct a 2D circle passing throught a point at a given center
	/// @param point The point that the 2D circle passes through
	/// @param center The center point
	AMCAX_API GccCircleTangentCenter(const Point2& point, const Point2& center);

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
	/// @return The qualifier of the tangent 2D curve
	[[nodiscard]] AMCAX_API GccPosition Qualifier(int index) const;

	/// @brief Get the information of the tangential relationship between the resulting 2D circle at a given index and the curve
	/// @param[in] index The index
	/// @param[out] parSol The parameter of the tangent point on the resulting 2D circle
	/// @param[out] parArg The parameter of the tangent point on the tangent curve
	/// @param[out] pointSol The tangent point
	AMCAX_API void Tangency1(int index, double& parSol, double& parArg, Point2& pointSol) const;

	/// @brief Is the resulting 2D circle at a given index is the same as the curve
	/// @param index The index
	/// @return True if the resulting 2D circle and the curve are the same
	[[nodiscard]] AMCAX_API bool IsSame1(int index) const;

private:
	bool isDone;
	int nSol;
	std::vector<Circle2> cirsol;
	std::vector<GccPosition> qualifier1;
	std::vector<int> same1;
	std::vector<Point2> pointTangent1;
	std::vector<double> param1;
	std::vector<double> paramArg1;
};
} // namespace AMCAX
