/// @file      GeomAPIIntSurfaceSurface.hpp
/// @brief     Class of computing intersection curves for two surfaces
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <memory>

#include <common/Macros.hpp>

namespace AMCAX
{
#ifndef DOXYGEN_SKIP
class Geom3Curve;
class Geom3Surface;
class GeomIntSS;
#endif

/// @brief Class of computing intersection curves for two surfaces
class GeomAPIIntSurfaceSurface
{
public:
	/// @brief Default constructor
	AMCAX_API GeomAPIIntSurfaceSurface();

	/// @brief Construct from two surfaces
	/// @param s1 The first surface
	/// @param s2 The second surface
	/// @param tol The tolerance for computing surface intersection
	AMCAX_API GeomAPIIntSurfaceSurface(const std::shared_ptr<Geom3Surface>& s1, const std::shared_ptr<Geom3Surface>& s2, double tol);

	/// @brief Perform the intersection from two surfaces
	/// @param s1 The first surface
	/// @param s2 The second surface
	/// @param tol The tolerance for computing surface intersection
	AMCAX_API void Perform(const std::shared_ptr<Geom3Surface>& s1, const std::shared_ptr<Geom3Surface>& s2, double tol);

	/// @brief Is the algorithm done
	/// @return True if the algorithm is successful
	[[nodiscard]] AMCAX_API bool IsDone() const noexcept;

	/// @brief Get the number of intersection curves
	/// @return The number of intersection curves
	[[nodiscard]] AMCAX_API int NLines() const;

	/// @brief Get the intersection curve at a given index
	/// @param index The index
	/// @return The intersection curve
	[[nodiscard]] AMCAX_API const std::shared_ptr<Geom3Curve>& Line(int index) const;

private:
	std::shared_ptr<GeomIntSS> intSS;
};
} // namespace AMCAX
