/// @file      GeomAPIPlaneCurve.hpp
/// @brief     Class of tools converting planar curves between 2D and 3D
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <memory>

#include <common/Macros.hpp>

namespace AMCAX
{
class Plane;
class Geom2Curve;
class Geom3Curve;

/// @brief Class of tools converting planar curves between 2D and 3D
class GeomAPIPlaneCurve
{
public:
	/// @brief Convert a 3D planar curve to a 2D curve
	/// @param c The 3D curve
	/// @param p The plane
	/// @return The 2D curve on the plane
	[[nodiscard]] AMCAX_API static std::shared_ptr<Geom2Curve> To2d(const std::shared_ptr<Geom3Curve>& c, const Plane& p);

	/// @brief Convert a 2D curve on the plane to a 3D curve
	/// @param c The 2D curve on the plane
	/// @param p The plane
	/// @return The 3D curve
	[[nodiscard]] AMCAX_API static std::shared_ptr<Geom3Curve> To3d(const std::shared_ptr<Geom2Curve>& c, const Plane& p);
};
} // namespace AMCAX
