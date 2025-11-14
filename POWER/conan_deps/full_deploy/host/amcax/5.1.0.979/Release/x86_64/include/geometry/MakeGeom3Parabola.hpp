/// @file      MakeGeom3Parabola.hpp
/// @brief     Class of making 3D geometric parabolas
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <geometry/Geom3Parabola.hpp>
#include <geometry/MakeGeometry.hpp>

namespace AMCAX
{
/// @brief Class of making 3D geometric parabolas
class MakeGeom3Parabola : public MakeGeometry
{
public:
	/// @brief Construct from a parabola
	/// @param p The parabola
	AMCAX_API explicit MakeGeom3Parabola(const Parabola3& p);

	/// @brief Construct a parabola from a local frame and a focal length
	/// @param frame The local frame
	/// @param focal The focal length
	AMCAX_API MakeGeom3Parabola(const Frame3& frame, double focal);

	/// @brief Construct a parabola from an axis of directrix and a focus point
	/// @param d The axis of dirextrix
	/// @param f The focus point
	AMCAX_API MakeGeom3Parabola(const Axis3& d, const Point3& f);

	/// @brief Get the constructed parabola
	/// @return The parabola
	[[nodiscard]] AMCAX_API const std::shared_ptr<Geom3Parabola>& Value() const;

	/// @brief Get the constructed parabola
	/// @return The parabola
	[[nodiscard]] AMCAX_API operator const std::shared_ptr<Geom3Parabola>&() const;

private:
	std::shared_ptr<Geom3Parabola> parabola;
};
} // namespace AMCAX
