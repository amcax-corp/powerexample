/// @file      NURBSAPIUntrim.hpp
/// @brief     The class of untrim operation
/// @copyright Copyright (c) 2024 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <common/Macros.hpp>

namespace AMCAX
{
class TopoEdge;
class TopoFace;
class TopoShape;

/// @brief Class of untrimming a face
/// @details This class computes the untrimmed face by removing the influence of a trim operation.
class NURBSAPIUntrim
{
public:
	/// @brief Restore the trimmed face (by n edges) to its untrimmed state (trimmed by n-1 edges)\n
	/// The cases are sort of complicated. It can be classified by:\n
	///		1. number of wires;\n
	///		2. the number of intersection points with boundaries of wire containing untrim edge;\n
	///		3. the number of oriBound edges and non-oriBound edges.\n
	/// If face has one wire:\n
	///		if num of intersection points is less than 2 or the untrimm edge is the only edge of the wire: \n
	///			return the face built by the whole surface.\n
	///		else if the number of non-oriBound edges is 0:\n
	///			return the face built by the whole surface.\n
	///		else if the number of oriBound edges is 0:\n
	///			Make two untrim faces and judge which is required by select a point on untrim edge.\n
	///		else\n
	///			Make the untrim face by the algorithm illustrated below. (usual cases)\n
	/// else if the untrim edge is on outer wire\n
	///		Perform as the one wire case and add the other wires to the result.\n
	/// else \n
	///		Since the untrim edge is on inner wire, just remove the inner wire.\n
	/// \n
	/// The algorithm of making the untrim face in usual cases is:\n
	///		1. judge whether the edges of the wire is on oriBound;\n
	///		2. decide which part of the edges is remained\n
	///		3. build new edges\n
	///		4. make new wire and judge orientation by the same edge of the two wires\n
	///		5. replace the old wire with the new wire
	/// @param edge Edge to untrim
	/// @param face Face to Untrim
	/// @return New face
	[[nodiscard]] AMCAX_API static TopoShape Untrim(const TopoEdge& edge, const TopoFace& face);
};
} // namespace AMCAX
