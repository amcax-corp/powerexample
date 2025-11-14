/// @file      FaceExtension.hpp
/// @brief     Class for Face Extension
/// @details   Operations related to extending faces
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd.
/// All rights reserved.
/// @par       This file is part of the AMCAX kernel.
#pragma once
#include <list>
#include <shapeEdit/EditShape.hpp>
#include <shapeEdit/Options.hpp>
#include <topology/TopoShape.hpp>
#include <unordered_map>

namespace AMCAX {
class TopoShape;
class TopoEdge;
class TopoFace;
class TopoVertex;
class TopoWire;

namespace GeomE {
/// @brief Class of Face Extension
class AMCAX_CLASS_API FaceExtension : public EditShape
{
public:
	/// @brief Default constructor
	AMCAX_API FaceExtension();

	/// @brief Extend the source faces by adding new faces along the normal
	/// direction of the selected edges (free edges), expanding outward from the
	/// source faces. The extension can be performed either by a specified
	/// distance or until reaching a target face or target face group. The surface
	/// of each new face is a natural continuation of its corresponding source
	/// face's surface. Optionally, the new faces can be automatically merged with
	/// the target faces
	/// @param[in,out] shape The shape that contains both the source and target
	/// faces
	/// @param[in] edgelist The selected edges (free edges) to extend from
	/// @param[in] options Additional options to control the extension behavior
	AMCAX_API void
	ExtendFaceToTarget(TopoShape &shape, const std::list<TopoEdge> &edgelist,
	                   const ExtendOptions &options = ExtendOptions());

	/// @brief Extend faces in pairs by generating extension faces between two
	/// groups of boundary edges
	/// @details This function extends two groups of faces, each defined by a list
	/// of free boundary edges. For each selected edge, a new face is created as
	/// an extension of the source face's underlying surface. Extensions are
	/// performed either by a specified distance or until extensions from one
	/// group reaches Faces of the other group
	/// @param[in,out] shape The shape that contains the faces to be extended.
	/// @param[in] edges1 The first list of boundary edges to extend from
	/// @param[in] edges2 The second list of boundary edges to extend from
	/// @param[in] options Additional options to control the extension behavior
	AMCAX_API void
	ExtendFacePairs(TopoShape &shape, const std::list<TopoEdge> &edges1,
	                const std::list<TopoEdge> &edges2,
	                const ExtendOptions       &options = ExtendOptions());

	/// @brief Compute the shape modified from a given shape s
	/// @details If any, the list will contain only those splits of the given
	/// shape
	/// @param[in] s The given shape
	/// @return The list of modified shapes
	AMCAX_API const std::list<TopoShape> &Modified(const TopoShape &s) override;

	/// @brief Compute the shape generated from a given shape s
	/// @details Only edges and faces could have generated shapes, i.e. edges
	/// generate new vertices, and faces generate new edges and vertices
	/// @param[in] s The given shape
	/// @return The list of generated shapes
	AMCAX_API const std::list<TopoShape> &Generated(const TopoShape &s) override;

	/// @brief Check if the shape s has been deleted during the operation
	/// @param[in] s The given shape
	/// @return Whether the shape is deleted
	AMCAX_API bool IsDeleted(const TopoShape &s) override;
};

} // namespace GeomE
} // namespace AMCAX