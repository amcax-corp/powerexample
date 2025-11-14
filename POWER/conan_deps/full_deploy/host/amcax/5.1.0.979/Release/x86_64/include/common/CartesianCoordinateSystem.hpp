/// @file      CartesianCoordinateSystem.hpp
/// @brief     Class of Cartesian coordinate system
/// @details   Convenient tools for standard Cartesian coordinate system
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <common/AxisT.hpp>
#include <common/FrameT.hpp>

namespace AMCAX
{
/// @brief Class of Cartesian coordinate system
class CartesianCoordinateSystem
{
public:
	/// @brief Get the origin point in 3D
	/// @return The origin point (0, 0, 0)
	[[nodiscard]] AMCAX_API static const Point3& Origin() noexcept;

	/// @brief Get the x-direction in 3D
	/// @return The x-direction (1, 0, 0)
	[[nodiscard]] AMCAX_API static const Direction3& DX() noexcept;

	/// @brief Get the y-direction in 3D
	/// @return The y-direction (0, 1, 0)
	[[nodiscard]] AMCAX_API static const Direction3& DY() noexcept;

	/// @brief Get the z-direction in 3D
	/// @return The z-direction (0, 0, 1)
	[[nodiscard]] AMCAX_API static const Direction3& DZ() noexcept;

	/// @brief Get the x-axis in 3D, including the origin and the x-direction
	/// @return The x-axis
	[[nodiscard]] AMCAX_API static const Axis3& OX() noexcept;

	/// @brief Get the y-axis in 3D, including the origin and the y-direction
	/// @return The y-axis
	[[nodiscard]] AMCAX_API static const Axis3& OY() noexcept;

	/// @brief Get the z-axis in 3D, including the origin and the z-direction
	/// @return The z-axis
	[[nodiscard]] AMCAX_API static const Axis3& OZ() noexcept;

	/// @brief Get a coordinate system where z-direction is the main direction
	/// @return The xyz coordinate system
	[[nodiscard]] AMCAX_API static const Frame3& XOY() noexcept;

	/// @brief Get a coordinate system where y-direction is the main direction
	/// @return The zxy coordinate system
	[[nodiscard]] AMCAX_API static const Frame3& ZOX() noexcept;

	/// @brief Get a coordinate system where x-direction is the main direction
	/// @return The yzx coordinate system
	[[nodiscard]] AMCAX_API static const Frame3& YOZ() noexcept;

	/// @brief Get the origin point in 2D
	/// @return The origin point (0, 0)
	[[nodiscard]] AMCAX_API static const Point2& Origin2() noexcept;

	/// @brief Get the x-direction in 2D
	/// @return The x-direction (1, 0)
	[[nodiscard]] AMCAX_API static const Direction2& DX2() noexcept;

	/// @brief Get the y-direction in 2D
	/// @return The y-direction (0, 1)
	[[nodiscard]] AMCAX_API static const Direction2& DY2() noexcept;

	/// @brief Get the x-axis in 2D, including the origin and the x-direction
	/// @return The x-axis
	[[nodiscard]] AMCAX_API static const Axis2& OX2() noexcept;

	/// @brief Get the y-axis in 2D, including the origin and the y-direction
	/// @return The y-axis
	[[nodiscard]] AMCAX_API static const Axis2& OY2() noexcept;
};
} // namespace AMCAX
