/// @file      Geom2Point.hpp
/// @brief     Class of 2D point
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <geometry/Geom2Geometry.hpp>

namespace AMCAX
{
/// @brief Class of 2D point
class AMCAX_CLASS_API Geom2Point : public Geom2Geometry
{
public:
	/// @brief Construct from a point
	/// @param p The point
	AMCAX_API explicit Geom2Point(const Point2& p) noexcept;

	/// @brief Construct from the coordinates
	/// @param x,y The coordinates
	AMCAX_API Geom2Point(double x, double y) noexcept;

	/// @brief Set the coordinates
	/// @param x,y The coordinates
	AMCAX_API void SetCoord(double x, double y) noexcept;

	/// @brief Set the point
	/// @param p The point
	AMCAX_API void SetPoint(const Point2& p) noexcept;

	/// @brief Set the x coordinate
	/// @param x The x coordinate
	AMCAX_API void SetX(double x) noexcept;

	/// @brief Set the y coordinate
	/// @param y The y coordinate
	AMCAX_API void SetY(double y) noexcept;

	/// @brief Get the coordinates
	/// @param[out] x,y The coordinates
	AMCAX_API void GetCoord(double& x, double& y) const noexcept;

	/// @brief Get the internal point
	/// @return The point
	[[nodiscard]] AMCAX_API const Point2& Point() const noexcept;

	/// @brief Get the x coordinate
	/// @return The x coordinate
	[[nodiscard]] AMCAX_API double X() const noexcept;

	/// @brief Get the y coordinate
	/// @return The y coordinate
	[[nodiscard]] AMCAX_API double Y() const noexcept;

	/// @brief Compute the distance to the other point
	/// @param other The other point
	/// @return The distance to the other point
	[[nodiscard]] AMCAX_API double Distance(const std::shared_ptr<const Geom2Point>& other) const noexcept;

	/// @brief Compute the squared distance to the other point
	/// @param other The other point
	/// @return The squared distance to the other point
	[[nodiscard]] AMCAX_API double SquaredDistance(const std::shared_ptr<const Geom2Point>& other) const noexcept;

	AMCAX_API void Transform(const Transformation2& tr) noexcept override;
	[[nodiscard]] AMCAX_API std::shared_ptr<Geom2Geometry> Copy() const override;
	AMCAX_API std::ostream& Write(std::ostream& os) const override;
	AMCAX_API std::istream& Read(std::istream& is) override;

private:
	/// @brief Point data
	Point2 point;
};
} // namespace AMCAX
