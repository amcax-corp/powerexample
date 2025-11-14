/// @file      Geom3Point.hpp
/// @brief     Class of 3D point
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <geometry/Geom3Geometry.hpp>

namespace AMCAX
{
/// @brief Class of 3D point
class AMCAX_CLASS_API Geom3Point : public Geom3Geometry
{
public:
	/// @brief Construct from a point
	/// @param p The point
	AMCAX_API explicit Geom3Point(const Point3& p) noexcept;

	/// @brief Construct from the coordinates
	/// @param x,y,z The coordinates
	AMCAX_API Geom3Point(double x, double y, double z) noexcept;

	/// @brief Set the coordinates
	/// @param x,y,z The coordinates
	AMCAX_API void SetCoord(double x, double y, double z) noexcept;

	/// @brief Set the point
	/// @param p The point
	AMCAX_API void SetPoint(const Point3& p) noexcept;

	/// @brief Set the x coordinate
	/// @param x The x coordinate
	AMCAX_API void SetX(double x) noexcept;

	/// @brief Set the y coordinate
	/// @param y The y coordinate
	AMCAX_API void SetY(double y) noexcept;

	/// @brief Set the z coordinate
	/// @param z The z coordinate
	AMCAX_API void SetZ(double z) noexcept;

	/// @brief Get the coordinates
	/// @param[out] x,y,z The coordinates
	AMCAX_API void GetCoord(double& x, double& y, double& z) const noexcept;

	/// @brief Get the internal point
	/// @return The point
	[[nodiscard]] AMCAX_API const Point3& Point() const noexcept;

	/// @brief Get the x coordinate
	/// @return The x coordinate
	[[nodiscard]] AMCAX_API double X() const noexcept;

	/// @brief Get the y coordinate
	/// @return The y coordinate
	[[nodiscard]] AMCAX_API double Y() const noexcept;

	/// @brief Get the z coordinate
	/// @return The z coordinate
	[[nodiscard]] AMCAX_API double Z() const noexcept;

	/// @brief Compute the distance to the other point
	/// @param other The other point
	/// @return The distance to the other point
	[[nodiscard]] AMCAX_API double Distance(const std::shared_ptr<const Geom3Point>& other) const noexcept;

	/// @brief Compute the squared distance to the other point
	/// @param other The other point
	/// @return The squared distance to the other point
	[[nodiscard]] AMCAX_API double SquaredDistance(const std::shared_ptr<const Geom3Point>& other) const noexcept;

	AMCAX_API void Transform(const Transformation3& tr) noexcept override;
	[[nodiscard]] AMCAX_API std::shared_ptr<Geom3Geometry> Copy() const override;
	AMCAX_API std::ostream& Write(std::ostream& os) const override;
	AMCAX_API std::istream& Read(std::istream& is) override;

private:
	Point3 point;
};
} // namespace AMCAX
