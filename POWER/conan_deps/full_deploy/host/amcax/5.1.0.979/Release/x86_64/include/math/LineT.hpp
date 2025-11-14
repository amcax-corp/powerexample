/// @file      LineT.hpp
/// @brief     Class of line
/// @details   Implementation of line
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <common/AxisT.hpp>
#include <common/FrameT.hpp>
#include <common/TransformationT.hpp>
#include <common/VectorT.hpp>

namespace AMCAX
{
/// @brief Base class of line
/// @tparam Derived Type of derived class
/// @tparam DIM Dimension
template<int DIM, typename Derived>
class LineBase
{
	[[nodiscard]] constexpr Derived& _derived() noexcept
	{
		return static_cast<Derived&>(*this);
	}

	[[nodiscard]] constexpr const Derived& _derived() const noexcept
	{
		return static_cast<const Derived&>(*this);
	}

public:
	/// @brief Default constructor
	constexpr LineBase() noexcept = default;

	/// @brief Construct from an axis
	/// @param axis The axis
	constexpr explicit LineBase(const AxisT<double, DIM>& axis) noexcept
		: pos(axis)
	{
	}

	/// @brief Construct from a point and a direction
	/// @param point The location point
	/// @param dir The line direction
	constexpr LineBase(const PointT<double, DIM>& point, const DirectionT<double, DIM>& dir) noexcept
		: pos(point, dir)
	{
	}

	/// @brief Set the location point of the line
	/// @param point The location point
	constexpr void SetLocation(const PointT<double, DIM>& point) noexcept
	{
		pos.SetLocation(point);
	}

	/// @brief Set the line direction
	/// @param dir The line direction
	constexpr void SetDirection(const DirectionT<double, DIM>& dir) noexcept
	{
		pos.SetDirection(dir);
	}

	/// @brief Set the axis of the line
	/// @param axis The axis
	constexpr void SetPosition(const AxisT<double, DIM>& axis) noexcept
	{
		pos = axis;
	}

	/// @brief Get the location point of the line
	/// @return The location point of the line
	[[nodiscard]] constexpr const PointT<double, DIM>& Location() const noexcept
	{
		return pos.Location();
	}

	/// @brief Get the direction of the line
	/// @return The direction of the line
	[[nodiscard]] constexpr const DirectionT<double, DIM>& Direction() const noexcept
	{
		return pos.Direction();
	}

	/// @brief Get the axis of the line
	/// @return The axis of the line
	[[nodiscard]] constexpr const AxisT<double, DIM>& Position() const noexcept
	{
		return pos;
	}

	/// @brief Compute the angle between the line and the other line
	/// @param other The other line
	/// @return The angle between the line and the other line
	[[nodiscard]] auto Angle(const LineBase& other) const noexcept
	{
		return pos.Direction().Angle(other.pos.Direction());
	}

	/// @brief Does the line contain a point under a distance tolerance
	/// @param p The point
	/// @param tol The tolerance
	/// @return True if the point is on the line under the tolerance
	[[nodiscard]] bool Contains(const PointT<double, DIM>& p, double tol) const noexcept
	{
		return _derived().Distance(p) <= tol;
	}

	/// @brief Reverse the line direction
	/// @return The reference to self
	constexpr Derived& Reverse() noexcept
	{
		pos.Reverse();
		return _derived();
	}

	/// @brief Get the line with reversed direction
	/// @return The line with reversed direction
	[[nodiscard]] constexpr Derived Reversed() const noexcept
	{
		return Derived(_derived()).Reverse();
	}

	/// @brief Mirror the line by a point
	/// @param point The mirror center point
	/// @return The reference to self
	constexpr Derived& Mirror(const PointT<double, DIM>& point) noexcept
	{
		pos.Mirror(point);
		return _derived();
	}

	/// @brief Get the line mirrored by a point
	/// @param point The mirror center point
	/// @return The mirrored line
	[[nodiscard]] constexpr Derived Mirrored(const PointT<double, DIM>& point) const noexcept
	{
		return Derived(_derived()).Mirror(point);
	}

	/// @brief Mirror the line by an axis
	/// @param axis The mirror axis
	/// @return The reference to self
	constexpr Derived& Mirror(const AxisT<double, DIM>& axis) noexcept
	{
		pos.Mirror(axis);
		return _derived();
	}

	/// @brief Get the line mirrored by an axis
	/// @param axis The mirror axis
	/// @return The mirrored line
	[[nodiscard]] constexpr Derived Mirrored(const AxisT<double, DIM>& axis) const noexcept
	{
		return Derived(_derived()).Mirror(axis);
	}

	/// @brief Scale the line by a point
	/// @param point The scaling center point
	/// @param scale The scale value
	/// @return The reference to self
	constexpr Derived& Scale(const PointT<double, DIM>& point, double scale) noexcept
	{
		pos.Scale(point, scale);
		return _derived();
	}

	/// @brief Get the line scaled by a point
	/// @param point The scaling center point
	/// @param scale The scale value
	/// @return The scaled line
	[[nodiscard]] constexpr Derived Scaled(const PointT<double, DIM>& point, double scale) const noexcept
	{
		return Derived(_derived()).Scale(point, scale);
	}

	/// @brief Transform the line
	/// @param tr The transformation
	/// @return The reference to self
	Derived& Transform(const TransformationT<double, DIM>& tr) noexcept
	{
		pos.Transform(tr);
		return _derived();
	}

	/// @brief Get the transformed line
	/// @param tr The transformation
	/// @return The transformed line
	[[nodiscard]] Derived Transformed(const TransformationT<double, DIM>& tr) const noexcept
	{
		return Derived(_derived()).Transform(tr);
	}

	/// @brief Translate the line by a vector
	/// @param vec The translation vector
	/// @return The reference to self
	constexpr Derived& Translate(const VectorT<double, DIM>& vec) noexcept
	{
		pos.Translate(vec);
		return _derived();
	}

	/// @brief Get the line translated by a vector
	/// @param vec The translation vector
	/// @return The translated line
	[[nodiscard]] constexpr Derived Translated(const VectorT<double, DIM>& vec) const noexcept
	{
		return Derived(_derived()).Translate(vec);
	}

	/// @brief Translate the line by a vector from a point to another point
	/// @param p1 The source point
	/// @param p2 The target point
	/// @return The reference to self
	constexpr Derived& Translate(const PointT<double, DIM>& p1, const PointT<double, DIM>& p2) noexcept
	{
		pos.Translate(p1, p2);
		return _derived();
	}

	/// @brief Get the line translated by a vector from a point to another point
	/// @param p1 The source point
	/// @param p2 The target point
	/// @return The translated line
	[[nodiscard]] constexpr Derived Translated(const PointT<double, DIM>& p1, const PointT<double, DIM>& p2) const noexcept
	{
		return Derived(_derived()).Translate(p1, p2);
	}

protected:
	/// @brief The axis of line
	AxisT<double, DIM> pos;
};

/// @brief Class of line
/// @tparam DIM Dimension
template<int DIM>
class LineS : public LineBase<DIM, LineS<DIM>>
{
	static_assert(DIM == 2 || DIM == 3);
};

/// @brief Class of 2D line
template<>
class LineS<2> : public LineBase<2, LineS<2>>
{
	using Base = LineBase<2, LineS<2>>;
	using Base::pos;

public:
	using Base::Base;

	/// @brief Construct from the algebraic coefficients of 2D line
	/// @param a,b,c The coefficients
	LineS(double a, double b, double c)
		: Base(Point2(-a * c / (a * a + b * b), -b * c / (a * a + b * b)), Direction2(-b, a))
	{
		Throw_Construction_Error_if(a * a + b * b <= std::numeric_limits<double>::min(), "invalid line construction");
	}

	/// @brief Get the coefficients of the algebraic representation of the 2D line
	/// @param[out] a,b,c The coefficients
	constexpr void Coefficients(double& a, double& b, double& c) const noexcept
	{
		a = pos.Direction().Y();
		b = -pos.Direction().X();
		c = -(a * pos.Location().X() + b * pos.Location().Y());
	}

	/// @brief Compute the distance from a point to the line
	/// @param p The point
	/// @return The distance between the point and the line
	[[nodiscard]] auto Distance(const Point2& p) const noexcept
	{
		return (p.Coord() - pos.Location().Coord() - pos.Direction().Coord() * (p.Coord() - pos.Location().Coord()).Dot(pos.Direction().Coord())).Norm();
	}

	/// @brief Compute the squared distance from a point to the line
	/// @param p The point
	/// @return The squared distance between the point and the line
	[[nodiscard]] constexpr auto SquaredDistance(const Point2& p) const noexcept
	{
		return (p.Coord() - pos.Location().Coord() - pos.Direction().Coord() * (p.Coord() - pos.Location().Coord()).Dot(pos.Direction().Coord())).SquaredNorm();
	}

	/// @brief Compute the distance between two lines
	/// @param l The other line
	/// @return The distance between two lines
	[[nodiscard]] auto Distance(const LineS& l) const noexcept
	{
		if (pos.IsParallel(l.Position(), std::numeric_limits<double>::min()))
		{
			return Distance(l.Location());
		}
		else
		{
			return 0.0;
		}
	}

	/// @brief Compute the squared distance between two lines
	/// @param l The other line
	/// @return The squared distance between two lines
	[[nodiscard]] auto SquaredDistance(const LineS& l) const noexcept
	{
		if (pos.IsParallel(l.Position(), std::numeric_limits<double>::min()))
		{
			return SquaredDistance(l.Location());
		}
		else
		{
			return 0.0;
		}
	}

	/// @brief Get a line passing through a point and perpendicular to the line
	/// @param p The point
	/// @return The line passing through a point and perpendicular to the line
	[[nodiscard]] constexpr LineS Normal(const Point2& p) const noexcept
	{
		return LineS(p, Frame2(pos).YDirection());
	}

	/// @brief Rotate the line around a point with an angle in 2D
	/// @param point The rotation center point
	/// @param angle The rotation angle
	/// @return The reference to self
	LineS& Rotate(const Point2& point, double angle) noexcept
	{
		pos.Rotate(point, angle);
		return *this;
	}

	/// @brief Get the line rotated around a point with an angle in 2D
	/// @param point The rotation center point
	/// @param angle The rotation angle
	/// @return The rotated line
	[[nodiscard]] LineS Rotated(const Point2& point, double angle) const noexcept
	{
		return LineS(*this).Rotate(point, angle);
	}
};

/// @brief Class of 3D line
template<>
class LineS<3> : public LineBase<3, LineS<3>>
{
	using Base = LineBase<3, LineS<3>>;
	using Base::pos;

public:
	using Base::Base;

	/// @brief Compute the distance from a point to the line
	/// @param p The point
	/// @return The distance between the point and the line
	[[nodiscard]] auto Distance(const Point3& p) const noexcept
	{
		return (p.Coord() - pos.Location().Coord() - pos.Direction().Coord() * (p.Coord() - pos.Location().Coord()).Dot(pos.Direction().Coord())).Norm();
	}

	/// @brief Compute the squared distance from a point to the line
	/// @param p The point
	/// @return The squared distance between the point and the line
	[[nodiscard]] constexpr auto SquaredDistance(const Point3& p) const noexcept
	{
		return (p.Coord() - pos.Location().Coord() - pos.Direction().Coord() * (p.Coord() - pos.Location().Coord()).Dot(pos.Direction().Coord())).SquaredNorm();
	}

	/// @brief Compute the distance between two lines
	/// @param l The other line
	/// @return The distance between two lines
	[[nodiscard]] auto Distance(const LineS& l) const noexcept
	{
		if (pos.IsParallel(l.Position(), std::numeric_limits<double>::min()))
		{
			return Distance(l.Location());
		}
		else
		{
			auto dir = pos.Direction().Coord().Cross(l.Direction().Coord()).Normalized();
			return std::fabs((l.Location().Coord() - pos.Location().Coord()).Dot(dir));
		}
	}

	/// @brief Compute the squared distance between two lines
	/// @param l The other line
	/// @return The squared distance between two lines
	[[nodiscard]] auto SquaredDistance(const LineS& l) const noexcept
	{
		if (pos.IsParallel(l.Position(), std::numeric_limits<double>::min()))
		{
			return SquaredDistance(l.Location());
		}
		else
		{
			auto dir = pos.Direction().Coord().Cross(l.Direction().Coord()).Normalized();
			auto d = (l.Location().Coord() - pos.Location().Coord()).Dot(dir);
			return d * d;
		}
	}

	/// @brief Get a line passing through a point and perpendicular to the line
	/// @param p The point
	/// @return The line passing through a point and perpendicular to the line
	[[nodiscard]] LineS Normal(const Point3& p) const
	{
		return LineS(p, Direction3(pos.Direction().Coord().Cross((p.Coord() - pos.Location().Coord()).Cross(pos.Direction().Coord()))));
	}

	/// @brief Mirror the line by a frame
	/// @param frame The mirror frame
	/// @return The reference to self
	constexpr LineS& Mirror(const Frame3& frame) noexcept
	{
		pos.Mirror(frame);
		return *this;
	}

	/// @brief Get the line mirrored by a frame
	/// @param frame The mirror frame
	/// @return The mirrored line
	[[nodiscard]] constexpr LineS Mirrored(const Frame3& frame) const noexcept
	{
		return LineS(*this).Mirror(frame);
	}

	/// @brief Rotate the line around an axis with an angle in 3D
	/// @param axis The rotation axis
	/// @param angle The rotation angle
	/// @return The reference to self
	LineS& Rotate(const Axis3& axis, double angle) noexcept
	{
		pos.Rotate(axis, angle);
		return *this;
	}

	/// @brief Get the line rotated around an axis with an angle in 3D
	/// @param axis The rotation axis
	/// @param angle The rotation angle
	/// @return The rotated line
	[[nodiscard]] LineS Rotated(const Axis3& axis, double angle) const noexcept
	{
		return LineS(*this).Rotate(axis, angle);
	}
};

/// @brief Compatible alias of LineS
/// @tparam Scalar Type of scalar value
/// @tparam DIM Dimension
template<typename Scalar, int DIM>
using LineT = LineS<DIM>;

/// @brief 2D line
using Line2 = LineS<2>;

/// @brief 3D line
using Line3 = LineS<3>;

} // namespace AMCAX
