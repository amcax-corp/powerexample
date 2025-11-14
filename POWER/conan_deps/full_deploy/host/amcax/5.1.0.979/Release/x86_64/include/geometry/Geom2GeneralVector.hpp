/// @file      Geom2GeneralVector.hpp
/// @brief     Class of 2D vector
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <geometry/Geom2Vector.hpp>

namespace AMCAX
{
/// @brief Class of 2D vector
class AMCAX_CLASS_API Geom2GeneralVector : public Geom2Vector
{
public:
	/// @brief Construct from a vector
	/// @param v The vector
	AMCAX_API explicit Geom2GeneralVector(const Vector2& v) noexcept;

	/// @brief Construct from coordinates
	/// @param x,y The coordinates
	AMCAX_API Geom2GeneralVector(double x, double y) noexcept;

	/// @brief Construct from two points
	/// @param p1 The source point
	/// @param p2 The target point
	AMCAX_API Geom2GeneralVector(const Point2& p1, const Point2& p2) noexcept;

	/// @brief Set the coordinates
	/// @param x,y The coordinates
	AMCAX_API void SetCoord(double x, double y) noexcept;

	/// @brief Set the vector
	/// @param v The vector
	AMCAX_API void SetVector(const Vector2& v) noexcept;

	/// @brief Set the x coordinate
	/// @param x The x coordinate
	AMCAX_API void SetX(double x) noexcept;

	/// @brief Set the y coordinate
	/// @param y The y coordinate
	AMCAX_API void SetY(double y) noexcept;

	/// @brief Compute the norm of the vector
	/// @return The norm of the vector
	[[nodiscard]] AMCAX_API double Norm() const noexcept override;

	/// @brief Compute the squared norm of the vector
	/// @return The squared norm of the vector
	[[nodiscard]] AMCAX_API double SquaredNorm() const noexcept override;

	/// @brief Normalize the vector
	AMCAX_API void Normalize() noexcept;

	/// @brief Get the normalized vector
	/// @return The normalized vector
	[[nodiscard]] AMCAX_API std::shared_ptr<Geom2GeneralVector> Normalized() const;

	AMCAX_API void Transform(const Transformation2& tr) noexcept override;
	[[nodiscard]] AMCAX_API std::shared_ptr<Geom2Geometry> Copy() const override;
	AMCAX_API std::ostream& Write(std::ostream& os) const override;
	AMCAX_API std::istream& Read(std::istream& is) override;
};
} // namespace AMCAX
