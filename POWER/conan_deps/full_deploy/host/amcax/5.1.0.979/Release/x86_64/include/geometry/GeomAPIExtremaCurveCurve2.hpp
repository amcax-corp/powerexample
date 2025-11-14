/// @file      GeomAPIExtremaCurveCurve2.hpp
/// @brief     Class of computing extremal points for two 2D curves
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <memory>

#include <common/PointT.hpp>

namespace AMCAX
{
#ifndef DOXYGEN_SKIP
template<int DIM>
class ExtremaCurveCurve;
#endif
class Geom2Curve;

/// @brief Class of computing extremal points for two 2D curves
class GeomAPIExtremaCurveCurve2
{
public:
	/// @brief Construct from two curves with their parameter bounds
	/// @param c1 The first curve
	/// @param c2 The second curve
	/// @param u1min The first parameter of the first curve
	/// @param u1max The last parameter of the first curve
	/// @param u2min The first parameter of the second curve
	/// @param u2max The last parameter of the second curve
	AMCAX_API GeomAPIExtremaCurveCurve2(const std::shared_ptr<Geom2Curve>& c1, const std::shared_ptr<Geom2Curve>& c2, double u1min, double u1max, double u2min, double u2max);

	/// @brief Get the number of extrema
	/// @return The number of extrema
	[[nodiscard]] AMCAX_API int NExtrema() const;

	/// @brief Get the number of extrema
	/// @return The number of extrema
	[[nodiscard]] AMCAX_API operator int() const;

	/// @brief Get the extremal points at a given index
	/// @param[in] index The index
	/// @param[out] p1 The extremal point on the first curve
	/// @param[out] p2 The extremal point on the second curve
	AMCAX_API void Points(int index, Point2& p1, Point2& p2) const;

	/// @brief Get the parameters of the extrema at a given index
	/// @param[in] index The index
	/// @param[out] u1 The parameter of the extremal point on the first curve
	/// @param[out] u2 The parameter of the extremal point on the second curve
	AMCAX_API void Parameters(int index, double& u1, double& u2) const;

	/// @brief Get the extremal distance at a given index
	/// @param index The index
	/// @return The extremal distance
	[[nodiscard]] AMCAX_API double Distance(int index) const;

	/// @brief Are the curves parallel
	/// @return True if two curves are parallel
	[[nodiscard]] AMCAX_API bool IsParallel() const;

	/// @brief Get the nearest points
	/// @param[out] p1 The nearest point on the first curve
	/// @param[out] p2 The nearest point on the second curve
	AMCAX_API void NearestPoints(Point2& p1, Point2& p2) const;

	/// @brief Get the parameters of the nearest points
	/// @param[out] u1 The parameter of the nearest point on the first curve
	/// @param[out] u2 The parameter of the nearest point on the second curve
	AMCAX_API void LowerDistanceParameters(double& u1, double& u2) const;

	/// @brief Get the distance of the nearest points
	/// @return The nearest distance
	[[nodiscard]] AMCAX_API double LowerDistance() const;

	/// @brief Get the distance of the nearest points
	/// @return The nearest distance
	[[nodiscard]] AMCAX_API operator double() const;

#ifndef DOXYGEN_SKIP

	/// @internal
	[[nodiscard]] const ExtremaCurveCurve<2>& Extrema() const noexcept;

#endif

private:
	bool done = false;
	int index = -1;
	std::shared_ptr<ExtremaCurveCurve<2>> ecc;
};
} // namespace AMCAX
