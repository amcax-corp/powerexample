/// @file      Geom3Vector.hpp
/// @brief     Base class of 3D vector
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <geometry/Geom3Geometry.hpp>

namespace AMCAX
{
/// @brief Base class of 3D vector
class AMCAX_CLASS_API Geom3Vector : public Geom3Geometry
{
public:
	/// @brief Reverse the vector
	AMCAX_API void Reverse() noexcept;

	/// @brief Get the reversed vector
	/// @return The reversed vector
	[[nodiscard]] AMCAX_API std::shared_ptr<Geom3Vector> Reversed() const;

	/// @brief Compute the angle difference to the other vector
	/// @param other The other vector
	/// @return The angle difference between two vectors
	[[nodiscard]] AMCAX_API double Angle(const std::shared_ptr<const Geom3Vector>& other) const;

	/// @brief Get the coordinates
	/// @param[out] x,y,z The coordinates
	AMCAX_API void GetCoord(double& x, double& y, double& z) const noexcept;

	/// @brief Compute the norm of the vector
	/// @return The norm of the vector
	[[nodiscard]] AMCAX_API virtual double Norm() const = 0;

	/// @brief Compute the squared norm of the vector
	/// @return The squared norm of the vector
	[[nodiscard]] AMCAX_API virtual double SquaredNorm() const = 0;

	/// @brief Get the x coordinate
	/// @return The x coordinate
	[[nodiscard]] AMCAX_API double X() const noexcept;

	/// @brief Get the y coordinate
	/// @return The y coordinate
	[[nodiscard]] AMCAX_API double Y() const noexcept;

	/// @brief Get the z coordinate
	/// @return The z coordinate
	[[nodiscard]] AMCAX_API double Z() const noexcept;

	/// @brief Compute the cross product by the other vector
	/// @param other The other vector
	/// @return The result of cross product
	[[nodiscard]] AMCAX_API virtual std::shared_ptr<Geom3Vector> Cross(const std::shared_ptr<const Geom3Vector>& other) const = 0;

	/// @brief Compute the dot product by other vector
	/// @param other The other vector
	/// @return The result of dot product
	[[nodiscard]] AMCAX_API double Dot(const std::shared_ptr<const Geom3Vector>& other) const noexcept;

	/// @brief Get the internal vector
	/// @return The internal vector
	[[nodiscard]] AMCAX_API const Vector3& Vector() const noexcept;

protected:
	/// @brief Construct from a vector
	/// @param v The vector
	explicit Geom3Vector(const Vector3& v) noexcept;

	/// @brief Construct from coordinates
	/// @param x,y,z The coordinates
	Geom3Vector(double x, double y, double z) noexcept;

	/// @brief Vector data
	Vector3 vector;
};
} // namespace AMCAX
