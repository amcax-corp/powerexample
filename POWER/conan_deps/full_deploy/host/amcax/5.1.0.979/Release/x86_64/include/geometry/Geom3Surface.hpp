/// @file      Geom3Surface.hpp
/// @brief     Base class of 3D surface
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <common/GeneralTransformationT.hpp>
#include <geometry/Geom3Geometry.hpp>
#include <math/GeometryMacros.hpp>

namespace AMCAX
{
class Geom3Curve;

/// @brief Base class of 3D surface
class AMCAX_CLASS_API Geom3Surface : public Geom3Geometry
{
public:
	/// @brief Compute the transformed parameters from original parameters
	/// @param[in,out] u The u parameter
	/// @param[in,out] v The v parameter
	/// @param[in] tr The transformation
	AMCAX_API virtual void TransformParameters(double& u, double& v, const Transformation3& tr) const noexcept;

	/// @brief Get the transformation required to compute the parametric transformation of the surface
	/// @param tr The transformation
	/// @return A general transformation from the parameters of a point on the surface and the parameters of the transformed point on the new surface
	[[nodiscard]] AMCAX_API virtual GeneralTransformation2 ParametricTransformation(const Transformation3& tr) const;

	/// @brief Get the parameter bounds
	/// @param[out] u1 The first u parameter
	/// @param[out] u2 The last u parameter
	/// @param[out] v1 The first v parameter
	/// @param[out] v2 The last v parameter
	AMCAX_API virtual void Bounds(double& u1, double& u2, double& v1, double& v2) const noexcept = 0;

	/// @brief Get the first u parameter
	/// @return The first u parameter
	[[nodiscard]] AMCAX_API virtual double FirstUParameter() const noexcept = 0;

	/// @brief Get the last u parameter
	/// @return The last u paramater
	[[nodiscard]] AMCAX_API virtual double LastUParameter() const noexcept = 0;

	/// @brief Get the first v parameter
	/// @return The first v parameter
	[[nodiscard]] AMCAX_API virtual double FirstVParameter() const noexcept = 0;

	/// @brief Get the last v parameter
	/// @return The last v parameter
	[[nodiscard]] AMCAX_API virtual double LastVParameter() const noexcept = 0;

	/// @brief Is the surface closed along the u direction
	/// @return True if the surface is closed along the u direction
	[[nodiscard]] AMCAX_API virtual bool IsUClosed() const = 0;

	/// @brief Is the surface closed along the v direction
	/// @return True if the surface is closed along the v direction
	[[nodiscard]] AMCAX_API virtual bool IsVClosed() const = 0;

	/// @brief Is the surface periodic along the u direction
	/// @return True if the surface is periodic along the u direction
	[[nodiscard]] AMCAX_API virtual bool IsUPeriodic() const noexcept = 0;

	/// @brief Is the surface periodic along the v direction
	/// @return True if the surface is periodic along the v direction
	[[nodiscard]] AMCAX_API virtual bool IsVPeriodic() const noexcept = 0;

	/// @brief Get the period along the u direction
	/// @return The period along the u direction
	[[nodiscard]] AMCAX_API virtual double UPeriod() const;

	/// @brief Get the period along the v direction
	/// @return The period along the v direction
	[[nodiscard]] AMCAX_API virtual double VPeriod() const;

	/// @brief Reverse the parameterization along the u direction
	AMCAX_API virtual void UReverse() = 0;

	/// @brief Reverse the parameterization along the v direction
	AMCAX_API virtual void VReverse() = 0;

	/// @brief Compute the reversed u parameter from a u parameter
	/// @param u The u parameter
	/// @return The reversed u parameter
	[[nodiscard]] AMCAX_API virtual double UReversedParameter(double u) const noexcept = 0;

	/// @brief Compute the reversed v parameter from a v parameter
	/// @param v The v parameter
	/// @return The reversed v parameter
	[[nodiscard]] AMCAX_API virtual double VReversedParameter(double v) const noexcept = 0;

	/// @brief Get the u isoparametric curve at a u parameter
	/// @param u The u parameter
	/// @return The u isoparametric curve
	[[nodiscard]] AMCAX_API virtual std::shared_ptr<Geom3Curve> UIso(double u) const = 0;

	/// @brief Get the v isoparametric curve at a v parameter
	/// @param v The v parameter
	/// @return The v isoparametric curve
	[[nodiscard]] AMCAX_API virtual std::shared_ptr<Geom3Curve> VIso(double v) const = 0;

	/// @brief Get the continuity of the surface
	/// @return The type of continuity
	[[nodiscard]] AMCAX_API virtual ContinuityType Continuity() const noexcept = 0;

	/// @brief Is the surface has an order n of continuity along the u direction
	/// @param n The order of continuity
	/// @return True if the surface is CN continuity along the u direction
	[[nodiscard]] AMCAX_API virtual bool IsCNu(int n) const = 0;

	/// @brief Is the surface has an order n of continuity along the v direction
	/// @param n The order of continuity
	/// @return True if the surface is CN continuity along the v direction
	[[nodiscard]] AMCAX_API virtual bool IsCNv(int n) const = 0;

	/// @brief Compute the point at given parameters
	/// @param u The u parameter
	/// @param v The v parameter
	/// @return The point
	[[nodiscard]] AMCAX_API virtual Point3 Value(double u, double v) const;

	/// @brief Compute the point at given parameters
	/// @param[in] u The u parameter
	/// @param[in] v The v parameter
	/// @param[out] p The point
	AMCAX_API virtual void D0(double u, double v, Point3& p) const = 0;

	/// @brief Compute the point and the first partial derivatives at given parameters
	/// @param[in] u The u parameter
	/// @param[in] v The v parameter
	/// @param[out] p The point
	/// @param[out] d1u The partial derivative du
	/// @param[out] d1v The partial derivative dv
	AMCAX_API virtual void D1(double u, double v, Point3& p, Vector3& d1u, Vector3& d1v) const = 0;

	/// @brief Compute the point, the first and second partial derivatives at given parameters
	/// @param[in] u The u parameter
	/// @param[in] v The v parameter
	/// @param[out] p The point
	/// @param[out] d1u The partial derivative du
	/// @param[out] d1v The partial derivative dv
	/// @param[out] d2uu The partial derivative du^2
	/// @param[out] d2uv The partial derivative duv
	/// @param[out] d2vv The partial derivative dv^2
	AMCAX_API virtual void D2(double u, double v, Point3& p, Vector3& d1u, Vector3& d1v, Vector3& d2uu, Vector3& d2uv, Vector3& d2vv) const = 0;

	/// @brief Compute the point, the first, second and third partial derivatives at given parameters
	/// @param[in] u The u parameter
	/// @param[in] v The v parameter
	/// @param[out] p The point
	/// @param[out] d1u The partial derivative du
	/// @param[out] d1v The partial derivative dv
	/// @param[out] d2uu The partial derivative du^2
	/// @param[out] d2uv The partial derivative duv
	/// @param[out] d2vv The partial derivative dv^2
	/// @param[out] d3uuu The partial derivative du^3
	/// @param[out] d3uuv The partial derivative du^2v
	/// @param[out] d3uvv The partial derivative duv^2
	/// @param[out] d3vvv The partial derivative dv^3
	AMCAX_API virtual void D3(double u, double v, Point3& p, Vector3& d1u, Vector3& d1v, Vector3& d2uu, Vector3& d2uv, Vector3& d2vv, Vector3& d3uuu, Vector3& d3uuv, Vector3& d3uvv, Vector3& d3vvv) const = 0;

	/// @brief Compute the partial derivative of given orders at given parameters
	/// @param u The u parameter
	/// @param v The v parameter
	/// @param nu The order of derivative along the u direction
	/// @param nv The order of derivative along the v direction
	/// @return The partial derivative d u^nu v^nv
	[[nodiscard]] AMCAX_API virtual Vector3 DN(double u, double v, int nu, int nv) const = 0;

	/// @brief Get the type of surface
	/// @return The type of surface
	[[nodiscard]] AMCAX_API virtual SurfaceType Type() const noexcept = 0;
};

/// @brief Write the surface
/// @param os The output stream
/// @param s The surface
/// @return The output stream
AMCAX_API std::ostream& operator<<(std::ostream& os, const Geom3Surface& s);

/// @brief Read the surface
/// @param is The input stream
/// @param s The surface
/// @return The input stream
AMCAX_API std::istream& operator>>(std::istream& is, Geom3Surface& s);
} // namespace AMCAX
