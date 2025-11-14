/// @file      Geom3SurfaceOfRevolution.hpp
/// @brief     Class of surface of revolution
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <geometry/Geom3SweptSurface.hpp>

namespace AMCAX
{
#ifndef DOXYGEN_SKIP
class Geom3EvaluatorSurfaceOfRevolution;
#endif

/// @brief Class of surface of revolution
class AMCAX_CLASS_API Geom3SurfaceOfRevolution : public Geom3SweptSurface
{
public:
	/// @brief Default constructor
	/// @details A default surface is a cylindrical surface with radius 1.
	AMCAX_API Geom3SurfaceOfRevolution();

	/// @brief Construct from a basis curve and a rotation axis
	/// @param c The basis curve
	/// @param axis The rotation axis
	AMCAX_API Geom3SurfaceOfRevolution(const std::shared_ptr<Geom3Curve>& c, const Axis3& axis);

	/// @brief Set the rotation axis
	/// @param axis The rotation axis
	AMCAX_API void SetAxis(const Axis3& axis) noexcept;

	/// @brief Set the direction of the rotation axis
	/// @param v The direction of the rotation axis
	AMCAX_API void SetDirection(const Direction3& v) noexcept;

	/// @brief Set the basis curve
	/// @param c The basis curve
	AMCAX_API void SetBasisCurve(const std::shared_ptr<Geom3Curve>& c);

	/// @brief Set the location of the rotation axis
	/// @param p The location of the rotattion axis
	AMCAX_API void SetLocation(const Point3& p) noexcept;

	/// @brief Get the rotation axis
	/// @return The rotation axis
	[[nodiscard]] AMCAX_API Axis3 Axis() const noexcept;

	/// @brief Get the location of the rotation axis
	/// @return The location of the rotation axis
	[[nodiscard]] AMCAX_API const Point3& Location() const noexcept;

	AMCAX_API void UReverse() noexcept override;
	AMCAX_API void VReverse() override;
	[[nodiscard]] AMCAX_API double UReversedParameter(double u) const noexcept override;
	[[nodiscard]] AMCAX_API double VReversedParameter(double v) const noexcept override;
	AMCAX_API void TransformParameters(double& u, double& v, const Transformation3& tr) const noexcept override;
	[[nodiscard]] AMCAX_API GeneralTransformation2 ParametricTransformation(const Transformation3& tr) const noexcept override;

	/// @brief Get the parameter bounds
	/// @details For a revolution surface, the u bounds are 0 to 2 pi, and the v bounds are the bounds of the basis curve
	/// @param[out] u1 The first u parameter
	/// @param[out] u2 The last u parameter
	/// @param[out] v1 The first v parameter
	/// @param[out] v2 The last v parameter
	AMCAX_API void Bounds(double& u1, double& u2, double& v1, double& v2) const noexcept override;

	/// @brief Get the first u parameter
	/// @details For an revolution surface, the first u parameter is 0
	/// @return The first u parameter
	[[nodiscard]] AMCAX_API double FirstUParameter() const noexcept override;

	/// @brief Get the last u parameter
	/// @details For a revolution surface, the last u parameter is 2 pi
	/// @return The last u paramater
	[[nodiscard]] AMCAX_API double LastUParameter() const noexcept override;

	/// @brief Get the first v parameter
	/// @details For a revolution surface, the first v parameter is the first parameter of the basis curve
	/// @return The first v parameter
	[[nodiscard]] AMCAX_API double FirstVParameter() const noexcept override;
	/// @brief Get the last v parameter
	/// @details For a revolution surface, the last v parameter is the last parameter of the basis curve
	/// @return The last v parameter
	[[nodiscard]] AMCAX_API double LastVParameter() const noexcept override;

	/// @brief Is the revolution surface closed along the u direction
	/// @return Always true
	[[nodiscard]] AMCAX_API bool IsUClosed() const noexcept override;

	/// @brief Is the revolution surface closed along the v direction
	/// @return True if the basis curve is closed
	[[nodiscard]] AMCAX_API bool IsVClosed() const override;

	/// @brief Is the revolution surface has an order n of continuity along the u direction
	/// @param n The order of continuity
	/// @return Always true
	[[nodiscard]] AMCAX_API bool IsCNu(int n) const noexcept override;

	/// @brief Is the revolution surface has an order n of continuity along the v direction
	/// @param n The order of continuity
	/// @return True if the basis curve has an order n continuity
	[[nodiscard]] AMCAX_API bool IsCNv(int n) const override;

	/// @brief Is the revolution surface periodic along the u direction
	/// @return Always true
	[[nodiscard]] AMCAX_API bool IsUPeriodic() const noexcept override;

	/// @brief Is the revolution surface periodic along the v direction
	/// @return True if the basis curve is periodic
	[[nodiscard]] AMCAX_API bool IsVPeriodic() const noexcept override;

	/// @brief Get the u isoparametric curve at a u parameter
	/// @details For a revolution surface, the u isoparametric curve is a rotated basis curve
	/// @param u The u parameter
	/// @return The u isoparametric curve
	[[nodiscard]] AMCAX_API std::shared_ptr<Geom3Curve> UIso(double u) const override;

	/// @brief Get the v isoparametric curve at a v parameter
	/// @details For a revolution surface, the v isoparametric curve is a circle
	/// @param v The v parameter
	/// @return The v isoparametric curve
	[[nodiscard]] AMCAX_API std::shared_ptr<Geom3Curve> VIso(double v) const override;

	AMCAX_API void D0(double u, double v, Point3& p) const override;
	AMCAX_API void D1(double u, double v, Point3& p, Vector3& d1u, Vector3& d1v) const override;
	AMCAX_API void D2(double u, double v, Point3& p, Vector3& d1u, Vector3& d1v, Vector3& d2uu, Vector3& d2uv, Vector3& d2vv) const override;
	AMCAX_API void D3(double u, double v, Point3& p, Vector3& d1u, Vector3& d1v, Vector3& d2uu, Vector3& d2uv, Vector3& d2vv, Vector3& d3uuu, Vector3& d3uuv, Vector3& d3uvv, Vector3& d3vvv) const override;
	[[nodiscard]] AMCAX_API Vector3 DN(double u, double v, int nu, int nv) const override;
	AMCAX_API void Transform(const Transformation3& tr) override;
	[[nodiscard]] AMCAX_API std::shared_ptr<Geom3Geometry> Copy() const override;
	AMCAX_API std::ostream& Write(std::ostream& os) const override;
	AMCAX_API std::istream& Read(std::istream& is) override;

	/// @brief Get the type of revolution surface
	/// @return The type surface of revolution
	[[nodiscard]] AMCAX_API SurfaceType Type() const noexcept override;

private:
	/// @brief Evaluator for surface of revolution
	std::shared_ptr<Geom3EvaluatorSurfaceOfRevolution> evaluator;

	/// @brief Location of axis
	Point3 location;
};
} // namespace AMCAX
