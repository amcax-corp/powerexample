/// @file      CurveLocalProperty.hpp
/// @brief     Template class of computing curve local property
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <common/DirectionT.hpp>
#include <common/PointT.hpp>
#include <common/VectorT.hpp>
#include <math/GeometryMacros.hpp>

namespace AMCAX
{
/// @brief Template class of computing curve local property
/// @tparam Curve The type of curve
/// @tparam DIM The dimension of the curve
template<typename Curve, int DIM>
class CurveLocalProperty
{
public:
	/// @brief Construct from a curve with a given derivative order and a resolution tolerance
	/// @param c The curve
	/// @param n The derivative order
	/// @param resolution The resolution tolerance
	AMCAX_API CurveLocalProperty(const Curve& c, int n, double resolution);

	/// @brief Construct from a curve with a parameter, a given derivative order and a resolution tolerance
	/// @param c The curve
	/// @param u The parameter
	/// @param n The derivative order
	/// @param resolution The resolution tolerance
	AMCAX_API CurveLocalProperty(const Curve& c, double u, int n, double resolution);

	/// @brief Construct from a given derivative order and a resolution tolerance
	/// @param n The derivative order
	/// @param resolution The resolution tolerance
	AMCAX_API CurveLocalProperty(int n, double resolution);

	/// @brief Set the parameter
	/// @param u The parameter
	AMCAX_API void SetParameter(double u);

	/// @brief Set the curve
	/// @param c The curve
	AMCAX_API void SetCurve(const Curve& c) noexcept;

	/// @brief Get the point
	/// @return The point
	[[nodiscard]] AMCAX_API const PointT<double, DIM>& Value() const noexcept;

	/// @brief Get the first derivative
	/// @return The first derivative
	[[nodiscard]] AMCAX_API const VectorT<double, DIM>& D1();

	/// @brief Get the second derivative
	/// @return The second derivative
	[[nodiscard]] AMCAX_API const VectorT<double, DIM>& D2();

	/// @brief Get the third derivative
	/// @return The third derivative
	[[nodiscard]] AMCAX_API const VectorT<double, DIM>& D3();

	/// @brief Is the tangent defined
	/// @return True if the tangent is defined
	[[nodiscard]] AMCAX_API bool IsTangentDefined();

	/// @brief Get the tangent direction
	/// @param[out] d The tangent direction
	AMCAX_API void Tangent(DirectionT<double, DIM>& d);

	/// @brief Get the curvature
	/// @return The curvature
	[[nodiscard]] AMCAX_API double Curvature();

	/// @brief Get the normal
	/// @param[out] n The normal
	AMCAX_API void Normal(DirectionT<double, DIM>& n);

	/// @brief Get the center of curvature
	/// @param[out] p The center of curvature
	AMCAX_API void CenterOfCurvature(PointT<double, DIM>& p);

private:
	Curve curve = {};
	double u = std::numeric_limits<double>::max();
	int derOrder;
	int cn = 0;
	double tol;
	PointT<double, DIM> point;
	VectorT<double, DIM> derivArr[3];
	DirectionT<double, DIM> tangent;
	double curvature = 0.0;
	LocalPropertyStatus tangentStatus = LocalPropertyStatus::Undecided;
	int significantFirstDerivativeOrder = 0;
	static constexpr double minStep = 1e-7;
};
} // namespace AMCAX
