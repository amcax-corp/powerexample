/// @file      Geom2Hyperbola.hpp
/// @brief     Class of 2D hyperbola
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <geometry/Geom2Conic.hpp>
#include <math/HyperbolaT.hpp>

namespace AMCAX
{
/// @brief Class of 2D hyperbola
class AMCAX_CLASS_API Geom2Hyperbola : public Geom2Conic
{
public:
	/// @brief Default constructor
	constexpr Geom2Hyperbola() noexcept = default;

	/// @brief Construct from an hyperbola
	/// @param h The hyperbola
	AMCAX_API explicit Geom2Hyperbola(const Hyperbola2& h) noexcept;

	/// @brief Construct from an axis, a major radius and a minor radius
	/// @param axis The axis
	/// @param major The major radius
	/// @param minor The minor radius
	/// @param isRight Is the local frame right-handed
	AMCAX_API Geom2Hyperbola(const Axis2& axis, double major, double minor, bool isRight = true);

	/// @brief Construct from a local frame, a major radius and a minor radius
	/// @param frame The local frame
	/// @param major The major radius
	/// @param minor The minor radius
	AMCAX_API Geom2Hyperbola(const Frame2& frame, double major, double minor);

	/// @brief Set the hyperbola
	/// @param h The hyperbola
	AMCAX_API void SetHyperbola(const Hyperbola2& h) noexcept;

	/// @brief Set the major radius
	/// @param major The major radius
	AMCAX_API void SetMajorRadius(double major);

	/// @brief Set the minor radius
	/// @param minor The minor radius
	AMCAX_API void SetMinorRadius(double minor);

	/// @brief Get the hyperbola
	/// @return The hyperbola
	[[nodiscard]] AMCAX_API Hyperbola2 Hyperbola() const noexcept;

	[[nodiscard]] AMCAX_API double ReversedParameter(double u) const noexcept override;

	/// @brief Get the first parameter
	/// @details For a hyperbola, the first parameter is negative infinity
	/// @return The first parameter
	[[nodiscard]] AMCAX_API double FirstParameter() const noexcept override;

	/// @brief Get the last parameter
	/// @details For a hyperbola, the last parameter is positive infinity
	/// @return The last parameter
	[[nodiscard]] AMCAX_API double LastParameter() const noexcept override;

	/// @brief Is the hyperbola closed
	/// @return Always false
	[[nodiscard]] AMCAX_API bool IsClosed() const noexcept override;

	/// @brief Is the hyperbola periodic
	/// @return Always false
	[[nodiscard]] AMCAX_API bool IsPeriodic() const noexcept override;

	/// @brief Get the asymptote of the hyperbola with positive slope
	/// @return The positive asymptote
	[[nodiscard]] AMCAX_API Axis2 Asymptote1() const;

	/// @brief Get the asymptote of the hyperbola with negative slope
	/// @return The negative asymptote
	[[nodiscard]] AMCAX_API Axis2 Asymptote2() const;

	/// @brief Get the conjugate hyperbola on the positive side of the minor axis
	/// @return The positive conjugate hyperbola
	[[nodiscard]] AMCAX_API Hyperbola2 ConjugateBranch1() const noexcept;

	/// @brief Get the conjugate hyperbola on the negative side of the minor axis
	/// @return The negative conjugate hyperbola
	[[nodiscard]] AMCAX_API Hyperbola2 ConjugateBranch2() const noexcept;

	/// @brief Get the directrix on the positive side of the major axis
	/// @return The positive directrix
	[[nodiscard]] AMCAX_API Axis2 Directrix1() const;

	/// @brief Get the directrix on the negative side of the major axis
	/// @return The negative directrix
	[[nodiscard]] AMCAX_API Axis2 Directrix2() const;

	/// @brief Get the eccentricity of the hyperbola
	/// @return The eccentricity
	[[nodiscard]] AMCAX_API double Eccentricity() const override;

	/// @brief Get the focal distance, i.e. the distance between two foci
	/// @return The focal distance
	[[nodiscard]] AMCAX_API double Focal() const noexcept;

	/// @brief Get the focus on the positive side of the major axis
	/// @return The positive focus
	[[nodiscard]] AMCAX_API Point2 Focus1() const noexcept;

	/// @brief Get the focus on the negative side of the major axis
	/// @return The negative focus
	[[nodiscard]] AMCAX_API Point2 Focus2() const noexcept;

	/// @brief Get the major radius
	/// @return The major radius
	[[nodiscard]] AMCAX_API double MajorRadius() const noexcept;

	/// @brief Get the minor radius
	/// @return The minor radius
	[[nodiscard]] AMCAX_API double MinorRadius() const noexcept;

	/// @brief Get the other branch of the hyperbola
	/// @return The hyperbola of the other branch
	[[nodiscard]] AMCAX_API Hyperbola2 OtherBranch() const noexcept;

	/// @brief Get the focal parameter of the hyperbola
	/// @details The focal parameter of hyperbola is the distance from a focus to the corresponding directrix.
	///          Focal parameter = 2 * minor ^ 2 / focal = major * (eccentricity ^ 2 - 1) / eccentricity
	/// @return The focal parameter
	[[nodiscard]] AMCAX_API double FocalParameter() const;

	/// @brief Get the semilatus rectum of the hyperbola
	/// @details The semilatus rectum of hyperbola is half of the length of the chord through a focus parallel to the directrix.
	///          Semilatus rectum = minor ^ 2 / major = major * (eccentricity ^ 2 - 1)
	/// @return The semilatus rectum
	[[nodiscard]] AMCAX_API double SemilatusRectum() const;

	AMCAX_API void D0(double u, Point2& p) const noexcept override;
	AMCAX_API void D1(double u, Point2& p, Vector2& v1) const noexcept override;
	AMCAX_API void D2(double u, Point2& p, Vector2& v1, Vector2& v2) const noexcept override;
	AMCAX_API void D3(double u, Point2& p, Vector2& v1, Vector2& v2, Vector2& v3) const noexcept override;
	[[nodiscard]] AMCAX_API Vector2 DN(double u, int n) const override;
	AMCAX_API void Transform(const Transformation2& tr) noexcept override;
	[[nodiscard]] AMCAX_API std::shared_ptr<Geom2Geometry> Copy() const override;
	AMCAX_API std::ostream& Write(std::ostream& os) const override;
	AMCAX_API std::istream& Read(std::istream& is) override;

	/// @brief Get the type of curve, a hyperbola
	/// @return Type hyperbola
	[[nodiscard]] AMCAX_API CurveType Type() const noexcept override;

private:
	void CheckValidity() const;

	/// @brief Major radius of hyperbola
	double majorRadius = std::numeric_limits<double>::max();

	/// @brief Minor radius of hyperbola
	double minorRadius = std::numeric_limits<double>::max();
};
} // namespace AMCAX
