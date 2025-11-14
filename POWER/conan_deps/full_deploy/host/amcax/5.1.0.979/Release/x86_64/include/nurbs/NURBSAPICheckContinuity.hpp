/// @file      NURBSAPICheckContinuity.hpp
/// @brief     Class of coninuity check api
/// @copyright Copyright (c) 2024 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <memory>
#include <vector>

#include <common/Macros.hpp>
#include <math/GeometryMacros.hpp>

namespace AMCAX
{
class TopoFace;
class TopoEdge;
class Geom3Curve;
class Geom3Surface;

/// @brief Class of curve or surface or face boundaries continuity check
class NURBSAPICheckContinuity
{
public:
	/// @brief Get the nearest iso-curves of the surfaces
	/// @param surf1 The first surface
	/// @param surf2 The second surface
	/// @return {is iso-curve 1 a uiso-curve, is iso-curve 1 a front iso-curve, is iso-curve 2 a uiso-curve, is iso-curve 2 a front iso-curve}
	[[nodiscard]] AMCAX_API static std::tuple<bool, bool, bool, bool> GetNearestSurfaceBoundaries(const std::shared_ptr<Geom3Surface>& surf1, const std::shared_ptr<Geom3Surface>& surf2);

	/// @brief Judge the continuity of two surface boundaries
	/// @param surf1 The first surface
	/// @param isUIso1 If the boundary of the first surface is a u-isocurve
	/// @param isFront1 If the boundary of the first surface is front isocurve
	/// @param surf2 The second surface
	/// @param isUIso2 If the boundary of the second surface is a u-isocurve
	/// @param isFront2 If the boundary of the second surface is front isocurve
	/// @param cont Continuity type
	/// @param tol The tolerances of each continuity level
	/// @param nsample The number of sample points to check continuity
	/// @param isConsiderReverse If the normal reversed surface continuity is considered
	/// @return Whether the error of continuity is smaller than the tolerances
	[[nodiscard]] AMCAX_API static bool JudgeSurfaceContinuity(const std::shared_ptr<Geom3Surface>& surf1, bool isUIso1, bool isFront1, const std::shared_ptr<Geom3Surface>& surf2, bool isUIso2, bool isFront2, ContinuityType cont, const std::vector<double>& tol, int nsample, bool isConsiderReverse = false);

	/// @brief Get the nearest edges of the faces
	/// @param face1 The face 1
	/// @param face2 The face 2
	/// @return The nearest edges
	[[nodiscard]] AMCAX_API static std::pair<TopoEdge, TopoEdge> GetNearestEdges(const TopoFace& face1, const TopoFace& face2);

	/// @brief Judge the continuity of two face boundaries
	/// @param face1 The first face
	/// @param edge1 The given boundary edge on the first face
	/// @param face2 The second face
	/// @param edge2 The given boundary edge on the second face
	/// @param cont Continuity type
	/// @param tol The tolerances of each continuity level
	/// @param nsample The number of sample points to check continuity
	/// @param isConsiderReverse If the normal reversed surface continuity is considered
	/// @return Whether the error of continuity is smaller than the tolerances
	[[nodiscard]] AMCAX_API static bool JudgeFaceContinuity(const TopoFace& face1, const TopoEdge& edge1, const TopoFace& face2, const TopoEdge& edge2, ContinuityType cont, const std::vector<double>& tol, int nsample, bool isConsiderReverse = false);

	/// @brief Judge the continuity of two curves
	/// @param curve1 The first curve
	/// @param isFront1 Whether the start point or the end point of the first curve is to be checked
	/// @param curve2 The second curve
	/// @param isFront2 Whether the start point or the end point of the second curve is to be checked
	/// @param tol The tolerances of each continuity level
	/// @param cont Continuity type
	/// @return Whether the error of continuity is smaller than the tolerances
	[[nodiscard]] AMCAX_API static bool JudgeCurveContinuity(const std::shared_ptr<Geom3Curve>& curve1, bool isFront1, const std::shared_ptr<Geom3Curve>& curve2, bool isFront2, const std::vector<double>& tol, ContinuityType cont);
};
} // namespace AMCAX
