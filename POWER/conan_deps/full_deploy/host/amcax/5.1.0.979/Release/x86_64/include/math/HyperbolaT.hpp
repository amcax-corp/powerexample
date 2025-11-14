/// @file      HyperbolaT.hpp
/// @brief     Class of hyperbola
/// @details   Implementation of hyperbola
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <math/ConicBase.hpp>

namespace AMCAX
{
/// @brief Base class of hyperbola
/// @tparam Derived Type of derived class
/// @tparam DIM Dimension
template<int DIM>
class HyperbolaS : public ConicBase<DIM, HyperbolaS<DIM>>
{
	using Base = ConicBase<DIM, HyperbolaS<DIM>>;

protected:
	using Base::pos;

public:
	/// @brief Default constructor
	constexpr HyperbolaS() noexcept = default;

	/// @brief Construct from an axis, major and minor radius in 2D
	/// @param majorAxis The major axis
	/// @param major The major radius
	/// @param minor The minor radius
	/// @param isRight Is the frame right-handed
	template<int DIM2 = DIM, std::enable_if_t<DIM2 == 2, int> = 0>
	HyperbolaS(const AxisT<double, DIM>& majorAxis, double major, double minor, bool isRight = true)
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
	HyperbolaS(const FrameT<double, DIM>& frame, double major, double minor)
		: Base(frame),
		  majorRadius(major),
		  minorRadius(minor)
	{
		CheckValidity();
	}

	/// @brief Get the coefficients in the algebraic representation of the hyperbola in 2D
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
				a = t00 * t00 / dmajor - t10 * t10 / dminor;
				b = t01 * t01 / dmajor - t11 * t11 / dminor;
				c = t00 * t01 / dmajor - t10 * t11 / dminor;
				d = t00 * t02 / dmajor - t10 * t12 / dminor;
				e = t01 * t02 / dmajor - t11 * t12 / dminor;
				f = t02 * t02 / dmajor - t12 * t12 / dminor - 1.0;
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

	/// @brief Get the asymptote of the hyperbola with positive slope
	/// @return The positive asymptote
	[[nodiscard]] AxisT<double, DIM> Asymptote1() const
	{
		Throw_Construction_Error_if(majorRadius <= std::numeric_limits<double>::min(), "major radius is zero");
		return AxisT<double, DIM>(pos.Location(), DirectionT<double, DIM>(pos.XDirection().Coord() + pos.YDirection().Coord() * (minorRadius / majorRadius)));
	}

	/// @brief Get the asymptote of the hyperbola with negative slope
	/// @return The negative asymptote
	[[nodiscard]] AxisT<double, DIM> Asymptote2() const
	{
		Throw_Construction_Error_if(majorRadius <= std::numeric_limits<double>::min(), "major radius is zero");
		return AxisT<double, DIM>(pos.Location(), DirectionT<double, DIM>(pos.XDirection().Coord() - pos.YDirection().Coord() * (minorRadius / majorRadius)));
	}

	/// @brief Get the directrix on the positive side of the major axis
	/// @return The positive directrix
	[[nodiscard]] AxisT<double, DIM> Directrix1() const
	{
		return AxisT<double, DIM>(PointT<double, DIM>(pos.XDirection().Coord() * (majorRadius / Eccentricity()) + pos.Location().Coord()), pos.YDirection());
	}

	/// @brief Get the directrix on the negative side of the major axis
	/// @return The negative directrix
	[[nodiscard]] AxisT<double, DIM> Directrix2() const
	{
		return AxisT<double, DIM>(PointT<double, DIM>(pos.XDirection().Coord() * (-majorRadius / Eccentricity()) + pos.Location().Coord()), pos.YDirection());
	}

	/// @brief Get the eccentricity of the hyperbola
	/// @return The eccentricity
	[[nodiscard]] double Eccentricity() const
	{
		Throw_Domain_Error_if(majorRadius <= std::numeric_limits<double>::min(), "major radius is zero");
		return std::sqrt(majorRadius * majorRadius + minorRadius * minorRadius) / majorRadius;
	}

	/// @brief Get the focal distance, i.e. the distance between two foci
	/// @return The focal distance
	[[nodiscard]] double Focal() const noexcept
	{
		return 2.0 * std::sqrt(majorRadius * majorRadius + minorRadius * minorRadius);
	}

	/// @brief Get the focus on the positive side of the major axis
	/// @return The positive focus
	[[nodiscard]] PointT<double, DIM> Focus1() const noexcept
	{
		return PointT<double, DIM>(pos.Location().Coord() + pos.XDirection().Coord() * std::sqrt(majorRadius * majorRadius + minorRadius * minorRadius));
	}

	/// @brief Get the focus on the negative side of the major axis
	/// @return The negative focus
	[[nodiscard]] PointT<double, DIM> Focus2() const noexcept
	{
		return PointT<double, DIM>(pos.Location().Coord() - pos.XDirection().Coord() * std::sqrt(majorRadius * majorRadius + minorRadius * minorRadius));
	}

	/// @brief Get the conjugate hyperbola on the positive side of the minor axis
	/// @return The positive conjugate hyperbola
	[[nodiscard]] HyperbolaS ConjugateBranch1() const noexcept
	{
		if constexpr (DIM == 2)
		{
			HyperbolaS hyperbola(*this);
			hyperbola.pos = Frame2(Axis2(pos.Location(), pos.YDirection()), pos.IsDirect());
			std::swap(hyperbola.majorRadius, hyperbola.minorRadius);
			return hyperbola;
		}
		else
		{
			HyperbolaS hyperbola(*this);
			hyperbola.pos = Frame3(pos.Location(), pos.Direction(), pos.YDirection());
			std::swap(hyperbola.majorRadius, hyperbola.minorRadius);
			return hyperbola;
		}
	}

	/// @brief Get the conjugate hyperbola on the negative side of the minor axis
	/// @return The negative conjugate hyperbola
	[[nodiscard]] HyperbolaS ConjugateBranch2() const noexcept
	{
		if constexpr (DIM == 2)
		{
			HyperbolaS hyperbola(*this);
			hyperbola.pos = Frame2(Axis2(pos.Location(), pos.YDirection().Reversed()), pos.IsDirect());
			std::swap(hyperbola.majorRadius, hyperbola.minorRadius);
			return hyperbola;
		}
		else
		{
			HyperbolaS hyperbola(*this);
			hyperbola.pos = Frame3(pos.Location(), pos.Direction(), pos.YDirection().Reversed());
			std::swap(hyperbola.majorRadius, hyperbola.minorRadius);
			return hyperbola;
		}
	}

	/// @brief Get the other branch of the hyperbola
	/// @return The hyperbola of the other branch
	[[nodiscard]] HyperbolaS OtherBranch() const noexcept
	{
		if constexpr (DIM == 2)
		{
			HyperbolaS hyperbola(*this);
			hyperbola.pos = Frame2(Axis2(pos.Location(), pos.XDirection().Reversed()), pos.IsDirect());
			return hyperbola;
		}
		else
		{
			HyperbolaS hyperbola(*this);
			hyperbola.pos = Frame3(pos.Location(), pos.Direction(), pos.XDirection().Reversed());
			return hyperbola;
		}
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

	/// @brief Get the focal parameter of the hyperbola
	/// @details The focal parameter of hyperbola is the distance from a focus to the corresponding directrix.
	///          Focal parameter = 2 * minor ^ 2 / focal = major * (eccentricity ^ 2 - 1) / eccentricity
	/// @return The focal parameter
	[[nodiscard]] double FocalParameter() const
	{
		Throw_Domain_Error_if(majorRadius <= std::numeric_limits<double>::min() && minorRadius <= std::numeric_limits<double>::min(), "major or minor radius is zero");
		return minorRadius * minorRadius / std::sqrt(majorRadius * majorRadius + minorRadius * minorRadius);
	}

	/// @brief Get the semilatus rectum of the hyperbola
	/// @details The semilatus rectum of hyperbola is half of the length of the chord through a focus parallel to the directrix.
	///          Semilatus rectum = minor ^ 2 / major = major * (eccentricity ^ 2 - 1)
	/// @return The semilatus rectum
	[[nodiscard]] double SemilatusRectum() const
	{
		Throw_Domain_Error_if(majorRadius <= std::numeric_limits<double>::min(), "major radius is zero");
		return minorRadius * minorRadius / majorRadius;
	}

	/// @brief Scale the hyperbola by a center point
	/// @param point The scaling center point
	/// @param scale The scale value
	/// @return The reference to self
	constexpr HyperbolaS& Scale(const PointT<double, DIM>& point, double scale) noexcept
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

	/// @brief Transform the hyperbola
	/// @param tr The transformation
	/// @return The reference to self
	HyperbolaS& Transform(const TransformationT<double, DIM>& tr) noexcept
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
	/// @brief Check the validity of hyperbola
	void CheckValidity() const
	{
		if (majorRadius < 0.0)
		{
			throw ConstructionError("major radius should be non-negative");
		}
		if (minorRadius < 0.0)
		{
			throw ConstructionError("minor radius should be non-negative");
		}
	}

	/// @brief The major radius of hyperbola
	double majorRadius = std::numeric_limits<double>::max();

	/// @brief The minor radius of hyperbola
	double minorRadius = std::numeric_limits<double>::max();
};

/// @brief Compatible alias of HyperbolaS
/// @tparam Scalar Type of scalar value
/// @tparam DIM Dimension
template<typename Scalar, int DIM>
using HyperbolaT = HyperbolaS<DIM>;

/// @brief 2D hyperbola
using Hyperbola2 = HyperbolaS<2>;

/// @brief 3D hyperbola
using Hyperbola3 = HyperbolaS<3>;
} // namespace AMCAX
