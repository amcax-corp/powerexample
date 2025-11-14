/// @file      MakeWire.hpp
/// @brief     Class of making a wire
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <modeling/MakeShape.hpp>
#include <topology/TopoWire.hpp>

namespace AMCAX
{
#ifndef DOXYGEN_SKIP
class MakeWireImpl;
class TopoEdge;
class TopoVertex;
#endif

/// @brief Class of making a wire
class AMCAX_CLASS_API MakeWire : public MakeShape
{
public:
	/// @brief Default constructor
	AMCAX_API MakeWire();

	/// @brief Construct a wire with an edge
	/// @param e The edge
	AMCAX_API explicit MakeWire(const TopoEdge& e);

	/// @brief Construct a wire with two edges
	/// @param e1 The first edge
	/// @param e2 The second edge
	AMCAX_API MakeWire(const TopoEdge& e1, const TopoEdge& e2);

	/// @brief Construct a wire with three edges
	/// @param e1 The first edge
	/// @param e2 The second edge
	/// @param e3 The third edge
	AMCAX_API MakeWire(const TopoEdge& e1, const TopoEdge& e2, const TopoEdge& e3);

	/// @brief Construct a wire with four edges
	/// @param e1 The first edge
	/// @param e2 The second edge
	/// @param e3 The third edge
	/// @param e4 The fourth edge
	AMCAX_API MakeWire(const TopoEdge& e1, const TopoEdge& e2, const TopoEdge& e3, const TopoEdge& e4);

	/// @brief Construct a wire with a wire
	/// @param w The wire
	AMCAX_API explicit MakeWire(const TopoWire& w);

	/// @brief Construct a wire from a wire and an edge
	/// @param w The wire
	/// @param e The edge
	AMCAX_API MakeWire(const TopoWire& w, const TopoEdge& e);

	/// @brief Add an edge to the wire
	/// @param e The edge
	AMCAX_API void Add(const TopoEdge& e);

	/// @brief Add a wire to the current wire
	/// @param w The wire
	AMCAX_API void Add(const TopoWire& w);

	/// @brief Add a list of edges to the wire
	/// @param l The list of edges
	AMCAX_API void Add(const std::list<TopoShape>& l);

	[[nodiscard]] AMCAX_API bool IsDone() const noexcept override;

	/// @brief Get the error status
	/// @return The error status
	[[nodiscard]] AMCAX_API WireError Error() const noexcept;

	/// @brief Get the constructed wire
	/// @return The constructed wire
	[[nodiscard]] AMCAX_API const TopoWire& Wire();

	/// @brief Get the constructed wire
	/// @return The constructed wire
	[[nodiscard]] AMCAX_API operator TopoWire();

	/// @brief Get the last edge added to the wire
	/// @return The last edge
	[[nodiscard]] AMCAX_API const TopoEdge& Edge() const noexcept;

	/// @brief Get the last vertex of the last edge added to the wire
	/// @return The last vertex
	[[nodiscard]] AMCAX_API const TopoVertex& Vertex() const noexcept;

private:
	std::shared_ptr<MakeWireImpl> makeWireImpl;
};
} // namespace AMCAX
