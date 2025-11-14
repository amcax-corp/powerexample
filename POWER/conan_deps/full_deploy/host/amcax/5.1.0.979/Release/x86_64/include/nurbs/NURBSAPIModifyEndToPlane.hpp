/// @file      NURBSAPIModifyEndToPlane.hpp
/// @brief     The class of modifying NURBS curve or surface end to the plane
/// @copyright Copyright (c) 2024 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <memory>

#include <common/Macros.hpp>

namespace AMCAX
{
class Geom3BSplineCurve;
class Geom3BSplineSurface;
class Geom3Plane;

/// @brief Class of making the curve/surface end on the plane
/// @details This class computes the result curve or surface of modifying a curve or surface boundary to a plane
class NURBSAPIModifyEndToPlane
{
public:
	/// @brief Make the curve end G0 to the plane. The front or back end is determined by distance to the plane
	/// @param curve The source curve
	/// @param plane The plane
	/// @return The result curve
	[[nodiscard]] AMCAX_API static std::shared_ptr<Geom3BSplineCurve> CurveToPlaneG0(const std::shared_ptr<Geom3BSplineCurve>& curve, const std::shared_ptr<Geom3Plane>& plane);

	/// @brief Make the curve end G0 to the plane.
	/// @param curve The source curve
	/// @param isFront The front or back end to connect to the plane
	/// @param plane The plane
	/// @return The result curve
	[[nodiscard]] AMCAX_API static std::shared_ptr<Geom3BSplineCurve> CurveToPlaneG0(const std::shared_ptr<Geom3BSplineCurve>& curve, bool isFront, const std::shared_ptr<Geom3Plane>& plane);

	/// @brief Make the curve end G1 to the plane. The front or back end is determined by distance to the plane
	/// @param curve The source curve
	/// @param plane The plane
	/// @return The result curve
	[[nodiscard]] AMCAX_API static std::shared_ptr<Geom3BSplineCurve> CurveToPlaneG1(const std::shared_ptr<Geom3BSplineCurve>& curve, const std::shared_ptr<Geom3Plane>& plane);

	/// @brief Make the curve end G1 to the plane.
	/// @param curve The source curve
	/// @param isFront The front or back end is determined by distance to the plane
	/// @param plane The plane
	/// @return The result curve
	[[nodiscard]] AMCAX_API static std::shared_ptr<Geom3BSplineCurve> CurveToPlaneG1(const std::shared_ptr<Geom3BSplineCurve>& curve, bool isFront, const std::shared_ptr<Geom3Plane>& plane);

	/// @brief Make the surface end G0 to the plane. The front or back, u or v end is determined by distance to the plane
	/// @param surf The source surface
	/// @param plane The plane
	/// @return The result surface
	[[nodiscard]] AMCAX_API static std::shared_ptr<Geom3BSplineSurface> SurfaceToPlaneG0(const std::shared_ptr<Geom3BSplineSurface>& surf, const std::shared_ptr<Geom3Plane>& plane);

	/// @brief Make the surface end G0 to the plane.
	/// @param surf The source surface
	/// @param isUIso U end or v end
	/// @param isFront Front or back end
	/// @param plane The plane
	/// @return The result surface
	[[nodiscard]] AMCAX_API static std::shared_ptr<Geom3BSplineSurface> SurfaceToPlaneG0(const std::shared_ptr<Geom3BSplineSurface>& surf, bool isUIso, bool isFront, const std::shared_ptr<Geom3Plane>& plane);

	/// @brief Make the surface end G1 to the plane. The front or back, u or v end is determined by distance to the plane
	/// @param surf The source surface
	/// @param plane The plane
	/// @return The result surface
	[[nodiscard]] AMCAX_API static std::shared_ptr<Geom3BSplineSurface> SurfaceToPlaneG1(const std::shared_ptr<Geom3BSplineSurface>& surf, const std::shared_ptr<Geom3Plane>& plane);

	/// @brief Make the surface end G1 to the plane.
	/// @param surf The source surface
	/// @param isUIso U end or v end
	/// @param isFront Front or back end
	/// @param plane The plane
	/// @return The result surface
	[[nodiscard]] AMCAX_API static std::shared_ptr<Geom3BSplineSurface> SurfaceToPlaneG1(const std::shared_ptr<Geom3BSplineSurface>& surf, bool isUIso, bool isFront, const std::shared_ptr<Geom3Plane>& plane);
};
} // namespace AMCAX
