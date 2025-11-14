/// @file      MakeFaceExtension.hpp
/// @brief     Class for extending a face
/// @copyright Copyright (c) 2024 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.

#pragma once
#include <unordered_map>

#include <modeling/MakeShape.hpp>
#include <topology/TopoFace.hpp>

namespace AMCAX
{
class TopoEdge;

/// @brief Class for extending a face by length
/// @details The length refers to the approximate chord length from the original edge to the new edge.
class AMCAX_CLASS_API MakeFaceExtension : public MakeShape
{
public:
	/// @brief Empty Constructor
	AMCAX_API MakeFaceExtension();

	/// @brief Set the non closed faces that need to be extended
	/// @param face The face
	AMCAX_API void SetFace(const TopoFace& face);

	/// @brief Extend the face using one edge by length
	/// @param edge The boundary edge belonging to the face
	/// @param length The extend Length, > 0 means extending face outward
	AMCAX_API void PerformWithEdgeAndLength(const TopoEdge& edge, double length);

	/// @brief Expand the face with cancel all trimming
	/// @details Extension length less than or equal to 0 indicates no extension in that direction, And need to extend in at least one direction
	/// @param uMinlen The extension length along the reversed U direction
	/// @param uMaxlen The extension length along the U direction
	/// @param vMinlen The extension length along the reversed V direction
	/// @param vMaxlen The extension length along the V direction
	AMCAX_API void PerformExpand(double uMinlen, double uMaxlen, double vMinlen, double vMaxlen);

private:
	bool CheckDataWithEdge(const TopoEdge& edge, bool& isInner);

	void PerformWire(const TopoEdge& edge, double length, bool isInner, TopoFace& newFace);

	TopoFace mFace;
	std::unordered_map<TopoShape, TopoShape> mFaceEdges;
};
} // namespace AMCAX
