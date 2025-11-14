/// @file      GeomAPIExtremaSurfaceSurface.hpp
/// @brief     Class of computing extremal points for two surfaces
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <memory>

#include <common/PointT.hpp>

namespace AMCAX
{
#ifndef DOXYGEN_SKIP
class ExtremaSurfaceSurface;
class Geom3Surface;
#endif

/// @brief Class of computing extremal points for two surfaces
class GeomAPIExtremaSurfaceSurface
{
public:
	/// @brief Default constructor
	AMCAX_API GeomAPIExtremaSurfaceSurface();

	/// @brief Construct from two surfaces
	/// @param s1 The first surface
	/// @param s2 The second surface
	AMCAX_API GeomAPIExtremaSurfaceSurface(const std::shared_ptr<Geom3Surface>& s1, const std::shared_ptr<Geom3Surface>& s2);

	/// @brief Construct from two surfaces with their parameter bounds
	/// @param s1 The first surface
	/// @param s2 The second surface
	/// @param u1min The u first parameter of the first surface
	/// @param u1max The u last parameter of the first surface
	/// @param v1min The v first parameter of the first surface
	/// @param v1max The v last parameter of the first surface
	/// @param u2min The u first parameter of the second surface
	/// @param u2max The u last parameter of the second surface
	/// @param v2min The v first parameter of the second surface
	/// @param v2max The v last parameter of the second surface
	AMCAX_API GeomAPIExtremaSurfaceSurface(const std::shared_ptr<Geom3Surface>& s1, const std::shared_ptr<Geom3Surface>& s2, double u1min, double u1max, double v1min, double v1max, double u2min, double u2max, double v2min, double v2max);

	/// @brief Initialize and construct from two surfaces with their parameter bounds
	/// @param s1 The first surface
	/// @param s2 The second surface
	AMCAX_API void Init(const std::shared_ptr<Geom3Surface>& s1, const std::shared_ptr<Geom3Surface>& s2);

	/// @brief Initialize and construct from two surfaces with their parameter bounds
	/// @param s1 The first surface
	/// @param s2 The second surface
	/// @param u1min The u first parameter of the first surface
	/// @param u1max The u last parameter of the first surface
	/// @param v1min The v first parameter of the first surface
	/// @param v1max The v last parameter of the first surface
	/// @param u2min The u first parameter of the second surface
	/// @param u2max The u last parameter of the second surface
	/// @param v2min The v first parameter of the second surface
	/// @param v2max The v last parameter of the second surface
	AMCAX_API void Init(const std::shared_ptr<Geom3Surface>& s1, const std::shared_ptr<Geom3Surface>& s2, double u1min, double u1max, double v1min, double v1max, double u2min, double u2max, double v2min, double v2max);

	/// @brief Get the number of extrema
	/// @return The numebr of extrema
	[[nodiscard]] AMCAX_API int NExtrema() const;

	/// @brief Get the number of extrema
	/// @return The numebr of extrema
	[[nodiscard]] AMCAX_API operator int() const;

	/// @brief Get the extremal points at a given index
	/// @param[in] index The index
	/// @param[out] p1 The extremal point on the first surface
	/// @param[out] p2 The extremal point on the second surface
	AMCAX_API void Points(int index, Point3& p1, Point3& p2) const;

	/// @brief Get the parameters of the extrema at a given index
	/// @param[in] index The index
	/// @param[out] u1 The u parameter of the extremal point on the first surface
	/// @param[out] v1 The v parameter of the extremal point on the first surface
	/// @param[out] u2 The u parameter of the extremal point on the second surface
	/// @param[out] v2 The v parameter of the extremal point on the second surface
	AMCAX_API void Parameters(int index, double& u1, double& v1, double& u2, double& v2) const;

	/// @brief Get the extremal distance at a given index
	/// @param index The index
	/// @return The extremal distance
	[[nodiscard]] AMCAX_API double Distance(int index) const;

	/// @brief Are the surfaces parallel
	/// @return True if two surfaces are parallel
	[[nodiscard]] AMCAX_API bool IsParallel() const;

	/// @brief Get the nearest points
	/// @param[out] p1 The nearest point on the first surface
	/// @param[out] p2 The nearest point on the second surface
	AMCAX_API void NearestPoints(Point3& p1, Point3& p2) const;

	/// @brief Get the parameters of the nearest points
	/// @param[out] u1 The u parameter of the nearest point on the first surface
	/// @param[out] v1 The v parameter of the nearest point on the first surface
	/// @param[out] u2 The u parameter of the nearest point on the second surface
	/// @param[out] v2 The v parameter of the nearest point on the second surface
	AMCAX_API void LowerDistanceParameters(double& u1, double& v1, double& u2, double& v2) const;

	/// @brief Get the distance of the nearest points
	/// @return The nearest distance
	[[nodiscard]] AMCAX_API double LowerDistance() const;

	/// @brief Get the distance of the nearest points
	/// @return The nearest distance
	[[nodiscard]] AMCAX_API operator double() const;

#ifndef DOXYGEN_SKIP

	/// @internal
	[[nodiscard]] const ExtremaSurfaceSurface& Extrema() const noexcept;

#endif

private:
	bool done = false;
	int index = -1;
	std::shared_ptr<ExtremaSurfaceSurface> ess;
};
} // namespace AMCAX
