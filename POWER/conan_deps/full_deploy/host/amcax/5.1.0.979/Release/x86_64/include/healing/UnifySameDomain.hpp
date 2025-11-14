/// @file      UnifySameDomain.hpp
/// @brief     The tool class for simplifying faces and edges of shapes located on the same geometry.
/// @copyright Copyright (c) 2024 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <list>
#include <unordered_set>

#include <topology/TopoShape.hpp>

namespace AMCAX
{
#ifndef DOXYGEN_SKIP
class ShapeUpgradeUnifySameDomain;
#endif

/// @brief The tool class for simplifying faces and edges of shapes located on the same geometry
class UnifySameDomain
{
public:
	/// @brief Default constructor
	AMCAX_API UnifySameDomain();

	/// @brief Constructor defining input shape and necessary flags
	/// @param shape Input shape
	/// @param isUnifyEdges The flag of whether to try to unify all possible edges
	/// @param isUnifyFaces The flag of whether to try to unify all possible faces
	/// @param isConcatBsplines The flag of whether to attempt to merge C1 continuous spline edges with common vertices to one edge
	AMCAX_API explicit UnifySameDomain(const TopoShape& shape, bool isUnifyEdges = true, bool isUnifyFaces = true, bool isConcatBsplines = false);

	/// @brief Initialize with input shape and necessary flags
	/// @param shape Input shape
	/// @param unifyEdges The flag of whether to try to unify all possible edges
	/// @param unifyFaces The flag of whether to try to unify all possible faces
	/// @param isConcatBsplines The flag of whether to attempt to merge C1 continuous spline edges with common vertices to one edge
	AMCAX_API void Initialize(const TopoShape& shape, bool unifyEdges = true, bool unifyFaces = true, bool isConcatBsplines = false);

	/// @brief  Sets the shape for avoid merging
	/// @param keepShapes the vertex or edges which will not be merged
	AMCAX_API void SetKeepShapes(const std::unordered_set<TopoShape>& keepShapes);

	/// @brief Enables or disables the inclusion of internal edges in the result
	/// @param theValue True to allow internal edges, false to suppress them
	AMCAX_API void AllowInternalEdges(bool theValue);

	/// @brief Set the linear tolerance for chord error
	/// @param ltol The linear tolerance, default is Precision::Confusion();
	AMCAX_API void SetLinearTolerance(double ltol);

	/// @brief Set the angular tolerance for shape connection angle error
	/// @param atol The angular tolerance, default is Precision::Angular()
	AMCAX_API void SetAngularTolerance(double atol);

	/// @brief Perform the algorithm
	AMCAX_API void Build();

	/// @brief Get the resulting shape
	/// @return The resulting shape
	[[nodiscard]] AMCAX_API TopoShape Shape() const;

	/// @brief Check if any of the input shapes has been modified.
	/// @return Whether there has any modified object
	[[nodiscard]] AMCAX_API bool HasModified() const;

	/// @brief Check if there are shapes been genereted during the operation.
	/// @return Whether there are shapes been generated.
	[[nodiscard]] AMCAX_API bool HasGenerated() const;

	/// @brief Check if there are any shapes been deleted.
	/// @return Whether there are any shapes been deleted.
	[[nodiscard]] AMCAX_API bool HasDeleted() const;

	/// @brief Get the shapes modified from the given shape
	/// @param s The given shape, only support shape type is vertex, edge, face, and solid
	/// @return The list of modified shapes
	[[nodiscard]] AMCAX_API const std::list<TopoShape>& Modified(const TopoShape& s);

	/// @brief Get the shapes generated from the given shape
	/// @param s The given shape, only support shape type is vertex, edge, face, and solid
	/// @return The list of generated shapes
	[[nodiscard]] AMCAX_API const std::list<TopoShape>& Generated(const TopoShape& s);

	/// @brief Is the given shape deleted
	/// @param s The given shape, only support shape type is vertex, edge, face, and solid
	/// @return True if the given shape is deleted
	[[nodiscard]] AMCAX_API bool IsDeleted(const TopoShape& s) const;

private:
	std::shared_ptr<ShapeUpgradeUnifySameDomain> unifyToolPtr;
	std::list<TopoShape> generated;
};
} // namespace AMCAX
