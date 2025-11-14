/// @file      BoundingSphere.hpp
/// @brief     Class of bounding sphere
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <common/CoordT.hpp>

namespace AMCAX
{
/// @brief Class of bounding sphere
class BoundingSphere
{
public:
	/// @brief Default constructor
	BoundingSphere() noexcept = default;

	/// @brief Construct from a center point and a radius
	/// @param center The coordinate of the center point
	/// @param radius The radius
	/// @param u The u parameter
	/// @param v The v parameter
	AMCAX_API BoundingSphere(const Coord3& center, double radius, int u, int v) noexcept;

	/// @brief Get the u parameter
	/// @return The u parameter
	[[nodiscard]] AMCAX_API int U() const noexcept;

	/// @brief Get the v parameter
	/// @return The v parameter
	[[nodiscard]] AMCAX_API int V() const noexcept;

	/// @brief Get the center of the bounding sphere
	/// @return The coordinate of the center point
	[[nodiscard]] AMCAX_API const Coord3& Center() const noexcept;

	/// @brief Get the radius of the bounding sphere
	/// @return The radius
	[[nodiscard]] AMCAX_API double Radius() const noexcept;

	/// @brief Get the minimal and maximal distances from a point to the bounding sphere
	/// @param[in] coord The coordinate of the point
	/// @param[out] mindist The minimal distance
	/// @param[out] maxdist The maximal distance
	AMCAX_API void Distances(const Coord3& coord, double& mindist, double& maxdist) const noexcept;

	/// @brief Get the minimal and maximal squared distances from a point to the bounding sphere
	/// @param[in] coord The coordinate of the point
	/// @param[out] mindist The minimal squared distance
	/// @param[out] maxdist The maximal squared distance
	AMCAX_API void SquaredDistances(const Coord3& coord, double& mindist, double& maxdist) const noexcept;

	/// @brief Get the distance from a point to the center of the bounding sphere
	/// @param coord The coodinate of the point
	/// @return The distance from the point to the center
	[[nodiscard]] AMCAX_API double Distance(const Coord3& coord) const noexcept;

	/// @brief Get the squared distance from a point to the center of the bounding sphere
	/// @param coord The coodinate of the point
	/// @return The squared distance from the point to the center
	[[nodiscard]] AMCAX_API double SquaredDistance(const Coord3& coord) const noexcept;

	/// @brief Extend the bounding sphere by adding another bounding sphere
	/// @param other The other bounding sphere
	AMCAX_API void Add(const BoundingSphere& other) & noexcept;

	/// @brief Is a bounding sphere is out of the bounding sphere
	/// @param other The other bounding sphere
	/// @return True if the given bounding sphere is out of the bounding sphere
	[[nodiscard]] AMCAX_API bool IsOut(const BoundingSphere& other) const noexcept;

	/// @brief Is a point is out of the bounding sphere
	/// @param point The point
	/// @param tol The distance tolerance
	/// @return True if the point is out of the bounding sphere
	[[nodiscard]] AMCAX_API bool IsOut(const Coord3& point, double tol) const noexcept;

	/// @brief Get the squared length of the diagonal of the bounding sphere
	/// @return The squared legnth of the diagonal
	[[nodiscard]] AMCAX_API double SquareDiagonal() const noexcept;

	/// @brief Get the length of the diagonal of the bounding sphere
	/// @return The length of the diagonal
	[[nodiscard]] AMCAX_API double Diagonal() const noexcept;

private:
	Coord3 center;
	double radius = 0.0;
	int u = 0;
	int v = 0;
};
} // namespace AMCAX
