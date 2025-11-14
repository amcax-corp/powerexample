/// @file      TMSplineThicken.hpp
/// @brief     Class of TMSpline API for Thicken a TMSpline
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <tmeshSpline/TMSpline.hpp>

namespace AMCAX
{
namespace TMS
{
/// @brief Class of TMSpline API for Thicken a TMSpline
class TMSplineThicken
{
public:
	/// @brief Offset a TMSpline to obtain a new TMSpline
	/// @param tsp the input TMSpline
	/// @param dist the reference offset distance
	/// @return TMSpline obtained by offset 
	AMCAX_API TMSpline* OffsetTMSpline(const TMSpline* tsp, double dist);

	/// @brief Thicken a TMSpline to obtain a new TMSpline.
	/// @param tsp the TMSpline
	/// @param dist the reference thickening distance
	/// @return True if process succeeded
	AMCAX_API bool ThickenTMSpline(TMSpline* tsp, double dist);

private:
	bool ThickenTMSpline(TMSpline* tsp, double dist, std::vector<int>& vlistNew, std::vector<Vector3>& vMoveDirection,
		bool isConnect = true);

	void OffsetMove(TMSpline* tsp, double dist, std::vector<Vector3>& vert_normal);
};

} // namespace TMS
} // namespace AMCAX
