/// @file      MakeSweep.hpp
/// @brief     Base class of making a swept shape
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <modeling/MakeShape.hpp>

namespace AMCAX
{
/// @brief Base class of making a swept shape
class AMCAX_CLASS_API MakeSweep : public MakeShape
{
public:
	/// @brief Get the first shape
	/// @return The first shape
	[[nodiscard]] AMCAX_API virtual TopoShape FirstShape() = 0;

	/// @brief Get the last shape
	/// @return The last shape
	[[nodiscard]] AMCAX_API virtual TopoShape LastShape() = 0;
};
} // namespace AMCAX
