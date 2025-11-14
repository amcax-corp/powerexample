/// @file      TMSplineAddFace.hpp
/// @brief     Class of TMSpline API for Adding faces
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <tmeshSpline/TMSpline.hpp>

namespace AMCAX
{
namespace TMS
{

/// @brief Class of TMSpline API for Adding faces
class TMSplineAddFace
{
public:
	/// @brief return true if it can add a single face constructed from points to a TMSpline
	/// @param tsp the TMSpline
	/// @param vplist the points for constructing face
	AMCAX_API bool CanAddSingleFace(TMSpline* tsp, const std::vector<Point3>& vplist);

	/// @brief return true if it can add a single face constructed from two edges to a TMSpline
	/// @param tsp the TMSpline
	/// @param e1index the first edge
	/// @param e2index the second edge
	AMCAX_API bool CanAddFaceByEdge(TMSpline* tsp, int e1index, int e2index);

	/// @brief add a single face constructed from points to a TMSpline
	/// @param tsp the TMSpline
	/// @param vplist the points for constructing face
	/// @return the result face
	AMCAX_API TFace* AddSingleFace(TMSpline* tsp, const std::vector<Point3>& vplist);

	/// @brief add a single face constructed from two edges to a TMSpline
	/// @param tsp the TMSpline
	/// @param e1index the first edge
	/// @param e2index the second edge
	/// @return the result face
	AMCAX_API TFace* AddFaceByEdge(TMSpline* tsp, int e1index, int e2index);

private:
	TFace* AddFreeSingleFace(TMSpline* tsp, const std::vector<Point3>& vplist);

	TFace* AppendSingleFace(TMSpline* tsp, const std::vector<Point3>& vplist, const std::vector<int>& vpindex, int vertNum);

	TFace* AppendSingleFaceWithTwoVert(TMSpline* tsp, const std::vector<Point3>& vplist, const std::vector<int>& vpindex);

	TFace* AppendSingleFaceWithThreeVert(TMSpline* tsp, const std::vector<Point3>& vplist, const std::vector<int>& vpindex);

	TFace* EnbedSingleFace(TMSpline* tsp, const std::vector<int>& vpindex);
};

} // namespace TMS
} // namespace AMCAX
