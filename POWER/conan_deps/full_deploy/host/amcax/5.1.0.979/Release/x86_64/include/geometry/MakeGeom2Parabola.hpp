/// @file      MakeGeom2Parabola.hpp
/// @brief     Class of making 2D geometric parabolas
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <geometry/Geom2Parabola.hpp>
#include <geometry/MakeGeometry.hpp>

namespace AMCAX
{
/// @brief Class of making 2D geometric parabolas
class MakeGeom2Parabola : public MakeGeometry
{
public:
	/// @brief Construct from a parabola
	/// @param p The parabola
	AMCAX_API explicit MakeGeom2Parabola(const Parabola2& p);

	/// @brief Construct a parabola from a local frame and a focal length
	/// @param frame The local frame
	/// @param focal The focal length
	AMCAX_API MakeGeom2Parabola(const Frame2& frame, double focal);

	/// @brief Construct a parabola from a mirror axis and a focal length
	/// @param mirrorAxis The mirror axis
	/// @param focal The focal length
	/// @param sense Determine whether the local frame is right-handed
	AMCAX_API MakeGeom2Parabola(const Axis2& mirrorAxis, double focal, bool sense = true);

	/// @brief Construct a parabola from an axis of directrix and a focus point
	/// @param d The axis of directrix
	/// @param f The focus point
	/// @param sense Determine whether the local frame is right-handed
	AMCAX_API MakeGeom2Parabola(const Axis2& d, const Point2& f, bool sense = true);

	/// @brief Construct a parabola from a focus point and a center point
	/// @param s1 The focus point
	/// @param o The center point (apex point)
	/// @param sense Determine whether the local frame is right-handed
	AMCAX_API MakeGeom2Parabola(const Point2& s1, const Point2& o, bool sense = true);

	/// @brief Get the constructed parabola
	/// @return The parabola
	[[nodiscard]] AMCAX_API const std::shared_ptr<Geom2Parabola>& Value() const;

	/// @brief Get the constructed parabola
	/// @return The parabola
	[[nodiscard]] AMCAX_API operator const std::shared_ptr<Geom2Parabola>&() const;

private:
	std::shared_ptr<Geom2Parabola> parabola;
};
} // namespace AMCAX
