/// @file      Geom3Curve.hpp
/// @brief     Base class of 3D curve
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <geometry/Geom3Geometry.hpp>
#include <math/GeometryMacros.hpp>

namespace AMCAX
{
/// @brief Base class of 3D curve
class AMCAX_CLASS_API Geom3Curve : public Geom3Geometry
{
public:
	/// @brief Reverse the curve
	AMCAX_API virtual void Reverse() = 0;

	/// @brief Get the reversed curve
	/// @return The reversed curve
	[[nodiscard]] AMCAX_API std::shared_ptr<Geom3Curve> Reversed() const;

	/// @brief Compute the reversed parameter from a parameter
	/// @param u The parameter
	/// @return The reversed parameter
	[[nodiscard]] AMCAX_API virtual double ReversedParameter(double u) const noexcept = 0;

	/// @brief Compute the transformed parameter from a parameter
	/// @param u The parameter
	/// @param tr The transformation
	/// @return The transformed parameter
	[[nodiscard]] AMCAX_API virtual double TransformedParameter(double u, const Transformation3& tr) const noexcept;

	/// @brief Get the coefficient required to compute the parametric transformation of the curve
	/// @param tr The transformation
	/// @return The ratio between the parameter of a point on the curve and the parameter of the transformed point on the new curve
	[[nodiscard]] AMCAX_API virtual double ParametricTransformation(const Transformation3& tr) const noexcept;

	/// @brief Get the first parameter
	/// @return The first parameter
	[[nodiscard]] AMCAX_API virtual double FirstParameter() const noexcept = 0;

	/// @brief Get the last parameter
	/// @return The last parameter
	[[nodiscard]] AMCAX_API virtual double LastParameter() const noexcept = 0;

	/// @brief Is the curve closed
	/// @return True if the curve is closed
	[[nodiscard]] AMCAX_API virtual bool IsClosed() const = 0;

	/// @brief Is the curve periodic
	/// @return True if the curve is periodic
	[[nodiscard]] AMCAX_API virtual bool IsPeriodic() const noexcept = 0;

	/// @brief Get the period of the curve
	/// @return The period
	[[nodiscard]] AMCAX_API virtual double Period() const;

	/// @brief Get the type of continuity of the curve
	/// @return The type of continuity
	[[nodiscard]] AMCAX_API virtual ContinuityType Continuity() const noexcept = 0;

	/// @brief Is the curve has an order n of continuity
	/// @param n The order of continuity
	/// @return True if the curve is CN continuity
	[[nodiscard]] AMCAX_API virtual bool IsCN(int n) const = 0;

	/// @brief Compute the point at a parameter
	/// @param[in] u The parameter
	/// @param[out] p The point
	AMCAX_API virtual void D0(double u, Point3& p) const = 0;

	/// @brief Compute the point and the first derivative at a parameter
	/// @param[in] u The parameter
	/// @param[out] p The point
	/// @param[out] v1 The first derivative
	AMCAX_API virtual void D1(double u, Point3& p, Vector3& v1) const = 0;

	/// @brief Compute the point and the first and second derivatives at a parameter
	/// @param[in] u The parameter
	/// @param[out] p The point
	/// @param[out] v1 The first derivative
	/// @param[out] v2 The second derivative
	AMCAX_API virtual void D2(double u, Point3& p, Vector3& v1, Vector3& v2) const = 0;

	/// @brief Compute the point and the first, second and third derivatives at a parameter
	/// @param[in] u The parameter
	/// @param[out] p The point
	/// @param[out] v1 The first derivative
	/// @param[out] v2 The second derivative
	/// @param[out] v3 The third derivative
	AMCAX_API virtual void D3(double u, Point3& p, Vector3& v1, Vector3& v2, Vector3& v3) const = 0;

	/// @brief Compute the n-th derivative at a parameter
	/// @param u The parameter
	/// @param n The order of derivative
	/// @return The n-th derivative
	[[nodiscard]] AMCAX_API virtual Vector3 DN(double u, int n) const = 0;

	/// @brief Compute the point at a parameter
	/// @param u The parameter
	/// @return The point
	[[nodiscard]] AMCAX_API Point3 Value(double u) const;

	/// @brief Get the type of curve
	/// @return The type of curve
	[[nodiscard]] AMCAX_API virtual CurveType Type() const noexcept = 0;
};

/// @brief Write the curve
/// @param os The output stream
/// @param c The curve
/// @return The output stream
AMCAX_API std::ostream& operator<<(std::ostream& os, const Geom3Curve& c);

/// @brief Read the curve
/// @param is The input stream
/// @param c The curve
/// @return The input stream
AMCAX_API std::istream& operator>>(std::istream& is, Geom3Curve& c);
} // namespace AMCAX
