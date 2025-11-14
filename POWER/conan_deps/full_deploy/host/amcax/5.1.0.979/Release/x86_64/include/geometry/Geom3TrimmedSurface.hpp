/// @file      Geom3TrimmedSurface.hpp
/// @brief     Class of 3D trimmed surface
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <geometry/Geom3BoundedSurface.hpp>

namespace AMCAX
{
/// @brief Class of 3D trimmed surface
class AMCAX_CLASS_API Geom3TrimmedSurface : public Geom3BoundedSurface
{
public:
	/// @brief Default constructor
	/// @details A default surface is a unit square
	AMCAX_API Geom3TrimmedSurface();

	/// @brief Construct from a surface and four bounds
	/// @param s The surface
	/// @param u1 The lower bound of u parameter
	/// @param u2 The upper bound of u parameter
	/// @param v1 The lower bound of v parameter
	/// @param v2 The upper bound of v parameter
	/// @param uSense For u periodic surface, the trimmed surface has the same orientation with the basis surface or not
	/// @param vSense For v periodic surface, the trimmed surface has the same orientation with the basis surface or not
	AMCAX_API Geom3TrimmedSurface(const std::shared_ptr<Geom3Surface>& s, double u1, double u2, double v1, double v2, bool uSense = true, bool vSense = true);

	/// @brief Construct from a surface and the bounds of one direction
	/// @param s The surface
	/// @param param1 The lower bound
	/// @param param2 The upper bound
	/// @param uTrim Is the surface trimmed along u or v direction
	/// @param sense For periodic surface, the trimmed surface has the same orientation with the basis surface or not
	AMCAX_API Geom3TrimmedSurface(const std::shared_ptr<Geom3Surface>& s, double param1, double param2, bool uTrim, bool sense = true);

	/// @brief Trim the surface
	/// @param u1 The lower bound of u parameter
	/// @param u2 The upper bound of u parameter
	/// @param v1 The lower bound of v parameter
	/// @param v2 The upper bound of v parameter
	/// @param uSense For u periodic surface, the trimmed surface has the same orientation with the basis surface or not
	/// @param vSense For v periodic surface, the trimmed surface has the same orientation with the basis surface or not
	AMCAX_API void SetTrim(double u1, double u2, double v1, double v2, bool uSense = true, bool vSense = true);

	/// @brief Trim the surface along one direction
	/// @param param1 The lower bound
	/// @param param2 The upper bound
	/// @param uTrim Is the surface trimmed along u or v direction
	/// @param sense For periodic surface, the trimmed surface has the same orientation with the basis surface or not
	AMCAX_API void SetTrim(double param1, double param2, bool uTrim, bool sense = true);

	/// @brief Get the basis surface
	/// @return The basis surface
	[[nodiscard]] AMCAX_API const std::shared_ptr<Geom3Surface>& BasisSurface() const noexcept;

	AMCAX_API void Bounds(double& u1, double& u2, double& v1, double& v2) const noexcept override;
	[[nodiscard]] AMCAX_API double FirstUParameter() const noexcept override;
	[[nodiscard]] AMCAX_API double LastUParameter() const noexcept override;
	[[nodiscard]] AMCAX_API double FirstVParameter() const noexcept override;
	[[nodiscard]] AMCAX_API double LastVParameter() const noexcept override;

	/// @brief Is the surface trimmed along the u direction
	/// @return True if the surface is trimmed along the u direction
	[[nodiscard]] AMCAX_API bool IsUTrimmed() const noexcept;

	/// @brief Is the surface trimmed along the v direction
	/// @return True if the surface is trimmed along the v direction
	[[nodiscard]] AMCAX_API bool IsVTrimmed() const noexcept;

	/// @brief Is the trimmed surface closed along the u direction
	/// @return True if the basis surface is not trimmed along the u direction and is closed along the u direction
	[[nodiscard]] AMCAX_API bool IsUClosed() const override;

	/// @brief Is the trimmed surface closed along the v direction
	/// @return True if the basis surface is not trimmed along the v direction and is closed along the v direction
	[[nodiscard]] AMCAX_API bool IsVClosed() const override;

	/// @brief Is the trimmed surface periodic along the u direction
	/// @return True if the basis surface is not trimmed along the u direction and is periodic along the u direction
	[[nodiscard]] AMCAX_API bool IsUPeriodic() const noexcept override;

	/// @brief Is the trimmed surface periodic along the v direction
	/// @return True if the basis surface is not trimmed along the v direction and is periodic along the v direction
	[[nodiscard]] AMCAX_API bool IsVPeriodic() const noexcept override;

	[[nodiscard]] AMCAX_API double UPeriod() const override;
	[[nodiscard]] AMCAX_API double VPeriod() const override;
	AMCAX_API void UReverse() override;
	AMCAX_API void VReverse() override;
	[[nodiscard]] AMCAX_API double UReversedParameter(double u) const noexcept override;
	[[nodiscard]] AMCAX_API double VReversedParameter(double v) const noexcept override;

	/// @brief Get the continuity of the trimmed surface
	/// @return The continuity of the basis surface
	[[nodiscard]] AMCAX_API ContinuityType Continuity() const noexcept override;

	/// @brief Is the trimmed surface has an order n of continuity along the u direction
	/// @param n The order of continuity
	/// @return True if the basis surface is CN continuity along the u direction
	[[nodiscard]] AMCAX_API bool IsCNu(int n) const override;

	/// @brief Is the trimmed surface has an order n of continuity along the v direction
	/// @param n The order of continuity
	/// @return True if the basis surface is CN continuity along the v direction
	[[nodiscard]] AMCAX_API bool IsCNv(int n) const override;

	/// @brief Get the u isoparametric curve at a u parameter
	/// @details For a trimmed surface, if the basis surface is trimmed along the v direction, the u isoparametric curve is a trimmed curve
	/// @param u The u parameter
	/// @return The u isoparametric curve
	[[nodiscard]] AMCAX_API std::shared_ptr<Geom3Curve> UIso(double u) const override;

	/// @brief Get the v isoparametric curve at a v parameter
	/// @details For a trimmed surface, if the basis surface is trimmed along the u direction, the v isoparametric curve is a trimmed curve
	/// @param v The v parameter
	/// @return The v isoparametric curve
	[[nodiscard]] AMCAX_API std::shared_ptr<Geom3Curve> VIso(double v) const override;

	AMCAX_API void D0(double u, double v, Point3& p) const override;
	AMCAX_API void D1(double u, double v, Point3& p, Vector3& d1u, Vector3& d1v) const override;
	AMCAX_API void D2(double u, double v, Point3& p, Vector3& d1u, Vector3& d1v, Vector3& d2uu, Vector3& d2uv, Vector3& d2vv) const override;
	AMCAX_API void D3(double u, double v, Point3& p, Vector3& d1u, Vector3& d1v, Vector3& d2uu, Vector3& d2uv, Vector3& d2vv, Vector3& d3uuu, Vector3& d3uuv, Vector3& d3uvv, Vector3& d3vvv) const override;
	[[nodiscard]] AMCAX_API Vector3 DN(double u, double v, int nu, int nv) const override;

	/// @brief Get the type of trimmed surface
	/// @return The type trimmed surface
	[[nodiscard]] AMCAX_API SurfaceType Type() const noexcept override;

	AMCAX_API void Transform(const Transformation3& tr) override;
	AMCAX_API void TransformParameters(double& u, double& v, const Transformation3& tr) const noexcept override;
	[[nodiscard]] AMCAX_API GeneralTransformation2 ParametricTransformation(const Transformation3& tr) const override;
	[[nodiscard]] AMCAX_API std::shared_ptr<Geom3Geometry> Copy() const override;
	AMCAX_API std::ostream& Write(std::ostream& os) const override;
	AMCAX_API std::istream& Read(std::istream& is) override;

private:
	void SetTrim(double u1, double u2, double v1, double v2, bool uTrim, bool vTrim, bool uSense, bool vSense);

	/// @brief Basis surface
	std::shared_ptr<Geom3Surface> basisSurface;

	/// @brief U start parameter
	double uTrim1 = Precision::NegativeInfinity();

	/// @brief V start parameter
	double vTrim1 = Precision::PositiveInfinity();

	/// @brief U end parameter
	double uTrim2 = Precision::NegativeInfinity();

	/// @brief V end parameter
	double vTrim2 = Precision::PositiveInfinity();

	/// @brief Is U trimmed
	bool isUTrimmed = false;

	/// @brief Is V trimmed
	bool isVTrimmed = false;
};
} // namespace AMCAX
