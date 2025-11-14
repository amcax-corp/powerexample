/// @file      BRepAdaptorSurface.hpp
/// @brief     Class of adaptor of 3D surfaces in B-Rep
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <geometry/AdaptorGeom3Surface.hpp>
#include <topology/TopoFace.hpp>

namespace AMCAX
{
/// @brief Class of adaptor of 3D surfaces in B-Rep
class AMCAX_CLASS_API BRepAdaptorSurface : public Adaptor3Surface
{
public:
	/// @brief Default constructor
	AMCAX_API BRepAdaptorSurface() noexcept = default;

	/// @brief Construct from a face
	/// @param f The face
	/// @param r Determine whether surface is restricted by edges
	AMCAX_API explicit BRepAdaptorSurface(const TopoFace& f, bool r = true);

	[[nodiscard]] AMCAX_API std::shared_ptr<Adaptor3Surface> ShallowCopy() const override;

	/// @brief Initialize from a face
	/// @param f The face
	/// @param restriction Determine whether surface is restricted by edges
	AMCAX_API void Initialize(const TopoFace& f, bool restriction = true);

	/// @brief Get the surface
	/// @return The surface
	[[nodiscard]] AMCAX_API const AdaptorGeom3Surface& Surface() const noexcept;

	/// @brief Get the surface
	/// @return The surface
	[[nodiscard]] AMCAX_API AdaptorGeom3Surface& ChangeSurface() noexcept;

	/// @brief Get the transformation
	/// @return The transformation
	[[nodiscard]] AMCAX_API const Transformation3& Transformation() const noexcept;

	/// @brief Get the face
	/// @return The face
	[[nodiscard]] AMCAX_API const TopoFace& Face() const noexcept;

	/// @brief Get the tolerance of the face
	/// @return The tolerance
	[[nodiscard]] AMCAX_API double Tolerance() const;

	[[nodiscard]] AMCAX_API double FirstUParameter() const override;
	[[nodiscard]] AMCAX_API double LastUParameter() const override;
	[[nodiscard]] AMCAX_API double FirstVParameter() const override;
	[[nodiscard]] AMCAX_API double LastVParameter() const override;
	[[nodiscard]] AMCAX_API ContinuityType UContinuity() const override;
	[[nodiscard]] AMCAX_API ContinuityType VContinuity() const override;
	[[nodiscard]] AMCAX_API int NUIntervals(ContinuityType c) const override;
	[[nodiscard]] AMCAX_API int NVIntervals(ContinuityType c) const override;
	AMCAX_API void UIntervals(std::vector<double>& t, ContinuityType c) const override;
	AMCAX_API void VIntervals(std::vector<double>& t, ContinuityType c) const override;
	[[nodiscard]] AMCAX_API std::shared_ptr<Adaptor3Surface> UTrim(double first, double last, double tol) const override;
	[[nodiscard]] AMCAX_API std::shared_ptr<Adaptor3Surface> VTrim(double first, double last, double tol) const override;
	[[nodiscard]] AMCAX_API bool IsUClosed() const override;
	[[nodiscard]] AMCAX_API bool IsVClosed() const override;
	[[nodiscard]] AMCAX_API bool IsUPeriodic() const override;
	[[nodiscard]] AMCAX_API double UPeriod() const override;
	[[nodiscard]] AMCAX_API bool IsVPeriodic() const override;
	[[nodiscard]] AMCAX_API double VPeriod() const override;
	[[nodiscard]] AMCAX_API Point3 Value(double u, double v) const override;
	AMCAX_API void D0(double u, double v, Point3& p) const override;
	AMCAX_API void D1(double u, double v, Point3& p, Vector3& d1u, Vector3& d1v) const override;
	AMCAX_API void D2(double u, double v, Point3& p, Vector3& d1u, Vector3& d1v, Vector3& d2uu, Vector3& d2uv, Vector3& d2vv) const override;
	AMCAX_API void D3(double u, double v, Point3& p, Vector3& d1u, Vector3& d1v, Vector3& d2uu, Vector3& d2uv, Vector3& d2vv, Vector3& d3uuu, Vector3& d3uuv, Vector3& d3uvv, Vector3& d3vvv) const override;
	[[nodiscard]] AMCAX_API Vector3 DN(double u, double v, int nu, int nv) const override;
	[[nodiscard]] AMCAX_API double UResolution(double r3d) const override;
	[[nodiscard]] AMCAX_API double VResolution(double r3d) const override;
	[[nodiscard]] AMCAX_API SurfaceType Type() const override;
	[[nodiscard]] AMCAX_API Plane GetPlane() const override;
	[[nodiscard]] AMCAX_API Cylinder GetCylinder() const override;
	[[nodiscard]] AMCAX_API Cone GetCone() const override;
	[[nodiscard]] AMCAX_API Sphere GetSphere() const override;
	[[nodiscard]] AMCAX_API Torus GetTorus() const override;
	[[nodiscard]] AMCAX_API int UDegree() const override;
	[[nodiscard]] AMCAX_API int NUPoles() const override;
	[[nodiscard]] AMCAX_API int VDegree() const override;
	[[nodiscard]] AMCAX_API int NVPoles() const override;
	[[nodiscard]] AMCAX_API int NUKnots() const override;
	[[nodiscard]] AMCAX_API int NVKnots() const override;
	[[nodiscard]] AMCAX_API bool IsURational() const override;
	[[nodiscard]] AMCAX_API bool IsVRational() const override;
	[[nodiscard]] AMCAX_API std::shared_ptr<Geom3BezierSurface> Bezier() const override;
	[[nodiscard]] AMCAX_API std::shared_ptr<Geom3BSplineSurface> BSpline() const override;
	[[nodiscard]] AMCAX_API Axis3 AxeOfRevolution() const override;
	[[nodiscard]] AMCAX_API Direction3 Direction() const override;
	[[nodiscard]] AMCAX_API std::shared_ptr<Adaptor3Curve> BasisCurve() const override;
	[[nodiscard]] AMCAX_API std::shared_ptr<Adaptor3Surface> BasisSurface() const override;
	[[nodiscard]] AMCAX_API double OffsetValue() const override;

private:
	AdaptorGeom3Surface surface;
	Transformation3 transformation;
	TopoFace face;
};
} // namespace AMCAX
