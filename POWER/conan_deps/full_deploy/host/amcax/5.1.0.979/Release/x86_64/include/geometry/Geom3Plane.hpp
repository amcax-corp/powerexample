/// @file      Geom3Plane.hpp
/// @brief     Class of 3D plane
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <geometry/Geom3ElementarySurface.hpp>

namespace AMCAX
{
class Plane;

/// @brief Class of 3D plane
class AMCAX_CLASS_API Geom3Plane : public Geom3ElementarySurface
{
public:
	/// @brief Default constructor
	constexpr Geom3Plane() noexcept = default;

	/// @brief Construct from a local frame
	/// @param frame The local frame
	AMCAX_API explicit Geom3Plane(const Frame3& frame) noexcept;

	/// @brief Construct from a plane
	/// @param plane The plane
	AMCAX_API explicit Geom3Plane(const Plane& plane) noexcept;

	/// @brief Construct from a location point and a normal direction
	/// @param p The location point
	/// @param v The normal direction
	AMCAX_API Geom3Plane(const Point3& p, const Direction3& v) noexcept;

	/// @brief Construct from the coefficients of the algebraic representation
	/// @param a,b,c,d The coefficients
	AMCAX_API Geom3Plane(double a, double b, double c, double d);

	/// @brief Set the plane
	/// @param plane The plane
	AMCAX_API void SetPlane(const Plane& plane) noexcept;

	/// @brief Get the plane
	/// @return The plane
	[[nodiscard]] AMCAX_API Plane GetPlane() const noexcept;

	AMCAX_API void UReverse() noexcept override;
	AMCAX_API void VReverse() noexcept override;
	[[nodiscard]] AMCAX_API double UReversedParameter(double u) const noexcept override;
	[[nodiscard]] AMCAX_API double VReversedParameter(double v) const noexcept override;
	AMCAX_API void TransformParameters(double& u, double& v, const Transformation3& tr) const noexcept override;
	[[nodiscard]] AMCAX_API GeneralTransformation2 ParametricTransformation(const Transformation3& tr) const override;

	/// @brief Get the parameter bounds
	/// @details For a plane, the bounds are infinity
	/// @param[out] u1 The first u parameter
	/// @param[out] u2 The last u parameter
	/// @param[out] v1 The first v parameter
	/// @param[out] v2 The last v parameter
	AMCAX_API void Bounds(double& u1, double& u2, double& v1, double& v2) const noexcept override;

	/// @brief Get the first u parameter
	/// @details For a plane, the first u parameter is negative infinity
	/// @return The first u parameter
	[[nodiscard]] AMCAX_API double FirstUParameter() const noexcept override;

	/// @brief Get the last u parameter
	/// @details For a plane, the last u parameter is positive infinity
	/// @return The last u paramater
	[[nodiscard]] AMCAX_API double LastUParameter() const noexcept override;

	/// @brief Get the first v parameter
	/// @details For a plane, the first v parameter is negative infinity
	/// @return The first v parameter
	[[nodiscard]] AMCAX_API double FirstVParameter() const noexcept override;

	/// @brief Get the last v parameter
	/// @details For a plane, the last v parameter is positive infinity
	/// @return The last v parameter
	[[nodiscard]] AMCAX_API double LastVParameter() const noexcept override;

	/// @brief Get the coefficients of the algebraic representation of the plane
	/// @param[out] a,b,c,d The coefficients
	AMCAX_API void Coefficients(double& a, double& b, double& c, double& d) const noexcept;

	/// @brief Is the plane closed along the u direction
	/// @return Always false
	[[nodiscard]] AMCAX_API bool IsUClosed() const noexcept override;

	/// @brief Is the plane closed along the v direction
	/// @return Always false
	[[nodiscard]] AMCAX_API bool IsVClosed() const noexcept override;

	/// @brief Is the plane periodic along the u direction
	/// @return Always false
	[[nodiscard]] AMCAX_API bool IsUPeriodic() const noexcept override;

	/// @brief Is the plane periodic along the v direction
	/// @return Always false
	[[nodiscard]] AMCAX_API bool IsVPeriodic() const noexcept override;

	/// @brief Get the u isoparametric curve at a u parameter
	/// @details For a plane, the u isoparametric curve is a line
	/// @param u The u parameter
	/// @return The u isoparametric curve
	[[nodiscard]] AMCAX_API std::shared_ptr<Geom3Curve> UIso(double u) const override;

	/// @brief Get the v isoparametric curve at a v parameter
	/// @details For a plane, the v isoparametric curve is a line
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

	/// @brief Get the type of plane
	/// @return The type plane
	[[nodiscard]] AMCAX_API SurfaceType Type() const noexcept override;
};
} // namespace AMCAX
