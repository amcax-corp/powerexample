/// @file      Geom2Circle.hpp
/// @brief     Class of 2D circle
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <geometry/Geom2Conic.hpp>
#include <math/CircleT.hpp>

namespace AMCAX
{
/// @brief Class of 2D circle
class AMCAX_CLASS_API Geom2Circle : public Geom2Conic
{
public:
	/// @brief Default constructor
	Geom2Circle() noexcept = default;

	/// @brief Construct from a circle
	/// @param c The circle
	AMCAX_API explicit Geom2Circle(const Circle2& c) noexcept;

	/// @brief Construct from an axis and a radius
	/// @param axis The axis
	/// @param r The radius
	/// @param isRight Is the local frame right-handed
	AMCAX_API Geom2Circle(const Axis2& axis, double r, bool isRight = true);

	/// @brief Construct from a local frame and a radius
	/// @param frame The local frame
	/// @param r The radius
	AMCAX_API Geom2Circle(const Frame2& frame, double r);

	/// @brief Set the circle
	/// @param c The circle
	AMCAX_API void SetCircle(const Circle2& c) noexcept;

	/// @brief Set the radius
	/// @param r The radius
	AMCAX_API void SetRadius(double r);

	/// @brief Get the circle
	/// @return The circle
	[[nodiscard]] AMCAX_API Circle2 Circle() const noexcept;

	/// @brief Get the radius
	/// @return The radius
	[[nodiscard]] AMCAX_API double Radius() const noexcept;

	[[nodiscard]] AMCAX_API double ReversedParameter(double u) const noexcept override;

	/// @brief Get the eccentricity
	/// @details For a circle, the eccentricity is 0
	/// @return The eccentricity
	[[nodiscard]] AMCAX_API double Eccentricity() const noexcept override;

	/// @brief Get the first parameter
	/// @details For a circle, the first parameter is 0
	/// @return The first parameter
	[[nodiscard]] AMCAX_API double FirstParameter() const noexcept override;

	/// @brief Get the last parameter
	/// @details For a circle, the last parameter is 2pi
	/// @return The last parameter
	[[nodiscard]] AMCAX_API double LastParameter() const noexcept override;

	/// @brief Is the circle closed
	/// @return Always true
	[[nodiscard]] AMCAX_API bool IsClosed() const noexcept override;

	/// @brief Is the circle periodic
	/// @return Always true
	[[nodiscard]] AMCAX_API bool IsPeriodic() const noexcept override;

	AMCAX_API void D0(double u, Point2& p) const noexcept override;
	AMCAX_API void D1(double u, Point2& p, Vector2& v1) const noexcept override;
	AMCAX_API void D2(double u, Point2& p, Vector2& v1, Vector2& v2) const noexcept override;
	AMCAX_API void D3(double u, Point2& p, Vector2& v1, Vector2& v2, Vector2& v3) const noexcept override;
	AMCAX_API Vector2 DN(double u, int n) const override;
	AMCAX_API void Transform(const Transformation2& tr) noexcept override;
	AMCAX_API std::shared_ptr<Geom2Geometry> Copy() const override;
	AMCAX_API std::ostream& Write(std::ostream& os) const override;
	AMCAX_API std::istream& Read(std::istream& is) override;

	/// @brief Get the type of curve, a circle
	/// @return Type circle
	[[nodiscard]] AMCAX_API CurveType Type() const noexcept override;

private:
	void CheckValidity() const;

	double radius = std::numeric_limits<double>::max();
};
} // namespace AMCAX
