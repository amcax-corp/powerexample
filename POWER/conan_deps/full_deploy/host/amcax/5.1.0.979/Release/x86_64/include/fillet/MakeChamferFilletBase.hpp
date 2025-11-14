/// @file      MakeChamferFilletBase.hpp
/// @brief     The base class of chamfer and fillet
/// @details   This class defines common interfaces for both chamfer and fillet.
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <vector>

#include <modeling/MakeShape.hpp>

namespace AMCAX
{
class TopoEdge;
class TopoVertex;

/// @brief The base class of chamfer and fillet
/// @details This virtual class defines common interfaces for both chamfer and fillet.
class AMCAX_CLASS_API MakeChamferFilletBase : public MakeShape
{
public:
	/// @brief Add an edge and build a contour
	/// @param e The edge to be processed
	AMCAX_API virtual void Add(const TopoEdge& e) = 0;

	/// @brief Reset the i-th contour
	/// @param i The index of contour
	AMCAX_API virtual void ResetContour(int i) = 0;

	/// @brief Get the number of contours
	/// @return The number of contours
	[[nodiscard]] AMCAX_API virtual int NContours() const = 0;

	/// @brief Get the index of contour that contains a given edge, if the edge does not belong to any contour, return -1
	/// @param e The given edge
	/// @return The index of contour
	[[nodiscard]] AMCAX_API virtual int Contour(const TopoEdge& e) const = 0;

	/// @brief Get the number of edges in the i-th contour
	/// @param i The index of contour
	/// @return The number of edges
	[[nodiscard]] AMCAX_API virtual int NEdges(int i) const = 0;

	/// @brief Get the j-th edge in the i-th contour
	/// @param i The index of edge
	/// @param j The index of contour
	/// @return The j-th edge in the i-th contour
	[[nodiscard]] AMCAX_API virtual const TopoEdge& Edge(int i, int j) const = 0;

	/// @brief Remove the contour containing a given edge
	/// @param e The given edge
	AMCAX_API virtual void Remove(const TopoEdge& e) = 0;

	/// @brief Get the length of the i-th contour
	/// @param i The index of contour
	/// @return The length of contour
	[[nodiscard]] AMCAX_API virtual double Length(int i) const = 0;

	/// @brief Get the first vertex of the i-th contour
	/// @param i The index of contour
	/// @return The first vertex of contour
	[[nodiscard]] AMCAX_API virtual TopoVertex FirstVertex(int i) const = 0;

	/// @brief Get the last vertex of the i-th contour
	/// @param i The index of contour
	/// @return The last vertex of contour
	[[nodiscard]] AMCAX_API virtual TopoVertex LastVertex(int i) const = 0;

	/// @brief Get the abscissa of a vertex on the i-th contour
	/// @param i The index of contour
	/// @param v The given vertex
	/// @return The abscissa of vertex
	[[nodiscard]] AMCAX_API virtual double Abscissa(int i, const TopoVertex& v) const = 0;

	/// @brief Get the relative abscissa of a vertex on the i-th contour, range in [0, 1]
	/// @param i The index of contour
	/// @param v The given vertex
	/// @return The relative abscissa of vertex
	[[nodiscard]] AMCAX_API virtual double RelativeAbscissa(int i, const TopoVertex& v) const = 0;

	/// @brief Get the status that whether the i-th contour is closed and tangent
	/// @param i The index of contour
	/// @return Whether the contour is closed and tangent
	[[nodiscard]] AMCAX_API virtual bool ClosedAndTangent(int i) const = 0;

	/// @brief Get the status that whether the i-th contour is closed
	/// @param i The index of contour
	/// @return Whether the contour is closed
	[[nodiscard]] AMCAX_API virtual bool Closed(int i) const = 0;

	/// @brief Reset the building state
	AMCAX_API virtual void Reset() = 0;

	/// @brief Simulate the i-th contour computation for fast preview
	/// @param i The index of contour
	AMCAX_API virtual void Simulate(int i) = 0;

	/// @brief Get the number of surfaces in the i-th contour
	/// @param i The index of contour
	/// @return The number of surfaces
	[[nodiscard]] AMCAX_API virtual int NSurf(int i) const = 0;
};
} // namespace AMCAX
