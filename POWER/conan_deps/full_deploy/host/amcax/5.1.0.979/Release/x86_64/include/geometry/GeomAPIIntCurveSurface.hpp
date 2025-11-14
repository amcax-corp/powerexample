/// @file      GeomAPIIntCurveSurface.hpp
/// @brief     Class of computing intersection points for a curve and a surface
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <memory>

#include <common/PointT.hpp>

namespace AMCAX
{
#ifndef DOXYGEN_SKIP
class Geom3Curve;
class Geom3Surface;
class IntCurveSurfaceIntersection;
#endif

/// @brief Class of computing intersection points for a curve and a surface
class GeomAPIIntCurveSurface
{
public:
	/// @brief Default constructor
	AMCAX_API GeomAPIIntCurveSurface();

	/// @brief Construct from a curve and a surface
	/// @param c The curve
	/// @param s The surface
	AMCAX_API GeomAPIIntCurveSurface(const std::shared_ptr<Geom3Curve>& c, const std::shared_ptr<Geom3Surface>& s);

	/// @brief Perform the algorithm from a curve and a surface
	/// @param c The curve
	/// @param s The surface
	AMCAX_API void Perform(const std::shared_ptr<Geom3Curve>& c, const std::shared_ptr<Geom3Surface>& s);

	/// @brief Is the algorithm done
	/// @return True if the algorithm is successful
	[[nodiscard]] AMCAX_API bool IsDone() const noexcept;

	/// @brief Get the number of intersection points
	/// @return The number of intersection points
	[[nodiscard]] AMCAX_API int NPoints() const;

	/// @brief Get the intersection point at a given index
	/// @param index The index
	/// @return The intersection point
	[[nodiscard]] AMCAX_API const Point3& Point(int index) const;

	/// @brief Get the parameters of the intersection point at a given index
	/// @param[in] index The index
	/// @param[out] u The u parameter of the intersection point on the surface
	/// @param[out] v The v parameter of the intersection point on the surface
	/// @param[out] w The parameter of the intersection point on the curve
	AMCAX_API void Parameters(int index, double& u, double& v, double& w) const;

	/// @brief Get the number of intersection segments
	/// @return The number of intersection segments
	[[nodiscard]] AMCAX_API int NSegments() const;

	/// @brief Get the intersection segment at a given index
	/// @param index The index
	/// @return The intersection segment
	[[nodiscard]] AMCAX_API std::shared_ptr<Geom3Curve> Segment(int index) const;

	/// @brief Get the parameter bounds of the intersection segment on the surface at a given index
	/// @param[in] index The index
	/// @param[out] u1 The u parameter of the start point of the intersection segment on the surface
	/// @param[out] v1 The v parameter of the start point of the intersection segment on the surface
	/// @param[out] u2 The u parameter of the end point of the intersection segment on the surface
	/// @param[out] v2 The v parameter of the end point of the intersection segment on the surface
	AMCAX_API void Parameters(int index, double& u1, double& v1, double& u2, double& v2) const;

private:
	std::shared_ptr<Geom3Curve> curve;
	std::shared_ptr<IntCurveSurfaceIntersection> intCS;
};
} // namespace AMCAX
