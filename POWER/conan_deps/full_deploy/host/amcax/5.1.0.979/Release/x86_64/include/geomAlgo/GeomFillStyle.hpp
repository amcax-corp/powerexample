/// @file      GeomFillStyle.hpp
/// @brief     Enumerate classes used in modeling algorithm
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once

namespace AMCAX
{
/// @brief Status during making a pipe
enum class GeomFillPipeStatus
{
	PipeOk,
	PipeNotOk,
	PlaneNotIntersectGuide,
	ImpossibleContact
};

#ifndef DOXYGEN_SKIP
/// @internal
/// @brief Type of approximation during sweeping algorithms
enum class GeomFillApproxStyle
{
	Section,
	Location
};
#endif

/// @brief Type of sweeping strategy
enum class GeomFillTrihedron
{
	/// @brief Default choice of MakePipe and MakePipeShell, use the classic corrected frenet method to make swept surface
	CorrectedFrenet,

	/// @brief Always use the same frenet, parallel sweep
	Fixed,

	/// @brief The basic frenet sweeping method
	Frenet,

	/// @brief Always use the same normal to build the frenet of the sweeping
	ConstantNormal,

	/// @brief Similar to Frenet, use darboux frenet
	Darboux,

	/// @brief Use additional guide curve to control the sweep frenet
	GuideAC,

	/// @brief Use additional plane to control the sweep frenet
	GuidePlan,

	/// @brief Use additional guide curve to control the sweep frenet and force contact
	GuideACWithContact,

	/// @brief Use additional plane to control the sweep frenet and force contact
	GuidePlanWithContact,

	/// @brief Use discrete method to make frenets
	DiscreteTrihedron
};
} // namespace AMCAX
