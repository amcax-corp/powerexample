/// @file      GeomAPIProjectPointOnCurve2.hpp
/// @brief     Class of projecting a 2D point on a curve
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <memory>

#include <common/PointT.hpp>

namespace AMCAX
{
class AdaptorGeom2Curve;
#ifndef DOXYGEN_SKIP
template<int>
class ExtremaPointCurve;
#endif
class Geom2Curve;

/// @brief Class of projecting a 2D point on a curve
class GeomAPIProjectPointOnCurve2
{
public:
	/// @brief Default constructor
	AMCAX_API GeomAPIProjectPointOnCurve2();

	/// @brief Construct from a point and a curve
	/// @param p The point to be projected
	/// @param curve The curve
	AMCAX_API GeomAPIProjectPointOnCurve2(const Point2& p, const std::shared_ptr<Geom2Curve>& curve);

	/// @brief Construct from a point and a curve with parameter bounds
	/// @param p The point to be projected
	/// @param curve The curve
	/// @param umin The first parameter of the curve
	/// @param umax The last parameter of the curve
	AMCAX_API GeomAPIProjectPointOnCurve2(const Point2& p, const std::shared_ptr<Geom2Curve>& curve, double umin, double umax);

	/// @brief Initialize and construct from a point and a curve
	/// @param p The point to be projected
	/// @param curve The curve
	AMCAX_API void Init(const Point2& p, const std::shared_ptr<Geom2Curve>& curve);

	/// @brief Initialize and construct from a point and a curve with parameter bounds
	/// @param p The point to be projected
	/// @param curve The curve
	/// @param umin The first parameter of the curve
	/// @param umax The last parameter of the curve
	AMCAX_API void Init(const Point2& p, const std::shared_ptr<Geom2Curve>& curve, double umin, double umax);

	/// @brief Initialize from a curve with parameter bounds
	/// @param curve The curve
	/// @param umin The first parameter of the curve
	/// @param umax The last parameter of the curve
	AMCAX_API void Init(const std::shared_ptr<Geom2Curve>& curve, double umin, double umax);

	/// @brief Perform the projection of a point
	/// @param p The point
	AMCAX_API void Perform(const Point2& p);

	/// @brief Get the number of projected points
	/// @return The number of projected points
	[[nodiscard]] AMCAX_API int NPoints() const;

	/// @brief Get the number of projected points
	/// @return The number of projected points
	[[nodiscard]] AMCAX_API operator int() const;

	/// @brief Get the projected point at a given index
	/// @param index The index
	/// @return The projected point
	[[nodiscard]] AMCAX_API Point2 Point(int index) const;

	/// @brief Get the parameter of the projected point at a given index
	/// @param index The index
	/// @return The parameter of the projected point
	[[nodiscard]] AMCAX_API double Parameter(int index) const;

	/// @brief Get the distance from the original point to the projected point at a given index
	/// @param index The index
	/// @return The projected distance
	[[nodiscard]] AMCAX_API double Distance(int index) const;

	/// @brief Get the nearest point
	/// @return The nearest point
	[[nodiscard]] AMCAX_API Point2 NearestPoint() const;

	/// @brief Get the nearest point
	/// @return The nearest point
	[[nodiscard]] AMCAX_API operator Point2() const;

	/// @brief Get the parameter of the nearest point on the curve
	/// @return The parameter of the nearest point
	[[nodiscard]] AMCAX_API double LowerDistanceParameter() const;

	/// @brief Get the distance from the original point to the nearest point
	/// @return The nearest distance
	[[nodiscard]] AMCAX_API double LowerDistance() const;

	/// @brief Get the distance from the original point to the nearest point
	/// @return The nearest distance
	[[nodiscard]] AMCAX_API operator double() const;

#ifndef DOXYGEN_SKIP

	/// @internal
	[[nodiscard]] const ExtremaPointCurve<2>& Extrema() const noexcept;

#endif

private:
	bool done = false;
	int index = -1;
	std::shared_ptr<ExtremaPointCurve<2>> epc;
	std::shared_ptr<AdaptorGeom2Curve> c;
};
} // namespace AMCAX
