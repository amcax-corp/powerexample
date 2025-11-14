/// @file      GccMacros.hpp
/// @brief     Enumerate classes of position type and bisecting type
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once

namespace AMCAX
{
/// @brief The position type
enum class GccPosition
{
	Unqualified, // The position of the solution is undefined, i.e. all solutions available
	Enclosing,	 // The solution encompasses the argument
	Enclosed,	 // The solution is encompassed the argument
	Outside,	 // The solution is outside the argument
	Noqualifier	 // The solution has no qualifier when the argument is unqualified
};

#ifndef DOXYGEN_SKIP
/// @internal
/// @brief The type of bisecting curve
enum class GccBisectingType
{
	Line,
	Circle,
	Ellipse,
	Parabola,
	Hyperbola
};
#endif
} // namespace AMCAX
