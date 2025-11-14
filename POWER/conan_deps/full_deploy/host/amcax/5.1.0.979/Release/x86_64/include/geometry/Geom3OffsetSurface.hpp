/// @file      Geom3OffsetSurface.hpp
/// @brief     Class of 3D offset surface
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <geometry/Geom3Surface.hpp>

namespace AMCAX
{
#ifndef DOXYGEN_SKIP
class Geom3BSplineSurface;
class Geom3Curve;
class Geom3EvaluatorOffsetSurface;
class Geom3Geometry;
class Geom3OsculatingSurface;
#endif

/// @brief Class of 3D offset surface
class AMCAX_CLASS_API Geom3OffsetSurface : public Geom3Surface
{
public:
	/// @brief Default constructor
	/// @details A default surface is an XOY plane
	AMCAX_API Geom3OffsetSurface();

	/// @brief Construct from a surface and an offset value
	/// @param s The basis surface
	/// @param offset The offset value
	/// @param isNotCheckC0 Is the checking of C0 continuity not performed
	AMCAX_API Geom3OffsetSurface(const std::shared_ptr<Geom3Surface>& s, double offset, bool isNotCheckC0 = false);

	/// @brief Set the basis surface
	/// @param s The basis surface
	/// @param isNotCheckC0 Is the checking of C0 continuity not performed
	AMCAX_API void SetBasisSurface(const std::shared_ptr<Geom3Surface>& s, bool isNotCheckC0 = false);

	/// @brief Set the offset value
	/// @param offset The offset value
	AMCAX_API void SetOffsetValue(double offset);

	/// @brief Get the offset value
	/// @return The offset value
	[[nodiscard]] AMCAX_API double Offset() const noexcept;

	/// @brief Get the basis surface
	/// @return The basis surface
	[[nodiscard]] AMCAX_API const std::shared_ptr<Geom3Surface>& BasisSurface() const noexcept;

	/// @brief Get the internal osculating surface
	/// @return The osculating surface
	[[nodiscard]] const std::shared_ptr<Geom3OsculatingSurface>& OsculatingSurface() const noexcept;

	AMCAX_API void UReverse() override;
	AMCAX_API void VReverse() override;
	[[nodiscard]] AMCAX_API double UReversedParameter(double u) const noexcept override;
	[[nodiscard]] AMCAX_API double VReversedParameter(double v) const noexcept override;

	/// @brief Get the parameter bounds
	/// @details The bounds are the same as the bounds of the basis surface
	/// @param[out] u1 The first u parameter
	/// @param[out] u2 The last u parameter
	/// @param[out] v1 The first v parameter
	/// @param[out] v2 The last v parameter
	AMCAX_API void Bounds(double& u1, double& u2, double& v1, double& v2) const noexcept override;

	/// @brief Get the first u parameter
	/// @details The first u parameter is the same as the first u parameter of the basis surface
	/// @return The first u parameter
	[[nodiscard]] AMCAX_API double FirstUParameter() const noexcept override;

	/// @brief Get the last u parameter
	/// @details The last u parameter is the same as the last u parameter of the basis surface
	/// @return The last u paramater
	[[nodiscard]] AMCAX_API double LastUParameter() const noexcept override;

	/// @brief Get the first v parameter
	/// @details The first v parameter is the same as the first v parameter of the basis surface
	/// @return The first v parameter
	[[nodiscard]] AMCAX_API double FirstVParameter() const noexcept override;

	/// @brief Get the last v parameter
	/// @details The last v parameter is the same as the last v parameter of the basis surface
	/// @return The last v parameter
	[[nodiscard]] AMCAX_API double LastVParameter() const noexcept override;

	/// @brief Get the continuity of the surface
	/// @details The continuity of the offset surface is not higher than the basis surface
	/// @return The type of continuity
	[[nodiscard]] AMCAX_API ContinuityType Continuity() const noexcept override;

	/// @brief Is the surface has an order n of continuity along the u direction
	/// @param n The order of continuity
	/// @return True if the basis surface has an order of n + 1 continuity along the u direction
	[[nodiscard]] AMCAX_API bool IsCNu(int n) const override;

	/// @brief Is the surface has an order n of continuity along the v direction
	/// @param n The order of continuity
	/// @return True if the basis surface has an order of n + 1 continuity along the v direction
	[[nodiscard]] AMCAX_API bool IsCNv(int n) const override;

	/// @brief Is the surface closed along the u direction
	/// @return True if the surface is closed along the u direction
	[[nodiscard]] AMCAX_API bool IsUClosed() const override;

	/// @brief Is the surface closed along the v direction
	/// @return True if the surface is closed along the v direction
	[[nodiscard]] AMCAX_API bool IsVClosed() const override;

	/// @brief Is the surface periodic along the u direction
	/// @return True if the basis surface is periodic along the u direction
	[[nodiscard]] AMCAX_API bool IsUPeriodic() const noexcept override;

	/// @brief Get the period along the u direction
	/// @return The period along the u direction
	[[nodiscard]] AMCAX_API double UPeriod() const override;

	/// @brief Is the surface periodic along the v direction
	/// @return True if the basis surface is periodic along the v direction
	[[nodiscard]] AMCAX_API bool IsVPeriodic() const noexcept override;

	/// @brief Get the period along the v direction
	/// @return The period along the v direction
	[[nodiscard]] AMCAX_API double VPeriod() const override;

	[[nodiscard]] AMCAX_API std::shared_ptr<Geom3Curve> UIso(double u) const override;
	[[nodiscard]] AMCAX_API std::shared_ptr<Geom3Curve> VIso(double v) const override;
	AMCAX_API void D0(double u, double v, Point3& p) const override;
	AMCAX_API void D1(double u, double v, Point3& p, Vector3& d1u, Vector3& d1v) const override;
	AMCAX_API void D2(double u, double v, Point3& p, Vector3& d1u, Vector3& d1v, Vector3& d2uu, Vector3& d2uv, Vector3& d2vv) const override;
	AMCAX_API void D3(double u, double v, Point3& p, Vector3& d1u, Vector3& d1v, Vector3& d2uu, Vector3& d2uv, Vector3& d2vv, Vector3& d3uuu, Vector3& d3uuv, Vector3& d3uvv, Vector3& d3vvv) const override;
	[[nodiscard]] AMCAX_API Vector3 DN(double u, double v, int nu, int nv) const override;
	AMCAX_API void Transform(const Transformation3& t) override;
	AMCAX_API void TransformParameters(double& u, double& v, const Transformation3& tr) const noexcept override;
	[[nodiscard]] AMCAX_API GeneralTransformation2 ParametricTransformation(const Transformation3& tr) const override;
	[[nodiscard]] AMCAX_API std::shared_ptr<Geom3Geometry> Copy() const override;

	/// @brief Get the resulting surface after offsetint for analytic surfaces
	/// @return The resulting surface
	[[nodiscard]] AMCAX_API std::shared_ptr<Geom3Surface> Surface() const;

#ifndef DOXYGEN_SKIP

	/// @internal
	/// @brief Compute the u osculating surface at given parameters
	/// @param[in] u The u parameter
	/// @param[in] v The v parameter
	/// @param[out] isOpposite Whether the parameterization is opposite direction
	/// @param[out] uOsculatingSurface The osculating surface
	/// @return True if the process is succeed
	bool UOsculatingSurface(double u, double v, bool& isOpposite, std::shared_ptr<Geom3BSplineSurface>& uOsculatingSurface) const noexcept;

	/// @internal
	/// @brief Compute the v osculating surface at given parameters
	/// @param[in] u The u parameter
	/// @param[in] v The v parameter
	/// @param[out] isOpposite Whether the parameterization is opposite direction
	/// @param[out] vOsculatingSurface The osculating surface
	/// @return True if the process is succeed
	bool VOsculatingSurface(double u, double v, bool& isOpposite, std::shared_ptr<Geom3BSplineSurface>& vOsculatingSurface) const noexcept;

#endif

	/// @brief Get the continuity of the basis surface
	/// @return The continuity of the basis surface
	[[nodiscard]] AMCAX_API ContinuityType GetBasisSurfContinuity() const noexcept;

	AMCAX_API std::ostream& Write(std::ostream& os) const override;
	AMCAX_API std::istream& Read(std::istream& is) override;

	/// @brief Get the type of the offset surface
	/// @return The type offset surface
	[[nodiscard]] AMCAX_API SurfaceType Type() const noexcept override;

private:
	/// @brief Basis surface
	std::shared_ptr<Geom3Surface> basisSurface;

	/// @brief Equivalent surface
	std::shared_ptr<Geom3Surface> equivSurface;

	/// @brief Value of offset
	double offsetValue = 0.0;

	/// @brief Osculating surface for Bezier and B spline surface
	std::shared_ptr<Geom3OsculatingSurface> osculatingSurface;

	/// @brief Continuity of basis surface
	ContinuityType basisSurfaceContinuity = ContinuityType::C0;

	/// @brief Evaluator for offset surface
	std::shared_ptr<Geom3EvaluatorOffsetSurface> evaluator;
};
} // namespace AMCAX
