/// @file      Geom3SurfaceOfExtrusion.hpp
/// @brief     Class of surface of extrusion
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <geometry/Geom3SweptSurface.hpp>

namespace AMCAX
{
#ifndef DOXYGEN_SKIP
class Geom3EvaluatorSurfaceOfExtrusion;
#endif

/// @brief Class of surface of extrusion
class AMCAX_CLASS_API Geom3SurfaceOfExtrusion : public Geom3SweptSurface
{
public:
	/// @brief Default constructor
	/// @details A default surface is a XOZ plane
	AMCAX_API Geom3SurfaceOfExtrusion();

	/// @brief Construct from a basis curve and an extrusion direction
	/// @param c The basis curve
	/// @param v The extrusion direction
	AMCAX_API Geom3SurfaceOfExtrusion(const std::shared_ptr<Geom3Curve>& c, const Direction3& v);

	/// @brief Set the extrusion direction
	/// @param v The extrusion direction
	AMCAX_API void SetDirection(const Direction3& v) noexcept;

	/// @brief Set the basis curve
	/// @param c The basis curve
	AMCAX_API void SetBasisCurve(const std::shared_ptr<Geom3Curve>& c);

	AMCAX_API void UReverse() override;
	AMCAX_API void VReverse() noexcept override;
	[[nodiscard]] AMCAX_API double UReversedParameter(double u) const noexcept override;
	[[nodiscard]] AMCAX_API double VReversedParameter(double v) const noexcept override;

	/// @brief Get the parameter bounds
	/// @details For an extrusion surface, the u bounds are the bounds of the basis curve, and the v bounds are infinity
	/// @param[out] u1 The first u parameter
	/// @param[out] u2 The last u parameter
	/// @param[out] v1 The first v parameter
	/// @param[out] v2 The last v parameter
	AMCAX_API void Bounds(double& u1, double& u2, double& v1, double& v2) const noexcept override;

	/// @brief Get the first u parameter
	/// @details For an extrusion surface, the first u parameter is the first parameter of the basis curve
	/// @return The first u parameter
	[[nodiscard]] AMCAX_API double FirstUParameter() const noexcept override;

	/// @brief Get the last u parameter
	/// @details For an extrusion surface, the last u parameter is the last parameter of the basis curve
	/// @return The last u paramater
	[[nodiscard]] AMCAX_API double LastUParameter() const noexcept override;

	/// @brief Get the first v parameter
	/// @details For an extrusion surface, the first v parameter is negative infinity
	/// @return The first v parameter
	[[nodiscard]] AMCAX_API double FirstVParameter() const noexcept override;

	/// @brief Get the last v parameter
	/// @details For an extrusion surface, the last v parameter is positive infinity
	/// @return The last v parameter
	[[nodiscard]] AMCAX_API double LastVParameter() const noexcept override;

	/// @brief Is the extrusion surface closed along the u direction
	/// @return True if the basis curve is closed
	[[nodiscard]] AMCAX_API bool IsUClosed() const override;

	/// @brief Is the extrusion surface closed along the v direction
	/// @return Always false
	[[nodiscard]] AMCAX_API bool IsVClosed() const noexcept override;

	/// @brief Is the extrusion surface has an order n of continuity along the u direction
	/// @param n The order of continuity
	/// @return True if the basis curve has an order n continuity
	[[nodiscard]] AMCAX_API bool IsCNu(int n) const override;

	/// @brief Is the extrusion surface has an order n of continuity along the v direction
	/// @param n The order of continuity
	/// @return Always true
	[[nodiscard]] AMCAX_API bool IsCNv(int n) const noexcept override;

	/// @brief Is the extrusion surface periodic along the u direction
	/// @return True if the basis curve is periodic
	[[nodiscard]] AMCAX_API bool IsUPeriodic() const noexcept override;

	/// @brief Is the extrusion surface periodic along the v direction
	/// @return Always false
	[[nodiscard]] AMCAX_API bool IsVPeriodic() const noexcept override;

	/// @brief Get the u isoparametric curve at a u parameter
	/// @details For an extrusion surface, the u isoparametric curve is a line
	/// @param u The u parameter
	/// @return The u isoparametric curve
	[[nodiscard]] AMCAX_API std::shared_ptr<Geom3Curve> UIso(double u) const override;

	/// @brief Get the v isoparametric curve at a v parameter
	/// @details For an extrusion surface, the v isoparametric curve is a translated basis curve
	/// @param v The v parameter
	/// @return The v isoparametric curve
	[[nodiscard]] AMCAX_API std::shared_ptr<Geom3Curve> VIso(double v) const override;

	AMCAX_API void D0(double u, double v, Point3& p) const override;
	AMCAX_API void D1(double u, double v, Point3& p, Vector3& d1u, Vector3& d1v) const override;
	AMCAX_API void D2(double u, double v, Point3& p, Vector3& d1u, Vector3& d1v, Vector3& d2uu, Vector3& d2uv, Vector3& d2vv) const override;
	AMCAX_API void D3(double u, double v, Point3& p, Vector3& d1u, Vector3& d1v, Vector3& d2uu, Vector3& d2uv, Vector3& d2vv, Vector3& d3uuu, Vector3& d3uuv, Vector3& d3uvv, Vector3& d3vvv) const override;
	[[nodiscard]] AMCAX_API Vector3 DN(double u, double v, int nu, int nv) const override;
	AMCAX_API void Transform(const Transformation3& tr) override;
	AMCAX_API void TransformParameters(double& u, double& v, const Transformation3& tr) const noexcept override;
	[[nodiscard]] AMCAX_API GeneralTransformation2 ParametricTransformation(const Transformation3& tr) const override;
	[[nodiscard]] AMCAX_API std::shared_ptr<Geom3Geometry> Copy() const override;
	AMCAX_API std::ostream& Write(std::ostream& os) const override;
	AMCAX_API std::istream& Read(std::istream& is) override;

	/// @brief Get the type of extrusion surface
	/// @return The type surface of extrusion
	[[nodiscard]] AMCAX_API SurfaceType Type() const noexcept override;

private:
	/// @brief Evaluator for surface of extrusion
	std::shared_ptr<Geom3EvaluatorSurfaceOfExtrusion> evaluator;
};
} // namespace AMCAX
