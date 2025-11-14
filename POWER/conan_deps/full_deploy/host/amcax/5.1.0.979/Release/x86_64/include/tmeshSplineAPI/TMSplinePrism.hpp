/// @file      TMSplinePrism.hpp
/// @brief     Class of TMSpline API for Make Prism
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <tmeshSpline/TMSpline.hpp>

namespace AMCAX
{
namespace TMS
{
/// @brief Class of TMSpline API for make a prism TMSpline
class TMSplinePrism
{
public:
	/// @brief return true if the input TMSpline can make prism
	/// @param tsp The TMSpline
	AMCAX_API bool CanMakePrism(TMSpline* tsp);

	/// @brief Prism the TMSpline along the extrusion vector
	/// @param tsp The TMSpline
	/// @param vector The extrusion vector
	/// @return true if the process is succeed
	AMCAX_API bool MakeTMSplintPrism(TMSpline* tsp, const Vector3& vector);

private:
	void DirectionMove(TMSpline* tsp, const Vector3& vector);
};

} // namespace TMS
} // namespace AMCAX