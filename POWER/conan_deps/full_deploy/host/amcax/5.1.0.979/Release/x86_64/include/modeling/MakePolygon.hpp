/// @file      MakePolygon.hpp
/// @brief     Class of making a polygon
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <common/PointT.hpp>
#include <modeling/MakeShape.hpp>

namespace AMCAX
{
#ifndef DOXYGEN_SKIP
class MakePolygonImpl;
class TopoEdge;
class TopoVertex;
class TopoWire;
#endif

/// @brief Class of making a polygon
class AMCAX_CLASS_API MakePolygon : public MakeShape
{
public:
	/// @brief Default constructor
	AMCAX_API MakePolygon();

	/// @brief Construct from two points
	/// @param p1 The first point
	/// @param p2 The second point
	AMCAX_API MakePolygon(const Point3& p1, const Point3& p2);

	/// @brief Construct from three points
	/// @param p1 The first point
	/// @param p2 The second point
	/// @param p3 The third point
	/// @param close Whether the polygon is closed
	AMCAX_API MakePolygon(const Point3& p1, const Point3& p2, const Point3& p3, bool close = false);

	/// @brief Construct from four points
	/// @param p1 The first point
	/// @param p2 The second point
	/// @param p3 The third point
	/// @param p4 The fourth point
	/// @param close Whether the polygon is closed
	AMCAX_API MakePolygon(const Point3& p1, const Point3& p2, const Point3& p3, const Point3& p4, bool close = false);

	/// @brief Construct from two vertices
	/// @param v1 The first vertex
	/// @param v2 The second vertex
	AMCAX_API MakePolygon(const TopoVertex& v1, const TopoVertex& v2);

	/// @brief Construct from three vertices
	/// @param v1 The first vertex
	/// @param v2 The second vertex
	/// @param v3 The third vertex
	/// @param close Whether the polygon is closed
	AMCAX_API MakePolygon(const TopoVertex& v1, const TopoVertex& v2, const TopoVertex& v3, bool close = false);

	/// @brief Construct fron four vertices
	/// @param v1 The first vertex
	/// @param v2 The second vertex
	/// @param v3 The third vertex
	/// @param v4 The fourth vertex
	/// @param close Whether the polygon is closed
	AMCAX_API MakePolygon(const TopoVertex& v1, const TopoVertex& v2, const TopoVertex& v3, const TopoVertex& v4, bool close = false);

	/// @brief Add a new point to the polygon
	/// @param p The point
	AMCAX_API void Add(const Point3& p);

	/// @brief Add a new vertex to the polygon
	/// @param v The vertex
	AMCAX_API void Add(const TopoVertex& v);

	/// @brief Check if the last added vertex is added successfully
	/// @return True if the last added vertex does not coincide with the previous vertex
	[[nodiscard]] AMCAX_API bool Added() const noexcept;

	/// @brief Close the polygon
	AMCAX_API void Close();

	/// @brief Get the first vertex
	/// @return The first vertex
	[[nodiscard]] AMCAX_API const TopoVertex& FirstVertex() const noexcept;

	/// @brief Get the last vertex
	/// @return The last vertex
	[[nodiscard]] AMCAX_API const TopoVertex& LastVertex() const noexcept;

	[[nodiscard]] AMCAX_API bool IsDone() const noexcept override;

	/// @brief Get the last constructed edge
	/// @return The last constructed edge
	[[nodiscard]] AMCAX_API const TopoEdge& Edge() const noexcept;

	/// @brief Get the last constructed edge
	/// @return The last constructed edge
	[[nodiscard]] AMCAX_API operator TopoEdge() const noexcept;

	/// @brief Get the polygon result
	/// @return The polygon wire
	[[nodiscard]] AMCAX_API const TopoWire& Wire();

	/// @brief Get the polygon result
	/// @return The polygon wire
	[[nodiscard]] AMCAX_API operator TopoWire();

private:
	std::shared_ptr<MakePolygonImpl> makePolygon;
};
} // namespace AMCAX
