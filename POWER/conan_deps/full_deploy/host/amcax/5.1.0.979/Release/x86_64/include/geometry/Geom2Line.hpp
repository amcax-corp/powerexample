/// @file      Geom2Line.hpp
/// @brief     Class of 2D line
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <geometry/Geom2Curve.hpp>
#include <math/LineT.hpp>

namespace AMCAX
{
/// @brief Class of 2D line
class AMCAX_CLASS_API Geom2Line : public Geom2Curve
{
public:
	/// @brief Default constructor
	constexpr Geom2Line() noexcept = default;

	/// @brief Construct from an axis
	/// @param axis The axis
	AMCAX_API explicit Geom2Line(const Axis2& axis) noexcept;

	/// @brief Construct from a line
	/// @param line The line
	AMCAX_API explicit Geom2Line(const Line2& line) noexcept;

	/// @brief Construct from a point and a direction
	/// @param point The location point
	/// @param dir The direction
	AMCAX_API Geom2Line(const Point2& point, const Direction2& dir) noexcept;

	/// @brief Set the line
	/// @param line The line
	AMCAX_API void SetLine(const Line2& line) noexcept;

	/// @brief Get the line
	/// @return The line
	[[nodiscard]] AMCAX_API Line2 Line() const noexcept;

	/// @brief Set the direction
	/// @param dir The direction
	AMCAX_API void SetDirection(const Direction2& dir) noexcept;

	/// @brief Get the direction
	/// @return The direction
	[[nodiscard]] AMCAX_API const Direction2& Direction() const noexcept;

	/// @brief Set the location point
	/// @param point The location point
	AMCAX_API void SetLocation(const Point2& point) noexcept;

	/// @brief Get the location point
	/// @return The location point
	[[nodiscard]] AMCAX_API const Point2& Location() const noexcept;

	/// @brief Set the axis
	/// @param axis The axis
	AMCAX_API void SetPosition(const Axis2& axis) noexcept;

	/// @brief Get the axis
	/// @return The axis
	[[nodiscard]] AMCAX_API const Axis2& Position() const noexcept;

	AMCAX_API void Reverse() noexcept override;
	[[nodiscard]] AMCAX_API double ReversedParameter(double u) const noexcept override;

	/// @brief Get the first parameter
	/// @details For a line, the first parameter is the negative infinity
	/// @return The first parameter
	[[nodiscard]] AMCAX_API double FirstParameter() const noexcept override;

	/// @brief Get the last parameter
	/// @details For a line, the last parameter is the positive infinity
	/// @return The last parameter
	[[nodiscard]] AMCAX_API double LastParameter() const noexcept override;

	/// @brief Is the line closed
	/// @return Always false
	[[nodiscard]] AMCAX_API bool IsClosed() const noexcept override;

	/// @brief Is the line periodic
	/// @return Always false
	[[nodiscard]] AMCAX_API bool IsPeriodic() const noexcept override;

	/// @brief Get the type of continuity of the line
	/// @return CN infinite continuity
	[[nodiscard]] AMCAX_API ContinuityType Continuity() const noexcept override;

	/// @brief Compute the distance to a point
	/// @param point The point
	/// @return The distance between the point and the line
	[[nodiscard]] AMCAX_API double Distance(const Point2& point) const noexcept;

	/// @brief Is the curve has an order n of continuity
	/// @param n The order of continuity
	/// @return Always true
	[[nodiscard]] AMCAX_API bool IsCN(int n) const noexcept override;

	AMCAX_API void D0(double u, Point2& p) const noexcept override;
	AMCAX_API void D1(double u, Point2& p, Vector2& v1) const noexcept override;
	AMCAX_API void D2(double u, Point2& p, Vector2& v1, Vector2& v2) const noexcept override;
	AMCAX_API void D3(double u, Point2& p, Vector2& v1, Vector2& v2, Vector2& v3) const noexcept override;
	[[nodiscard]] AMCAX_API Vector2 DN(double u, int n) const override;
	AMCAX_API void Transform(const Transformation2& tr) noexcept override;
	[[nodiscard]] AMCAX_API double TransformedParameter(double u, const Transformation2& tr) const noexcept override;
	[[nodiscard]] AMCAX_API double ParametricTransformation(const Transformation2& tr) const noexcept override;
	[[nodiscard]] AMCAX_API std::shared_ptr<Geom2Geometry> Copy() const override;
	AMCAX_API std::ostream& Write(std::ostream& os) const override;
	AMCAX_API std::istream& Read(std::istream& is) override;

	/// @brief Get the type of curve, a line
	/// @return Type line
	[[nodiscard]] AMCAX_API CurveType Type() const noexcept override;

private:
	/// @brief Axis of line
	Axis2 pos;
};
} // namespace AMCAX
