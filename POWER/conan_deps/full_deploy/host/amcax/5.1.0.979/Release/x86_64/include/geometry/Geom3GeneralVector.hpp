/// @file      Geom3GeneralVector.hpp
/// @brief     Class of 3D general vector
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <geometry/Geom3Vector.hpp>

namespace AMCAX
{
/// @brief Class of 3D general vector
class AMCAX_CLASS_API Geom3GeneralVector : public Geom3Vector
{
public:
	/// @brief Construct from a vector
	/// @param v The vector
	AMCAX_API explicit Geom3GeneralVector(const Vector3& v) noexcept;

	/// @brief Construct from coordinates
	/// @param x,y,z The coordinates
	AMCAX_API Geom3GeneralVector(double x, double y, double z) noexcept;

	/// @brief Construct from two points
	/// @param p1 The source point
	/// @param p2 The target point
	AMCAX_API Geom3GeneralVector(const Point3& p1, const Point3& p2) noexcept;

	/// @brief Set the coordinates
	/// @param x,y,z The coordinates
	AMCAX_API void SetCoord(double x, double y, double z) noexcept;

	/// @brief Set the vector
	/// @param v The vector
	AMCAX_API void SetVector(const Vector3& v) noexcept;

	/// @brief Set the x coordinate
	/// @param x The x coordinate
	AMCAX_API void SetX(double x) noexcept;

	/// @brief Set the y coordinate
	/// @param y The y coordinate
	AMCAX_API void SetY(double y) noexcept;

	/// @brief Set the z coordinate
	/// @param z The z coordinate
	AMCAX_API void SetZ(double z) noexcept;

	/// @brief Compute the norm of the vector
	/// @return The norm of the vector
	[[nodiscard]] AMCAX_API double Norm() const noexcept override;

	/// @brief Compute the squared norm of the vector
	/// @return The squared norm of the vector
	[[nodiscard]] AMCAX_API double SquaredNorm() const noexcept override;

	/// @brief Compute the cross product by the other vector
	/// @param other The other vector
	/// @return The result of cross product
	[[nodiscard]] AMCAX_API std::shared_ptr<Geom3Vector> Cross(const std::shared_ptr<const Geom3Vector>& other) const override;

	/// @brief Normalize the vector
	AMCAX_API void Normalize() noexcept;

	/// @brief Get the normalized vector
	/// @return The normalized vector
	[[nodiscard]] AMCAX_API std::shared_ptr<Geom3GeneralVector> Normalized() const;

	AMCAX_API void Transform(const Transformation3& tr) noexcept override;
	[[nodiscard]] AMCAX_API std::shared_ptr<Geom3Geometry> Copy() const override;
	AMCAX_API std::ostream& Write(std::ostream& os) const override;
	AMCAX_API std::istream& Read(std::istream& is) override;
};
} // namespace AMCAX
