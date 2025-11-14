/// @file      MakeHelix.hpp
/// @brief     Class of making a helix, represented by a B spline curve
/// @copyright Copyright (c) 2024 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <memory>

#include <common/FrameT.hpp>
#include <geometry/MakeGeometry.hpp>

namespace AMCAX
{
class Geom3BSplineCurve;

/// @brief Class of making a helix, represented by a B spline curve
class MakeHelix : public MakeGeometry
{
public:
	/// @brief Construct a helix with a constant radius and number of turns
	/// @param frame The local frame
	/// @param radius The radius
	/// @param height The height of helix
	/// @param nTurn The number of turns
	AMCAX_API MakeHelix(const Frame3& frame, double radius, double height, int nTurn);

	/// @brief Construct a helix with a constant radius and height of one turn
	/// @param frame The local frame
	/// @param radius The radius
	/// @param height The height of helix
	/// @param turnHeight The height of one turn
	AMCAX_API MakeHelix(const Frame3& frame, double radius, double height, double turnHeight);

	/// @brief Construct a helix with varying radii and number of turns
	/// @param frame The local frame
	/// @param radius1 The start radius
	/// @param radius2 The end radius
	/// @param height The height of helix
	/// @param nTurn The number of turns
	AMCAX_API MakeHelix(const Frame3& frame, double radius1, double radius2, double height, int nTurn);

	/// @brief Construct a helix with varying radii and height of one turn
	/// @param frame The local frame
	/// @param radius1 The start radius
	/// @param radius2 The end radius
	/// @param height The height of helix
	/// @param turnHeight The height of one turn
	AMCAX_API MakeHelix(const Frame3& frame, double radius1, double radius2, double height, double turnHeight);

	/// @brief Construct a helix with varying radii, height range and angle range
	/// @param frame The local frame
	/// @param radius1 The start radius
	/// @param radius2 The end radius
	/// @param height1 The start height
	/// @param height2 The end height
	/// @param angle1 The start angle
	/// @param angle2 The end angle
	/// @param mode The construction mode, 0 for interpolation, 1 for approximation
	AMCAX_API MakeHelix(const Frame3& frame, double radius1, double radius2, double height1, double height2, double angle1, double angle2, int mode = 0);

	/// @brief Get the helix
	/// @return The helix
	[[nodiscard]] AMCAX_API const std::shared_ptr<Geom3BSplineCurve>& Value() const noexcept;

	/// @brief Get the helix
	/// @return The helix
	[[nodiscard]] AMCAX_API operator const std::shared_ptr<Geom3BSplineCurve>&() const noexcept;

private:
	std::shared_ptr<Geom3BSplineCurve> helix;
};
} // namespace AMCAX
