/// @file      AdaptorGeom3Surface.hpp
/// @brief     Class of adaptor of 3D geometric surfaces
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <geometry/Adaptor3Surface.hpp>

namespace AMCAX
{
class BSplineSurfaceCache;
class Geom3EvaluatorSurface;
class Geom3Surface;

/// @brief Class of adaptor of 3D geometric surfaces
class AMCAX_CLASS_API AdaptorGeom3Surface : public Adaptor3Surface
{
public:
	/// @brief Default constructor
	AdaptorGeom3Surface() noexcept = default;

	/// @brief Construct from a surface
	/// @param s The surface
	AMCAX_API explicit AdaptorGeom3Surface(const std::shared_ptr<Geom3Surface>& s);

	/// @brief Construct from a surface, bounds of parameters, and tolerances
	/// @param s The surface
	/// @param puFirst The first u parameter
	/// @param puLast The last u parameter
	/// @param pvFirst The first v parameter
	/// @param pvLast The last v parameter
	/// @param toleranceU The u tolerance
	/// @param toleranceV The v tolerance
	AMCAX_API AdaptorGeom3Surface(const std::shared_ptr<Geom3Surface>& s, double puFirst, double puLast, double pvFirst, double pvLast, double toleranceU = 0.0, double toleranceV = 0.0);

	AMCAX_API std::shared_ptr<Adaptor3Surface> ShallowCopy() const override;

	/// @brief Load a surface
	/// @param s The surface
	AMCAX_API void Load(const std::shared_ptr<Geom3Surface>& s);

	/// @brief Load a surface, bounds of parameters and tolerances
	/// @param s The surface
	/// @param puFirst The first u parameter
	/// @param puLast The last u parameter
	/// @param pvFirst The first v parameter
	/// @param pvLast The last v parameter
	/// @param toleranceU The u tolerance
	/// @param toleranceV The v tolerance
	AMCAX_API void Load(const std::shared_ptr<Geom3Surface>& s, double puFirst, double puLast, double pvFirst, double pvLast, double toleranceU = 0.0, double toleranceV = 0.0);

	/// @brief Get the base surface
	/// @return The base surface
	AMCAX_API const std::shared_ptr<Geom3Surface>& Surface() const noexcept;

	AMCAX_API double FirstUParameter() const override;
	AMCAX_API double LastUParameter() const override;
	AMCAX_API double FirstVParameter() const override;
	AMCAX_API double LastVParameter() const override;
	AMCAX_API ContinuityType UContinuity() const override;
	AMCAX_API ContinuityType VContinuity() const override;
	AMCAX_API int NUIntervals(ContinuityType c) const override;
	AMCAX_API int NVIntervals(ContinuityType c) const override;
	AMCAX_API void UIntervals(std::vector<double>& t, ContinuityType c) const override;
	AMCAX_API void VIntervals(std::vector<double>& t, ContinuityType c) const override;
	AMCAX_API std::shared_ptr<Adaptor3Surface> UTrim(double first, double last, double tol) const override;
	AMCAX_API std::shared_ptr<Adaptor3Surface> VTrim(double first, double last, double tol) const override;
	AMCAX_API bool IsUClosed() const override;
	AMCAX_API bool IsVClosed() const override;
	AMCAX_API bool IsUPeriodic() const override;
	AMCAX_API double UPeriod() const override;
	AMCAX_API bool IsVPeriodic() const override;
	AMCAX_API double VPeriod() const override;
	AMCAX_API Point3 Value(double u, double v) const override;
	AMCAX_API void D0(double u, double v, Point3& p) const override;
	AMCAX_API void D1(double u, double v, Point3& p, Vector3& d1u, Vector3& d1v) const override;
	AMCAX_API void D2(double u, double v, Point3& p, Vector3& d1u, Vector3& d1v, Vector3& d2uu, Vector3& d2uv, Vector3& d2vv) const override;
	AMCAX_API void D3(double u, double v, Point3& p, Vector3& d1u, Vector3& d1v, Vector3& d2uu, Vector3& d2uv, Vector3& d2vv, Vector3& d3uuu, Vector3& d3uuv, Vector3& d3uvv, Vector3& d3vvv) const override;
	AMCAX_API Vector3 DN(double u, double v, int nu, int nv) const override;
	AMCAX_API double UResolution(double r3d) const override;
	AMCAX_API double VResolution(double r3d) const override;
	AMCAX_API SurfaceType Type() const override;
	AMCAX_API Plane GetPlane() const override;
	AMCAX_API Cylinder GetCylinder() const override;
	AMCAX_API Cone GetCone() const override;
	AMCAX_API Sphere GetSphere() const override;
	AMCAX_API Torus GetTorus() const override;
	AMCAX_API int UDegree() const override;
	AMCAX_API int NUPoles() const override;
	AMCAX_API int VDegree() const override;
	AMCAX_API int NVPoles() const override;
	AMCAX_API int NUKnots() const override;
	AMCAX_API int NVKnots() const override;
	AMCAX_API bool IsURational() const override;
	AMCAX_API bool IsVRational() const override;
	AMCAX_API std::shared_ptr<Geom3BezierSurface> Bezier() const override;
	AMCAX_API std::shared_ptr<Geom3BSplineSurface> BSpline() const override;
	AMCAX_API Axis3 AxeOfRevolution() const override;
	AMCAX_API Direction3 Direction() const override;
	AMCAX_API std::shared_ptr<Adaptor3Curve> BasisCurve() const override;
	AMCAX_API std::shared_ptr<Adaptor3Surface> BasisSurface() const override;
	AMCAX_API double OffsetValue() const override;

private:
	static void Span(int side, int& iStart, int& iEnd, int first, int last) noexcept;
	bool IfUVBound(double u, double v, int& ideb, int& ifin, int& iVdeb, int& iVfin, int uSide, int vSide) const;
	void RebuildCache(double u, double v) const;

protected:
	/// @brief Base surface
	std::shared_ptr<Geom3Surface> surface;

	/// @brief First U parameter
	double uFirst = 0.0;

	/// @brief Last U parameter
	double uLast = 0.0;

	/// @brief First V parameter
	double vFirst = 0.0;

	/// @brief Last V parameter
	double vLast = 0.0;

	/// @brief Tolerance along U direction
	double tolU = 0.0;

	/// @brief Tolerance along V direction
	double tolV = 0.0;

	/// @brief B spline surface
	std::shared_ptr<Geom3BSplineSurface> bSplineSurface;

	/// @brief Cache for fast computation of B spline surface
	mutable std::shared_ptr<BSplineSurfaceCache> surfaceCache;

	/// @brief Type of surface
	SurfaceType type = SurfaceType::Undefined;

	/// @brief Evaluator
	std::shared_ptr<Geom3EvaluatorSurface> nestedEvaluator;
};
} // namespace AMCAX
