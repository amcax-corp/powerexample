/// @file      Adaptor3CurveOnSurface.hpp
/// @brief     Class of adaptor of 3D curves on surface
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <geometry/Adaptor3Curve.hpp>

namespace AMCAX
{
class Adaptor2Curve;
class Adaptor3Surface;

/// @brief Class of adaptor of 3D curves on surface
class AMCAX_CLASS_API Adaptor3CurveOnSurface : public Adaptor3Curve
{
public:
	/// @brief Default constructor
	Adaptor3CurveOnSurface() noexcept = default;

	/// @brief Construct from a surface
	/// @param s The surface
	AMCAX_API explicit Adaptor3CurveOnSurface(const std::shared_ptr<Adaptor3Surface>& s);

	/// @brief Construct from a curve on the parameter domain of a surface
	/// @param c The 2D curve
	/// @param s The 3D surface
	AMCAX_API Adaptor3CurveOnSurface(const std::shared_ptr<Adaptor2Curve>& c, const std::shared_ptr<Adaptor3Surface>& s);

	AMCAX_API std::shared_ptr<Adaptor3Curve> ShallowCopy() const override;

	/// @brief Load a surface
	/// @param s The surface
	AMCAX_API void Load(const std::shared_ptr<Adaptor3Surface>& s);

	/// @brief Load a 2D curve
	/// @param c The 2D curve
	AMCAX_API void Load(const std::shared_ptr<Adaptor2Curve>& c);

	/// @brief Load a 2D curve and a surface
	/// @param c The 2D curve
	/// @param s The surface
	AMCAX_API void Load(const std::shared_ptr<Adaptor2Curve>& c, const std::shared_ptr<Adaptor3Surface>& s);

	/// @brief Get the curve
	/// @return The curve
	AMCAX_API const std::shared_ptr<Adaptor2Curve>& GetCurve() const noexcept;

	/// @brief Get the surface
	/// @return The surface
	AMCAX_API const std::shared_ptr<Adaptor3Surface>& GetSurface() const noexcept;

	AMCAX_API double FirstParameter() const override;
	AMCAX_API double LastParameter() const override;
	AMCAX_API ContinuityType Continuity() const override;
	AMCAX_API int NIntervals(ContinuityType c) const override;
	AMCAX_API void Intervals(std::vector<double>& t, ContinuityType c) const override;
	AMCAX_API std::shared_ptr<Adaptor3Curve> Trim(double first, double last, double tol) const override;
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
	void EvalKPart();
	void EvalFirstLastSurf();
	void LocatePart(const Point2& uv, const Vector2& duv, const std::shared_ptr<Adaptor3Surface>& s, Point2& leftBottom, Point2& rightTop) const;
	bool LocatePartRevExt(const Point2& uv, const Vector2& duv, const std::shared_ptr<Adaptor3Surface>& s, Point2& leftBottom, Point2& rightTop) const;
	bool LocatePartOffset(const Point2& uv, const Vector2& duv, const std::shared_ptr<Adaptor3Surface>& s, Point2& leftBottom, Point2& rightTop) const;

private:
	/// @brief Basis surface where the curve lies
	std::shared_ptr<Adaptor3Surface> surface;

	/// @brief Curve on 2D parameter domain
	std::shared_ptr<Adaptor2Curve> curve;

	/// @brief Type of curve
	CurveType type = CurveType::Undefined;

	/// @brief Resulting 3D circle
	Circle3 circle;

	/// @brief Resulting 3D line
	Line3 line;

	/// @brief First surface
	std::shared_ptr<Adaptor3Surface> firstSurface;

	/// @brief Last surface
	std::shared_ptr<Adaptor3Surface> lastSurface;

	/// @brief Cache of intervals
	mutable std::vector<double> intervals;

	/// @brief Integrated continuity
	mutable ContinuityType intContinuity = ContinuityType::CN;
};
} // namespace AMCAX
