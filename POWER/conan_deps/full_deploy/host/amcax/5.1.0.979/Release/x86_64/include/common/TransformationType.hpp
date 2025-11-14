/// @file      TransformationType.hpp
/// @brief     Enumeration class of transformation type
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once

namespace AMCAX
{
/// @brief Type of transformation
enum class TransformationType
{
	/// @brief Identity transformation, with unit scale, identity matrix and zero translation vector
	Identity,

	/// @brief Rotation transformation, with unit scale, rotation matrix (determinant is 1) and arbitrary translation vector
	Rotation,

	/// @brief Translation transformation, with unit scale, identity matrix and arbitrary translation vector
	Translation,

	/// @brief Mirror transformation w.r.t. a point, with minus one scale, identity matrix and arbitrary translation vector
	PointMirror,

	/// @brief Mirror transformation w.r.t. an axis, with unit scale, mirror matrix (determinant is 1 in 3D or -1 in 2D) and arbitrary translation vector
	AxisMirror,

	/// @brief Mirror transformation w.r.t. a 3D frame, i.e. mirror w.r.t. a plane defined by the XOY plane of the frame, wtih minus one scale, mirror matrix (determinant is 1) and arbitrary translation vector
	FrameMirror,

	/// @brief Scale transformation, with non-zero scale, identity matrix and arbitrary translation vector
	Scale,

	/// @brief Compound transformation of the other basic transformations
	Compound,

	/// @brief Non-orthogomal transformation, only used in general transformation.
	Other
};
} // namespace AMCAX
