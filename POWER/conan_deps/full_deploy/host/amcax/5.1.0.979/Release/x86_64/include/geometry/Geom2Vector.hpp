/// @file      Geom2Vector.hpp
/// @brief     Base class of 2D vector
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <geometry/Geom2Geometry.hpp>

namespace AMCAX
{
/// @brief Base class of 2D vector
class AMCAX_CLASS_API Geom2Vector : public Geom2Geometry
{
public:
	/// @brief Reverse the vector
	AMCAX_API void Reverse() noexcept;

	/// @brief Get the reversed vector
	/// @return The reversed vector
	[[nodiscard]] AMCAX_API std::shared_ptr<Geom2Vector> Reversed() const;

	/// @brief Compute the angle difference to the other vector
	/// @param other The other vector
	/// @return The angle difference between two vectors
	[[nodiscard]] AMCAX_API double Angle(const std::shared_ptr<const Geom2Vector>& other) const;

	/// @brief Get the coordinates
	/// @param[out] x,y The coordinates
	AMCAX_API void GetCoord(double& x, double& y) const noexcept;

	/// @brief Compute the norm of the vector
	/// @return The norm of the vector
	[[nodiscard]] AMCAX_API virtual double Norm() const noexcept = 0;

	/// @brief Compute the squared norm of the vector
	/// @return The squared norm of the vector
	[[nodiscard]] AMCAX_API virtual double SquaredNorm() const noexcept = 0;

	/// @brief Get the x coordinate
	/// @return The x coordinate
	[[nodiscard]] AMCAX_API double X() const noexcept;

	/// @brief Get the y coordinate
	/// @return The y coordinate
	[[nodiscard]] AMCAX_API double Y() const noexcept;

	/// @brief Compute the cross product by the other vector
	/// @param other The other vector
	/// @return The result of cross product
	[[nodiscard]] AMCAX_API double Cross(const std::shared_ptr<const Geom2Vector>& other) const noexcept;

	/// @brief Compute the dot product by other vector
	/// @param other The other vector
	/// @return The result of dot product
	[[nodiscard]] AMCAX_API double Dot(const std::shared_ptr<const Geom2Vector>& other) const noexcept;

	/// @brief Get the internal vector
	/// @return The internal vector
	[[nodiscard]] AMCAX_API const Vector2& Vector() const noexcept;

protected:
	/// @brief Construct from a vector
	/// @param v The vector
	explicit Geom2Vector(const Vector2& v) noexcept;

	/// @brief Construct from coordinates
	/// @param x,y The coordinates
	Geom2Vector(double x, double y) noexcept;

	/// @brief Vector data
	Vector2 vector;
};
} // namespace AMCAX
