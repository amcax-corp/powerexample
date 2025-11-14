/// @file      TMSplineTransform.hpp
/// @brief     Class of transforming a TMSpline
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <tmeshSpline/TMSpline.hpp>
#include <common/GeneralTransformationT.hpp>

namespace AMCAX
{
namespace TMS
{
/// @brief Class of transforming a TMSpline, change the input and post processing required after transforming the spline
class TMSplineTransform
{
public:
	/// @brief Set the Transformation to be applied
	/// @param t The transformation to be applied
	AMCAX_API void SetTransformation(const Transformation3& t);

	/// @brief Set the GeneralTransformation to be applied
	/// @param gt The general transformation to be applied
	AMCAX_API void SetGTransformation(const GeneralTransformation3& gt);

	/// @brief Applying transformations to a TMSpline
	/// @param tsp input TMSpline to be applied
	AMCAX_API void TransformTMSpline(TMSpline* tsp);

	/// @brief Applying transformations to vert list in a TMSpline
	/// @param tsp input TMSpline to be applied
	/// @param vlist indices of the verts in TMSpline
	AMCAX_API void TransformTMSplineVertices(TMSpline* tsp, const std::vector<int>& vlist);

	/// @brief Applying transformations to edge list in a TMSpline
	/// @param tsp input TMSpline to be applied
	/// @param vlist indices of the edges in TMSpline
	AMCAX_API void TransformTMSplineEdges(TMSpline* tsp, const std::vector<int>& elist);

	/// @brief Applying transformations to face list in a TMSpline
	/// @param tsp input TMSpline to be applied
	/// @param vlist indices of the faces in TMSpline
	AMCAX_API void TransformTMSplineFaces(TMSpline* tsp, const std::vector<int>& flist);

	/// @brief Post processing function required after transforming the spline
	/// @param tsp The TMSpline which applied transformation
	AMCAX_API void TransformReprocessing(TMSpline* tsp);

private:
	GeneralTransformation3 trsf_;
};

} // namespace TMS
} // namespace AMCAX
