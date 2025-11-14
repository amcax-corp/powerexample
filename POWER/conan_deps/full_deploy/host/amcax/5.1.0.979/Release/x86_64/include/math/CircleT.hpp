/// @file      CircleT.hpp
/// @brief     Class of circle
/// @details   Implementation of circle
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <math/ConicBase.hpp>

namespace AMCAX
{
/// @brief Base class of circle
/// @tparam Derived Type of derived class
/// @tparam DIM Dimension
template<int DIM>
class CircleS : public ConicBase<DIM, CircleS<DIM>>
{
	using Base = ConicBase<DIM, CircleS<DIM>>;

protected:
	using Base::pos;

public:
	/// @brief Default constructor
	constexpr CircleS() noexcept = default;

	/// @brief Construct from an axis and a radius in 2D
	/// @param axis The axis
	/// @param r The radius
	/// @param isRight Is the frame right-handed
	template<int DIM2 = DIM, std::enable_if_t<DIM2 == 2, int> = 0>
	CircleS(const AxisT<double, DIM>& axis, double r, bool isRight = true)
		: Base(axis, isRight),
		  radius{r}
	{
		CheckValidity();
	}

	/// @brief Construct from a local frame and a radius
	/// @param frame The local frame
	/// @param r The radius
	CircleS(const FrameT<double, DIM>& frame, double r)
		: Base(frame),
		  radius{r}
	{
		CheckValidity();
	}

	/// @brief Set the radius of the circle
	/// @param r The radius
	void SetRadius(double r)
	{
		radius = r;
		CheckValidity();
	}

	/// @brief Get the radius
	/// @return The radius
	[[nodiscard]] constexpr double Radius() const noexcept
	{
		return radius;
	}

	/// @brief Compute the area of the circle
	/// @return The area of the circle
	[[nodiscard]] constexpr double Area() const noexcept
	{
		return Constants::pi * radius * radius;
	}

	/// @brief Get the length of the circle
	/// @return The length of the circle
	[[nodiscard]] constexpr double Length() const noexcept
	{
		return Constants::two_pi * radius;
	}

	/// @brief Get the coefficients in the algebraic reprentation of the circle in 2D
	/// @details The algebraic representation is ax^2 + by^2 + 2cxy + 2dx + 2ey + f = 0
	/// @param[out] a,b,c,d,e,f The coefficients
	template<int DIM2 = DIM, std::enable_if_t<DIM2 == 2, int> = 0>
	constexpr void Coefficients(double& a, double& b, double& c, double& d, double& e, double& f) const noexcept
	{
		a = 1.0;
		b = 1.0;
		c = 0.0;
		d = -pos.Location().X();
		e = -pos.Location().Y();
		f = pos.Location().Coord().SquaredNorm() - radius * radius;
	}

	/// @brief Compute the distance from a point to the circle
	/// @param p The point
	/// @return The distance from the point to the circle
	[[nodiscard]] double Distance(const PointT<double, DIM>& p) const noexcept
	{
		if constexpr (DIM == 2)
		{
			return std::fabs(radius - (p.Coord() - pos.Location().Coord()).Norm());
		}
		else
		{
			return std::sqrt(SquaredDistance(p));
		}
	}

	/// @brief Compute the squared distance from a point to the circle
	/// @param p The point
	/// @return The squared distance from the point to the circle
	[[nodiscard]] double SquaredDistance(const PointT<double, DIM>& p) const noexcept
	{
		if constexpr (DIM == 2)
		{
			double d = radius - (p.Coord() - pos.Location().Coord()).Norm();
			return d * d;
		}
		else
		{
			auto v = p.Coord() - pos.Location().Coord();
			auto x = v.Dot(pos.XDirection().Coord());
			auto y = v.Dot(pos.YDirection().Coord());
			auto z = v.Dot(pos.Direction().Coord());
			auto t = std::sqrt(x * x + y * y) - radius;
			return t * t + z * z;
		}
	}

	/// @brief Does the circle contain a point under a tolerace
	/// @param p The point
	/// @param tol The tolerance
	/// @return True if the point is on the circle under the tolerance
	[[nodiscard]] bool Contains(const PointT<double, DIM>& p, double tol) const noexcept
	{
		return Distance(p) <= tol;
	}

	/// @brief Scale the circle by a center point
	/// @param p The scaling center point
	/// @param scale The scale value
	/// @return The reference to self
	constexpr CircleS& Scale(const PointT<double, DIM>& p, double scale) noexcept
	{
		radius *= scale;
		if (radius < 0.0)
		{
			radius = -radius;
		}
		return Base::Scale(p, scale);
	}

	/// @brief Transform the circle
	/// @param tr The transformation
	/// @return The reference to self
	CircleS& Transform(const TransformationT<double, DIM>& tr) noexcept
	{
		radius *= tr.ScaleFactor();
		if (radius < 0.0)
		{
			radius = -radius;
		}
		return Base::Transform(tr);
	}

protected:
	/// @brief Check the validity of circle
	void CheckValidity() const
	{
		if (radius < 0.0)
		{
			throw ConstructionError("radius should be non-negative");
		}
	}

	/// @brief The radius of circle
	double radius = std::numeric_limits<double>::max();
};

/// @brief Compatible alias of CircleS
/// @tparam Scalar Type of scalar value
/// @tparam DIM Dimension
template<typename Scalar, int DIM>
using CircleT = CircleS<DIM>;

/// @brief 2D circle
using Circle2 = CircleS<2>;

/// @brief 3D circle
using Circle3 = CircleS<3>;
} // namespace AMCAX
