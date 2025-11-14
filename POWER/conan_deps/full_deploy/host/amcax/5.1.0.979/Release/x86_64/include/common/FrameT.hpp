/// @file      FrameT.hpp
/// @brief     Class of frame
/// @details   Implementation of frame, a local coordinate system
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <common/DirectionT.hpp>
#include <common/PointT.hpp>
#include <common/Precision.hpp>

namespace AMCAX
{
template<typename Scalar, int DIM>
class AxisT;
template<typename Scalar, int DIM>
class TransformationT;
template<typename Scalar, int DIM>
class VectorT;

/// @brief Class of frame
/// @details A frame consists of a location and some orthogonal directions. The frame can be right-handed or left-handed, determined by the sign of the determinant of the matrix formed by the directions.
/// @tparam Scalar Underlying scalar type of frame
/// @tparam DIM Dimension
template<typename Scalar, int DIM>
class FrameT
{
public:
	/// @brief Default constructor
	/// @details The default frame is the standard orthogonal frame
	constexpr FrameT() noexcept
	{
		if constexpr (DIM == 2)
		{
			directions[1].coord.SetCoord(Scalar{0}, Scalar{1});
		}
		else if constexpr (DIM == 3)
		{
			directions[1].coord.SetCoord(Scalar{0}, Scalar{1}, Scalar{0});
			directions[2].coord.SetCoord(Scalar{0}, Scalar{0}, Scalar{1});
		}
	}

	/// @brief Construct from a location and two directions in 2D
	/// @tparam OtherScalar The scalar type of the location point
	/// @tparam OtherScalar2 The scalar type of the x direction
	/// @tparam OtherScalar3 The scalar type of the y direction
	/// @param point The location point
	/// @param xdir The x direction
	/// @param ydir The y direction
	template<typename OtherScalar, typename OtherScalar2, typename OtherScalar3, int DIM2 = DIM, std::enable_if_t<DIM2 == 2, int> = 0>
	constexpr FrameT(const PointT<OtherScalar, DIM>& point, const DirectionT<OtherScalar2, DIM>& xdir, const DirectionT<OtherScalar3, DIM>& ydir) noexcept
		: location(point),
		  directions{xdir, ydir}
	{
		if (xdir.Cross(ydir) >= 0.0)
		{
			directions[1].coord.SetCoord(-directions[0].Y(), directions[0].X());
		}
		else
		{
			directions[1].coord.SetCoord(directions[0].Y(), -directions[0].X());
		}
	}

	/// @brief Construct from a location, an x direction and a right-handed flag in 2D
	/// @tparam OtherScalar The scalar type of the location point
	/// @tparam OtherScalar2 The scalar type of the x direction
	/// @param point The location point
	/// @param xdir The x direction
	/// @param isright Is right-handed frame
	template<typename OtherScalar, typename OtherScalar2, int DIM2 = DIM, std::enable_if_t<DIM2 == 2, int> = 0>
	constexpr FrameT(const PointT<OtherScalar, DIM>& point, const DirectionT<OtherScalar2, DIM>& xdir, bool isright = true) noexcept
		: location(point)
	{
		directions[0] = xdir;
		if (isright)
		{
			directions[1].coord.SetCoord(-xdir.Y(), xdir.X());
		}
		else
		{
			directions[1].coord.SetCoord(xdir.Y(), -xdir.X());
		}
	}

	/// @brief Construct from an x axis and a right-handed flag in 2D
	/// @tparam OtherScalar The scalar type of the x axis
	/// @param axis The x axis
	/// @param isright Is right-handed frame
	template<typename OtherScalar, int DIM2 = DIM, std::enable_if_t<DIM2 == 2, int> = 0>
	constexpr explicit FrameT(const AxisT<OtherScalar, DIM>& axis, bool isright = true) noexcept
		: location(axis.Location())
	{
		directions[0] = axis.Direction();
		if (isright)
		{
			directions[1].coord.SetCoord(-directions[0].Y(), directions[0].X());
		}
		else
		{
			directions[1].coord.SetCoord(directions[0].Y(), -directions[0].X());
		}
	}

	/// @brief Construct from a location, a z direction and a reference x direction in 3D
	/// @details The x direction could be changed due to the orthogonalization process.
	/// @tparam OtherScalar The scalar type of the location point
	/// @tparam OtherScalar2 The scalar type of the z direction
	/// @tparam OtherScalar3 The scalar type of the reference x direction
	/// @param point The location point
	/// @param normal The z direction
	/// @param x The reference x direction
	template<typename OtherScalar, typename OtherScalar2, typename OtherScalar3, int DIM2 = DIM, std::enable_if_t<DIM2 == 3, int> = 0>
	FrameT(const PointT<OtherScalar, DIM>& point, const DirectionT<OtherScalar2, DIM>& normal, const DirectionT<OtherScalar3, DIM>& x) noexcept
		: location(point)
	{
		directions[2] = normal;
		const double an = x.Dot(normal);
		if (1.0 - std::fabs(an) <= Precision::Angular())
		{
			OtherScalar2 a = std::fabs(normal.X());
			OtherScalar2 b = std::fabs(normal.Y());
			OtherScalar2 c = std::fabs(normal.Z());
			if (b <= a && b <= c)
			{
				if (a > c)
				{
					directions[0].coord.SetCoord(-normal.Z(), OtherScalar2{0}, normal.X());
				}
				else
				{
					directions[0].coord.SetCoord(normal.Z(), OtherScalar2{0}, -normal.X());
				}
			}
			else if (a <= b && a <= c)
			{
				if (b > c)
				{
					directions[0].coord.SetCoord(OtherScalar2{0}, -normal.Z(), normal.Y());
				}
				else
				{
					directions[0].coord.SetCoord(OtherScalar2{0}, normal.Z(), -normal.Y());
				}
			}
			else
			{
				if (a > b)
				{
					directions[0].coord.SetCoord(-normal.Y(), normal.X(), OtherScalar2{0});
				}
				else
				{
					directions[0].coord.SetCoord(normal.Y(), -normal.X(), OtherScalar2{0});
				}
			}
			directions[0].coord.Normalize();
			directions[1].coord = normal.Coord().Cross(directions[0].Coord());
		}
		else
		{
			directions[0].coord = directions[2].Coord().Cross(x.Coord().Cross(directions[2].Coord())).Normalized();
			directions[1].coord = directions[2].Coord().Cross(directions[0].Coord());
		}
	}

	/// @brief Construct from a location and a z direction in 3D
	/// @details The other two directions are generated automatically.
	/// @tparam OtherScalar The scalar type of the location point
	/// @tparam OtherScalar2 The scalar type of the z direction
	/// @param point The location point
	/// @param dir The z direction
	template<typename OtherScalar, typename OtherScalar2, int DIM2 = DIM, std::enable_if_t<DIM2 == 3, int> = 0>
	FrameT(const PointT<OtherScalar, DIM>& point, const DirectionT<OtherScalar2, DIM>& dir) noexcept
		: location(point)
	{
		directions[2] = dir;
		OtherScalar2 a = std::fabs(dir.X());
		OtherScalar2 b = std::fabs(dir.Y());
		OtherScalar2 c = std::fabs(dir.Z());
		if (b <= a && b <= c)
		{
			if (a > c)
			{
				directions[0].coord.SetCoord(-dir.Z(), OtherScalar2{0}, dir.X());
			}
			else
			{
				directions[0].coord.SetCoord(dir.Z(), OtherScalar2{0}, -dir.X());
			}
		}
		else if (a <= b && a <= c)
		{
			if (b > c)
			{
				directions[0].coord.SetCoord(OtherScalar2{0}, -dir.Z(), dir.Y());
			}
			else
			{
				directions[0].coord.SetCoord(OtherScalar2{0}, dir.Z(), -dir.Y());
			}
		}
		else
		{
			if (a > b)
			{
				directions[0].coord.SetCoord(-dir.Y(), dir.X(), OtherScalar2{0});
			}
			else
			{
				directions[0].coord.SetCoord(dir.Y(), -dir.X(), OtherScalar2{0});
			}
		}
		directions[0].coord.Normalize();
		directions[1].coord = dir.Coord().Cross(directions[0].Coord());
	}

	/// @brief Set the z axis in 3D
	/// @details The other two directions could be changed accordingly
	/// @tparam OtherScalar The scalar type of the axis
	/// @param a The new z axis
	template<typename OtherScalar, int DIM2 = DIM, std::enable_if_t<DIM2 == 3, int> = 0>
	void SetAxis(const AxisT<OtherScalar, DIM>& a) noexcept
	{
		location = a.Location();
		SetDirection(a.Direction());
	}

	/// @brief Set x axis in 2D
	/// @details The y direction could be changed accordingly
	/// @tparam OtherScalar The scalar type of the axis
	/// @param axis The new x axis
	template<typename OtherScalar, int DIM2 = DIM, std::enable_if_t<DIM2 == 2, int> = 0>
	void SetXAxis(const AxisT<OtherScalar, DIM>& axis) noexcept
	{
		location = axis.Location();
		SetXDirection(axis.Direction());
	}

	/// @brief Set y axis in 2D
	/// @details The x direction could be changed accordingly
	/// @tparam OtherScalar The scalar type of the axis
	/// @param axis The new y axis
	template<typename OtherScalar, int DIM2 = DIM, std::enable_if_t<DIM2 == 2, int> = 0>
	void SetYAxis(const AxisT<OtherScalar, DIM>& axis) noexcept
	{
		location = axis.Location();
		SetYDirection(axis.Direction());
	}

	/// @brief Set the z direction in 3D
	/// @details The other two directions could be changed accordingly
	/// @tparam OtherScalar The scalar type of the direction
	/// @param dir The new z direction
	template<typename OtherScalar, int DIM2 = DIM, std::enable_if_t<DIM2 == 3, int> = 0>
	void SetDirection(const DirectionT<OtherScalar, DIM>& dir) noexcept
	{
		const double an = dir.Dot(directions[0]);
		if (std::fabs(std::fabs(an) - 1.0) <= Precision::Angular())
		{
			if (an > 0.0)
			{
				directions[0] = directions[1];
				directions[1] = directions[2];
			}
			else
			{
				directions[0] = directions[2];
			}
		}
		else
		{
			if (IsDirect())
			{
				directions[0].coord = dir.Coord().Cross(directions[0].Coord().Cross(dir.Coord())).Normalized();
				directions[1].coord = dir.Coord().Cross(directions[0].Coord());
			}
			else
			{
				directions[0].coord = dir.Coord().Cross(directions[0].Coord().Cross(dir.Coord())).Normalized();
				directions[1].coord = directions[0].Coord().Cross(dir.Coord());
			}
		}
		directions[2] = dir;
	}

	/// @brief Set the location
	/// @tparam OtherScalar The scalar type of the location
	/// @param point The new location point
	template<typename OtherScalar>
	constexpr void SetLocation(const PointT<OtherScalar, DIM>& point) noexcept
	{
		location = point;
	}

	/// @brief Set the x direction in 2D
	/// @details The y direction could be changed accordingly
	/// @tparam OtherScalar The scalar type of the x direction
	/// @param x The new x direction
	template<typename OtherScalar, int DIM2 = DIM, std::enable_if_t<DIM2 == 2, int> = 0>
	constexpr void SetXDirection(const DirectionT<OtherScalar, DIM>& x) noexcept
	{
		if (directions[0].Cross(directions[1]) >= 0.0)
		{
			directions[0] = x;
			directions[1].coord.SetCoord(-directions[0].Y(), directions[0].X());
		}
		else
		{
			directions[0] = x;
			directions[1].coord.SetCoord(directions[0].Y(), -directions[0].X());
		}
	}

	/// @brief Set the x direction in 3D
	/// @details If the new x direction equals the z direction, then swap the x and z direction; otherwise, z direction is not changed and the resulting x direction is perpendicular to the z direction.
	/// @tparam OtherScalar The scalar type of the x direction
	/// @param x The new x direction
	template<typename OtherScalar, int DIM2 = DIM, std::enable_if_t<DIM2 == 3, int> = 0>
	void SetXDirection(const DirectionT<OtherScalar, DIM>& x) noexcept
	{
		const double an = x.Dot(directions[2]);
		if (1.0 - std::fabs(an) <= Precision::Angular())
		{
			directions[2] = directions[0];
			if (an > 0.0)
			{
				directions[1] = -directions[1];
			}
			directions[0] = x;
		}
		else
		{
			if (IsDirect())
			{
				directions[0].coord = directions[2].Coord().Cross(x.Coord().Cross(directions[2].Coord())).Normalized();
				directions[1].coord = directions[2].Coord().Cross(directions[0].Coord());
			}
			else
			{
				directions[0].coord = directions[2].Coord().Cross(x.Coord().Cross(directions[2].Coord())).Normalized();
				directions[1].coord = directions[0].Coord().Cross(directions[2].Coord());
			}
		}
	}

	/// @brief Set the y direction in 2D
	/// @details The x direction could be changed accordingly
	/// @tparam OtherScalar The scalar type of the y direction
	/// @param y The y direction
	template<typename OtherScalar, int DIM2 = DIM, std::enable_if_t<DIM2 == 2, int> = 0>
	constexpr void SetYDirection(const DirectionT<OtherScalar, DIM>& y) noexcept
	{
		if (directions[0].Cross(directions[1]) >= 0.0)
		{
			directions[1] = y;
			directions[0].coord.SetCoord(directions[1].Y(), -directions[1].X());
		}
		else
		{
			directions[1] = y;
			directions[0].coord.SetCoord(-directions[1].Y(), directions[1].X());
		}
	}

	/// @brief Set the y direction in 3D
	/// @details If the new y direction equals the z direction, then swap the x and z direction; otherwise, z direction is not changed and the resulting y direction is perpendicular to the z direction.
	/// @tparam OtherScalar The scalar type of the y direction
	/// @param y The new y direction
	template<typename OtherScalar, int DIM2 = DIM, std::enable_if_t<DIM2 == 3, int> = 0>
	void SetYDirection(const DirectionT<OtherScalar, DIM>& y) noexcept
	{
		const double an = y.Dot(directions[2]);
		if (1.0 - std::fabs(an) <= Precision::Angular())
		{
			directions[2] = directions[1];
			if (an > 0.0)
			{
				directions[0] = -directions[0];
			}
			directions[1] = y;
		}
		else
		{
			if (IsDirect())
			{
				directions[1].coord = directions[2].Coord().Cross(y.Coord().Cross(directions[2].Coord())).Normalized();
				directions[0].coord = directions[1].Coord().Cross(directions[2].Coord());
			}
			else
			{
				directions[1].coord = directions[2].Coord().Cross(y.Coord().Cross(directions[2].Coord())).Normalized();
				directions[0].coord = directions[2].Coord().Cross(directions[1].Coord());
			}
		}
	}

	/// @brief Compute the angle difference to the other frame
	/// @details The angle difference between frames is the angle difference between their main direction
	/// @tparam OtherScalar The scalar type of the other frame
	/// @param other The other frame
	/// @return The angle difference to the other frame
	template<typename OtherScalar, int DIM2 = DIM, std::enable_if_t<DIM2 == 3, int> = 0>
	[[nodiscard]] double Angle(const FrameT<OtherScalar, DIM>& other) const noexcept
	{
		return Direction().Angle(other.Direction());
	}

	/// @brief Get the main axis, i.e. location and the main direction
	/// @return The main axis
	template<int DIM2 = DIM, std::enable_if_t<DIM2 == 3, int> = 0>
	[[nodiscard]] constexpr AxisT<Scalar, DIM> Axis() const noexcept
	{
		return AxisT<Scalar, DIM>(location, Direction());
	}

	/// @brief Get the x axis, only available when DIM >= 1
	/// @return The x axis
	template<int DIM2 = DIM, std::enable_if_t<DIM2 >= 1, int> = 0>
	[[nodiscard]] constexpr AxisT<Scalar, DIM> XAxis() const noexcept
	{
		return AxisT<Scalar, DIM>(location, XDirection());
	}

	/// @brief Get the y axis, only available when DIM >= 2
	/// @return The y axis
	template<int DIM2 = DIM, std::enable_if_t<DIM2 >= 2, int> = 0>
	[[nodiscard]] constexpr AxisT<Scalar, DIM> YAxis() const noexcept
	{
		return AxisT<Scalar, DIM>(location, YDirection());
	}

	/// @brief Get the location
	/// @return The location
	[[nodiscard]] constexpr const PointT<Scalar, DIM>& Location() const noexcept
	{
		return location;
	}

	/// @brief Get the main direction (z direction) in 3D
	/// @return The main direction
	template<int DIM2 = DIM, std::enable_if_t<DIM2 == 3, int> = 0>
	[[nodiscard]] constexpr const DirectionT<Scalar, DIM>& Direction() const noexcept
	{
		return directions.back();
	}

	/// @brief Get the x direction, only available when DIM >= 1
	/// @return The x direction
	template<int DIM2 = DIM, std::enable_if_t<DIM2 >= 1, int> = 0>
	[[nodiscard]] constexpr const DirectionT<Scalar, DIM>& XDirection() const noexcept
	{
		return directions[0];
	}

	/// @brief Get the y direction, only available when DIM >= 2
	/// @return The y direction
	template<int DIM2 = DIM, std::enable_if_t<DIM2 >= 2, int> = 0>
	[[nodiscard]] constexpr const DirectionT<Scalar, DIM>& YDirection() const noexcept
	{
		return directions[1];
	}

	/// @brief Get the local coordinate of a point
	/// @param p The point in the world coordinate
	/// @return The local coordinate of the point
	constexpr CoordT<Scalar, DIM> LocalCoordinate(const CoordT<Scalar, DIM>& p) const noexcept
	{
		const CoordT<Scalar, DIM> d = p - location.Coord();
		if constexpr (DIM == 2)
		{
			return CoordT<Scalar, DIM>(directions[0].Coord().Dot(d), directions[1].Coord().Dot(d));
		}
		else if constexpr (DIM == 3)
		{
			return CoordT<Scalar, DIM>(directions[0].Coord().Dot(d), directions[1].Coord().Dot(d), directions[2].Coord().Dot(d));
		}
		else
		{
			CoordT<Scalar, DIM> result;
			for (int i = 0; i < DIM; i++)
			{
				result[i] = directions[i].Coord().Dot(d);
			}
			return result;
		}
	}

	/// @brief Is the frame is coplanar to the other frame under a distance tolerance and an angle tolerance in 3D
	/// @details Two frames are coplanar if their z directions are parallel and each location is located on the xy plane of the other frame
	/// @tparam OtherScalar The scalar type of the other frame
	/// @tparam OtherScalar2 The type of distance tolerance
	/// @tparam OtherScalar3 The type of angle tolerance
	/// @param other The other frame
	/// @param distol The distance tolerance
	/// @param angtol The angle tolerance
	/// @return True if the two frames are coplanar
	template<typename OtherScalar, typename OtherScalar2, typename OtherScalar3, int DIM2 = DIM, std::enable_if_t<DIM2 == 3, int> = 0>
	[[nodiscard]] bool IsCoplanar(const FrameT<OtherScalar, DIM>& other, const OtherScalar2& distol, const OtherScalar3& angtol) const noexcept
	{
		return std::fabs(Direction().Coord().Dot(other.Location().Coord() - Location().Coord())) <= distol && Direction().IsParallel(other.Direction(), angtol);
	}

	/// @brief Is the frame is coplanar to an axis under a distance tolerance and an angle tolerance in 3D
	/// @details A frame and an axis are coplanar if the z direction of the frame is parallel to the direction of axis and their locations are located on the xy plane of the frame
	/// @tparam OtherScalar The scalar type of the axis
	/// @tparam OtherScalar2 The type of the distance tolerance
	/// @tparam OtherScalar3 The type of the angle tolerance
	/// @param a The axis
	/// @param distol The distance tolerance
	/// @param angtol The angle tolerance
	/// @return True if the frame is coplanar to the axis
	template<typename OtherScalar, typename OtherScalar2, typename OtherScalar3, int DIM2 = DIM, std::enable_if_t<DIM2 == 3, int> = 0>
	[[nodiscard]] bool IsCoplanar(const AxisT<OtherScalar, DIM>& a, const OtherScalar2& distol, const OtherScalar3& angtol) const noexcept
	{
		return std::fabs(Direction().Coord().Dot(a.Location().Coord() - Location().Coord())) <= distol && Direction().IsNormal(a.Direction(), angtol);
	}

	/// @brief Is the 3D frame right-handed
	/// @return True if the 3D frame is right-handed
	template<int DIM2 = DIM, std::enable_if_t<DIM2 == 3, int> = 0>
	[[nodiscard]] constexpr bool IsDirect() const noexcept
	{
		return directions[0].Coord().Cross(directions[1].Coord()).Dot(directions[2].Coord()) > 0.0;
	}

	/// @brief Make the 3D frame to be right-handed by reversing the z direction if necessary
	/// @return The reference to self
	template<int DIM2 = DIM, std::enable_if_t<DIM2 == 3, int> = 0>
	constexpr FrameT& MakeDirect() noexcept
	{
		if (!IsDirect())
		{
			ZReverse();
		}
		return *this;
	}

	/// @brief Get the right-handed frame by reversing the z direction if necessary
	/// @return The right-handed frame
	template<int DIM2 = DIM, std::enable_if_t<DIM2 == 3, int> = 0>
	[[nodiscard]] constexpr FrameT ToDirect() const noexcept
	{
		FrameT f(*this);
		if (!f.IsDirect())
		{
			f.ZReverse();
		}
		return f;
	}

	/// @brief Is the 2D frame right-handed
	/// @return True if the 2D frame is right-handed
	template<int DIM2 = DIM, std::enable_if_t<DIM2 == 2, int> = 0>
	[[nodiscard]] constexpr bool IsDirect() const noexcept
	{
		return directions[0].Cross(directions[1]) > 0.0;
	}

	/// @brief Reverse the x axis, the orientation is changed
	template<int DIM2 = DIM, std::enable_if_t<DIM2 >= 1, int> = 0>
	constexpr void XReverse() noexcept
	{
		directions[0].Reverse();
	}

	/// @brief Reverse the y axis, the orientation is changed
	template<int DIM2 = DIM, std::enable_if_t<DIM2 >= 2, int> = 0>
	constexpr void YReverse() noexcept
	{
		directions[1].Reverse();
	}

	/// @brief Reverse the z axis, the orientation is changed
	template<int DIM2 = DIM, std::enable_if_t<DIM2 >= 3, int> = 0>
	constexpr void ZReverse() noexcept
	{
		directions[2].Reverse();
	}

	/// @brief Mirror the frame by a mirror point
	/// @details When DIM is odd, the orientation becomes reversed
	/// @tparam OtherScalar The scalar type of the mirror point
	/// @param point The mirror point
	/// @return The reference to self
	template<typename OtherScalar>
	constexpr FrameT& Mirror(const PointT<OtherScalar, DIM>& point) noexcept
	{
		location.Mirror(point);
		for (int i = 0; i < DIM; i++)
		{
			directions[i].Reverse();
		}
		return *this;
	}

	/// @brief Get the frame mirrored by a mirror point
	/// @details When DIM is odd, the orientation becomes reversed
	/// @tparam OtherScalar The scalar type of the mirror point
	/// @param point The mirror point
	/// @return The mirrored frame
	template<typename OtherScalar>
	[[nodiscard]] constexpr FrameT Mirrored(const PointT<OtherScalar, DIM>& point) const noexcept
	{
		return FrameT(*this).Mirror(point);
	}

	/// @brief Mirror the frame by an axis
	/// @details When DIM is even, the orientation becomes reversed
	/// @tparam OtherScalar The scalar type of the mirror axis
	/// @param a The mirror axis
	/// @return The reference to self
	template<typename OtherScalar>
	constexpr FrameT& Mirror(const AxisT<OtherScalar, DIM>& a) noexcept
	{
		location.Mirror(a);
		for (int i = 0; i < DIM; i++)
		{
			directions[i].Mirror(a);
		}
		return *this;
	}

	/// @brief Get the frame mirrored by an axis
	/// @details When DIM is even, the orientation becomes reversed
	/// @tparam OtherScalar The scalar type of the mirror axis
	/// @param a The mirror axis
	/// @return The mirrored frame
	template<typename OtherScalar>
	[[nodiscard]] constexpr FrameT Mirrored(const AxisT<OtherScalar, DIM>& a) const noexcept
	{
		return FrameT(*this).Mirror(a);
	}

	/// @brief Mirror the frame by another frame
	/// @details The frame is mirrored by the DIM - 1 dimensional hyperplane orthogonal to the main direction of the other frame. The orientation is reversed.
	/// @tparam OtherScalar The scalar type of the other frame
	/// @param frame The other frame
	/// @return The reference to self
	template<typename OtherScalar, int DIM2 = DIM, std::enable_if_t<DIM2 == 3, int> = 0>
	constexpr FrameT& Mirror(const FrameT<OtherScalar, DIM>& frame) noexcept
	{
		location.Mirror(frame);
		for (int i = 0; i < DIM; i++)
		{
			directions[i].Mirror(frame);
		}
		return *this;
	}

	/// @brief Get the frame mirrored by another frame
	/// @details The frame is mirrored by the DIM - 1 dimensional hyperplane orthogonal to the main direction of the other frame. The orientation is reversed.
	/// @tparam OtherScalar The scalar type of the other frame
	/// @param frame The other frame
	/// @return The mirrored frame
	template<typename OtherScalar, int DIM2 = DIM, std::enable_if_t<DIM2 == 3, int> = 0>
	[[nodiscard]] constexpr FrameT Mirrored(const FrameT<OtherScalar, DIM>& frame) const noexcept
	{
		return FrameT(*this).Mirror(frame);
	}

	/// @brief Rotate the frame around a point by an angle in 2D
	/// @tparam OtherScalar The scalar type of the rotation center point
	/// @tparam OtherScalar2 The type of the rotation angle
	/// @param point The rotation center point
	/// @param angle The rotation angle
	/// @return The reference to self
	template<typename OtherScalar, typename OtherScalar2, int DIM2 = DIM, std::enable_if_t<DIM2 == 2, int> = 0>
	FrameT& Rotate(const PointT<OtherScalar, DIM>& point, const OtherScalar2& angle) noexcept
	{
		location.Rotate(point, angle);
		for (int i = 0; i < DIM; i++)
		{
			directions[i].Rotate(angle);
		}
		return *this;
	}

	/// @brief Get the frame rotated around a point by an angle in 2D
	/// @tparam OtherScalar The scalar type of the rotation center point
	/// @tparam OtherScalar2 The type of the rotation angle
	/// @param point The rotation center point
	/// @param angle The rotation angle
	/// @return The rotated frame
	template<typename OtherScalar, typename OtherScalar2, int DIM2 = DIM, std::enable_if_t<DIM2 == 2, int> = 0>
	[[nodiscard]] FrameT Rotated(const PointT<OtherScalar, DIM>& point, const OtherScalar2& angle) const noexcept
	{
		return FrameT(*this).Rotate(point, angle);
	}

	/// @brief Rotate the frame around an axis by an angle in 3D
	/// @tparam OtherScalar The scalar type of the rotation axis
	/// @tparam OtherScalar2 The type of the rotation angle
	/// @param a The rotation axis
	/// @param angle The rotation angle
	/// @return The reference to self
	template<typename OtherScalar, typename OtherScalar2, int DIM2 = DIM, std::enable_if_t<DIM2 == 3, int> = 0>
	FrameT& Rotate(const AxisT<OtherScalar, DIM>& a, const OtherScalar2& angle) noexcept
	{
		location.Rotate(a, angle);
		for (int i = 0; i < DIM; i++)
		{
			directions[i].Rotate(a, angle);
		}
		return *this;
	}

	/// @brief Get the frame rotated around an axis by an angle in 3D
	/// @tparam OtherScalar The scalar type of the rotation axis
	/// @tparam OtherScalar2 The type of the rotation angle
	/// @param a The rotation axis
	/// @param angle The rotation angle
	/// @return The rotated frame
	template<typename OtherScalar, typename OtherScalar2, int DIM2 = DIM, std::enable_if_t<DIM2 == 3, int> = 0>
	[[nodiscard]] FrameT Rotated(const AxisT<OtherScalar, DIM>& a, const OtherScalar2& angle) const noexcept
	{
		return FrameT(*this).Rotate(a, angle);
	}

	/// @brief Scale the frame
	/// @details When scale < 0, the orientation becomes reversed
	/// @tparam OtherScalar The scalar type of the scaling center point
	/// @tparam OtherScalar2 The type of the scale value
	/// @param point The scaling center point
	/// @param scale The scale value
	/// @return The reference to self
	template<typename OtherScalar, typename OtherScalar2>
	constexpr FrameT& Scale(const PointT<OtherScalar, DIM>& point, const OtherScalar2& scale) noexcept
	{
		location.Scale(point, scale);
		if (scale < 0.0)
		{
			for (int i = 0; i < DIM; i++)
			{
				directions[i].Reverse();
			}
		}
		return *this;
	}

	/// @brief Get the scaled frame
	/// @details When scale < 0, the orientation becomes reversed
	/// @tparam OtherScalar The scalar type of the scaling center point
	/// @tparam OtherScalar2 The type of the scale value
	/// @param point The scaling center point
	/// @param scale The scale value
	/// @return The scaled frame
	template<typename OtherScalar, typename OtherScalar2>
	[[nodiscard]] constexpr FrameT Scaled(const PointT<OtherScalar, DIM>& point, const OtherScalar2& scale) const noexcept
	{
		return FrameT(*this).Scale(point, scale);
	}

	/// @brief Transform the frame
	/// @details When tr.ScaleFactor() < 0, the orientation becomes reversed
	/// @tparam OtherScalar The scalar type of the transformation
	/// @param tr The transformation
	/// @return The reference to self
	template<typename OtherScalar>
	FrameT& Transform(const TransformationT<OtherScalar, DIM>& tr) noexcept
	{
		location.Transform(tr);
		for (int i = 0; i < DIM; i++)
		{
			directions[i].Transform(tr);
		}
		return *this;
	}

	/// @brief Get the transformed frame
	/// @details When tr.ScaleFactor() < 0, the orientation becomes reversed
	/// @tparam OtherScalar The scalar type of the transformation
	/// @param tr The transformation
	/// @return The transformed frame
	template<typename OtherScalar>
	[[nodiscard]] FrameT Transformed(const TransformationT<OtherScalar, DIM>& tr) const noexcept
	{
		return FrameT(*this).Transform(tr);
	}

	/// @brief Translate the frame
	/// @tparam OtherScalar The scalar type of the translation vector
	/// @param vec The translation vector
	/// @return The reference to self
	template<typename OtherScalar>
	constexpr FrameT& Translate(const VectorT<OtherScalar, DIM>& vec) noexcept
	{
		location.Translate(vec);
		return *this;
	}

	/// @brief Get the translated frame
	/// @tparam OtherScalar The scalar type of the translation vector
	/// @param vec The translation vector
	/// @return The translated frame
	template<typename OtherScalar>
	[[nodiscard]] constexpr FrameT Translated(const VectorT<OtherScalar, DIM>& vec) const noexcept
	{
		return FrameT(*this).Translate(vec);
	}

	/// @brief Translate the frame by a vector from a point to another point
	/// @tparam OtherScalar The scalar type of the first point
	/// @tparam OtherScalar2 The scalar type of the second point
	/// @param p1 The first point
	/// @param p2 The second point
	/// @return The reference to self
	template<typename OtherScalar, typename OtherScalar2>
	constexpr FrameT& Translate(const PointT<OtherScalar, DIM>& p1, const PointT<OtherScalar2, DIM>& p2) noexcept
	{
		location.Translate(p1, p2);
		return *this;
	}

	/// @brief Get the frame translated by a vector from a point to another point
	/// @tparam OtherScalar The scalar type of the first point
	/// @tparam OtherScalar2 The scalar type of the second point
	/// @param p1 The first point
	/// @param p2 The second point
	/// @return The translated frame
	template<typename OtherScalar, typename OtherScalar2>
	[[nodiscard]] constexpr FrameT Translated(const PointT<OtherScalar, DIM>& p1, const PointT<OtherScalar2, DIM>& p2) const noexcept
	{
		return FrameT(*this).Translate(p1, p2);
	}

	/// @brief Write the frame
	/// @tparam Stream The type of output stream
	/// @param os The output stream
	/// @param frame The frame
	/// @return The output stream
	template<typename Stream>
	friend Stream& operator<<(Stream& os, const FrameT& frame)
	{
		if constexpr (DIM == 3)
		{
			os << frame.location << ' ' << frame.directions.back() << ' ' << frame.directions[0] << ' ' << frame.directions[1];
			return os;
		}
		else
		{
			os << frame.location;
			for (int i = 0; i < DIM; i++)
			{
				os << ' ' << frame.directions[i];
			}
			return os;
		}
	}

	/// @brief Read the frame
	/// @tparam Stream The type of input stream
	/// @param is The input stream
	/// @param frame The frame
	/// @return The input stream
	template<typename Stream>
	friend Stream& operator>>(Stream& is, FrameT& frame)
	{
		if constexpr (DIM == 3)
		{
			is >> frame.location >> frame.directions.back() >> frame.directions[0] >> frame.directions[1];
			return is;
		}
		else
		{
			is >> frame.location;
			for (int i = 0; i < DIM; i++)
			{
				is >> frame.directions[i];
			}
			return is;
		}
	}

private:
	/// @brief The origin of the frame
	PointT<Scalar, DIM> location;

	/// @brief The orthogonal axis directions
	std::array<DirectionT<Scalar, DIM>, DIM> directions;
};

/// @brief 2D frame
using Frame2 = FrameT<double, 2>;

/// @brief 3D frame
using Frame3 = FrameT<double, 3>;

} // namespace AMCAX
