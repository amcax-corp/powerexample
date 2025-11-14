/// @file      MeshParameters.hpp
/// @brief     Class of parameters used in triangular mesh
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <common/Macros.hpp>

namespace AMCAX
{
/// @brief Class of parameters used in triangular mesh
class MeshParameters
{
public:
	/// @brief Construct from linear deflection, angle deflection and mimimum size
	/// @param def The linear deflection
	/// @param ang The angle deflection
	/// @param min The minimum size
	AMCAX_API explicit MeshParameters(double def = -1.0, double ang = -1.0, double min = -1.0) noexcept;

	/// @brief Is the linear deflection is defined
	/// @return True if the linear deflection is non-negative
	[[nodiscard]] AMCAX_API bool HasDeflection() const noexcept;

	/// @brief Is the angle deflection defined
	/// @return True if the angle deflection is non-negative
	[[nodiscard]] AMCAX_API bool HasAngle() const noexcept;

	/// @brief Is the minimum size defined
	/// @return True if the minimum size is non-negative
	[[nodiscard]] AMCAX_API bool HasMinSize() const noexcept;

	/// @brief Get the linear deflection
	/// @return The linear deflection
	[[nodiscard]] AMCAX_API double Deflection() const noexcept;

	/// @brief Get the angle deflection
	/// @return The angle deflection
	[[nodiscard]] AMCAX_API double Angle() const noexcept;

	/// @brief Get the minimum size
	/// @return The minimum size
	[[nodiscard]] AMCAX_API double MinSize() const noexcept;

private:
	/// @brief Linear deflection
	double deflection;

	/// @brief Angular deflection
	double angle;

	/// @brief Minimum size
	double minSize;
};
} // namespace AMCAX
