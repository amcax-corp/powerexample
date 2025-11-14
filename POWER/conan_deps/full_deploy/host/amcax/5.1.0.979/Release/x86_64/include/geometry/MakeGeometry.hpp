/// @file      MakeGeometry.hpp
/// @brief     Base class of making geometry objects
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <common/Macros.hpp>

namespace AMCAX
{
/// @brief Error type of make geometry
enum class MakeGeometryErrorType
{
	Done,
	ConfusedPoints,
	NegativeRadius,
	ColinearPoints,
	IntersectionError,
	NullAxis,
	NullAngle,
	NullRadius,
	InvertAxis,
	BadAngle,
	InvertRadius,
	NullFocusLength,
	NullVector,
	BadEquation
};

/// @brief Base class of making geometry objects
class MakeGeometry
{
public:
	/// @brief Is the algorithm done
	/// @return True if there is no error
	[[nodiscard]] AMCAX_API bool IsDone() const noexcept;

	/// @brief Get the error type
	/// @return The error type
	[[nodiscard]] AMCAX_API MakeGeometryErrorType Status() const noexcept;

protected:
	/// @brief Default constructor
	MakeGeometry() noexcept = default;

	/// @brief Error type in making geometry
	MakeGeometryErrorType error = MakeGeometryErrorType::Done;
};
} // namespace AMCAX
