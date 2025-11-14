/// @file      ComputePointsTangentialDeflection.hpp
/// @brief     Class of sampling points on a curve by controlling the points with bounded tangential deflection conditions
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <vector>

#include <common/PointT.hpp>

namespace AMCAX
{
class Adaptor2Curve;
class Adaptor3Curve;

/// @brief Class of sampling points on a curve by controlling the points with bounded tangential deflection conditions
/// @details The sampling points satisfy two conditions:
///          ||P3P1 x P3P2|| / ||P3P1||||P3P2|| < angular deflection (the sine of exterior angle)
///          and ||P1P2 x P1P3|| / ||P1P2|| < curvature deflection (the distance from P3 to line P1P2),
///          where P1 and P2 are the successive sampling points with parameters u1 and u2, P3 is the point at (u1 + u2) / 2.
class ComputePointsTangentialDeflection
{
public:
	/// @brief Default constructor
	ComputePointsTangentialDeflection() noexcept = default;

	/// @brief Sample points on a 3D curve with given angular and curvature deflection
	/// @param c The curve
	/// @param angularDeflection The angular deflection
	/// @param curvatureDeflection The curvature deflection
	/// @param minimumNPoints The minimum number of points
	/// @param tol The tolerance
	/// @param minimumLength The minimum length between two successive points
	AMCAX_API ComputePointsTangentialDeflection(const Adaptor3Curve& c, double angularDeflection, double curvatureDeflection, int minimumNPoints = 2, double tol = 1.0e-9, double minimumLength = 1.0e-7);

	/// @brief Sample points on a 2D curve with given angular and curvature deflection
	/// @param c The curve
	/// @param angularDeflection The angular deflection
	/// @param curvatureDeflection The curvature deflection
	/// @param minimumNPoints The minimum number of points
	/// @param tol The tolerance
	/// @param minimumLength The minimum length between two successive points
	AMCAX_API ComputePointsTangentialDeflection(const Adaptor2Curve& c, double angularDeflection, double curvatureDeflection, int minimumNPoints = 2, double tol = 1.0e-9, double minimumLength = 1.0e-7);

	/// @brief Sample points on a bounded 3D curve with given angular and curvature deflection
	/// @param c The curve
	/// @param firstParameter The first parameter of the curve
	/// @param lastParameter The last parameter of the curve
	/// @param angularDeflection The angular deflection
	/// @param curvatureDeflection The curvature deflection
	/// @param minimumNPoints The minimum number of points
	/// @param tol The tolerance
	/// @param minimumLength The minimum length between two successive points
	AMCAX_API ComputePointsTangentialDeflection(const Adaptor3Curve& c, double firstParameter, double lastParameter, double angularDeflection, double curvatureDeflection, int minimumNPoints = 2, double tol = 1.0e-9, double minimumLength = 1.0e-7);

	/// @brief Sample points on a bounded 2D curve with given angular and curvature deflection
	/// @param c The curve
	/// @param firstParameter The first parameter of the curve
	/// @param lastParameter The last parameter of the curve
	/// @param angularDeflection The angular deflection
	/// @param curvatureDeflection The curvature deflection
	/// @param minimumNPoints The minimum number of points
	/// @param tol The tolerance
	/// @param minimumLength The minimum length between two successive points
	AMCAX_API ComputePointsTangentialDeflection(const Adaptor2Curve& c, double firstParameter, double lastParameter, double angularDeflection, double curvatureDeflection, int minimumNPoints = 2, double tol = 1.0e-9, double minimumLength = 1.0e-7);

	/// @brief Initialize and sample points on a 3D curve with given angular and curvature deflection
	/// @param c The curve
	/// @param angularDeflection The angular deflection
	/// @param curvatureDeflection The curvature deflection
	/// @param minimumNPoints The minimum number of points
	/// @param tol The tolerance
	/// @param minimumLength The minimum length between two successive points
	AMCAX_API void Initialize(const Adaptor3Curve& c, double angularDeflection, double curvatureDeflection, int minimumNPoints = 2, double tol = 1.0e-9, double minimumLength = 1.0e-7);

	/// @brief Initialize and sample points on a 2D curve with given angular and curvature deflection
	/// @param c The curve
	/// @param angularDeflection The angular deflection
	/// @param curvatureDeflection The curvature deflection
	/// @param minimumNPoints The minimum number of points
	/// @param tol The tolerance
	/// @param minimumLength The minimum length between two successive points
	AMCAX_API void Initialize(const Adaptor2Curve& c, double angularDeflection, double curvatureDeflection, int minimumNPoints = 2, double tol = 1.0e-9, double minimumLength = 1.0e-7);

	/// @brief Initialize and sample points on a bounded 3D curve with given angular and curvature deflection
	/// @param c The curve
	/// @param firstParameter The first parameter of the curve
	/// @param lastParameter The last parameter of the curve
	/// @param angularDeflection The angular deflection
	/// @param curvatureDeflection The curvature deflection
	/// @param minimumNPoints The minimum number of points
	/// @param tol The tolerance
	/// @param minimumLength The minimum length between two successive points
	AMCAX_API void Initialize(const Adaptor3Curve& c, double firstParameter, double lastParameter, double angularDeflection, double curvatureDeflection, int minimumNPoints = 2, double tol = 1.0e-9, double minimumLength = 1.0e-7);

	/// @brief Initialize and sample points on a bounded 2D curve with given angular and curvature deflection
	/// @param c The curve
	/// @param firstParameter The first parameter of the curve
	/// @param lastParameter The last parameter of the curve
	/// @param angularDeflection The angular deflection
	/// @param curvatureDeflection The curvature deflection
	/// @param minimumNPoints The minimum number of points
	/// @param tol The tolerance
	/// @param minimumLength The minimum length between two successive points
	AMCAX_API void Initialize(const Adaptor2Curve& c, double firstParameter, double lastParameter, double angularDeflection, double curvatureDeflection, int minimumNPoints = 2, double tol = 1.0e-9, double minimumLength = 1.0e-7);

	/// @brief Add a sample point
	/// @param point The point
	/// @param param The parameter
	/// @param isReplace Is the new point replace the old point if the parameters coincide w.r.t. a tolerance
	/// @return The index of the added or replaced point
	AMCAX_API int AddPoint(const Point3& point, double param, bool isReplace = true);

	/// @brief Get the number of sampling points
	/// @return The number of sampling points
	[[nodiscard]] AMCAX_API int NPoints() const noexcept;

	/// @brief Get the parameter at a given index
	/// @param i The index
	/// @return The parameter of the sampling point at a given index
	[[nodiscard]] AMCAX_API double Parameter(int i) const noexcept;

	/// @brief Get the sampling parameter at a given index
	/// @param i The index
	/// @return The sampling point at a given index
	[[nodiscard]] AMCAX_API const Point3& Value(int i) const noexcept;

	/// @brief Get the angular step for the arc using linear and angular deflection
	/// @param radius The radius of the arc
	/// @param linearDeflection The linear deflection
	/// @param angularDeflection The angular deflection
	/// @param minimunLength The minimum length
	/// @return The step length
	[[nodiscard]] AMCAX_API static double ArcAngularStep(double radius, double linearDeflection, double angularDeflection, double minimunLength);

private:
	template<class AdaptorType>
	void InitializeImpl(const AdaptorType& c, double firstParameter, double lastParameter, double angularDeflection, double curvatureDeflection, int minimumNPoints, double tol, double minimumLength);
	template<class AdaptorType>
	void PerformLinear(const AdaptorType& c);
	template<class AdaptorType>
	void PerformCircular(const AdaptorType& c);
	template<class AdaptorType>
	void PerformCurve(const AdaptorType& c);
	template<class AdaptorType>
	void EvaluateDu(const AdaptorType& c, double u, Point3& p, double& du, bool& notDone) const;
	template<class AdaptorType>
	void EstimateDeflection(const AdaptorType& c, double u1, double u2, double& maxDefl, double& uMax);
	double angDef = 0.0;
	double curvDef = 0.0;
	double utol = 0.0;
	int minNPts = 0;
	double minLen = 0.0;
	double first = 0.0;
	double last = 0.0;
	std::vector<Point3> points;
	std::vector<double> params;
};
} // namespace AMCAX
