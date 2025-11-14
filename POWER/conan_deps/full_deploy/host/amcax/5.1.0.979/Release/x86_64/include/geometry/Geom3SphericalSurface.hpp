/// @file      Geom3SphericalSurface.hpp
/// @brief     Class of 3D spherical surface
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <geometry/Geom3ElementarySurface.hpp>

namespace AMCAX
{
class Sphere;

/// @brief Class of 3D spherical surface
class AMCAX_CLASS_API Geom3SphericalSurface : public Geom3ElementarySurface
{
public:
	/// @brief Default constructor
	Geom3SphericalSurface() noexcept = default;

	/// @brief Construct from a local frame and a radius
	/// @param frame The local frame
	/// @param r The radius
	AMCAX_API Geom3SphericalSurface(const Frame3& frame, double r);

	/// @brief Construct from a sphere
	/// @param s The sphere
	AMCAX_API explicit Geom3SphericalSurface(const Sphere& s) noexcept;

	/// @brief Set the radius
	/// @param r The radius
	AMCAX_API void SetRadius(double r);

	/// @brief Set the sphere
	/// @param s The sphere
	AMCAX_API void SetSphere(const Sphere& s) noexcept;

	/// @brief Get the sphere
	/// @return The sphere
	[[nodiscard]] AMCAX_API Sphere GetSphere() const noexcept;

	[[nodiscard]] AMCAX_API double UReversedParameter(double u) const noexcept override;
	[[nodiscard]] AMCAX_API double VReversedParameter(double v) const noexcept override;

	/// @brief Get the area of the spherial surface
	/// @return The area
	[[nodiscard]] AMCAX_API double Area() const noexcept;

	/// @brief Get the parameter bounds
	/// @details For a spherical surface, the u bounds are 0 to 2pi, the v bounds are -pi/2 to pi/2
	/// @param[out] u1 The first u parameter
	/// @param[out] u2 The last u parameter
	/// @param[out] v1 The first v parameter
	/// @param[out] v2 The last v parameter
	AMCAX_API void Bounds(double& u1, double& u2, double& v1, double& v2) const noexcept override;

	/// @brief Get the first u parameter
	/// @details For a spherical surface, the first u parameter is 0
	/// @return The first u parameter
	[[nodiscard]] AMCAX_API double FirstUParameter() const noexcept override;

	/// @brief Get the last u parameter
	/// @details For a spherical surface, the last u parameter is 2pi
	/// @return The last u paramater
	[[nodiscard]] AMCAX_API double LastUParameter() const noexcept override;

	/// @brief Get the first v parameter
	/// @details For a spherical surface, the first v parameter is -pi/2
	/// @return The first v parameter
	[[nodiscard]] AMCAX_API double FirstVParameter() const noexcept override;

	/// @brief Get the last v parameter
	/// @details For a spherical surface, the last v parameter is pi/2
	/// @return The last v parameter
	[[nodiscard]] AMCAX_API double LastVParameter() const noexcept override;

	/// @brief Get the coefficients of the algebraic representation of the sphere
	/// @details The algebraic representation of the sphere is a_1 x^2 + a_2 y^2 + a_3 z^2 + 2 (b_1 xy + b_2 xz + b_3 yz) + 2 (c_1 x + c_2 y + c_3 z) + d = 0
	/// @param[out] a1,a2,a3,b1,b2,b3,c1,c2,c3,d The coefficients
	AMCAX_API void Coefficients(double& a1, double& a2, double& a3, double& b1, double& b2, double& b3, double& c1, double& c2, double& c3, double& d) const;

	/// @brief Get the radius
	/// @return The radius
	[[nodiscard]] AMCAX_API double Radius() const noexcept;

	/// @brief Get the volume of the ball
	/// @return The volume
	[[nodiscard]] AMCAX_API double Volume() const noexcept;

	/// @brief Is the spherical surface closed along the u direction
	/// @return Always true
	[[nodiscard]] AMCAX_API bool IsUClosed() const noexcept override;

	/// @brief Is the spherical surface closed along the v direction
	/// @return Always false
	[[nodiscard]] AMCAX_API bool IsVClosed() const noexcept override;

	/// @brief Is the spherical surface periodic along the u direction
	/// @return Always true
	[[nodiscard]] AMCAX_API bool IsUPeriodic() const noexcept override;

	/// @brief Is the spherical surface periodic along the v direction
	/// @return Always false
	[[nodiscard]] AMCAX_API bool IsVPeriodic() const noexcept override;

	/// @brief Get the u isoparametric curve at a u parameter
	/// @details For a spherical surface, the u isoparametric curve is a trimmed circle
	/// @param u The u parameter
	/// @return The u isoparametric curve
	[[nodiscard]] AMCAX_API std::shared_ptr<Geom3Curve> UIso(double u) const override;

	/// @brief Get the v isoparametric curve at a v parameter
	/// @details For a spherical surface, the v isoparametric curve is a circle
	/// @param v The v parameter
	/// @return The v isoparametric curve
	[[nodiscard]] AMCAX_API std::shared_ptr<Geom3Curve> VIso(double v) const override;

	AMCAX_API void D0(double u, double v, Point3& p) const noexcept override;
	AMCAX_API void D1(double u, double v, Point3& p, Vector3& d1u, Vector3& d1v) const noexcept override;
	AMCAX_API void D2(double u, double v, Point3& p, Vector3& d1u, Vector3& d1v, Vector3& d2uu, Vector3& d2uv, Vector3& d2vv) const noexcept override;
	AMCAX_API void D3(double u, double v, Point3& p, Vector3& d1u, Vector3& d1v, Vector3& d2uu, Vector3& d2uv, Vector3& d2vv, Vector3& d3uuu, Vector3& d3uuv, Vector3& d3uvv, Vector3& d3vvv) const noexcept override;
	[[nodiscard]] AMCAX_API Vector3 DN(double u, double v, int nu, int nv) const override;
	AMCAX_API void Transform(const Transformation3& tr) noexcept override;
	[[nodiscard]] AMCAX_API std::shared_ptr<Geom3Geometry> Copy() const override;
	AMCAX_API std::ostream& Write(std::ostream& os) const override;
	AMCAX_API std::istream& Read(std::istream& is) override;

	/// @brief Get the type of spherical surface
	/// @return The type Sphere
	[[nodiscard]] AMCAX_API SurfaceType Type() const noexcept override;

private:
	/// @brief Radius of spherical surface
	double radius = std::numeric_limits<double>::max();
};
} // namespace AMCAX
