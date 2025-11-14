/// @file      MakeEdge2d.hpp
/// @brief     Class of making a 2d edge
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <math/CircleT.hpp>
#include <math/EllipseT.hpp>
#include <math/HyperbolaT.hpp>
#include <math/LineT.hpp>
#include <math/ParabolaT.hpp>
#include <modeling/MakeShape.hpp>
#include <topology/TopoEdge.hpp>

namespace AMCAX
{
#ifndef DOXYGEN_SKIP
class Geom2Curve;
class MakeEdge2dImpl;
class TopoVertex;
#endif

/// @brief Class of making a 2D edge
class AMCAX_CLASS_API MakeEdge2d : public MakeShape
{
public:
	/// @brief Construct from two vertices, connected by a line segment
	/// @param v1 The first vertex
	/// @param v2 The second vertex
	AMCAX_API MakeEdge2d(const TopoVertex& v1, const TopoVertex& v2);

	/// @brief Construct from two points, connected by a line segment
	/// @param p1 The first point
	/// @param p2 The second point
	AMCAX_API MakeEdge2d(const Point2& p1, const Point2& p2);

	/// @brief Construct from an infinite line
	/// @param l The line
	AMCAX_API explicit MakeEdge2d(const Line2& l);

	/// @brief Construct from a line with parameter bounds
	/// @param l The line
	/// @param p1 The first parameter
	/// @param p2 The last parameter
	AMCAX_API MakeEdge2d(const Line2& l, double p1, double p2);

	/// @brief Construct from a line with two end points
	/// @param l The line
	/// @param p1 The first point
	/// @param p2 The second point
	AMCAX_API MakeEdge2d(const Line2& l, const Point2& p1, const Point2& p2);

	/// @brief Construct from a line with two end vertices
	/// @param l The line
	/// @param v1 The first vertex
	/// @param v2 The second vertex
	AMCAX_API MakeEdge2d(const Line2& l, const TopoVertex& v1, const TopoVertex& v2);

	/// @brief Construct from a circle
	/// @param c The circle
	AMCAX_API explicit MakeEdge2d(const Circle2& c);

	/// @brief Construct from a circle with parameter bounds
	/// @param c The circle
	/// @param p1 The first parameter
	/// @param p2 The last parameter
	AMCAX_API MakeEdge2d(const Circle2& c, double p1, double p2);

	/// @brief Construct from a circle with two end points
	/// @param c The circle
	/// @param p1 The first point
	/// @param p2 The second point
	AMCAX_API MakeEdge2d(const Circle2& c, const Point2& p1, const Point2& p2);

	/// @brief Construct from a circle with two end vertices
	/// @param c The circle
	/// @param v1 The first vertex
	/// @param v2 The second vertex
	AMCAX_API MakeEdge2d(const Circle2& c, const TopoVertex& v1, const TopoVertex& v2);

	/// @brief Construct from an ellipse
	/// @param e The ellipse
	AMCAX_API explicit MakeEdge2d(const Ellipse2& e);

	/// @brief Construct from an ellipse with parameter bounds
	/// @param e The ellipse
	/// @param p1 The first parameter
	/// @param p2 The last parameter
	AMCAX_API MakeEdge2d(const Ellipse2& e, double p1, double p2);

	/// @brief Construct from an ellipse with two end points
	/// @param e The ellipse
	/// @param p1 The first point
	/// @param p2 The second point
	AMCAX_API MakeEdge2d(const Ellipse2& e, const Point2& p1, const Point2& p2);

	/// @brief Construct from an ellipse with two end vertices
	/// @param e The ellipse
	/// @param v1 The first vertex
	/// @param v2 The second vertex
	AMCAX_API MakeEdge2d(const Ellipse2& e, const TopoVertex& v1, const TopoVertex& v2);

	/// @brief Construct from a hyperbola
	/// @param h The hyperbola
	AMCAX_API explicit MakeEdge2d(const Hyperbola2& h);

	/// @brief Construct from a hyperbola with parameter bounds
	/// @param h The hyperbola
	/// @param p1 The first parameter
	/// @param p2 The last parameter
	AMCAX_API MakeEdge2d(const Hyperbola2& h, double p1, double p2);

	/// @brief Construct from a hyperbola with two end points
	/// @param h The hyperbola
	/// @param p1 The first point
	/// @param p2 The second point
	AMCAX_API MakeEdge2d(const Hyperbola2& h, const Point2& p1, const Point2& p2);

	/// @brief Construct from a hyperbola with two end vertices
	/// @param h The hyperbola
	/// @param v1 The first vertex
	/// @param v2 The second vertex
	AMCAX_API MakeEdge2d(const Hyperbola2& h, const TopoVertex& v1, const TopoVertex& v2);

	/// @brief Construct from a parabola
	/// @param p The parabola
	AMCAX_API explicit MakeEdge2d(const Parabola2& p);

	/// @brief Construct from a parabola with parameter bounds
	/// @param p The parabola
	/// @param p1 The first parameter
	/// @param p2 The last parameter
	AMCAX_API MakeEdge2d(const Parabola2& p, double p1, double p2);

	/// @brief Construct from a parabola with two end points
	/// @param p The parabola
	/// @param p1 The first point
	/// @param p2 The second point
	AMCAX_API MakeEdge2d(const Parabola2& p, const Point2& p1, const Point2& p2);

	/// @brief Construct from a parabola with two end vertices
	/// @param p The parabola
	/// @param v1 The first vertex
	/// @param v2 The second vertex
	AMCAX_API MakeEdge2d(const Parabola2& p, const TopoVertex& v1, const TopoVertex& v2);

	/// @brief Construct from a curve
	/// @param c The curve
	AMCAX_API explicit MakeEdge2d(const std::shared_ptr<Geom2Curve>& c);

	/// @brief Construct from a curve with parameter bounds
	/// @param c The curve
	/// @param p1 The first parameter
	/// @param p2 The last parameter
	AMCAX_API MakeEdge2d(const std::shared_ptr<Geom2Curve>& c, double p1, double p2);

	/// @brief Construct from a curve with two end points
	/// @param c The curve
	/// @param p1 The first point
	/// @param p2 The second point
	AMCAX_API MakeEdge2d(const std::shared_ptr<Geom2Curve>& c, const Point2& p1, const Point2& p2);

	/// @brief Construct from a curve with two end vertices
	/// @param c The curve
	/// @param v1 The first vertex
	/// @param v2 The second vertex
	AMCAX_API MakeEdge2d(const std::shared_ptr<Geom2Curve>& c, const TopoVertex& v1, const TopoVertex& v2);

	/// @brief Construct from a curve with two end points and their parameters
	/// @param c The curve
	/// @param p1 The first point
	/// @param p2 The second point
	/// @param param1 The first parameter
	/// @param param2 The last parameter
	AMCAX_API MakeEdge2d(const std::shared_ptr<Geom2Curve>& c, const Point2& p1, const Point2& p2, double param1, double param2);

	/// @brief Construct from a curve with two end vertices and their parameters
	/// @param c The curve
	/// @param v1 The first vertex
	/// @param v2 The second vertex
	/// @param param1 The first parameter
	/// @param param2 The last parameter
	AMCAX_API MakeEdge2d(const std::shared_ptr<Geom2Curve>& c, const TopoVertex& v1, const TopoVertex& v2, double param1, double param2);

	/// @brief Initialize and construct from a curve
	/// @param c The curve
	AMCAX_API void Init(const std::shared_ptr<Geom2Curve>& c);

	/// @brief Initialize and construct from a curve with parameter bounds
	/// @param c The curve
	/// @param p1 The first parameter
	/// @param p2 The last parameter
	AMCAX_API void Init(const std::shared_ptr<Geom2Curve>& c, double p1, double p2);

	/// @brief Initialize and construct from a curve with two end points
	/// @param c The curve
	/// @param p1 The first point
	/// @param p2 The second point
	AMCAX_API void Init(const std::shared_ptr<Geom2Curve>& c, const Point2& p1, const Point2& p2);

	/// @brief Initialize and construct from a curve with two end vertices
	/// @param c The curve
	/// @param v1 The first vertex
	/// @param v2 The second vertex
	AMCAX_API void Init(const std::shared_ptr<Geom2Curve>& c, const TopoVertex& v1, const TopoVertex& v2);

	/// @brief Initialize and construct from a curve with two end points and their parameters
	/// @param c The curve
	/// @param p1 The first point
	/// @param p2 The second point
	/// @param param1 The first parameter
	/// @param param2 The last parameter
	AMCAX_API void Init(const std::shared_ptr<Geom2Curve>& c, const Point2& p1, const Point2& p2, double param1, double param2);

	/// @brief Initialize and construct from a curve with two end vertices and their parameters
	/// @param c The curve
	/// @param v1 The first vertex
	/// @param v2 The second vertex
	/// @param param1 The first parameter
	/// @param param2 The last parameter
	AMCAX_API void Init(const std::shared_ptr<Geom2Curve>& c, const TopoVertex& v1, const TopoVertex& v2, double param1, double param2);

	[[nodiscard]] AMCAX_API bool IsDone() const noexcept override;

	/// @brief Get the error status
	/// @return The error status
	[[nodiscard]] AMCAX_API EdgeError Error() const noexcept;

	/// @brief Get the constructed edge
	/// @return The constructed edge
	[[nodiscard]] AMCAX_API const TopoEdge& Edge();

	/// @brief Get the constructed edge
	/// @return The constructed edge
	[[nodiscard]] AMCAX_API operator TopoEdge();

	/// @brief Get the first vertex
	/// @return The first vertex
	[[nodiscard]] AMCAX_API const TopoVertex& Vertex1() const;

	/// @brief Get the second vertex
	/// @return The second vertex
	[[nodiscard]] AMCAX_API const TopoVertex& Vertex2() const;

private:
	std::shared_ptr<MakeEdge2dImpl> makeEdge2d;
};
} // namespace AMCAX
