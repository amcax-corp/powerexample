/// @file      MakeParabola2.hpp
/// @brief     Class of making 2D parabolas
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <geometry/MakeGeometry.hpp>
#include <math/ParabolaT.hpp>

namespace AMCAX
{
/// @brief Class of making 2D parabolas
class MakeParabola2 : public MakeGeometry
{
public:
	/// @brief Construct a parabola from a mirror axis and a focal length
	/// @param mirrorAxis The mirror axis
	/// @param focal The focal length
	/// @param sense Determine whether the local frame is right-handed
	AMCAX_API MakeParabola2(const Axis2& mirrorAxis, double focal, bool sense = true);

	/// @brief Construct a parabola from a local frame and a focal length
	/// @param frame The local frame
	/// @param focal The focal length
	AMCAX_API MakeParabola2(const Frame2& frame, double focal);

	/// @brief Construct a parabola from an axis of directrix and a focus point
	/// @param d The axis of directrix
	/// @param f The focus point
	/// @param sense Determine whether the local frame is right-handed
	AMCAX_API MakeParabola2(const Axis2& d, const Point2& f, bool sense = true);

	/// @brief Construct a parabola from a focus point and a center point
	/// @param s1 The focus point
	/// @param center The center point (apex point)
	/// @param sense Determine whether the local frame is right-handed
	AMCAX_API MakeParabola2(const Point2& s1, const Point2& center, bool sense = true);

	/// @brief Get the constructed parabola
	/// @return The parabola
	[[nodiscard]] AMCAX_API const Parabola2& Value() const;

	/// @brief Get the constructed parabola
	/// @return The parabola
	[[nodiscard]] AMCAX_API operator const Parabola2&() const;

private:
	Parabola2 parabola;
};
} // namespace AMCAX
