/// @file      GeomAPIProjectPointOnSurface.hpp
/// @brief     Class of projecting a point on a surface
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <memory>

#include <common/PointT.hpp>
#include <geometry/ExtremaMacros.hpp>

namespace AMCAX
{
#ifndef DOXYGEN_SKIP
class AdaptorGeom3Surface;
class ExtremaPointSurface;
class Geom3Surface;
#endif

/// @brief Class of projecting a point on a surface
class GeomAPIProjectPointOnSurface
{
public:
	/// @brief Default constructor
	AMCAX_API GeomAPIProjectPointOnSurface();

	/// @brief Construct from a point and a surface
	/// @param p The point to be projected
	/// @param surface The surface
	/// @param algo The type of extrema algorithm
	AMCAX_API GeomAPIProjectPointOnSurface(const Point3& p, const std::shared_ptr<Geom3Surface>& surface, ExtremaAlgorithm algo = ExtremaAlgorithm::Grad);

	/// @brief Construct from a point and a surface with tolerance
	/// @param p The point to be projected
	/// @param surface The surface
	/// @param tolerance The computing tolerance
	/// @param algo The type of extrema algorithm
	AMCAX_API GeomAPIProjectPointOnSurface(const Point3& p, const std::shared_ptr<Geom3Surface>& surface, double tolerance, ExtremaAlgorithm algo = ExtremaAlgorithm::Grad);

	/// @brief Construct from a point and a surface with parameter bounds
	/// @param p The point to be projected
	/// @param surface The surface
	/// @param umin The u first parameter of the surface
	/// @param umax The u last parameter of the surface
	/// @param vmin The v first parameter of the surface
	/// @param vmax The v last parameter of the surface
	/// @param algo The type of extrema algorithm
	AMCAX_API GeomAPIProjectPointOnSurface(const Point3& p, const std::shared_ptr<Geom3Surface>& surface, double umin, double umax, double vmin, double vmax, ExtremaAlgorithm algo = ExtremaAlgorithm::Grad);

	/// @brief Construct from a point and a surface with parameter bounds and tolerance
	/// @param p The point to be projected
	/// @param surface The surface
	/// @param umin The u first parameter of the surface
	/// @param umax The u last parameter of the surface
	/// @param vmin The v first parameter of the surface
	/// @param vmax The v last parameter of the surface
	/// @param tolerance The computing tolerance
	/// @param algo The type of extrema algorithm
	AMCAX_API GeomAPIProjectPointOnSurface(const Point3& p, const std::shared_ptr<Geom3Surface>& surface, double umin, double umax, double vmin, double vmax, double tolerance, ExtremaAlgorithm algo = ExtremaAlgorithm::Grad);

	/// @brief Initialize and construct from a point and a surface
	/// @param p The point to be projected
	/// @param surface The surface
	/// @param algo The type of extrema algorithm
	AMCAX_API void Init(const Point3& p, const std::shared_ptr<Geom3Surface>& surface, ExtremaAlgorithm algo = ExtremaAlgorithm::Grad);

	/// @brief Initialize and construct from a point and a surface with tolerance
	/// @param p The point to be projected
	/// @param surface The surface
	/// @param tolerance The computing tolerance
	/// @param algo The type of extrema algorithm
	AMCAX_API void Init(const Point3& p, const std::shared_ptr<Geom3Surface>& surface, double tolerance, ExtremaAlgorithm algo = ExtremaAlgorithm::Grad);

	/// @brief Initialize and construct from a point and a surface with parameter bounds
	/// @param p The point to be projected
	/// @param surface The surface
	/// @param umin The u first parameter of the surface
	/// @param umax The u last parameter of the surface
	/// @param vmin The v first parameter of the surface
	/// @param vmax The v last parameter of the surface
	/// @param algo The type of extrema algorithm
	AMCAX_API void Init(const Point3& p, const std::shared_ptr<Geom3Surface>& surface, double umin, double umax, double vmin, double vmax, ExtremaAlgorithm algo = ExtremaAlgorithm::Grad);

	/// @brief Initialize and construct from a point and a surface with parameter bounds and tolerance
	/// @param p The point to be projected
	/// @param surface The surface
	/// @param umin The u first parameter of the surface
	/// @param umax The u last parameter of the surface
	/// @param vmin The v first parameter of the surface
	/// @param vmax The v last parameter of the surface
	/// @param tolerance The computing tolerance
	/// @param algo The type of extrema algorithm
	AMCAX_API void Init(const Point3& p, const std::shared_ptr<Geom3Surface>& surface, double umin, double umax, double vmin, double vmax, double tolerance, const ExtremaAlgorithm algo = ExtremaAlgorithm::Grad);

	/// @brief Initialize from a surface with parameter bounds
	/// @param surface The surface
	/// @param umin The u first parameter of the surface
	/// @param umax The u last parameter of the surface
	/// @param vmin The v first parameter of the surface
	/// @param vmax The v last parameter of the surface
	/// @param algo The type of extrema algorithm
	AMCAX_API void Init(const std::shared_ptr<Geom3Surface>& surface, double umin, double umax, double vmin, double vmax, ExtremaAlgorithm algo = ExtremaAlgorithm::Grad);

	/// @brief Initialize from a surface with parameter bounds
	/// @param surface The surface
	/// @param umin The u first parameter of the surface
	/// @param umax The u last parameter of the surface
	/// @param vmin The v first parameter of the surface
	/// @param vmax The v last parameter of the surface
	/// @param tolerance The computing tolerance
	/// @param algo The type of extrema algorithm
	AMCAX_API void Init(const std::shared_ptr<Geom3Surface>& surface, double umin, double umax, double vmin, double vmax, double tolerance, ExtremaAlgorithm algo = ExtremaAlgorithm::Grad);

	/// @brief Set the type of extrema algorithm
	/// @param algo The type of extrema algorithm
	AMCAX_API void SetExtremaAlgo(ExtremaAlgorithm algo);

	/// @brief Set the extrema flag
	/// @param flag The extrema flag
	AMCAX_API void SetExtremaFlag(ExtremaFlag flag);

	/// @brief Perform the projection of a point
	/// @param p The point
	AMCAX_API void Perform(const Point3& p);

	/// @brief Is the algorithm done
	/// @return True if the projection is successful
	[[nodiscard]] AMCAX_API bool IsDone() const noexcept;

	/// @brief Get the number of projected points
	/// @return The number of projected points
	[[nodiscard]] AMCAX_API int NPoints() const;

	/// @brief Get the number of projected points
	/// @return The number of projected points
	[[nodiscard]] AMCAX_API operator int() const;

	/// @brief Get the projected point at a given index
	/// @param index The index
	/// @return The projected point
	[[nodiscard]] AMCAX_API Point3 Point(int index) const;

	/// @brief Get the parameters of the projected point at a given index
	/// @param[in] index The index
	/// @param[out] u The u parameter of the projected point
	/// @param[out] v The v parameter of the projected point
	AMCAX_API void Parameters(int index, double& u, double& v) const;

	/// @brief Get the distance from the original point to the projected point at a given index
	/// @param index The index
	/// @return The projected distance
	[[nodiscard]] AMCAX_API double Distance(int index) const;

	/// @brief Get the nearest point
	/// @return The nearest point
	[[nodiscard]] AMCAX_API Point3 NearestPoint() const;

	/// @brief Get the nearest point
	/// @return The nearest point
	[[nodiscard]] AMCAX_API operator Point3() const;

	/// @brief Get the parameters of the nearest point on the surface
	/// @param[out] u The u parameter of the nearest point
	/// @param[out] v The v parameter of the nearest point
	AMCAX_API void LowerDistanceParameters(double& u, double& v) const;

	/// @brief Get the distance from the original point to the nearest point
	/// @return The nearest distance
	[[nodiscard]] AMCAX_API double LowerDistance() const;

	/// @brief Get the distance from the original point to the nearest point
	/// @return The nearest distance
	[[nodiscard]] AMCAX_API operator double() const;

#ifndef DOXYGEN_SKIP

	/// @internal
	[[nodiscard]] const ExtremaPointSurface& Extrema() const noexcept;

#endif

private:
	bool done = false;
	int index = -1;
	std::shared_ptr<ExtremaPointSurface> eps;
	std::shared_ptr<AdaptorGeom3Surface> s;
};
} // namespace AMCAX
