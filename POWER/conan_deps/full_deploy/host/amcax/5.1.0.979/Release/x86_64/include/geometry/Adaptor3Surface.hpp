/// @file      Adaptor3Surface.hpp
/// @brief     Base class of adaptor of 3D surfaces
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <memory>
#include <vector>

#include <math/Cone.hpp>
#include <math/Cylinder.hpp>
#include <math/GeometryMacros.hpp>
#include <math/Plane.hpp>
#include <math/Sphere.hpp>
#include <math/Torus.hpp>

namespace AMCAX
{
class Adaptor3Curve;
class Geom3BezierSurface;
class Geom3BSplineSurface;

/// @brief Base class of adpator of 3D surfaces
class AMCAX_CLASS_API Adaptor3Surface
{
public:
	/// @brief Default constructor
	Adaptor3Surface() noexcept = default;

	/// @brief Copy constructor
	Adaptor3Surface(const Adaptor3Surface&) noexcept = default;

	/// @brief Move constructor
	Adaptor3Surface(Adaptor3Surface&&) noexcept = default;

	/// @brief Destructor
	virtual ~Adaptor3Surface() noexcept = default;

	/// @brief Copy assignment
	/// @return The reference to self
	Adaptor3Surface& operator=(const Adaptor3Surface&) noexcept = default;

	/// @brief Move assignement
	/// @return The reference to self
	Adaptor3Surface& operator=(Adaptor3Surface&&) noexcept = default;

	/// @brief Get the shallow copied adaptor
	/// @return The copied adaptor
	AMCAX_API virtual std::shared_ptr<Adaptor3Surface> ShallowCopy() const = 0;

	/// @brief Get the first u parameter
	/// @return The first u parameter
	AMCAX_API virtual double FirstUParameter() const = 0;

	/// @brief Get the last u parameter
	/// @return The last u parameter
	AMCAX_API virtual double LastUParameter() const = 0;

	/// @brief Get the first v parameter
	/// @return The first v parameter
	AMCAX_API virtual double FirstVParameter() const = 0;

	/// @brief Get the last v parameter
	/// @return The last v parameter
	AMCAX_API virtual double LastVParameter() const = 0;

	/// @brief Get the type of continuity along the u direction
	/// @return The u continuity
	AMCAX_API virtual ContinuityType UContinuity() const = 0;

	/// @brief Get the type of continuity along the v direction
	/// @return The v continuity
	AMCAX_API virtual ContinuityType VContinuity() const = 0;

	/// @brief Get the number of intervals based on a given continuity along the u direction
	/// @param c The continuity
	/// @return The number of intervals
	AMCAX_API virtual int NUIntervals(ContinuityType c) const = 0;

	/// @brief Get the number of intervals based on a given continuity along the v direction
	/// @param c The continuity
	/// @return The number of intervals
	AMCAX_API virtual int NVIntervals(ContinuityType c) const = 0;

	/// @brief Get the intervals based on a given continuity along the u direction
	/// @param[in, out] t The resulting intervals, must be resized before
	/// @param[in] c The continuity
	AMCAX_API virtual void UIntervals(std::vector<double>& t, ContinuityType c) const = 0;

	/// @brief Get the intervals based on a given continuity along the v direction
	/// @param[in, out] t The resulting intervals, must be resized before
	/// @param[in] c The continuity
	AMCAX_API virtual void VIntervals(std::vector<double>& t, ContinuityType c) const = 0;

	/// @brief Get the trimmed surface along the u direction
	/// @param first The first parameter
	/// @param last The last parameter
	/// @param tol The tolerance for point confusion
	/// @return The trimmed surface
	AMCAX_API virtual std::shared_ptr<Adaptor3Surface> UTrim(double first, double last, double tol) const = 0;

	/// @brief Get the trimmed surface along the v direction
	/// @param first The first parameter
	/// @param last The last parameter
	/// @param tol The tolerance for point confusion
	/// @return The trimmed surface
	AMCAX_API virtual std::shared_ptr<Adaptor3Surface> VTrim(double first, double last, double tol) const = 0;

	/// @brief Is the surface closed along the u direction
	/// @return True if the surface is closed along the u direction
	AMCAX_API virtual bool IsUClosed() const = 0;

	/// @brief Is the surface closed along the v direction
	/// @return True if the surface is closed along the v direction
	AMCAX_API virtual bool IsVClosed() const = 0;

	/// @brief Is the surface periodic along the u direction
	/// @return True if the surface is periodic along the u direction
	AMCAX_API virtual bool IsUPeriodic() const = 0;

	/// @brief Get the period along the u direction
	/// @return The u period
	AMCAX_API virtual double UPeriod() const = 0;

	/// @brief Is the surface periodic along the v direction
	/// @return True if the surface is periodic along the v direction
	AMCAX_API virtual bool IsVPeriodic() const = 0;

	/// @brief Get the period along the v direction
	/// @return The v period
	AMCAX_API virtual double VPeriod() const = 0;

	/// @brief Compute the point at given parameters
	/// @param u The u parameter
	/// @param v The v parameter
	/// @return The point
	AMCAX_API virtual Point3 Value(double u, double v) const = 0;

	/// @brief Compute the point at given parameters
	/// @param[in] u The u parameter
	/// @param[in] v The v parameter
	/// @param[out] p The point
	AMCAX_API virtual void D0(double u, double v, Point3& p) const = 0;

	/// @brief Compute the point and the first partial derivatives at given parameters
	/// @param[in] u The u parameter
	/// @param[in] v The v parameter
	/// @param[out] p The point
	/// @param[out] d1u The derivative du
	/// @param[out] d1v The derivative dv
	AMCAX_API virtual void D1(double u, double v, Point3& p, Vector3& d1u, Vector3& d1v) const = 0;

	/// @brief Compute the point, the first and second partial derivatives at given parameters
	/// @param[in] u The u parameter
	/// @param[in] v The v parameter
	/// @param[out] p The point
	/// @param[out] d1u The derivative du
	/// @param[out] d1v The derivative dv
	/// @param[out] d2uu The derivative du^2
	/// @param[out] d2uv The derivative duv
	/// @param[out] d2vv The derivative dv^2
	AMCAX_API virtual void D2(double u, double v, Point3& p, Vector3& d1u, Vector3& d1v, Vector3& d2uu, Vector3& d2uv, Vector3& d2vv) const = 0;

	/// @brief Compute the point, the first, second and third partial derivatives at given parameters
	/// @param[in] u The u parameter
	/// @param[in] v The v parameter
	/// @param[out] p The point
	/// @param[out] d1u The derivative du
	/// @param[out] d1v The derivative dv
	/// @param[out] d2uu The derivative du^2
	/// @param[out] d2uv The derivative duv
	/// @param[out] d2vv The derivative dv^2
	/// @param[out] d3uuu The derivative du^3
	/// @param[out] d3uuv The derivative du^2v
	/// @param[out] d3uvv The derivative duv^2
	/// @param[out] d3vvv The derivative dv^3
	AMCAX_API virtual void D3(double u, double v, Point3& p, Vector3& d1u, Vector3& d1v, Vector3& d2uu, Vector3& d2uv, Vector3& d2vv, Vector3& d3uuu, Vector3& d3uuv, Vector3& d3uvv, Vector3& d3vvv) const = 0;

	/// @brief Compute the partial derivative of given orders at given parameters
	/// @param u The u parameter
	/// @param v The v parameter
	/// @param nu The order of derivative along the u direction
	/// @param nv The order of derivative along the v direction
	/// @return The partial derivative d u^nu v^nv
	AMCAX_API virtual Vector3 DN(double u, double v, int nu, int nv) const = 0;

	/// @brief Get the u tolerance on the parameters from a 3D tolerance
	/// @param r3d The 3D tolerance
	/// @return The u tolerance
	AMCAX_API virtual double UResolution(double r3d) const = 0;

	/// @brief Get the v tolerance on the parameters from a 3D tolerance
	/// @param r3d The 3D tolerance
	/// @return The v tolerance
	AMCAX_API virtual double VResolution(double r3d) const = 0;

	/// @brief Get the type of surface
	/// @return The type of surface
	AMCAX_API virtual SurfaceType Type() const = 0;

	/// @brief Get a plane if the surface type is plane
	/// @return The plane
	AMCAX_API virtual Plane GetPlane() const = 0;

	/// @brief Get a cylinder if the surface type is cylinder
	/// @return The cylinder
	AMCAX_API virtual Cylinder GetCylinder() const = 0;

	/// @brief Get a cone if the surface type is cone
	/// @return The cone
	AMCAX_API virtual Cone GetCone() const = 0;

	/// @brief Get a sphere if the surface type is sphere
	/// @return The sphere
	AMCAX_API virtual Sphere GetSphere() const = 0;

	/// @brief Get a torus if the surface type is torus
	/// @return
	AMCAX_API virtual Torus GetTorus() const = 0;

	/// @brief Get the degree along the u direction
	/// @return The degree along the u direction
	AMCAX_API virtual int UDegree() const = 0;

	/// @brief Get the number of poles along the u direction
	/// @return The number of poles along the u direction
	AMCAX_API virtual int NUPoles() const = 0;

	/// @brief Get the degree along the v direction
	/// @return The degree along the v direction
	AMCAX_API virtual int VDegree() const = 0;

	/// @brief Get the number of poles along the v direction
	/// @return The number of poles along the v direction
	AMCAX_API virtual int NVPoles() const = 0;

	/// @brief Get the number of u knots
	/// @return The number of u knots
	AMCAX_API virtual int NUKnots() const = 0;

	/// @brief Get the number of v knots
	/// @return The number of v knots
	AMCAX_API virtual int NVKnots() const = 0;

	/// @brief Is the surface rational along the u direction
	/// @return True if the surface is rational along the u direction
	AMCAX_API virtual bool IsURational() const = 0;

	/// @brief Is the surface rational along the v direction
	/// @return True if the surface is rational along the v direction
	AMCAX_API virtual bool IsVRational() const = 0;

	/// @brief Get a bezier surface if the surface type is bezier surface
	/// @return The bezier surface
	AMCAX_API virtual std::shared_ptr<Geom3BezierSurface> Bezier() const = 0;

	/// @brief Get a B spline surface if the surface type is B spline surface
	/// @return The B spline surface
	AMCAX_API virtual std::shared_ptr<Geom3BSplineSurface> BSpline() const = 0;

	/// @brief Get the axis of revolution
	/// @return The axis of revolution
	AMCAX_API virtual Axis3 AxeOfRevolution() const = 0;

	/// @brief Get the direction of extrusion
	/// @return The direction of extrusion
	AMCAX_API virtual Direction3 Direction() const = 0;

	/// @brief Get the basis curve of a surface of extrusion or revolution
	/// @return The basis curve
	AMCAX_API virtual std::shared_ptr<Adaptor3Curve> BasisCurve() const = 0;

	/// @brief Get the basis surface of an offset surface
	/// @return The basis surface
	AMCAX_API virtual std::shared_ptr<Adaptor3Surface> BasisSurface() const = 0;

	/// @brief Get the offset value
	/// @return The offset value
	AMCAX_API virtual double OffsetValue() const = 0;
};
} // namespace AMCAX
