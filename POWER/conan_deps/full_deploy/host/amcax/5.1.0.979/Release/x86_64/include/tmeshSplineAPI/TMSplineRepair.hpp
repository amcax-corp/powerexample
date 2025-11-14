/// @file      TMSplineRepair.hpp
/// @brief     Class of TMSpline API for repair TMSpline
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <tmeshSpline/TMSpline.hpp>

namespace AMCAX
{
namespace TMS
{
/// @brief Class of TMSpline API for repair TMSpline, This is a utility tool used when meshing failure
class TMSplineRepair
{
public:
	/// @brief Auto Repair a TMSpline and make it meet the t-mesh conditions, Some T-junction will be change to singular points
	/// @param tsp The TMSpline that need to be repair
	/// @return true if process succeeded
	AMCAX_API bool RepairTSpline(TMSpline* tsp);

	/// @brief Try make all the knots intervals(edge param length) in a TMSpline uniform, this is useful when the surface strange bunching
	/// @param tsp The TMSpline that need to be unforem
	/// @return true if process succeeded
	AMCAX_API bool UniformTSpline(TMSpline* tsp);

private:
	bool repairTSplineTopology(TMSpline* tsp);
};

} // namespace TMS
} // namespace AMCAX
