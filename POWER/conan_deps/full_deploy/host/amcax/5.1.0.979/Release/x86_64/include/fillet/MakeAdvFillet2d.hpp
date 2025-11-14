/// @file      MakeAdvFillet2d.hpp
/// @brief     Class of make fillet for 2D wires
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <unordered_map>

#include <fillet/ChamferFilletMacros.hpp>
#include <topology/TopoVertex.hpp>
#include <topology/TopoWire.hpp>

namespace AMCAX
{
class Geom3Plane;

/// @brief Class of make fillet for 2D wires
class MakeAdvFillet2d
{
public:
	/// @brief Construct from a wire
	/// @param wire The wire
	AMCAX_API explicit MakeAdvFillet2d(const TopoWire& wire);

	/// @brief Add a vertex to be fillet with a radius
	/// @param v The vertex to be fillet
	/// @param radius The fillet radius
	AMCAX_API void AddFillet(const TopoVertex& v, double radius);

	/// @brief Perform the algorithm
	AMCAX_API void Perform();

	/// @brief Get the resulting wire
	/// @return The resulting wire
	[[nodiscard]] AMCAX_API TopoWire Wire() const noexcept;

	/// @brief Get the resulting shape
	/// @return The resulting shape
	[[nodiscard]] AMCAX_API TopoShape Shape() const noexcept;

	/// @brief Get the error status
	/// @return The error status
	[[nodiscard]] AMCAX_API Fillet2dConstructionError Status() const noexcept;

private:
	Fillet2dConstructionError status;
	std::unordered_map<TopoVertex, double, std::hash<TopoShape>, std::equal_to<TopoShape>> verticesToFillet;
	TopoWire oriWire;
	TopoWire newWire;
	std::shared_ptr<Geom3Plane> refPlane;
};
} // namespace AMCAX
