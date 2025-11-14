/// @file      Geom3ConicalSurface.hpp
/// @brief     Class of 3D conical surface
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <geometry/Geom3ElementarySurface.hpp>

namespace AMCAX
{
class Cone;

/// @brief Class of 3D conical surface
class AMCAX_CLASS_API Geom3ConicalSurface : public Geom3ElementarySurface
{
public:
	/// @brief Default constructor
	Geom3ConicalSurface() noexcept = default;

	/// @brief Construct from a local frame, a reference radius and a semi-angle
	/// @param frame The local frame
	/// @param r The reference radius
	/// @param angle The semi-angle
	AMCAX_API Geom3ConicalSurface(const Frame3& frame, double r, double angle);

	/// @brief Construct from a cone
	/// @param c The cone
	AMCAX_API explicit Geom3ConicalSurface(const Cone& c) noexcept;

	/// @brief Set the cone
	/// @param c The cone
	AMCAX_API void SetCone(const Cone& c) noexcept;

	/// @brief Set the reference radius
	/// @param r The radius
	AMCAX_API void SetRadius(double r);

	/// @brief Set the semi-angle
	/// @param angle The semi-angle
	AMCAX_API void SetSemiAngle(double angle);

	/// @brief Get the cone
	/// @return The cone
	[[nodiscard]] AMCAX_API Cone GetCone() const noexcept;

	AMCAX_API void VReverse() noexcept override;
	[[nodiscard]] AMCAX_API double UReversedParameter(double u) const noexcept override;
	[[nodiscard]] AMCAX_API double VReversedParameter(double v) const noexcept override;
	AMCAX_API void TransformParameters(double& u, double& v, const Transformation3& tr) const noexcept override;
	[[nodiscard]] AMCAX_API GeneralTransformation2 ParametricTransformation(const Transformation3& tr) const noexcept override;

	/// @brief Get the apex point
	/// @return The apex point
	[[nodiscard]] AMCAX_API Point3 Apex() const noexcept;

	/// @brief Get the parameter bounds
	/// @details For a conical surface, the u bounds are 0 to 2pi, the v bounds are infinity
	/// @param[out] u1 The first u parameter
	/// @param[out] u2 The last u parameter
	/// @param[out] v1 The first v parameter
	/// @param[out] v2 The last v parameter
	AMCAX_API void Bounds(double& u1, double& u2, double& v1, double& v2) const noexcept override;

	/// @brief Get the first u parameter
	/// @details For a conical surface, the first u parameter is 0
	/// @return The first u parameter
	[[nodiscard]] AMCAX_API double FirstUParameter() const noexcept override;

	/// @brief Get the last u parameter
	/// @details For a conical surface, the last u parameter is 2pi
	/// @return The last u paramater
	[[nodiscard]] AMCAX_API double LastUParameter() const noexcept override;

	/// @brief Get the first v parameter
	/// @details For a conical surface, the first v parameter is negative infinity
	/// @return The first v parameter
	[[nodiscard]] AMCAX_API double FirstVParameter() const noexcept override;

	/// @brief Get the last v parameter
	/// @details For a conical surface, the last v parameter is positive infinity
	/// @return The last v parameter
	[[nodiscard]] AMCAX_API double LastVParameter() const noexcept override;

	/// @brief Get the coefficients of the algebraic representation of the cone
	/// @details The algebraic representation of the cone is a_1 x^2 + a_2 y^2 + a_3 z^2 + 2 (b_1 xy + b_2 xz + b_3 yz) + 2 (c_1 x + c_2 y + c_3 z) + d = 0
	/// @param[out] a1,a2,a3,b1,b2,b3,c1,c2,c3,d The coefficients
	AMCAX_API void Coefficients(double& a1, double& a2, double& a3, double& b1, double& b2, double& b3, double& c1, double& c2, double& c3, double& d) const;

	/// @brief Get the radius
	/// @return The radius
	[[nodiscard]] AMCAX_API double Radius() const noexcept;

	/// @brief Get the semi-angle
	/// @return The semi-angle
	[[nodiscard]] AMCAX_API double SemiAngle() const noexcept;

	/// @brief Is the conical surface closed along the u direction
	/// @return Always true
	[[nodiscard]] AMCAX_API bool IsUClosed() const noexcept override;

	/// @brief Is the conical surface closed along the v direction
	/// @return Always false
	[[nodiscard]] AMCAX_API bool IsVClosed() const noexcept override;

	/// @brief Is the conical surface periodic along the u direction
	/// @return Always true
	[[nodiscard]] AMCAX_API bool IsUPeriodic() const noexcept override;

	/// @brief Is the conical surface periodic along the v direction
	/// @return Always false
	[[nodiscard]] AMCAX_API bool IsVPeriodic() const noexcept override;

	/// @brief Get the u isoparametric curve at a u parameter
	/// @details For a conical surface, the u isoparametric curve is a line
	/// @param u The u parameter
	/// @return The u isoparametric curve
	[[nodiscard]] AMCAX_API std::shared_ptr<Geom3Curve> UIso(double u) const override;

	/// @brief Get the v isoparametric curve at a v parameter
	/// @details For a conical surface, the v isoparametric curve is a circle
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

	/// @brief Get the type of conical surface
	/// @return The type Cone
	[[nodiscard]] AMCAX_API SurfaceType Type() const noexcept override;

private:
	/// @brief Reference radius of conical surface
	double radius = std::numeric_limits<double>::max();

	/// @brief Semi-angle of conical surface
	double semiAngle = Constants::quarter_pi;
};
} // namespace AMCAX
