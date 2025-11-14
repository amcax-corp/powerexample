/// @file      Geom3Direction.hpp
/// @brief     Class of 3D direction
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <geometry/Geom3Vector.hpp>

namespace AMCAX
{
/// @brief Class of 3D direction, which is a normalized vector
class AMCAX_CLASS_API Geom3Direction : public Geom3Vector
{
public:
	/// @brief Construct from a direction
	/// @param v The direction
	AMCAX_API explicit Geom3Direction(const Direction3& v) noexcept;

	/// @brief Construct from coordinates
	/// @param x,y,z The coordinates
	AMCAX_API Geom3Direction(double x, double y, double z);

	/// @brief Set the coordinates
	/// @param x,y,z The coordinates
	AMCAX_API void SetCoord(double x, double y, double z);

	/// @brief Set the direction
	/// @param v The direction
	AMCAX_API void SetDirection(const Direction3& v) noexcept;

	/// @brief Set the x coordinate
	/// @details The coordinate can be changed due to the normalization
	/// @param x The x coordinate
	AMCAX_API void SetX(double x);

	/// @brief Set the y coordinate
	/// @details The coordinate can be changed due to the normalization
	/// @param y The y coordinate
	AMCAX_API void SetY(double y);

	/// @brief Set the z coordinate
	/// @details The coordinate can be changed due to the normalization
	/// @param z The z coordinate
	AMCAX_API void SetZ(double z);

	/// @brief Get the direction
	/// @details Perform normalization when constructing a Direction3 object.
	/// @return The direction
	[[nodiscard]] AMCAX_API Direction3 Direction() const;

	/// @brief Compute the norm of the direction
	/// @return The norm of the direction
	[[nodiscard]] AMCAX_API double Norm() const noexcept override;

	/// @brief Compute the squared norm of the direction
	/// @return The squared norm of the direction
	[[nodiscard]] AMCAX_API double SquaredNorm() const noexcept override;

	/// @brief Compute the cross product by the other vector
	/// @param other The other vector
	/// @return The result of cross product is a direction
	[[nodiscard]] AMCAX_API std::shared_ptr<Geom3Vector> Cross(const std::shared_ptr<const Geom3Vector>& other) const override;

	AMCAX_API void Transform(const Transformation3& tr) override;
	[[nodiscard]] AMCAX_API std::shared_ptr<Geom3Geometry> Copy() const override;
	AMCAX_API std::ostream& Write(std::ostream& os) const override;
	AMCAX_API std::istream& Read(std::istream& is) override;

private:
	void CheckValidity() const;
};
} // namespace AMCAX
