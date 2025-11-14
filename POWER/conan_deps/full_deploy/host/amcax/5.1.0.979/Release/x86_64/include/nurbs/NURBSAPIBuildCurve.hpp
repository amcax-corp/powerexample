/// @file      NURBSAPIBuildCurve.hpp
/// @brief     Class of NURBS curve building
/// @copyright Copyright (c) 2024 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <memory>
#include <vector>

#include <common/PointT.hpp>

namespace AMCAX
{
class Geom3BSplineCurve;

/// @brief Class of building NURBS curve
/// @details This class computes the result NURBS curve of construction infomation including given poles, target degree and isPeriodic.
class NURBSAPIBuildCurve
{
public:
	/// @brief Build BSpline curve
	/// @param poles Curve poles. If it is a periodic curve, don't include the point at the end that repeats the first point
	/// @param degree The curve degree
	/// @param isPeriodic Whether the curve is periodic or not
	/// @return The built curve. If building curve is failed, return nullptr
	[[nodiscard]] AMCAX_API static std::shared_ptr<Geom3BSplineCurve> BuildCurve(const std::vector<Point3>& poles, int degree, bool isPeriodic);

	/// @brief Build NURBS curve
	/// @param poles Curve poles. If it is a periodic curve, don't include the point at the end that repeats the first point
	/// @param weights Curve weights
	/// @param degree The curve degree
	/// @param isPeriodic Whether the curve is periodic or not
	/// @return The built curve. If building curve is failed, return nullptr
	[[nodiscard]] AMCAX_API static std::shared_ptr<Geom3BSplineCurve> BuildCurve(const std::vector<Point3>& poles, const std::vector<double>& weights, int degree, bool isPeriodic);

	/// @brief Given the number of the control points, calculate the maximum valide degree of a BSpline curve
	/// @param npoles The number of control points
	/// @param isPeriodic Whether the curve is periodic
	/// @return The maximum valid degree
	[[nodiscard]] AMCAX_API static int ValidMaxDegree(int npoles, bool isPeriodic);

	/// @brief Given the BSpline curve degree, calculate the minimum valide number of the poles of a BSpline curve
	/// @param degree The BSpline curve degree
	/// @param isPeriodic Whether the curve is periodic
	/// @return The minimum valid number of the poles
	[[nodiscard]] AMCAX_API static int ValidMinNPoles(int degree, bool isPeriodic);
};
} // namespace AMCAX
