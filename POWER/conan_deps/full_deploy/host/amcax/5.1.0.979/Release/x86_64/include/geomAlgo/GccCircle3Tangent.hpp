/// @file      GccCircle3Tangent.hpp
/// @brief     Class of constructing a 2D circle tangent to three curves or points
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <vector>

#include <geomAlgo/GccMacros.hpp>
#include <math/CircleT.hpp>

namespace AMCAX
{
#ifndef DOXYGEN_SKIP
class GccAnaCircle3Tangent;
class GccQualifiedCurve;
#endif

/// @brief Class of constructing a 2D circle tangent to three curves or points
class GccCircle3Tangent
{
public:
	/// @brief Construct a 2D circle tangent to three curves
	/// @param qualified1 The first curve
	/// @param qualified2 The second curve
	/// @param qualified3 The third curve
	/// @param tolerance The tolerance
	/// @param parameter1 The initial guess of the parameter on the first curve
	/// @param parameter2 The initial guess of the parameter on the second curve
	/// @param parameter3 The initial guess of the parameter on the third curve
	AMCAX_API GccCircle3Tangent(const GccQualifiedCurve& qualified1, const GccQualifiedCurve& qualified2, const GccQualifiedCurve& qualified3, double tolerance, double parameter1, double parameter2, double parameter3);

	/// @brief Construct a 2D circle tangent to two curves and passing through a point
	/// @param qualified1 The first curve
	/// @param qualified2 The second curve
	/// @param point The point that the 2D circle passes through
	/// @param tolerance The tolerance
	/// @param parameter1 The initial guess of the parameter on the first curve
	/// @param parameter2 The initial guess of the parameter on the second curve
	AMCAX_API GccCircle3Tangent(const GccQualifiedCurve& qualified1, const GccQualifiedCurve& qualified2, const Point2& point, double tolerance, double parameter1, double parameter2);

	/// @brief Construct a 2D circle tangent to a curve and passing throught two points
	/// @param qualified1 The tangent curve
	/// @param point1 The first point
	/// @param point2 The second point
	/// @param tolerance The tolerance
	/// @param parameter1 The initial guess of the parameter on the curve
	AMCAX_API GccCircle3Tangent(const GccQualifiedCurve& qualified1, const Point2& point1, const Point2& point2, double tolerance, double parameter1);

	/// @brief Construct a 2D circle passing through three points
	/// @param point1 The first point
	/// @param point2 The second point
	/// @param point3 The third point
	/// @param tolerance The tolerance
	AMCAX_API GccCircle3Tangent(const Point2& point1, const Point2& point2, const Point2& point3, double tolerance);

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

	/// @brief Get the qualifiers of the tangency at a given index
	/// @param[in] index The index
	/// @param[out] qualif1 The qualifier of the first tangent curve
	/// @param[out] qualif2 The qualifier of the second tangent curve
	/// @param[out] qualif3 The qualifier of the third tangent curve
	AMCAX_API void Qualifier(int index, GccPosition& qualif1, GccPosition& qualif2, GccPosition& qualif3) const;

	/// @brief Get the information of the tangential relationship between the resulting 2D circle at a given index and the first curve
	/// @param[in] index The index
	/// @param[out] parSol The parameter of the tangent point on the resulting 2D circle
	/// @param[out] parArg The parameter of the tangent point on the tangent curve
	/// @param[out] pointSol The tangent point
	AMCAX_API void Tangency1(int index, double& parSol, double& parArg, Point2& pointSol) const;

	/// @brief Get the information of the tangential relationship between the resulting 2D circle at a given index and the second curve
	/// @param[in] index The index
	/// @param[out] parSol The parameter of the tangent point on the resulting 2D circle
	/// @param[out] parArg The parameter of the tangent point on the tangent curve
	/// @param[out] pointSol The tangent point
	AMCAX_API void Tangency2(int index, double& parSol, double& parArg, Point2& pointSol) const;

	/// @brief Get the information of the tangential relationship between the resulting 2D circle at a given index and the third curve
	/// @param[in] index The index
	/// @param[out] parSol The parameter of the tangent point on the resulting 2D circle
	/// @param[out] parArg The parameter of the tangent point on the tangent curve
	/// @param[out] pointSol The tangent point
	AMCAX_API void Tangency3(int index, double& parSol, double& parArg, Point2& pointSol) const;

	/// @brief Is the resulting 2D circle at a given index is the same as the first curve
	/// @param index The index
	/// @return True if the resulting 2D circle and the first curve are the same
	[[nodiscard]] AMCAX_API bool IsSame1(int index) const;

	/// @brief Is the resulting 2D circle at a given index is the same as the second curve
	/// @param index The index
	/// @return True if the resulting 2D circle and the first curve are the same
	[[nodiscard]] AMCAX_API bool IsSame2(int index) const;

	/// @brief Is the resulting 2D circle at a given index is the same as the third curve
	/// @param index The index
	/// @return True if the resulting 2D circle and the first curve are the same
	[[nodiscard]] AMCAX_API bool IsSame3(int index) const;

private:
	void Results(const GccAnaCircle3Tangent& gccCircle, int rank1, int rank2, int rank3);

	std::vector<Circle2> cirsol;
	int nSol = 0;
	bool isDone = false;
	std::vector<GccPosition> qualifier1;
	std::vector<GccPosition> qualifier2;
	std::vector<GccPosition> qualifier3;
	std::vector<int> same1;
	std::vector<int> same2;
	std::vector<int> same3;
	std::vector<Point2> pointTangent1;
	std::vector<Point2> pointTangent2;
	std::vector<Point2> pointTangent3;
	std::vector<double> param1;
	std::vector<double> param2;
	std::vector<double> param3;
	std::vector<double> paramArg1;
	std::vector<double> paramArg2;
	std::vector<double> paramArg3;
};
} // namespace AMCAX
