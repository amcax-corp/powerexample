/// @file      WireExplorer.hpp
/// @brief     Class of tool for exploring wire
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <list>
#include <unordered_map>
#include <unordered_set>

#include <topology/TopoEdge.hpp>
#include <topology/TopoFace.hpp>
#include <topology/TopoVertex.hpp>

namespace AMCAX
{
class TopoWire;

/// @brief Class of tool for exploring wire
class WireExplorer
{
public:
	/// @brief Default constructor
	WireExplorer() = default;

	/// @brief Construct from a wire
	/// @param w The wire
	AMCAX_API explicit WireExplorer(const TopoWire& w);

	/// @brief Construct from a wire and a face
	/// @param w The wire
	/// @param f The face
	AMCAX_API WireExplorer(const TopoWire& w, const TopoFace& f);

	/// @brief Initialize the explorer by a wire
	/// @param w The wire
	AMCAX_API void Init(const TopoWire& w);

	/// @brief Initialize the explorer by a wire and a face
	/// @param w The wire
	/// @param f The face
	AMCAX_API void Init(const TopoWire& w, const TopoFace& f);

	/// @brief Initialize the explorer by a wire and a face with UV bounds
	/// @param w The wire
	/// @param f The face
	/// @param uMin The u lower bound
	/// @param uMax The u upper bound
	/// @param vMin The v lower bound
	/// @param vMax The v upper bound
	AMCAX_API void Init(const TopoWire& w, const TopoFace& f, double uMin, double uMax, double vMin, double vMax);

	/// @brief Does the explorer have more edges
	/// @return True if there is a current edge
	[[nodiscard]] AMCAX_API bool More() const noexcept;

	/// @brief Move to the next edge
	AMCAX_API void Next();

	/// @brief Get the current edge
	/// @return The current edge
	[[nodiscard]] AMCAX_API const TopoEdge& Current() const noexcept;

	/// @brief Get the orientation of the current edge
	/// @return The orientation of the current edge
	[[nodiscard]] AMCAX_API OrientationType Orientation() const;

	/// @brief Get the vertex connecting the previous edge
	/// @return The current vertex
	[[nodiscard]] AMCAX_API const TopoVertex& CurrentVertex() const noexcept;

	/// @brief Clear the explorer
	AMCAX_API void Clear() noexcept;

private:
	/// @brief Shape map
	std::unordered_map<TopoShape, std::list<TopoEdge>> shapemap;

	/// @brief Current edge
	TopoEdge edge;

	/// @brief Current vertex
	TopoVertex vertex;

	/// @brief Parent face
	TopoFace face;

	/// @brief Doubles
	std::unordered_set<TopoShape> doubles;

	/// @brief Reverse orientation
	bool reverse = false;

	/// @brief U tolerance
	double tolU = 0.0;

	/// @brief V tolerance
	double tolV = 0.0;
};
} // namespace AMCAX
