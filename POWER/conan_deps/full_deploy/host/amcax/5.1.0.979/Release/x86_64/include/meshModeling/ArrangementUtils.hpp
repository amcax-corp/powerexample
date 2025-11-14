/**
 * @file ArrangementUtils.hpp
 * @brief Define utils used by arrangements.
 * @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd.
 * All rights reserved.
 * @par This file is part of AMCAX kernel.
 */

#pragma once

#include <utilities/Exception.hpp>
#include <utilities/IndexDef.hpp>

#include <bitset>
#include <deque>
#include <vector>

namespace AMCAX {
namespace Meshing {
namespace Arrangements {

inline constexpr int NBIT = 32;

/// * Label for each triangle in arrangements (boolean, and other applications).
///   Label indicates where this triangle locates on.
///   (For example, if Label[0] and Label[1] is true, this triangle locates on
///   triangle soup with index 0 and triangle soup with index 1 at the same
///   time.)
/// * Users can use this label to transfer attributes from input triangle soups
///   to the output triangle soup.
/// * Consider efficiency, we limit maximal label count to be less than
///   NBIT(32).
using Label = std::bitset<NBIT>;

struct MeshArrangements_Stats
{
	/* Preprocessing *************************************************/

	double pp_elapsed   = 0.; // timings of preprocessing
	double mdv_elapsed  = 0.; // timings of merging duplicate vertices
	double rdt_elapsed  = 0.; // timings of removing degenerate and
	                          // duplicate triangles
	double tree_elapsed = 0.; // timings of building tree

	/* Detect intersections ******************************************/

	double di_elapsed = 0.; // timings of detecting intersection

	/* connect intersetion *******************************************/

	double cn_elapsed = 0.; // timings of connecting intersection

	/* classify intersection *****************************************/

	double ci_elapsed = 0.; // timings of classifying intersection

	/* triangulation *************************************************/

	double tr_elapsed = 0.; // timings of triangulation
};

/// @brief Each output triangle has a surface label and inside label.
struct Labels
{
	/// surface (mesh) that a triangle belongs to.
	std::vector<Label> surface;
	/// surface (mesh) that a triangle is inside.
	std::vector<Label> inside;
	/// how many surfaces (meshes) in arrangements.
	size_t             num;
};

/// @brief The faces index of input meshes.
template <typename TriIndexT>
struct SourceFaceInfo
{
	/** @brief index in triangle*/
	using ti_t = TriIndexT;

	// The first is mesh index and the second is face index.
	std::vector<std::pair<ti_t, ti_t>> face_ids;
};

/// @brief The intersection segments information of result mesh.
template <typename TriIndexT>
struct InterSegments
{
	/** @brief index in triangle*/
	using ti_t = TriIndexT;

	// The vertices index of intersection segments.
	std::vector<ti_t> vertex_ids;
	// If true, the segments are connected end-to-end, otherwise not.
	bool              closed;
};

} // namespace Arrangements
} // namespace Meshing
} // namespace AMCAX

#ifdef AMCAXMeshing_HAS_IMPL
	#include "ArrangementUtils.inl"
#endif
