/// @file      GccCircle2TangentOn.hpp
/// @brief     Class of constructing a 2D circle tangent to two curves or points and having a center on a curve
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <vector>

#include <geomAlgo/GccMacros.hpp>
#include <math/CircleT.hpp>

namespace AMCAX
{
#ifndef DOXYGEN_SKIP
class GccQualifiedCurve;
class AdaptorGeom2Curve;
class GccAnaCircle2TangentOn;
class GccGeoCircle2TangentOn;
#endif

/// @brief Class of constructing a 2D circle tangent to two curves or points and having a center on a curve
class GccCircle2TangentOn
{
public:
	/// @brief Construct a 2D circle tangent to two curves and having a center on a curve
	/// @param qualified1 The first curve
	/// @param qualified2 The second curve
	/// @param curve The curve where the center lies
	/// @param tolerance The tolerance
	/// @param parameter1 The initial guess of the parameter on the first curve
	/// @param parameter2 The initial guess of the parameter on the second curve
	/// @param parameter3 The initial guess of the parameter on the curve where the center lies
	AMCAX_API GccCircle2TangentOn(const GccQualifiedCurve& qualified1, const GccQualifiedCurve& qualified2, const AdaptorGeom2Curve& curve, double tolerance, double parameter1, double parameter2, double parameter3);

	/// @brief Construct a 2D circle tangent to a curve, passing through a point and having a center on a curve
	/// @param qualified1 The tangent curve
	/// @param point The point that the 2D circle passes through
	/// @param curve The curve where the center lies
	/// @param tolerance The tolerance
	/// @param parameter1 The initial guess of the parameter on the tangent curve
	/// @param parameter2 The initial guess of the parameter on the curve where the center lies
	AMCAX_API GccCircle2TangentOn(const GccQualifiedCurve& qualified1, const Point2& point, const AdaptorGeom2Curve& curve, double tolerance, double parameter1, double parameter2);

	/// @brief Construct a 2D circle passing through two points and having a center on a curve
	/// @param point1 The first point
	/// @param point2 The second point
	/// @param curve The curve where the center lies
	/// @param tolerance The tolerance
	AMCAX_API GccCircle2TangentOn(const Point2& point1, const Point2& point2, const AdaptorGeom2Curve& curve, double tolerance);

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
	AMCAX_API void Qualifier(int index, GccPosition& qualif1, GccPosition& qualif2) const;

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

	/// @brief Get the information of the center point at a given index
	/// @param[in] index The index
	/// @param[out] parArg The parameter of the center point on the curve
	/// @param[out] pointSol The center point
	AMCAX_API void CenterOn3(int index, double& parArg, Point2& pointSol) const;

	/// @brief Is the resulting 2D circle at a given index is the same as the first curve
	/// @param index The index
	/// @return True if the resulting 2D circle and the first curve are the same
	[[nodiscard]] AMCAX_API bool IsSame1(int index) const;

	/// @brief Is the resulting 2D circle at a given index is the same as the second curve
	/// @param index The index
	/// @return True if the resulting 2D circle and the second curve are the same
	[[nodiscard]] AMCAX_API bool IsSame2(int index) const;

private:
	void Results(const GccAnaCircle2TangentOn& gccCircle);
	void Results(const GccGeoCircle2TangentOn& gccCircle);

	bool isDone = false;
	std::vector<Circle2> cirsol;
	int nSol = 0;
	std::vector<GccPosition> qualifier1;
	std::vector<GccPosition> qualifier2;
	std::vector<int> same1;
	std::vector<int> same2;
	std::vector<Point2> pointTangent1;
	std::vector<Point2> pointTangent2;
	std::vector<Point2> pointCenter;
	std::vector<double> param1;
	std::vector<double> param2;
	std::vector<double> paramArg1;
	std::vector<double> paramArg2;
	std::vector<double> paramCenter3;
	bool invert = false;
};
} // namespace AMCAX
