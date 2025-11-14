/// @file      MakeParabola3.hpp
/// @brief     Class of making 3D parabolas
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <geometry/MakeGeometry.hpp>
#include <math/ParabolaT.hpp>

namespace AMCAX
{
/// @brief Class of making 3D parabolas
class MakeParabola3 : public MakeGeometry
{
public:
	/// @brief Construct a parabola from a local frame and a focal length
	/// @param frame The local frame
	/// @param focal The focal length
	AMCAX_API MakeParabola3(const Frame3& frame, double focal);

	/// @brief Construct a parabola from an axis of directrix and a focus point
	/// @param d The axis of dirextrix
	/// @param f The focus point
	AMCAX_API MakeParabola3(const Axis3& d, const Point3& f);

	/// @brief Get the constructed parabola
	/// @return The parabola
	[[nodiscard]] AMCAX_API const Parabola3& Value() const;

	/// @brief Get the constructed parabola
	/// @return The parabola
	[[nodiscard]] AMCAX_API operator const Parabola3&() const;

private:
	Parabola3 parabola;
};
} // namespace AMCAX
