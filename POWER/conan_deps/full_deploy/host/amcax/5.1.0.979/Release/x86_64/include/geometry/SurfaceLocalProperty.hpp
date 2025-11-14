/// @file      SurfaceLocalProperty.hpp
/// @brief     Template class of local property of surfaces
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <common/DirectionT.hpp>
#include <common/PointT.hpp>
#include <common/VectorT.hpp>
#include <math/GeometryMacros.hpp>

namespace AMCAX
{
/// @brief Template class of local property of surfaces
/// @tparam Surface Type of surface
template<typename Surface>
class SurfaceLocalProperty
{
public:
	/// @brief Construct from a surface with parameters, a given derivative order and a resolution tolerance
	/// @param s The surface
	/// @param u The u parameter
	/// @param v The v parameter
	/// @param n The derivative order
	/// @param resolution The resolution tolerance
	AMCAX_API SurfaceLocalProperty(const Surface& s, double u, double v, int n, double resolution);

	/// @brief Construct from a surface with a given derivative order and a resolution tolerance
	/// @param s The surface
	/// @param n The derivative order
	/// @param resolution The resolution tolerance
	AMCAX_API SurfaceLocalProperty(const Surface& s, int n, double resolution);

	/// @brief Construct from a given derivative order and a resolution tolerance
	/// @param n The derivative order
	/// @param resolution The resolution tolerance
	AMCAX_API SurfaceLocalProperty(int n, double resolution);

	/// @brief Set the surface
	/// @param s The surface
	AMCAX_API void SetSurface(const Surface& s) noexcept;

	/// @brief Set the parameters
	/// @param u The u parameter
	/// @param v The v parameter
	AMCAX_API void SetParameters(double u, double v);

	/// @brief Get the point
	/// @return The point
	[[nodiscard]] AMCAX_API const Point3& Value() const noexcept;

	/// @brief Get the partial u derivative
	/// @return The partial u derivative
	[[nodiscard]] AMCAX_API const Vector3& D1U();

	/// @brief Get the partial v derivative
	/// @return The partial v derivative
	[[nodiscard]] AMCAX_API const Vector3& D1V();

	/// @brief Get the partial uu derivative
	/// @return The partial uu derivative
	[[nodiscard]] AMCAX_API const Vector3& D2U();

	/// @brief Get the partial vv derivative
	/// @return The partial vv derivative
	[[nodiscard]] AMCAX_API const Vector3& D2V();

	/// @brief Get the partial uv derivative
	/// @return The partial uv derivative
	[[nodiscard]] AMCAX_API const Vector3& DUV();

	/// @brief Is the tangent along u direction defined
	/// @return True if the u tangent is defined
	[[nodiscard]] AMCAX_API bool IsTangentUDefined();

	/// @brief Get the tangent direction along u direction
	/// @param[out] d The u tangent direction
	AMCAX_API void TangentU(Direction3& d);

	/// @brief Is the tangent along v direction defined
	/// @return True if the v tangent is defined
	[[nodiscard]] AMCAX_API bool IsTangentVDefined();

	/// @brief Get the tangent direction along v direction
	/// @param[out] d The v tangent direction
	AMCAX_API void TangentV(Direction3& d);

	/// @brief Is normal defined
	/// @return True if the normal is defined
	[[nodiscard]] AMCAX_API bool IsNormalDefined();

	/// @brief Get the normal direction
	/// @return The normal direction
	[[nodiscard]] AMCAX_API const Direction3& Normal();

	/// @brief Is curvature defined
	/// @return True if curvature is defined
	[[nodiscard]] AMCAX_API bool IsCurvatureDefined();

	/// @brief Is umbilic point
	/// @return True if the point is umbilic
	[[nodiscard]] AMCAX_API bool IsUmbilic();

	/// @brief Get the maximum principal curvature
	/// @return The maximum principal curvature
	[[nodiscard]] AMCAX_API double MaxCurvature();

	/// @brief Get the minimum principal curvature
	/// @return The minimum principal curvature
	[[nodiscard]] AMCAX_API double MinCurvature();

	/// @brief Get the principal curvature directions
	/// @param[out] maxD The maximum principal curvature direction
	/// @param[out] minD The minimum principal curvature direction
	AMCAX_API void CurvatureDirections(Direction3& maxD, Direction3& minD);

	/// @brief Get the mean curvature
	/// @return The mean curvature
	[[nodiscard]] AMCAX_API double MeanCurvature();

	/// @brief Get the Gaussian curvature
	/// @return The Gaussian curvature
	[[nodiscard]] AMCAX_API double GaussianCurvature();

private:
	bool IsTangentDefined(int deriv, int& order, LocalPropertyStatus& status);
	Surface surface;
	double u = std::numeric_limits<double>::max();
	double v = std::numeric_limits<double>::max();
	int derOrder;
	int cn = 0;
	double tol;
	Point3 point;
	Vector3 d1u;
	Vector3 d1v;
	Vector3 d2u;
	Vector3 d2v;
	Vector3 duv;
	Direction3 normal;
	double minCurvature = 0.0;
	double maxCurvature = 0.0;
	Direction3 dirMinCurvature;
	Direction3 dirMaxCurvature;
	double meanCurvature = 0.0;
	double gaussCurvature = 0.0;
	int significantFirstDerivativeOrderU = 0;
	int significantFirstDerivativeOrderV = 0;
	LocalPropertyStatus uTangentStatus = LocalPropertyStatus::Undecided;
	LocalPropertyStatus vTangentStatus = LocalPropertyStatus::Undecided;
	LocalPropertyStatus normalStatus = LocalPropertyStatus::Undecided;
	LocalPropertyStatus curvatureStatus = LocalPropertyStatus::Undecided;
	static constexpr double minStep = 1e-7;
};
} // namespace AMCAX
