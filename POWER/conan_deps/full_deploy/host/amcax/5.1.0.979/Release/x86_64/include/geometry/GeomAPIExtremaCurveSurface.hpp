/// @file      GeomAPIExtremaCurveSurface.hpp
/// @brief     Class of computing extremal points for a curve and a surface
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <memory>

#include <common/PointT.hpp>

namespace AMCAX
{
#ifndef DOXYGEN_SKIP
class ExtremaCurveSurface;
class Geom3Curve;
class Geom3Surface;
#endif

/// @brief Class of computing extremal points for a curve and a surface
class GeomAPIExtremaCurveSurface
{
public:
	/// @brief Default constructor
	AMCAX_API GeomAPIExtremaCurveSurface();

	/// @brief Construct from a curve and a surface
	/// @param curve The curve
	/// @param surface The surface
	AMCAX_API GeomAPIExtremaCurveSurface(const std::shared_ptr<Geom3Curve>& curve, const std::shared_ptr<Geom3Surface>& surface);

	/// @brief Construct from a curve and a surface with their parameter bounds
	/// @param curve The curve
	/// @param surface The surface
	/// @param tmin The first parameter of the curve
	/// @param tmax The last parameter of the curve
	/// @param umin The u first parameter of the surface
	/// @param umax The u last parameter of the surface
	/// @param vmin The v first parameter of the surface
	/// @param vmax The v last parameter of the surface
	AMCAX_API GeomAPIExtremaCurveSurface(const std::shared_ptr<Geom3Curve>& curve, const std::shared_ptr<Geom3Surface>& surface, double tmin, double tmax, double umin, double umax, double vmin, double vmax);

	/// @brief Initialize and construct from a curve and a surface
	/// @param curve The curve
	/// @param surface The surface
	AMCAX_API void Init(const std::shared_ptr<Geom3Curve>& curve, const std::shared_ptr<Geom3Surface>& surface);

	/// @brief Initialize and construct from a curve and a surface with their parameter bounds
	/// @param curve The curve
	/// @param surface The surface
	/// @param tmin The first parameter of the curve
	/// @param tmax The last parameter of the curve
	/// @param umin The u first parameter of the surface
	/// @param umax The u last parameter of the surface
	/// @param vmin The v first parameter of the surface
	/// @param vmax The v last parameter of the surface
	AMCAX_API void Init(const std::shared_ptr<Geom3Curve>& curve, const std::shared_ptr<Geom3Surface>& surface, double tmin, double tmax, double umin, double umax, double vmin, double vmax);

	/// @brief Get the number of extrema
	/// @return The number of extrema
	[[nodiscard]] AMCAX_API int NExtrema() const;

	/// @brief Get the number of extrema
	/// @return The number of extrema
	[[nodiscard]] AMCAX_API operator int() const;

	/// @brief Get the extremal points at a given index
	/// @param[in] index The index
	/// @param[out] p1 The extremal point on the curve
	/// @param[out] p2 The extremal point on the surface
	AMCAX_API void Points(int index, Point3& p1, Point3& p2) const;

	/// @brief Get the parameters of the extrema at a given index
	/// @param[in] index The index
	/// @param[out] t The parameter of the extremal point on the curve
	/// @param[out] u The u parameter of the extremal point on the surface
	/// @param[out] v The v parameter of the extremal point on the surface
	AMCAX_API void Parameters(int index, double& t, double& u, double& v) const;

	/// @brief Get the extremal distance at a given index
	/// @param index The index
	/// @return The extremal distance
	[[nodiscard]] AMCAX_API double Distance(int index) const;

	/// @brief Is the curve parallel to the surface
	/// @return True if the curve is parallel to the surface
	[[nodiscard]] AMCAX_API bool IsParallel() const;

	/// @brief Get the nearest points
	/// @param[out] pc The nearest point on the curve
	/// @param[out] ps The nearest point on the surface
	AMCAX_API void NearestPoints(Point3& pc, Point3& ps) const;

	/// @brief Get the parameters of the nearest points
	/// @param[out] t The parameter of the nearest point on the curve
	/// @param[out] u The u parameter of the nearest point on the surface
	/// @param[out] v The v parameter of the nearest point on the surface
	AMCAX_API void LowerDistanceParameters(double& t, double& u, double& v) const;

	/// @brief Get the distance of the nearest points
	/// @return The nearest distance
	[[nodiscard]] AMCAX_API double LowerDistance() const;

	/// @brief Get the distance of the nearest points
	/// @return The nearest distance
	[[nodiscard]] AMCAX_API operator double() const;

#ifndef DOXYGEN_SKIP

	/// @internal
	[[nodiscard]] const ExtremaCurveSurface& Extrema() const noexcept;

#endif

private:
	bool done = false;
	int index = -1;
	std::shared_ptr<ExtremaCurveSurface> ecs;
};
} // namespace AMCAX
