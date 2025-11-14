/// @file      GeomImprint.hpp
/// @brief     Class of Geometric Imprinting
/// @details   Operations related to grometric imprinting
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd.
/// All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <list>
#include <shapeEdit/EditShape.hpp>
#include <shapeEdit/Options.hpp>
#include <topology/TopoShape.hpp>

namespace AMCAX {
class TopoShape;
class TopoEdge;
class TopoFace;
class TopoVertex;
class TopoWire;

namespace GeomE {
/// @brief Class of Geometric Imprinting
class AMCAX_CLASS_API GeomImprint : public EditShape
{
public:
	/// @brief Default constructor
	AMCAX_API GeomImprint();

	/// @brief Performs mutual imprinting of multiple shapes or imprints a list of
	/// faces onto another list of faces
	/// @param[in,out] shape The global shape that serves as the base
	/// @param[in] targetlist The list of target shapes to be imprinted
	/// @param[in] toollist The list of tool shapes used for imprinting
	/// @param[in] options Additional options to control the imprinting behavior
	AMCAX_API void Imprint(TopoShape                  &shape,
	                       const std::list<TopoShape> &targetlist,
	                       const std::list<TopoShape> &toollist = {},
	                       const ImprintOptions &options = ImprintOptions());

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

private:
	std::unordered_map<TopoShape, Trace> traceMap;
};

} // namespace GeomE
} // namespace AMCAX