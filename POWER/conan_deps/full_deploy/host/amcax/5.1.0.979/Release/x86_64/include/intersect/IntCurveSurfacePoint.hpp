/// @file      IntCurveSurfacePoint.hpp
/// @brief     The data structure of an interserction point between a curve and a surface
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <common/PointT.hpp>
#include <intersect/IntCurveSurfaceMacros.hpp>

namespace AMCAX
{
/// @brief The data structure of an interserction point between a curve and a surface
class IntCurveSurfacePoint
{
public:
	/// @brief Default constructor
	AMCAX_API IntCurveSurfacePoint();

	/// @brief Construct an interserction point
	/// @param p The geometry point
	/// @param uSurf The u parameter of the intersection point on the surface
	/// @param vSurf The v parameter of the intersection point on the surface
	/// @param tCurv The parameter of the intersection point on the curve
	/// @param trCurv the Transition of the intersection point
	AMCAX_API IntCurveSurfacePoint(const Point3& p, double uSurf, double vSurf, double tCurv, IntCurveSurfaceTransOnCurveType trCurv);

	/// @brief Set the fields of the interserction point
	/// @param p The geometry point
	/// @param uSurf The u parameter of the intersection point on the surface
	/// @param vSurf The v parameter of the intersection point on the surface
	/// @param tCurv The parameter of the intersection point on the curve
	/// @param trCurv the Transition of the intersection point
	AMCAX_API void SetValues(const Point3& p, double uSurf, double vSurf, double tCurv, IntCurveSurfaceTransOnCurveType trCurv);

	/// @brief Get the fields of the interserction point
	/// @param[out] p The geometry point
	/// @param[out] uSurf The u parameter of the intersection point on the surface
	/// @param[out] vSurf The v parameter of the intersection point on the surface
	/// @param[out] tCurv The parameter of the intersection point on the curve
	/// @param[out] trCurv the Transition of the intersection point
	AMCAX_API void Values(Point3& p, double& uSurf, double& vSurf, double& tCurv, IntCurveSurfaceTransOnCurveType& trCurv) const;

	/// @brief Get geometry point
	/// @return The geometry point
	[[nodiscard]] const Point3& Point() const noexcept
	{
		return mP;
	}

	/// @brief Get the u parameter of the intersection point on the surface
	/// @return The u parameter of the intersection point on the surface
	[[nodiscard]] double U() const noexcept
	{
		return uSurf;
	}

	/// @brief Get the v parameter of the intersection point on the surface
	/// @return The v parameter of the intersection point on the surface
	[[nodiscard]] double V() const noexcept
	{
		return vSurf;
	}

	/// @brief Get the w parameter of the intersection point on the curve
	/// @return The w parameter of the intersection point on the curve
	[[nodiscard]] double W() const noexcept
	{
		return tCurv;
	}

	/// @brief Get the transition of the intersection point
	/// @return The transition of the intersection point
	[[nodiscard]] IntCurveSurfaceTransOnCurveType Transition() const noexcept
	{
		return mTransOnCurv;
	}

private:
	Point3 mP;
	double uSurf;
	double vSurf;
	double tCurv;
	IntCurveSurfaceTransOnCurveType mTransOnCurv;
};

/// @brief Alias name of IntCurveSurfacePoint
using IntCurveSurfaceIntersectionPoint = IntCurveSurfacePoint;

} // namespace AMCAX
