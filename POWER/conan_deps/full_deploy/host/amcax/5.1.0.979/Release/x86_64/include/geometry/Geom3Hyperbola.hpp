/// @file      Geom3Hyperbola.hpp
/// @brief     Class of 3D hyperbola
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <geometry/Geom3Conic.hpp>
#include <math/HyperbolaT.hpp>

namespace AMCAX
{
/// @brief Class of 3D hyperbola
class AMCAX_CLASS_API Geom3Hyperbola : public Geom3Conic
{
public:
	/// @brief Default constructor
	constexpr Geom3Hyperbola() noexcept = default;

	/// @brief Construct from an hyperbola
	/// @param h The hyperbola
	AMCAX_API explicit Geom3Hyperbola(const Hyperbola3& h) noexcept;

	/// @brief Construct from a local frame, a major radius and a minor radius
	/// @param frame The local frame
	/// @param major The major radius
	/// @param minor The minor radius
	AMCAX_API Geom3Hyperbola(const Frame3& frame, double major, double minor);

	/// @brief Set the hyperbola
	/// @param h The hyperbola
	AMCAX_API void SetHyperbola(const Hyperbola3& h) noexcept;

	/// @brief Set the major radius
	/// @param major The major radius
	AMCAX_API void SetMajorRadius(double major);

	/// @brief Set the minor radius
	/// @param minor The minor radius
	AMCAX_API void SetMinorRadius(double minor);

	/// @brief Get the hyperbola
	/// @return The hyperbola
	[[nodiscard]] AMCAX_API Hyperbola3 Hyperbola() const noexcept;

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
	[[nodiscard]] AMCAX_API Axis3 Asymptote1() const;

	/// @brief Get the asymptote of the hyperbola with negative slope
	/// @return The negative asymptote
	[[nodiscard]] AMCAX_API Axis3 Asymptote2() const;

	/// @brief Get the conjugate hyperbola on the positive side of the minor axis
	/// @return The positive conjugate hyperbola
	[[nodiscard]] AMCAX_API Hyperbola3 ConjugateBranch1() const noexcept;

	/// @brief Get the conjugate hyperbola on the negative side of the minor axis
	/// @return The negative conjugate hyperbola
	[[nodiscard]] AMCAX_API Hyperbola3 ConjugateBranch2() const noexcept;

	/// @brief Get the directrix on the positive side of the major axis
	/// @return The positive directrix
	[[nodiscard]] AMCAX_API Axis3 Directrix1() const;

	/// @brief Get the directrix on the negative side of the major axis
	/// @return The negative directrix
	[[nodiscard]] AMCAX_API Axis3 Directrix2() const;

	/// @brief Get the eccentricity of the hyperbola
	/// @return The eccentricity
	[[nodiscard]] AMCAX_API double Eccentricity() const override;

	/// @brief Get the focal distance, i.e. the distance between two foci
	/// @return The focal distance
	[[nodiscard]] AMCAX_API double Focal() const noexcept;

	/// @brief Get the focus on the positive side of the major axis
	/// @return The positive focus
	[[nodiscard]] AMCAX_API Point3 Focus1() const noexcept;

	/// @brief Get the focus on the negative side of the major axis
	/// @return The negative focus
	[[nodiscard]] AMCAX_API Point3 Focus2() const noexcept;

	/// @brief Get the major radius
	/// @return The major radius
	[[nodiscard]] AMCAX_API double MajorRadius() const noexcept;

	/// @brief Get the minor radius
	/// @return The minor radius
	[[nodiscard]] AMCAX_API double MinorRadius() const noexcept;

	/// @brief Get the other branch of the hyperbola
	/// @return The hyperbola of the other branch
	[[nodiscard]] AMCAX_API Hyperbola3 OtherBranch() const noexcept;

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

	AMCAX_API void D0(double u, Point3& p) const noexcept override;
	AMCAX_API void D1(double u, Point3& p, Vector3& v1) const noexcept override;
	AMCAX_API void D2(double u, Point3& p, Vector3& v1, Vector3& v2) const noexcept override;
	AMCAX_API void D3(double u, Point3& p, Vector3& v1, Vector3& v2, Vector3& v3) const noexcept override;
	[[nodiscard]] AMCAX_API Vector3 DN(double u, int n) const override;
	AMCAX_API void Transform(const Transformation3& tr) noexcept override;
	[[nodiscard]] AMCAX_API std::shared_ptr<Geom3Geometry> Copy() const override;
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
