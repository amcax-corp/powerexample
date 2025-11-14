/// @file      EllipseT.hpp
/// @brief     Class of ellipse
/// @details   Implementation of ellipse
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <math/ConicBase.hpp>

namespace AMCAX
{
/// @brief Base class of ellipse
/// @tparam Derived Type of derived class
/// @tparam DIM Dimension
template<int DIM>
class EllipseS : public ConicBase<DIM, EllipseS<DIM>>
{
	using Base = ConicBase<DIM, EllipseS<DIM>>;

protected:
	using Base::pos;

public:
	/// @brief Default constructor
	constexpr EllipseS() noexcept = default;

	/// @brief Construct from an axis, major and minor radius in 2D
	/// @param majorAxis The major axis
	/// @param major The major radius
	/// @param minor The minor radius
	/// @param isRight Is the frame right-handed
	template<int DIM2 = DIM, std::enable_if_t<DIM2 == 2, int> = 0>
	EllipseS(const AxisT<double, DIM>& majorAxis, double major, double minor, bool isRight = true)
		: Base(majorAxis, isRight),
		  majorRadius(major),
		  minorRadius(minor)
	{
		CheckValidity();
	}

	/// @brief Construct from a frame, major and minor radius
	/// @param frame The frame
	/// @param major The major radius
	/// @param minor The minor radius
	EllipseS(const FrameT<double, DIM>& frame, double major, double minor)
		: Base(frame),
		  majorRadius(major),
		  minorRadius(minor)
	{
		CheckValidity();
	}

	/// @brief Get the coefficients in the algebraic representation of the ellipse in 2D
	/// @details The algebraic representation is ax^2 + by^2 + 2cxy + 2dx + 2ey + f = 0
	/// @param[out] a,b,c,d,e,f The coefficients
	template<int DIM2 = DIM, std::enable_if_t<DIM2 == 2, int> = 0>
	constexpr void Coefficients(double& a, double& b, double& c, double& d, double& e, double& f) const noexcept
	{
		double dminor = minorRadius * minorRadius;
		double dmajor = majorRadius * majorRadius;
		if (dminor <= std::numeric_limits<double>::min() && dmajor <= std::numeric_limits<double>::min())
		{
			a = b = c = d = e = f = 0.0;
		}
		else
		{
			Transformation2 tr;
			tr.SetTransformation(pos.XAxis());
			double t00 = tr.Value(0, 0);
			double t01 = tr.Value(0, 1);
			double t02 = tr.Value(0, 2);
			if (dminor <= std::numeric_limits<double>::min())
			{
				a = t00 * t00;
				b = t01 * t01;
				c = t00 * t01;
				d = t00 * t02;
				e = t01 * t02;
				f = t02 * t02 - dmajor;
			}
			else
			{
				double t10 = tr.Value(1, 0);
				double t11 = tr.Value(1, 1);
				double t12 = tr.Value(1, 2);
				a = t00 * t00 / dmajor + t10 * t10 / dminor;
				b = t01 * t01 / dmajor + t11 * t11 / dminor;
				c = t00 * t01 / dmajor + t10 * t11 / dminor;
				d = t00 * t02 / dmajor + t10 * t12 / dminor;
				e = t01 * t02 / dmajor + t11 * t12 / dminor;
				f = t02 * t02 / dmajor + t12 * t12 / dminor - 1.0;
			}
		}
	}

	/// @brief Set the major radius
	/// @param r The new major radius
	void SetMajorRadius(double r)
	{
		majorRadius = r;
		CheckValidity();
	}

	/// @brief Set the minor radius
	/// @param r The new minor radius
	void SetMinorRadius(double r)
	{
		minorRadius = r;
		CheckValidity();
	}

	/// @brief Get the area of the ellipse
	/// @return The area of the ellipse
	[[nodiscard]] constexpr double Area() const noexcept
	{
		return Constants::pi * majorRadius * minorRadius;
	}

	/// @brief Get the directrix on the positive side of the major axis
	/// @return The positive directrix
	[[nodiscard]] AxisT<double, DIM> Directrix1() const
	{
		double e = Eccentricity();
		Throw_Construction_Error_if(e <= std::numeric_limits<double>::min(), "zero eccentricity");
		return AxisT<double, DIM>(PointT<double, DIM>(pos.XDirection().Coord() * (majorRadius / e) + pos.Location().Coord()), pos.YDirection());
	}

	/// @brief Get the directrix on the negative side of the major axis
	/// @return The negative directrix
	[[nodiscard]] AxisT<double, DIM> Directrix2() const
	{
		double e = Eccentricity();
		Throw_Construction_Error_if(e <= std::numeric_limits<double>::min(), "zero eccentricity");
		return AxisT<double, DIM>(PointT<double, DIM>(pos.XDirection().Coord() * (-majorRadius / e) + pos.Location().Coord()), pos.YDirection());
	}

	/// @brief Get the eccentricity of the ellipse
	/// @return The eccentricity
	[[nodiscard]] double Eccentricity() const
	{
		Throw_Domain_Error_if(majorRadius <= std::numeric_limits<double>::min(), "major radius is zero");
		return std::sqrt(majorRadius * majorRadius - minorRadius * minorRadius) / majorRadius;
	}

	/// @brief Get the focal distance, i.e. the distance between two foci
	/// @return The focal distance
	[[nodiscard]] double Focal() const noexcept
	{
		return 2.0 * std::sqrt(majorRadius * majorRadius - minorRadius * minorRadius);
	}

	/// @brief Get the focus on the positive side of the major axis
	/// @return The positive focus
	[[nodiscard]] PointT<double, DIM> Focus1() const noexcept
	{
		return PointT<double, DIM>(pos.Location().Coord() + pos.XDirection().Coord() * std::sqrt(majorRadius * majorRadius - minorRadius * minorRadius));
	}

	/// @brief Get the focus on the negative side of the major axis
	/// @return The negative focus
	[[nodiscard]] PointT<double, DIM> Focus2() const noexcept
	{
		return PointT<double, DIM>(pos.Location().Coord() - pos.XDirection().Coord() * std::sqrt(majorRadius * majorRadius - minorRadius * minorRadius));
	}

	/// @brief Get the major radius
	/// @return The major radius
	[[nodiscard]] constexpr double MajorRadius() const noexcept
	{
		return majorRadius;
	}

	/// @brief Get the minor radius
	/// @return The minor radius
	[[nodiscard]] constexpr double MinorRadius() const noexcept
	{
		return minorRadius;
	}

	/// @brief Get the focal parameter of the ellipse
	/// @details The focal parameter of ellipse is the distance from a focus to the corresponding directrix.
	///          Focal parameter = 2 * minor ^ 2 / focal = major * (1 - eccentricity ^ 2) / eccentricity
	/// @return The focal parameter
	[[nodiscard]] double FocalParameter() const
	{
		Throw_Domain_Error_if(majorRadius == minorRadius, "major and minor radii are equal");
		return minorRadius * minorRadius / std::sqrt(majorRadius * majorRadius - minorRadius * minorRadius);
	}

	/// @brief Get the semilatus rectum of the ellipse
	/// @details The semilatus rectum of ellipse is half of the length of the chord through a focus parallel to the directrix.
	///          Semilatus rectum = minor ^ 2 / major = major * (1 - eccentricity ^ 2)
	/// @return The semilatus rectum
	[[nodiscard]] double SemilatusRectum() const
	{
		Throw_Domain_Error_if(majorRadius <= std::numeric_limits<double>::min(), "major radius is zero");
		return minorRadius * minorRadius / majorRadius;
	}

	/// @brief Scale the ellipse by a center point
	/// @param point The scaling center point
	/// @param scale The scale value
	/// @return The reference to self
	constexpr EllipseS& Scale(const PointT<double, DIM>& point, double scale) noexcept
	{
		majorRadius *= scale;
		if (majorRadius < 0.0)
		{
			majorRadius = -majorRadius;
		}
		minorRadius *= scale;
		if (minorRadius < 0.0)
		{
			minorRadius = -minorRadius;
		}
		return Base::Scale(point, scale);
	}

	/// @brief Transform the ellipse
	/// @param tr The transformation
	/// @return The reference to self
	EllipseS& Transform(const TransformationT<double, DIM>& tr) noexcept
	{
		majorRadius *= tr.ScaleFactor();
		if (majorRadius < 0.0)
		{
			majorRadius = -majorRadius;
		}
		minorRadius *= tr.ScaleFactor();
		if (minorRadius < 0.0)
		{
			minorRadius = -minorRadius;
		}
		return Base::Transform(tr);
	}

protected:
	/// @brief Check the validity of ellipse
	void CheckValidity() const
	{
		if (majorRadius < minorRadius)
		{
			throw ConstructionError("major radius should be not smaller than minor radius");
		}
		if (minorRadius < 0.0)
		{
			throw ConstructionError("minor radius should be positive");
		}
	}

	/// @brief The major radius of ellipse
	double majorRadius = std::numeric_limits<double>::max();

	/// @brief The minor radius of ellipse
	double minorRadius = std::numeric_limits<double>::min();
};

/// @brief Compatible alias of EllipseS
/// @tparam Scalar Type of scalar value
/// @tparam DIM Dimension
template<typename Scalar, int DIM>
using EllipseT = EllipseS<DIM>;

/// @brief 2D ellipse
using Ellipse2 = EllipseS<2>;

/// @brief 3D ellipse
using Ellipse3 = EllipseS<3>;

} // namespace AMCAX
