/// @file      AdaptorGeom3Curve.hpp
/// @brief     Class of adaptor of 3D geometric curves
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <geometry/Adaptor3Curve.hpp>

namespace AMCAX
{
#ifndef DOXYGEN_SKIP
template<int DIM>
class BSplineCurveCache;
class Geom3Curve;
class Geom3EvaluatorCurve;
#endif

/// @brief Class of adaptor of 3D geometric curves
class AMCAX_CLASS_API AdaptorGeom3Curve : public Adaptor3Curve
{
public:
	/// @brief Default constructor
	AdaptorGeom3Curve() noexcept = default;

	/// @brief Construct from a curve
	/// @param c The curve
	AMCAX_API explicit AdaptorGeom3Curve(const std::shared_ptr<Geom3Curve>& c);

	/// @brief Construct from a curve and a range of parameter
	/// @param c The curve
	/// @param uFirst The first parameter
	/// @param uLast The last parameter
	AMCAX_API AdaptorGeom3Curve(const std::shared_ptr<Geom3Curve>& c, double uFirst, double uLast);

	AMCAX_API std::shared_ptr<Adaptor3Curve> ShallowCopy() const override;

	/// @brief Clean the curve information
	AMCAX_API void Reset() noexcept;

	/// @brief Load a curve
	/// @param c The curve
	AMCAX_API void Load(const std::shared_ptr<Geom3Curve>& c);

	/// @brief Load a curve and a range of parameter
	/// @param c The curve
	/// @param uFirst The first parameter
	/// @param uLast The last parameter
	AMCAX_API void Load(const std::shared_ptr<Geom3Curve>& c, double uFirst, double uLast);

	/// @brief Get the base curve
	/// @return The base curve
	AMCAX_API const std::shared_ptr<Geom3Curve>& Curve() const noexcept;

	AMCAX_API double FirstParameter() const noexcept override;
	AMCAX_API double LastParameter() const noexcept override;
	AMCAX_API ContinuityType Continuity() const override;
	AMCAX_API int NIntervals(ContinuityType c) const override;
	AMCAX_API void Intervals(std::vector<double>& t, ContinuityType c) const override;
	AMCAX_API std::shared_ptr<Adaptor3Curve> Trim(double uFirst, double uLast, double tol) const override;
	AMCAX_API bool IsClosed() const override;
	AMCAX_API bool IsPeriodic() const override;
	AMCAX_API double Period() const override;
	AMCAX_API Point3 Value(double u) const override;
	AMCAX_API void D0(double u, Point3& p) const override;
	AMCAX_API void D1(double u, Point3& p, Vector3& v) const override;
	AMCAX_API void D2(double u, Point3& p, Vector3& v1, Vector3& v2) const override;
	AMCAX_API void D3(double u, Point3& p, Vector3& v1, Vector3& v2, Vector3& v3) const override;
	AMCAX_API Vector3 DN(double u, int n) const override;
	AMCAX_API double Resolution(double r3d) const override;
	AMCAX_API CurveType Type() const noexcept override;
	AMCAX_API Line3 Line() const override;
	AMCAX_API Circle3 Circle() const override;
	AMCAX_API Ellipse3 Ellipse() const override;
	AMCAX_API Hyperbola3 Hyperbola() const override;
	AMCAX_API Parabola3 Parabola() const override;
	AMCAX_API int Degree() const override;
	AMCAX_API bool IsRational() const override;
	AMCAX_API int NPoles() const override;
	AMCAX_API int NKnots() const override;
	AMCAX_API std::shared_ptr<Geom3BezierCurve> Bezier() const override;
	AMCAX_API std::shared_ptr<Geom3BSplineCurve> BSpline() const override;
	AMCAX_API std::shared_ptr<Geom3OffsetCurve> OffsetCurve() const override;

private:
	ContinuityType LocalContinuity(double u1, double u2) const;
	bool IsBoundary(double u, int& spanStart, int& spanFinish) const noexcept;
	void RebuildCache(double parameter) const;

private:
	/// @brief Base curve
	std::shared_ptr<Geom3Curve> curve;

	/// @brief Type of curve
	CurveType type = CurveType::Undefined;

	/// @brief First parameter
	double first = 0.0;

	/// @brief Last parameter
	double last = 0.0;

	/// @brief B spline curve
	std::shared_ptr<Geom3BSplineCurve> bSplineCurve;

	/// @brief Cache for fast computation of B spline curve
	mutable std::shared_ptr<BSplineCurveCache<3>> curveCache;

	/// @brief Evaluator
	std::shared_ptr<Geom3EvaluatorCurve> nestedEvaluator;
};
} // namespace AMCAX
