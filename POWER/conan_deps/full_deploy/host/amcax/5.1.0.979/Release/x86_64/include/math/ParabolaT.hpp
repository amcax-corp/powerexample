/// @file      ParabolaT.hpp
/// @brief     Class of parabola
/// @details   Implementation of parabola
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <math/ConicBase.hpp>

namespace AMCAX
{
/// @brief Base class of parabola
/// @tparam Derived Type of derived class
/// @tparam DIM Dimension
template<int DIM>
class ParabolaS : public ConicBase<DIM, ParabolaS<DIM>>
{
	using Base = ConicBase<DIM, ParabolaS<DIM>>;

protected:
	using Base::pos;

public:
	/// @brief Default constructor
	constexpr ParabolaS() noexcept = default;

	/// @brief Construct from an axis and a focal length in 2D
	/// @param axis The axis
	/// @param focal The focal length
	/// @param isRight Is the frame right-handed
	template<int DIM2 = DIM, std::enable_if_t<DIM2 == 2, int> = 0>
	ParabolaS(const Axis2& axis, double focal, bool isRight = true)
		: Base(axis, isRight),
		  focalLength(focal)
	{
		CheckValidity();
	}

	/// @brief Construct from a frame and a focal length
	/// @param frame The frame
	/// @param focal The focal length
	ParabolaS(const FrameT<double, DIM>& frame, double focal)
		: Base(frame),
		  focalLength(focal)
	{
		CheckValidity();
	}

	/// @brief Construct from a directrix and a focus in 2D
	/// @param directrix The directrix
	/// @param focus The focus
	/// @param isRight Is the frame right-handed
	template<int DIM2 = DIM, std::enable_if_t<DIM2 == 2, int> = 0>
	ParabolaS(const Axis2& directrix, const Point2& focus, bool isRight = true)
		: focalLength(0.5 * std::fabs((focus.Coord() - directrix.Location().Coord()).Cross(directrix.Direction().Coord())))
	{
		Point2 origin(directrix.Location().Coord() + directrix.Direction().Coord() * (focus.Coord() - directrix.Location().Coord()).Dot(directrix.Direction().Coord()));
		pos = Frame2(Point2(0.5 * (origin.Coord() + focus.Coord())), focalLength > 0.0 ? Direction2(focus.Coord() - origin.Coord()) : directrix.Rotated(directrix.Location(), isRight ? -Constants::half_pi : Constants::half_pi).Direction(), directrix.Direction());
	}

	/// @brief Construct from a directrix and a focus in 3D
	/// @param directrix The directrix
	/// @param focus The focus
	template<int DIM2 = DIM, std::enable_if_t<DIM2 == 3, int> = 0>
	ParabolaS(const Axis3& directrix, const Point3& focus)
		: focalLength(0.5 * (focus.Coord() - directrix.Location().Coord()).Cross(directrix.Direction().Coord()).Norm())
	{
		Direction3 dir(directrix.Direction().Coord().Cross((focus.Coord() - directrix.Location().Coord()).Cross(directrix.Direction().Coord())));
		pos = Frame3(Point3(focus.Coord() - focalLength * dir.Coord()), Direction3(dir.Coord().Cross(directrix.Location().Coord())), dir);
	}

	/// @brief Set the mirror axis in 2D
	/// @param axis The mirror axis
	template<int DIM2 = DIM, std::enable_if_t<DIM2 == 2, int> = 0>
	void SetMirrorAxis(const Axis2& axis) noexcept
	{
		pos.SetXAxis(axis);
	}

	/// @brief Get the mirror axis of the parabola in 2D
	/// @return The mirror axis
	template<int DIM2 = DIM, std::enable_if_t<DIM2 == 2, int> = 0>
	[[nodiscard]] constexpr Axis2 MirrorAxis() const noexcept
	{
		return pos.XAxis();
	}

	/// @brief Get the coefficients in the algebraic representation of the parabola in 2D
	/// @details The algebraic representation is ax^2 + by^2 + 2cxy + 2dx + 2ey + f = 0
	/// @param[out] a,b,c,d,e,f The coefficients
	template<int DIM2 = DIM, std::enable_if_t<DIM2 == 2, int> = 0>
	constexpr void Coefficients(double& a, double& b, double& c, double& d, double& e, double& f) const noexcept
	{
		Transformation2 tr;
		tr.SetTransformation(pos.XAxis());
		double t00 = tr.Value(0, 0);
		double t01 = tr.Value(0, 1);
		double t02 = tr.Value(0, 2);
		double t10 = tr.Value(1, 0);
		double t11 = tr.Value(1, 1);
		double t12 = tr.Value(1, 2);
		a = t10 * t10;
		b = t11 * t11;
		c = t10 * t11;
		d = t10 * t12 - 2.0 * focalLength * t00;
		e = t11 * t12 - 2.0 * focalLength * t01;
		f = t12 * t12 - 4.0 * focalLength * t02;
	}

	/// @brief Set the focal length
	/// @param focal The focal length
	void SetFocal(double focal)
	{
		focalLength = focal;
		CheckValidity();
	}

	/// @brief Get the directrix
	/// @return The directrix
	[[nodiscard]] constexpr AxisT<double, DIM> Directrix() const noexcept
	{
		return AxisT<double, DIM>(PointT<double, DIM>(pos.Location().Coord() - focalLength * pos.XDirection().Coord()), pos.YDirection());
	}

	/// @brief Get the focal length
	/// @return The focal length
	[[nodiscard]] constexpr double Focal() const noexcept
	{
		return focalLength;
	}

	/// @brief Get the focus point
	/// @return The focus point
	[[nodiscard]] constexpr PointT<double, DIM> Focus() const noexcept
	{
		return PointT<double, DIM>(pos.Location().Coord() + focalLength * pos.XDirection().Coord());
	}

	/// @brief Get the focal parameter of the parabola
	/// @details The focal parameter of parabola is the distance from the focus to the directrix.
	///          Focal parameter = 2 * focalLength.
	/// @return The focal parameter
	[[nodiscard]] constexpr double FocalParameter() const noexcept
	{
		return 2.0 * focalLength;
	}

	/// @brief Get the semilatus rectum of the parabola
	/// @details The semilatus rectum of parabola is half of the length of the chord through a focus parallel to the directrix.
	///          Semilatus rectum = 2 * focalLength
	/// @return The semilatus rectum
	[[nodiscard]] constexpr double SemilatusRectum() const noexcept
	{
		return 2.0 * focalLength;
	}

	/// @brief Scale the parabola by a center point
	/// @param point The scaling center point
	/// @param scale The scale value
	/// @return The reference to self
	constexpr ParabolaS& Scale(const PointT<double, DIM>& point, double scale) noexcept
	{
		focalLength *= scale;
		if (focalLength < 0.0)
		{
			focalLength = -focalLength;
		}
		return Base::Scale(point, scale);
	}

	/// @brief Transform the parabola
	/// @param tr The transformation
	/// @return The reference to self
	ParabolaS& Transform(const TransformationT<double, DIM>& tr) noexcept
	{
		focalLength *= tr.ScaleFactor();
		if (focalLength < 0.0)
		{
			focalLength = -focalLength;
		}
		return Base::Transform(tr);
	}

protected:
	/// @brief Check the validity of parabola
	void CheckValidity() const
	{
		if (focalLength < 0.0)
		{
			throw ConstructionError("focal length should be non-negative");
		}
	}

	/// @brief The focal length
	double focalLength = std::numeric_limits<double>::max();
};

/// @brief Compatible alias of ParabolaS
/// @tparam Scalar Type of scalar value
/// @tparam DIM Dimension
template<typename Scalar, int DIM>
using ParabolaT = ParabolaS<DIM>;

/// @brief 2D parabola
using Parabola2 = ParabolaS<2>;

/// @brief 3D parabola
using Parabola3 = ParabolaS<3>;

} // namespace AMCAX
