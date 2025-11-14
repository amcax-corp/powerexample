/// @file      NURBSAPIGetGeometry.hpp
/// @brief     Class of Getting not infinite curve or surface from edge or face
/// @copyright Copyright (c) 2024 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once

#include <common/Macros.hpp>
#include <memory>

namespace AMCAX
{
class Geom2Curve;
class Geom3Curve;
class TopoEdge;
class TopoFace;
class Geom3Surface;

/// @brief Class of Getting not infinite curve or surface from edge or face
class NURBSAPIGetGeometry
{
public:
	/// @brief Get not infinite curve from the edge such as part of a line
	/// @param edge The edge
	/// @return The trimmed curve
	[[nodiscard]] AMCAX_API static std::shared_ptr<Geom3Curve> GetCurve(const TopoEdge& edge);

#ifndef DOXYGEN_SKIP
	/// @brief Get not infinite pcurve from the edge such as part of a line
	/// @param edge The edge
	/// @param face The face
	/// @return The trimmed pcurve
	[[nodiscard]] AMCAX_TEST_API static std::shared_ptr<Geom2Curve> GetPCurve(const TopoEdge& edge, const TopoFace& face);
#endif

	/// @brief Get not infinite surface from the face such as part of a plane or cylinder
	/// @param face The face
	/// @return The trimmed surface
	[[nodiscard]] AMCAX_API static std::shared_ptr<Geom3Surface> GetSurface(const TopoFace& face);
};
} // namespace AMCAX
