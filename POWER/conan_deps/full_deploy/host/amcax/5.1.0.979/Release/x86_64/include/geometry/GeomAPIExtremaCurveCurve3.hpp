/// @file      GeomAPIExtremaCurveCurve3.hpp
/// @brief     Class of computing extremal points for two 3D curves
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <memory>

#include <common/PointT.hpp>

namespace AMCAX
{
class AdaptorGeom3Curve;
#ifndef DOXYGEN_SKIP
template<int>
class ExtremaCurveCurve;
#endif
class Geom3Curve;

/// @brief Class of computing extremal points for two 3D curves
class GeomAPIExtremaCurveCurve3
{
public:
	/// @brief Default constructor
	AMCAX_API GeomAPIExtremaCurveCurve3();

	/// @brief Construct from two curves
	/// @param c1 The first curve
	/// @param c2 The second curve
	AMCAX_API GeomAPIExtremaCurveCurve3(const std::shared_ptr<Geom3Curve>& c1, const std::shared_ptr<Geom3Curve>& c2);

	/// @brief Construct from two curves and their parameter bounds
	/// @param c1 The first curve
	/// @param c2 The second curve
	/// @param u1min The first parameter of the first curve
	/// @param u1max The last parameter of the first curve
	/// @param u2min The first parameter of the second curve
	/// @param u2max The last parameter of the second curve
	AMCAX_API GeomAPIExtremaCurveCurve3(const std::shared_ptr<Geom3Curve>& c1, const std::shared_ptr<Geom3Curve>& c2, double u1min, double u1max, double u2min, double u2max);

	/// @brief Initialize and construct from two curves
	/// @param c1 The first curve
	/// @param c2 The second curve
	AMCAX_API void Init(const std::shared_ptr<Geom3Curve>& c1, const std::shared_ptr<Geom3Curve>& c2);

	/// @brief Initialize and construct from two curves and their parameter bounds
	/// @param c1 The first curve
	/// @param c2 The second curve
	/// @param u1min The first parameter of the first curve
	/// @param u1max The last parameter of the first curve
	/// @param u2min The first parameter of the second curve
	/// @param u2max The last parameter of the second curve
	AMCAX_API void Init(const std::shared_ptr<Geom3Curve>& c1, const std::shared_ptr<Geom3Curve>& c2, double u1min, double u1max, double u2min, double u2max);

	/// @brief Get the number of extrema
	/// @return The number of extrema
	[[nodiscard]] AMCAX_API int NExtrema() const;

	/// @brief Get the number of extrema
	/// @return The number of extrema
	[[nodiscard]] AMCAX_API operator int() const;

	/// @brief Get the extremal points at a given index
	/// @param[in] index The index
	/// @param[out] p1 The extremal point on the first curve
	/// @param[out] p2 The extremal point on the second curve
	AMCAX_API void Points(int index, Point3& p1, Point3& p2) const;

	/// @brief Get the parameters of the extrema at a given index
	/// @param[in] index The index
	/// @param[out] u1 The parameter of the extremal point on the first curve
	/// @param[out] u2 The parameter of the extremal point on the second curve
	AMCAX_API void Parameters(int index, double& u1, double& u2) const;

	/// @brief Get the extremal distance at a given index
	/// @param index The index
	/// @return The extremal distance
	[[nodiscard]] AMCAX_API double Distance(int index) const;

	/// @brief Are the curves parallel
	/// @return True if two curves are parallel
	[[nodiscard]] AMCAX_API bool IsParallel() const;

	/// @brief Get the nearest points
	/// @param[out] p1 The nearest point on the first curve
	/// @param[out] p2 The nearest point on the second curve
	AMCAX_API void NearestPoints(Point3& p1, Point3& p2) const;

	/// @brief Get the parameters of the nearest points
	/// @param[out] u1 The parameter of the nearest point on the first curve
	/// @param[out] u2 The parameter of the nearest point on the second curve
	AMCAX_API void LowerDistanceParameters(double& u1, double& u2) const;

	/// @brief Get the distance of the nearest points
	/// @return The nearest distance
	[[nodiscard]] AMCAX_API double LowerDistance() const;

	/// @brief Get the distance of the nearest points
	/// @return The nearest distance
	[[nodiscard]] AMCAX_API operator double() const;

#ifndef DOXYGEN_SKIP

	/// @internal
	[[nodiscard]] const ExtremaCurveCurve<3>& Extrema() const noexcept;

#endif

	/// @brief Get the total nearest points with taking end points into accounts
	/// @param[out] p1 The nearest point on the first curve
	/// @param[out] p2 The nearest point on the second curve
	/// @return True if the nearest points are finite
	AMCAX_API bool TotalNearestPoints(Point3& p1, Point3& p2);

	/// @brief Get the parameters of the total nearest points with taking end points into accounts
	/// @param[out] u1 The parameter of the nearest point on the first curve
	/// @param[out] u2 The parameter of the nearest point on the second curve
	/// @return True if the nearest points are finite
	AMCAX_API bool TotalLowerDistanceParameters(double& u1, double& u2);

	/// @brief Get the distance of the total nearest points with taking end points into accounts
	/// @return The total nearest distance
	[[nodiscard]] AMCAX_API double TotalLowerDistance();

private:
	void TotalPerform();
	bool done = false;
	int index = -1;
	std::shared_ptr<ExtremaCurveCurve<3>> ecc;
	std::shared_ptr<AdaptorGeom3Curve> c1;
	std::shared_ptr<AdaptorGeom3Curve> c2;
	bool totalExt = false;
	bool isInfinite = false;
	double totalDist = 0.0;
	Point3 totalPoints[2];
	double totalParams[2] = {};
};
} // namespace AMCAX
