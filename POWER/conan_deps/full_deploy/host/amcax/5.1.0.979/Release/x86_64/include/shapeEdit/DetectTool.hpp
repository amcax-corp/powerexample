/// @file      DetectTool.hpp
/// @brief     Class of Detect Tool
/// @details   Some detecting tools
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd.
/// All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <common/IndexMap.hpp>
#include <common/IndexSet.hpp>
#include <common/PointT.hpp>
#include <list>
#include <shapeEdit/FeatureStructs.hpp>
#include <shapeEdit/GeomEMacros.hpp>
#include <topology/TopoEdge.hpp>
#include <topology/TopoWire.hpp>
#include <vector>

namespace AMCAX {
namespace GeomE {
/// @brief Class of Detect Tools
class DetectTool
{
public:
	/// @brief Detect the type of a given edge within the specified shape
	/// @param[in] shape The shape containing the edge
	/// @param[in] edge The edge whose type is to be identified
	/// @return The type of edge
	[[nodiscard]] AMCAX_API static EdgeType GetEdgeType(const TopoShape &shape, const TopoEdge& edge);

	/// @brief Detect the type of each edge within the specified shape
	/// @param shape The shape
	/// @return The map of each edge to its type
	[[nodiscard]] AMCAX_API static IndexMap<TopoShape, EdgeType> GetEdgeType(const TopoShape& shape);

	/// @brief Find a set of free boundaries within the given shape that includes
	/// the specified free edge
	/// @param[in] shape The given shape
	/// @param[in] edge The specified free edge
	/// @return A set of edges representing the free boundaries that include the
	/// specified edge
	AMCAX_API static IndexSet<TopoShape> DetectFreeBoundaries(const TopoShape &shape, const TopoEdge &edge);

	/// @brief Find all free edges
	/// @param[in] shape The shape
	/// @return The free edges
	AMCAX_API static IndexSet<AMCAX::TopoShape> DetectFreeEdges(const AMCAX::TopoShape &shape);

	/// @brief Check whether the solid, shell, wire or edge is closed
	/// @details If the shape is a solid or shell, then return true if the shape
	/// has no boundary edge. If the shape is a wire, then return true if the wire
	/// has no boundary vertex. If the shape is an edge, then return true if the
	/// edge has two coincide vertices
	/// @param[in] s The shape
	/// @return True if the shape is closed
	AMCAX_API static bool IsClosed(const TopoShape &s);

	/// @brief Find a set of canonical 3D hole features within the given shape,
	/// consisting of combinations of cylindrical, conical and toroidal surfaces
	/// @param[in] shape The given shape
	/// @return A set of canonical 3D hole features consisting of
	/// combinations of cylindrical, conical and toroidal surfaces
	AMCAX_API static std::vector<HoleProperties> ExtractCanonical3DHoles(const AMCAX::TopoShape &shape);

	/// @brief Using the feature edge method, cylindrical holes, rectangular
	/// holes, conical holes and various irregular 3D hole features are searched
	/// in the shape. Depending on whether the bottom of the inner wall surface is
	/// closed, they are classified as through holes and blind holes.
	/// @param[in] shape The given shape
	/// @param[out] holesInfo A set of 3D hole features Finded from the shape
	/// @return void
	AMCAX_API static void Extract3DHolesByFeatureEdge(const AMCAX::TopoShape &shape, std::vector<HoleProperties> &holesInfo);

	/// @brief Starting from the edge, search for a closed concave or
	/// convex contour line within the shape range based on the parameter
	/// convexity.
	/// @param[in] convexity Concave or convex
	/// @param[in] edge Search for start edge
	/// @param[in] shape The given shape
	/// @return Closed concave or convex contour line
	AMCAX_API static IndexSet<TopoShape> DetectConvexAndConcaveBoundaries(bool convexity, const AMCAX::TopoShape &edge, const AMCAX::TopoShape& shape);

	/// @brief Find a set of LOGO feature within the given shape
	/// @param[in] convexity Convexity is equal to true for detecting convex logos
	/// and equal to false for detecting concave logos.
	/// @param[in] shape The given shape
	/// @param[out] logoInfos Finded LOGO feature from the shape
	/// @return void
	AMCAX_API static void Extract3DLogo(bool convexity,const AMCAX::TopoShape &shape, std::vector<LogoProperties> &logoInfos);

	/// @brief Find a set of fillet feature within the given shape
	/// @param[in] shape The given shape
	/// @param[out] filletInfos Finded fillet feature from the shape
	/// @return void
	AMCAX_API static void ExtractFillets(const AMCAX::TopoShape &shape,std::vector<FilletProperties> &filletInfos);

	/// @brief Find a set of chamfer feature within the given shape
	/// @param[in] shape The given shape
	/// @param[out] chamferInfos Finded chamfer feature from the shape
	/// @return void
	AMCAX_API static void ExtractChamfers(const AMCAX::TopoShape &shape,std::vector<ChamferProperties> &chamferInfos);

#ifdef INTERNAL_TEST

	/// @brief Find and locate the installation surface of the clamp from the
	/// model
	/// @param[in] shape The given shape
	/// @return installation surface  of the clamp
	AMCAX_TEST_API static TopoShape FindClampInstallationSurface(const AMCAX::TopoShape &shape);

	/// @brief Find a set of groove feature within the given shape
	/// @param[in] shape The given shape
	/// @param[out] groovesInfo Finded groove feature from the shape
	/// @return void
	AMCAX_TEST_API static void ExtractGrooves(const AMCAX::TopoShape &shape, std::vector<GrooveMessage>& groovesInfo);
	               
#endif
};
} // namespace GeomE
} // namespace AMCAX