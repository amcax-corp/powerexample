/// @file      TMSplineFillHole.hpp
/// @brief     Class of TMSpline API for fill hole
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <tmeshSpline/TMSpline.hpp>

namespace AMCAX
{
namespace TMS
{

/// @brief Class of TMSpline API for fill hole
class TMSplineFillHole
{
public:
	/// @brief check if there are hole with input edge in TMSpline
	/// @param tsp the TMSpline
	/// @param edgeIndex input edge
	/// @return true if there are holes with input edge
	AMCAX_API bool CanFillSingleHole(TMSpline* tsp, size_t edgeIndex);

	/// @brief fill hole whit input edge by use a singel polygon face
	/// @param tsp the TMSpline
	/// @param edgeIndex input edge
	AMCAX_API void FillSingleHole(TMSpline* tsp, size_t edgeIndex);

	/// @brief fill all holes in TMSpline by use a singel polygon face
	/// @param tsp the TMSpline
	/// @return true if the process is succeed
	AMCAX_API bool FillAllHoles(TMSpline* tsp);

private:
	bool FillSingleHole(TMSpline* tsp, TLink* he);

	bool CheckFaceParam(TMSpline* tsp, TFace* f);

	bool CheckFaceType(TMSpline* tsp, TFace* f);

	void SetHoleLinkType(TLink* he, std::vector<size_t>& fhIndex);
};

} // namespace TMS
} // namespace AMCAX
