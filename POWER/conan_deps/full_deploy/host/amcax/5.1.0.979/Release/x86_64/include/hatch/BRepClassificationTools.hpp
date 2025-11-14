/// @file      BRepClassificationTools.hpp
/// @brief     Class of tools for classification of BRep structure
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <common/PointT.hpp>
#include <topology/TopologyMacros.hpp>

namespace AMCAX
{
class TopoEdge;
class TopoFace;
class TopoSolid;

/// @brief Class of tools for classification of BRep structure, Make a one-time accurate judgment that doesn't care about performance
class BRepClassificationTools
{
public:
	/// @brief Classify whether a point is inside an edge (except for the endpoints)
	/// @details If the input tolerance is negative, then the tolerance of the edge is used
	/// @param e The edge
	/// @param p3d The point
	/// @param tol The tolerance
	/// @return True if the point is in the edge
	[[nodiscard]] AMCAX_API static bool IsPointInEdge(const TopoEdge& e, const Point3& p3d, double tol = -1.0);

	/// @brief Classify whether a point is inside an edge or at the endpoints
	/// @details If the input tolerance is negative, then the tolerance of the edge is used
	/// @param e The edge
	/// @param p3d The point
	/// @param tol The tolerance
	/// @return True if the point is in the edge or at the endpoints of the edge
	[[nodiscard]] AMCAX_API static bool IsPointInOnEdge(const TopoEdge& e, const Point3& p3d, double tol = -1.0);

	/// @brief Get the state of a UV point with a face (inside, on the boundary, or outside)
	/// @param f The face
	/// @param p2d The point
	/// @return The state of the point
	[[nodiscard]] AMCAX_API static StateType StatePointFace(const TopoFace& f, const Point2& p2d);

	/// @brief Classify whether a UV point is inside a face
	/// @param f The face
	/// @param p2d The point
	/// @return True if the point is inside the face
	[[nodiscard]] AMCAX_API static bool IsPointInFace(const TopoFace& f, const Point2& p2d);

	/// @brief Classify whether a 3D point is inside a face
	/// @details If the input tolerance is negative, then the tolerance of the face is used
	/// @param f The face
	/// @param p3d The point
	/// @param tol The tolerance
	/// @return True if the point is inside the face
	[[nodiscard]] AMCAX_API static bool IsPointInFace(const TopoFace& f, const Point3& p3d, double tol = -1.0);

	/// @brief Classify whether a 3D point is inside a face or on the edge of face
	/// @details If the input tolerance is negative, then the tolerance of the face is used
	/// @param f The face
	/// @param p3d The point
	/// @param tol The tolerance
	/// @return True if the point is in or on the face
	[[nodiscard]] AMCAX_API static bool IsPointInOnFace(const TopoFace& f, const Point3& p3d, double tol = -1.0);

	/// @brief Classify whether a UV point is inside a face or on the boundary edges
	/// @param f The face
	/// @param p2d The point
	/// @return True if the point is in or on the face
	[[nodiscard]] AMCAX_API static bool IsPointInOnFace(const TopoFace& f, const Point2& p2d);

	/// @brief Get the state of a point with a solid (inside, on the boundary, or outside)
	/// @details If the input tolerance is negative, then a default tolerance is used
	/// @param s The solid
	/// @param p3d The point
	/// @param tol The tolerance
	/// @return The state of the point
	[[nodiscard]] AMCAX_API static StateType StatePointSolid(const TopoSolid& s, const Point3& p3d, double tol = -1.0);

	/// @brief Classify whether a point is inside a solid
	/// @details If the input tolerance is negative, then a default tolerance is used
	/// @param s The solid
	/// @param p3d The point
	/// @param tol The tolerance
	/// @return True if the point is inside the solid
	[[nodiscard]] AMCAX_API static bool IsPointInSolid(const TopoSolid& s, const Point3& p3d, double tol = -1.0);

	/// @brief Classify whether a point is inside a solid or on the boundary of a solid
	/// @details If the input tolerance is negative, then a default tolerance is used
	/// @param s The solid
	/// @param p3d The point
	/// @param tol The tolerance
	/// @return True if the point is inside the solid or on the boundary of a solid
	[[nodiscard]] AMCAX_API static bool IsPointInOnSolid(const TopoSolid& s, const Point3& p3d, double tol = -1.0);

	/// @brief Classify whether the solid is bounded (The infinite point is outside)
	/// @param s The solid
	/// @return True if the solid is bounded (The infinite point is outside);
	[[nodiscard]] AMCAX_API static bool IsSolidBounded(const TopoSolid& s);
};
} // namespace AMCAX
