/// @file      NURBSLinearSweepWithDraftDirectionLength.hpp
/// @brief     The struct of length definition of linear sweeping with draft direction
/// @copyright Copyright (c) 2024 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <memory>

#include <nurbs/NURBSMacros.hpp>

namespace AMCAX
{
class Geom3Surface;

/// @brief Struct of length definition of linear sweeping with draft direction
/// @details This struct defines four types of linear section length used by linear sweeping with draft direction
struct NURBSLinearSweepWithDraftDirectionLength
{
	/// @brief Constructor
	/// @param type Four length types are supported:
	/// 1. FromCurve, length = 0, the parameter length and relimitingSurface is not used;
	/// 2. Standard, the length is computed in sweeping planes, the parameter relimitingSurface is not used
	/// 3. FromTo, the length is computed by intersecting with the relimiting surface, the parameter length is not used
	/// 4. FromExtremum, the length is defined along the draft direction from an extremum plane, the parameter relimitingSurface is not used
	/// @param length The length
	/// @param relimitingSurface The relimiting Surface to restrict the shape of the line
	NURBSLinearSweepWithDraftDirectionLength(NURBSLinearSweepWithDraftDirectionLengthType type, double length, const std::shared_ptr<Geom3Surface>& relimitingSurface)
		: type(type),
		  length(length),
		  relimitingSurface(relimitingSurface)
	{
	}

	/// @brief Type of length
	NURBSLinearSweepWithDraftDirectionLengthType type;

	/// @brief Length
	double length;

	/// @brief The relimiting surface
	std::shared_ptr<Geom3Surface> relimitingSurface;
};
} // namespace AMCAX
