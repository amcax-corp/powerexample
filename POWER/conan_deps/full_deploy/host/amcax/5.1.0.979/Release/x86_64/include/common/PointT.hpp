/// @file      PointT.hpp
/// @brief     Class of point
/// @details   Implementation of point
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <common/CoordT.hpp>
#include <common/TransformationType.hpp>

namespace AMCAX
{
template<typename Scalar, int DIM>
class AxisT;
template<typename Scalar, int DIM>
class FrameT;
template<typename Scalar, int DIM>
class TransformationT;
template<typename Scalar, int DIM>
class VectorT;

/// @brief Template class of point
/// @tparam Scalar The type of scalar
/// @tparam DIM Dimension of the point
template<typename Scalar, int DIM>
class PointT
{
public:
	/// @brief The type of coordinate
	using CoordType = CoordT<Scalar, DIM>;

	/// @brief Default constructor
	/// @details The default point is (0, 0, ..., 0)
	constexpr PointT() noexcept = default;

	/// @brief Construct from a coordinate
	/// @param v The coordinate
	constexpr explicit PointT(const CoordType& v) noexcept
		: coord(v)
	{
	}

	/// @brief Construct from components
	/// @tparam ...T Types of values
	/// @param ...vs Values
	template<typename... T, std::enable_if_t<static_cast<int>(sizeof...(T)) == DIM && are_convertible_v<Scalar, T...>, int> = 0>
	constexpr explicit PointT(T&&... vs) noexcept
		: coord(std::forward<T>(vs)...)
	{
	}

	/// @brief Set component values
	/// @tparam ...T Types of values
	/// @param ...vs Values
	template<typename... T, std::enable_if_t<static_cast<int>(sizeof...(T)) == DIM && are_convertible_v<Scalar, T...>, int> = 0>
	constexpr void SetCoord(T&&... vs) & noexcept
	{
		coord.SetCoord(std::forward<T>(vs)...);
	}

	/// @brief Set the coordinate of point
	/// @param v The coordinate
	constexpr void SetCoord(const CoordType& v) & noexcept
	{
		coord = v;
	}

	/// @brief Set the x-coordinate, only available when DIM >= 1
	/// @tparam OtherScalar The type of value
	/// @param x New x-coordinate value
	template<typename OtherScalar, std::enable_if_t<std::is_convertible_v<OtherScalar, Scalar> && DIM >= 1, int> = 0>
	constexpr void SetX(const OtherScalar& x) & noexcept
	{
		coord.SetX(x);
	}

	/// @brief Set the y-coordinate, only available when DIM >= 2
	/// @tparam OtherScalar The type of value
	/// @param y New y-coordinate value
	template<typename OtherScalar, std::enable_if_t<std::is_convertible_v<OtherScalar, Scalar> && DIM >= 2, int> = 0>
	constexpr void SetY(const OtherScalar& y) & noexcept
	{
		coord.SetY(y);
	}

	/// @brief Set the z-coordinate, only available when DIM >= 3
	/// @tparam OtherScalar The type of value
	/// @param z New z-coordinate value
	template<typename OtherScalar, std::enable_if_t<std::is_convertible_v<OtherScalar, Scalar> && DIM >= 3, int> = 0>
	constexpr void SetZ(const OtherScalar& z) & noexcept
	{
		coord.SetZ(z);
	}

	/// @brief Set the w-coordinate, only available when DIM >= 4
	/// @tparam OtherScalar The type of value
	/// @param w New w-coordinate value
	template<typename OtherScalar, std::enable_if_t<std::is_convertible_v<OtherScalar, Scalar> && DIM >= 4, int> = 0>
	constexpr void SetW(const OtherScalar& w) & noexcept
	{
		coord.SetW(w);
	}

	/// @brief Get the i-th component
	/// @return The const reference to the i-th compenent
	[[nodiscard]] constexpr const Scalar& operator[](int i) const noexcept
	{
		return coord[i];
	}

	/// @brief Get the i-th component
	/// @return The reference to the i-th compenent
	[[nodiscard]] constexpr Scalar& operator[](int i) noexcept
	{
		return coord[i];
	}

	/// @brief Get x-coordinate of a point, only available when DIM >= 1
	/// @return The value of x-coordinate
	template<int DIM2 = DIM, std::enable_if_t<DIM2 >= 1, int> = 0>
	[[nodiscard]] constexpr const Scalar& X() const noexcept
	{
		return coord.X();
	}

	/// @brief Get y-coordinate of a point, only available when DIM >= 2
	/// @return The value of y-coordinate
	template<int DIM2 = DIM, std::enable_if_t<DIM2 >= 2, int> = 0>
	[[nodiscard]] constexpr const Scalar& Y() const noexcept
	{
		return coord.Y();
	}

	/// @brief Get z-coordinate of a point, only available when DIM >= 3
	/// @return The value of z-coordinate
	template<int DIM2 = DIM, std::enable_if_t<DIM2 >= 3, int> = 0>
	[[nodiscard]] constexpr const Scalar& Z() const noexcept
	{
		return coord.Z();
	}

	/// @brief Get w-coordinate of a point, only available when DIM >= 4
	/// @return The value of w-coordinate
	template<int DIM2 = DIM, std::enable_if_t<DIM2 >= 4, int> = 0>
	[[nodiscard]] constexpr const Scalar& W() const noexcept
	{
		return coord.W();
	}

	/// @brief Get the coordinate of point
	/// @return The const reference to the coordinate of point
	[[nodiscard]] constexpr const CoordType& Coord() const noexcept
	{
		return coord;
	}

	/// @brief Get the coordinate of point
	/// @return The reference to the coordinate of point
	[[nodiscard]] constexpr CoordType& Coord() noexcept
	{
		return coord;
	}

	/// @brief Determine the point equals the other point w.r.t. the tolerance
	/// @tparam OtherScalar The scalar type of other point
	/// @tparam OtherScalar2 The type of tolerance
	/// @param other The other point
	/// @param tol The tolerance
	/// @return True if all the components of the two points are within the tolerance
	template<typename OtherScalar, typename OtherScalar2>
	[[nodiscard]] bool IsEqual(const PointT<OtherScalar, DIM>& other, const OtherScalar2& tol) const noexcept
	{
		return coord.IsEqual(other.Coord(), tol);
	}

	/// @brief Compute the Euclidean distance from the other point
	/// @tparam OtherScalar The scalar type of other point
	/// @param other The other point
	/// @return The distance value
	template<typename OtherScalar>
	[[nodiscard]] auto Distance(const PointT<OtherScalar, DIM>& other) const noexcept
	{
		return (coord - other.Coord()).Norm();
	}

	/// @brief Compute the squared distance from the other point
	/// @tparam OtherScalar The scalar type of other point
	/// @param other The other point
	/// @return The squared distance value
	template<typename OtherScalar>
	[[nodiscard]] constexpr auto SquaredDistance(const PointT<OtherScalar, DIM>& other) const noexcept
	{
		return (coord - other.Coord()).SquaredNorm();
	}

	/// @brief Mirror the point by a center point
	/// @tparam OtherScalar The scalar type of the center point
	/// @param p The center point
	/// @return The reference to self
	template<typename OtherScalar>
	constexpr PointT& Mirror(const PointT<OtherScalar, DIM>& p) noexcept
	{
		coord = -coord + p.Coord() * OtherScalar{2};
		return *this;
	}

	/// @brief Compute the mirrored point w.r.t. a center point
	/// @tparam OtherScalar The scalar type of the center point
	/// @param p The center point
	/// @return The mirrored point
	template<typename OtherScalar>
	[[nodiscard]] constexpr PointT Mirrored(const PointT<OtherScalar, DIM>& p) const noexcept
	{
		return PointT(*this).Mirror(p);
	}

	/// @brief Mirror the point by an axis
	/// @tparam OtherScalar The scalar type of the axis
	/// @param axis The axis
	/// @return The reference to self
	template<typename OtherScalar>
	constexpr PointT& Mirror(const AxisT<OtherScalar, DIM>& axis) noexcept
	{
		TransformationT<OtherScalar, DIM> tr;
		tr.SetMirror(axis);
		tr.Transform(coord);
		return *this;
	}

	/// @brief Compute the mirrored point w.r.t. an axis
	/// @tparam OtherScalar The scalar type of the axis
	/// @param axis The axis
	/// @return The mirrored point
	template<typename OtherScalar>
	[[nodiscard]] constexpr PointT Mirrored(const AxisT<OtherScalar, DIM>& axis) const noexcept
	{
		return PointT(*this).Mirror(axis);
	}

	/// @brief Mirror the point by a plane/line with a frame
	/// @tparam OtherScalar The scalar type of the frame
	/// @param frame The frame whose main direction is the normal direction
	/// @return The reference to self
	template<typename OtherScalar, int DIM2 = DIM, std::enable_if_t<DIM2 == 3, int> = 0>
	constexpr PointT& Mirror(const FrameT<OtherScalar, DIM>& frame) noexcept
	{
		TransformationT<OtherScalar, DIM> tr;
		tr.SetMirror(frame);
		tr.Transform(coord);
		return *this;
	}

	/// @brief Compute the mirrored point w.r.t. a plane/line with a frame
	/// @tparam OtherScalar The scalar type of the frame
	/// @param frame The frame whose main direction is the normal direction
	/// @return The mirrored point
	template<typename OtherScalar, int DIM2 = DIM, std::enable_if_t<DIM2 == 3, int> = 0>
	[[nodiscard]] constexpr PointT Mirrored(const FrameT<OtherScalar, DIM>& frame) const noexcept
	{
		return PointT(*this).Mirror(frame);
	}

	/// @brief Rotate the point related to a roatation center and an angle, only available when DIM = 2
	/// @tparam OtherScalar The scalar type of the rotation center
	/// @tparam OtherScalar2 The type of angle
	/// @param point The rotation center
	/// @param angle The rotation angle
	/// @return The reference to self
	template<typename OtherScalar, typename OtherScalar2, int DIM2 = DIM, std::enable_if_t<DIM2 == 2, int> = 0>
	PointT& Rotate(const PointT<OtherScalar, DIM>& point, const OtherScalar2& angle) noexcept
	{
		TransformationT<OtherScalar, DIM> tr;
		tr.SetRotation(point, angle);
		tr.Transform(coord);
		return *this;
	}

	/// @brief Compute the rotated point related to a rotation center and an angle, only avaliable when DIM = 2
	/// @tparam OtherScalar The scalar type of the rotation center
	/// @tparam OtherScalar2 The type of angle
	/// @param point The rotation center
	/// @param angle The rotation angle
	/// @return The rotated point
	template<typename OtherScalar, typename OtherScalar2, int DIM2 = DIM, std::enable_if_t<DIM2 == 2, int> = 0>
	[[nodiscard]] PointT Rotated(const PointT<OtherScalar, DIM>& point, const OtherScalar2& angle) const noexcept
	{
		return PointT(*this).Rotate(point, angle);
	}

	/// @brief Rotate the point related to an axis with an angle, only available when DIM = 3
	/// @tparam OtherScalar The scalar type of the rotation axis
	/// @tparam OtherScalar2 The type of angle
	/// @param axis The rotation axis
	/// @param angle The rotation angle
	/// @return The reference to self
	template<typename OtherScalar, typename OtherScalar2, int DIM2 = DIM, std::enable_if_t<DIM2 == 3, int> = 0>
	PointT& Rotate(const AxisT<OtherScalar, DIM>& axis, const OtherScalar2& angle) noexcept
	{
		TransformationT<OtherScalar, DIM> tr;
		tr.SetRotation(axis, angle);
		tr.Transform(coord);
		return *this;
	}

	/// @brief Compute the rotated point related to an axis with an angle, only available when DIM = 3
	/// @tparam OtherScalar The scalar type of the rotation axis
	/// @tparam OtherScalar2 The type of angle
	/// @param axis The rotation axis
	/// @param angle The rotation angle
	/// @return The rotated point
	template<typename OtherScalar, typename OtherScalar2, int DIM2 = DIM, std::enable_if_t<DIM2 == 3, int> = 0>
	[[nodiscard]] PointT Rotated(const AxisT<OtherScalar, DIM>& axis, const OtherScalar2& angle) const noexcept
	{
		return PointT(*this).Rotate(axis, angle);
	}

	/// @brief Scale the point w.r.t. a center point with a scale
	/// @tparam OtherScalar The scalar type of the center point
	/// @tparam OtherScalar2 The type of the scale
	/// @param point The center point
	/// @param scale The scale
	/// @return The reference to self
	template<typename OtherScalar, typename OtherScalar2>
	constexpr PointT& Scale(const PointT<OtherScalar, DIM>& point, const OtherScalar2& scale) noexcept
	{
		coord = coord * scale + point.coord * (OtherScalar2{1} - scale);
		return *this;
	}

	/// @brief Compute the scaled point w.r.t. a center point with a scale
	/// @tparam OtherScalar The scalar type of the center point
	/// @tparam OtherScalar2 The type of scale
	/// @param point The center point
	/// @param scale The scale
	/// @return The scaled point
	template<typename OtherScalar, typename OtherScalar2>
	[[nodiscard]] constexpr PointT Scaled(const PointT<OtherScalar, DIM>& point, const OtherScalar2& scale) const noexcept
	{
		return PointT(*this).Scale(point, scale);
	}

	/// @brief Transform the point
	/// @tparam OtherScalar The scalar type of the transformation
	/// @param tr The transformation
	/// @return The reference to self
	template<typename OtherScalar>
	constexpr PointT& Transform(const TransformationT<OtherScalar, DIM>& tr) noexcept
	{
		if (tr.Type() == TransformationType::Identity)
		{
		}
		else if (tr.Type() == TransformationType::Translation)
		{
			coord += tr.TranslationPart();
		}
		else if (tr.Type() == TransformationType::Scale)
		{
			coord = coord * tr.ScaleFactor() + tr.TranslationPart();
		}
		else if (tr.Type() == TransformationType::PointMirror)
		{
			coord = -coord + tr.TranslationPart();
		}
		else
		{
			tr.Transform(coord);
		}
		return *this;
	}

	/// @brief Compute the transformed point
	/// @tparam OtherScalar The scalar type of the transformation
	/// @param tr The transformation
	/// @return The transformed point
	template<typename OtherScalar>
	[[nodiscard]] constexpr PointT Transformed(const TransformationT<OtherScalar, DIM>& tr) const noexcept
	{
		return PointT(*this).Transform(tr);
	}

	/// @brief Translate the point through a vector
	/// @tparam OtherScalar The scalar type of the vector
	/// @param vec The translation vector
	/// @return The reference to self
	template<typename OtherScalar>
	constexpr PointT& Translate(const VectorT<OtherScalar, DIM>& vec) noexcept
	{
		coord += vec.Coord();
		return *this;
	}

	/// @brief Compute the translated point through a vector
	/// @tparam OtherScalar The scalar type of the vector
	/// @param vec The translation vector
	/// @return The translated point
	template<typename OtherScalar>
	[[nodiscard]] constexpr PointT Translated(const VectorT<OtherScalar, DIM>& vec) const noexcept
	{
		return PointT(*this).Translate(vec);
	}

	/// @brief Translate the point through a vector formed by two points
	/// @tparam OtherScalar The scalar type of the first point
	/// @tparam OtherScalar2 The scalar type of the second point
	/// @param p1 The first point
	/// @param p2 The second point
	/// @return The referece to self
	template<typename OtherScalar, typename OtherScalar2>
	constexpr PointT& Translate(const PointT<OtherScalar, DIM>& p1, const PointT<OtherScalar2, DIM>& p2) noexcept
	{
		coord += p2.Coord() - p1.Coord();
		return *this;
	}

	/// @brief Compute the translated point through a vector formed by two points
	/// @tparam OtherScalar The scalar type of the first point
	/// @tparam OtherScalar2 The scalar type of the second point
	/// @param p1 The first point
	/// @param p2 The second point
	/// @return The translated point
	template<typename OtherScalar, typename OtherScalar2>
	[[nodiscard]] constexpr PointT Translated(const PointT<OtherScalar, DIM>& p1, const PointT<OtherScalar2, DIM>& p2) const noexcept
	{
		return PointT(*this).Translate(p1, p2);
	}

	/// @brief Write the point to the stream
	/// @tparam Stream The type of output stream
	/// @param os The output stream
	/// @param point The point
	/// @return The output stream
	template<typename Stream>
	friend Stream& operator<<(Stream& os, const PointT& point)
	{
		os << point.coord;
		return os;
	}

	/// @brief Read the point from the stream
	/// @tparam Stream The type of input stream
	/// @param is The input stream
	/// @param point The point
	/// @return The input stream
	template<typename Stream>
	friend Stream& operator>>(Stream& is, PointT& point)
	{
		is >> point.coord;
		return is;
	}

private:
	/// @brief Coordinate of point
	CoordType coord;
};

/// @brief 2D point
using Point2 = PointT<double, 2>;

/// @brief 3D point
using Point3 = PointT<double, 3>;

} // namespace AMCAX
