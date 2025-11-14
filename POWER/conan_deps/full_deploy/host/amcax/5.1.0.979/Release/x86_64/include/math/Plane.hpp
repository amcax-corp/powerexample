/// @file      Plane.hpp
/// @brief     Class of Plane
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <math/LineT.hpp>
#include <math/SurfaceBase.hpp>

namespace AMCAX
{
/// @brief Class of Plane
class Plane : public SurfaceBase<Plane>
{
	using Base = SurfaceBase<Plane>;
	using Base::pos;

public:
	/// Default constructor
	constexpr Plane() noexcept = default;

	/// @brief Construct from a local frame, XOY plane
	/// @param frame The local frame
	AMCAX_API explicit Plane(const Frame3& frame) noexcept;

	/// @brief Construct from a point and a direction
	/// @param point The point
	/// @param dir The direction
	AMCAX_API Plane(const Point3& point, const Direction3& dir) noexcept;

	/// @brief Construct from an algebraic representation: ax + by + cz + d = 0
	/// @param a,b,c,d The coefficients
	AMCAX_API Plane(double a, double b, double c, double d);

	/// @brief Get coefficients of algebraic representation: ax + by + cz + d = 0
	/// @param[out] a,b,c,d The coefficients
	AMCAX_API void Coefficients(double& a, double& b, double& c, double& d) const noexcept;

	/// @brief Reverse the u parameter
	AMCAX_API void UReverse() noexcept;

	/// @brief Reverse the v parameter
	AMCAX_API void VReverse() noexcept;

	/// @brief Compute the distance from a point to the plane
	/// @param point The point
	/// @return The point-plane distance
	[[nodiscard]] AMCAX_API double Distance(const Point3& point) const noexcept;

	/// @brief Compute the distance from a line to the plane
	/// @param line The line
	/// @return The line-plane distance
	[[nodiscard]] AMCAX_API double Distance(const Line3& line) const noexcept;

	/// @brief Compute the distance from another plane to the plane
	/// @param plane The other plane
	/// @return The plane-plane distance
	[[nodiscard]] AMCAX_API double Distance(const Plane& plane) const noexcept;

	/// @brief Compute the squared distance from a point to the plane
	/// @param point The point
	/// @return The squared point-plane distance
	[[nodiscard]] AMCAX_API double SquaredDistance(const Point3& point) const noexcept;

	/// @brief Compute the squared distance from a line to the plane
	/// @param line The line
	/// @return The squared line-plane distance
	[[nodiscard]] AMCAX_API double SquaredDistance(const Line3& line) const noexcept;

	/// @brief Compute the squared distance from another plane to the plane
	/// @param plane The other plane
	/// @return The squared plane-plane distance
	[[nodiscard]] AMCAX_API double SquaredDistance(const Plane& plane) const noexcept;

	/// @brief Determines whether the plane contains a point under a tolerance or not
	/// @param point The point
	/// @param tol The distance tolerance
	/// @return True if the distance between the point and the plane is under the distance tolerance
	[[nodiscard]] AMCAX_API bool Contains(const Point3& point, double tol) const noexcept;

	/// @brief Determines whether the plane contains a line under a distance tolerance and an angle tolerance
	/// @param line The line
	/// @param distol The distance tolerance
	/// @param angtol The angle tolerance
	/// @return True if the distance from the location point of the line to the plane is under the distance tolerance and the direction of the line is perpendicular to the normal direction of the plane
	[[nodiscard]] AMCAX_API bool Contains(const Line3& line, double distol, double angtol) const noexcept;
};
} // namespace AMCAX
