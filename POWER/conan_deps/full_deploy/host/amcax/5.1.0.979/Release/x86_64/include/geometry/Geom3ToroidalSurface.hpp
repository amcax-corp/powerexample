/// @file      Geom3ToroidalSurface.hpp
/// @brief     Class of 3D toroidal surface
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <geometry/Geom3ElementarySurface.hpp>

namespace AMCAX
{
class Torus;

/// @brief Class of 3D toroidal surface
class AMCAX_CLASS_API Geom3ToroidalSurface : public Geom3ElementarySurface
{
public:
	/// @brief Default constructor
	Geom3ToroidalSurface() noexcept = default;

	/// @brief Construct from a local frame, a major radius and a minor radius
	/// @param frame The local frame
	/// @param major The major radius
	/// @param minor The minor radius
	AMCAX_API Geom3ToroidalSurface(const Frame3& frame, double major, double minor);

	/// @brief Construct from a torus
	/// @param t The torus
	AMCAX_API explicit Geom3ToroidalSurface(const Torus& t) noexcept;

	/// @brief Set the major radius
	/// @param major The major radius
	AMCAX_API void SetMajorRadius(double major);

	/// @brief Set the minor radius
	/// @param minor The minor radius
	AMCAX_API void SetMinorRadius(double minor);

	/// @brief Set the torus
	/// @param t The torus
	AMCAX_API void SetTorus(const Torus& t) noexcept;

	/// @brief Get the torus
	/// @return The torus
	[[nodiscard]] AMCAX_API Torus GetTorus() const noexcept;

	[[nodiscard]] AMCAX_API double UReversedParameter(double u) const noexcept override;
	[[nodiscard]] AMCAX_API double VReversedParameter(double v) const noexcept override;

	/// @brief Get the area of the toroidal surface
	/// @return The area
	[[nodiscard]] AMCAX_API double Area() const noexcept;

	/// @brief Get the parameter bounds
	/// @details For a toroidal surface, the u bounds are 0 to 2 pi, the v bounds are 0 to 2 pi
	/// @param[out] u1 The first u parameter
	/// @param[out] u2 The last u parameter
	/// @param[out] v1 The first v parameter
	/// @param[out] v2 The last v parameter
	AMCAX_API void Bounds(double& u1, double& u2, double& v1, double& v2) const noexcept override;

	/// @brief Get the first u parameter
	/// @details For a toroidal surface, the first u parameter is 0
	/// @return The first u parameter
	[[nodiscard]] AMCAX_API double FirstUParameter() const noexcept override;

	/// @brief Get the last u parameter
	/// @details For a toroidal surface, the last u parameter is 2pi
	/// @return The last u paramater
	[[nodiscard]] AMCAX_API double LastUParameter() const noexcept override;

	/// @brief Get the first v parameter
	/// @details For a toroidal surface, the first v parameter is 0
	/// @return The first v parameter
	[[nodiscard]] AMCAX_API double FirstVParameter() const noexcept override;

	/// @brief Get the last v parameter
	/// @details For a toroidal surface, the last v parameter is 2pi
	/// @return The last v parameter
	[[nodiscard]] AMCAX_API double LastVParameter() const noexcept override;

	/// @brief Get the coefficients of the algebraic representation of the torus
	/// @details The algebraic representation of the torus is
	/// @code
	///     coeff[0]  * x^4    + coeff[1]  * y^4    + coeff[2]  * z^4    +
	///     coeff[3]  * x^3y   + coeff[4]  * x^3z   + coeff[5]  * xy^3   +
	///     coeff[6]  * y^3z   + coeff[7]  * xz^3   + coeff[8]  * yz^3   +
	///     coeff[9]  * x^2y^2 + coeff[10] * x^2z^2 + coeff[11] * y^2z^2 +
	///     coeff[12] * x^2yz  + coeff[13] * xy^2z  + coeff[14] * xyz^2  +
	///     coeff[15] * x^3    + coeff[16] * y^3    + coeff[17] * z^3    +
	///     coeff[18] * x^2y   + coeff[19] * x^2z   + coeff[20] * xy^2   +
	///     coeff[21] * y^2z   + coeff[22] * xz^2   + coeff[23] * yz^2   +
	///     coeff[24] * xyz    +
	///     coeff[25] * x^2    + coeff[26] * y^2    + coeff[27] * z^2    +
	///     coeff[28] * xy     + coeff[29] * xz     + coeff[30] * yz     +
	///     coeff[31] * x      + coeff[32] * y      + coeff[33] * z      +
	///     coeff[34] = 0.0
	/// @endcode
	/// @param[out] coeff The coefficients
	AMCAX_API void Coefficient(std::array<double, 35>& coeff) const;

	/// @brief Get the major radius
	/// @return The major radius
	[[nodiscard]] AMCAX_API double MajorRadius() const noexcept;

	/// @brief Get the minor radius
	/// @return The minor radius
	[[nodiscard]] AMCAX_API double MinorRadius() const noexcept;

	/// @brief Get the volume of the torus
	/// @return The volume
	[[nodiscard]] AMCAX_API double Volume() const noexcept;

	/// @brief Is the toroidal surface closed along the u direction
	/// @return Always true
	[[nodiscard]] AMCAX_API bool IsUClosed() const noexcept override;

	/// @brief Is the toroidal surface closed along the v direction
	/// @return Always true
	[[nodiscard]] AMCAX_API bool IsVClosed() const noexcept override;

	/// @brief Is the toroidal surface periodic along the u direction
	/// @return Always true
	[[nodiscard]] AMCAX_API bool IsUPeriodic() const noexcept override;

	/// @brief Is the toroidal surface periodic along the v direction
	/// @return Always true
	[[nodiscard]] AMCAX_API bool IsVPeriodic() const noexcept override;

	/// @brief Get the u isoparametric curve at a u parameter
	/// @details For a toroidal surface, the u isoparametric curve is a circle
	/// @param u The u parameter
	/// @return The u isoparametric curve
	[[nodiscard]] AMCAX_API std::shared_ptr<Geom3Curve> UIso(double u) const override;

	/// @brief Get the v isoparametric curve at a v parameter
	/// @details For a toroidal surface, the v isoparametric curve is a circle
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

	/// @brief Get the type of toroidal surface
	/// @return The type Torus
	[[nodiscard]] AMCAX_API SurfaceType Type() const noexcept override;

private:
	/// @brief Major radius of toroidal surface
	double majorRadius = std::numeric_limits<double>::max();

	/// @brief Minor radius of toroidal surface
	double minorRadius = std::numeric_limits<double>::min();
};
} // namespace AMCAX
