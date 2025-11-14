/// @file      Geom2Direction.hpp
/// @brief     Class of 2D direction
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <geometry/Geom2Vector.hpp>

namespace AMCAX
{
/// @brief Class of 2D direction, which is a normalized vector
class AMCAX_CLASS_API Geom2Direction : public Geom2Vector
{
public:
	/// @brief Construct from a direction
	/// @param v The direction
	AMCAX_API explicit Geom2Direction(const Direction2& v) noexcept;

	/// @brief Construct from coordinates
	/// @param x,y The coordinates
	AMCAX_API Geom2Direction(double x, double y);

	/// @brief Set the coordinates
	/// @param x,y The coordinates
	AMCAX_API void SetCoord(double x, double y);

	/// @brief Set the direction
	/// @param v The direction
	AMCAX_API void SetDirection(const Direction2& v) noexcept;

	/// @brief Set the x coordinate
	/// @details The coordinate can be changed due to the normalization
	/// @param x The x coordinate
	AMCAX_API void SetX(double x);

	/// @brief Set the y coordinate
	/// @details The coordinate can be changed due to the normalization
	/// @param y The y coordinate
	AMCAX_API void SetY(double y);

	/// @brief Get the direction
	/// @details Perform normalization when constructing a Direction2 object.
	/// @return The direction
	[[nodiscard]] AMCAX_API Direction2 Direction() const noexcept;

	/// @brief Compute the norm of the direction
	/// @return The norm of the direction
	[[nodiscard]] AMCAX_API double Norm() const noexcept override;

	/// @brief Compute the squared norm of the direction
	/// @return The squared norm of the direction
	[[nodiscard]] AMCAX_API double SquaredNorm() const noexcept override;

	AMCAX_API void Transform(const Transformation2& tr) noexcept override;
	[[nodiscard]] AMCAX_API std::shared_ptr<Geom2Geometry> Copy() const override;
	AMCAX_API std::ostream& Write(std::ostream& os) const override;
	AMCAX_API std::istream& Read(std::istream& is) override;

private:
	void CheckValidity() const;
};
} // namespace AMCAX
