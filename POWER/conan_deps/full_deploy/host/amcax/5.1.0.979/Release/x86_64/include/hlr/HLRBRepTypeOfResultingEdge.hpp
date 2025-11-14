/// @file      HLRBRepTypeOfResultingEdge.hpp
/// @brief     Enumerate class of type of resulting edge used in hidden line removal
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once

namespace AMCAX
{
/// @brief Type of resulting edge used in hidden line removal
enum class HLRBRepTypeOfResultingEdge
{
	Unknow,
	IsoLine,
	OutLine,
	Rg1Line,
	RgNLine,
	Sharp
};
} // namespace AMCAX
