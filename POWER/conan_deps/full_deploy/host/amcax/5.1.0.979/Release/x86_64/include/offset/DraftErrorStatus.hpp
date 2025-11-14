/// @file      DraftErrorStatus.hpp
/// @brief     Enumeration class used in the draft algorithm
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once

namespace AMCAX
{
/// @brief Type of draft error
enum class DraftErrorStatus
{
	NoError,
	FaceRecomputation,
	EdgeRecomputation,
	VertexRecomputation
};
} // namespace AMCAX
