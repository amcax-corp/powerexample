/// @file      Geom3Ellipse.hpp
/// @brief     Class of 3D ellipse
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <geometry/Geom3Conic.hpp>
#include <math/EllipseT.hpp>

namespace AMCAX
{
/// @brief Class of 3D ellipse
class AMCAX_CLASS_API Geom3Ellipse : public Geom3Conic
{
public:
	/// @brief Default constructor
	constexpr Geom3Ellipse() noexcept = default;

	/// @brief Construct from an ellipse
	/// @param e The ellipse
	AMCAX_API explicit Geom3Ellipse(const Ellipse3& e) noexcept;

	/// @brief Construct from a local frame, a major radius and a minor radius
	/// @param frame The local frame
	/// @param major The major radius
	/// @param minor The minor radius
	AMCAX_API Geom3Ellipse(const Frame3& frame, double major, double minor);

	/// @brief Set the ellipse
	/// @param e The ellipse
	AMCAX_API void SetEllipse(const Ellipse3& e) noexcept;

	/// @brief Set the major radius
	/// @param major The major radius
	AMCAX_API void SetMajorRadius(double major);

	/// @brief Set the minor radius
	/// @param minor The minor radius
	AMCAX_API void SetMinorRadius(double minor);

	/// @brief Get the ellipse
	/// @return The ellipse
	[[nodiscard]] AMCAX_API Ellipse3 Ellipse() const noexcept;

	[[nodiscard]] AMCAX_API double ReversedParameter(double u) const noexcept override;

	/// @brief Get the directrix on the positive side of the major axis
	/// @return The positive directrix
	[[nodiscard]] AMCAX_API Axis3 Directrix1() const;

	/// @brief Get the directrix on the negative side of the major axis
	/// @return The negative directrix
	[[nodiscard]] AMCAX_API Axis3 Directrix2() const;

	/// @brief Get the eccentricity of the ellipse
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

	/// @brief Get the focal parameter of the ellipse
	/// @details The focal parameter of ellipse is the distance from a focus to the corresponding directrix.
	///          Focal parameter = 2 * minor ^ 2 / focal = major * (1 - eccentricity ^ 2) / eccentricity
	/// @return The focal parameter
	[[nodiscard]] AMCAX_API double FocalParameter() const;

	/// @brief Get the semilatus rectum of the ellipse
	/// @details The semilatus rectum of ellipse is half of the length of the chord through a focus parallel to the directrix.
	///          Semilatus rectum = minor ^ 2 / major = major * (1 - eccentricity ^ 2)
	/// @return The semilatus rectum
	[[nodiscard]] AMCAX_API double SemilatusRectum() const;

	/// @brief Get the first parameter
	/// @details For an ellipse, the first parameter is 0
	/// @return The first parameter
	[[nodiscard]] AMCAX_API double FirstParameter() const noexcept override;

	/// @brief Get the last parameter
	/// @details For an ellipse, the last parameter is 2pi
	/// @return The last parameter
	[[nodiscard]] AMCAX_API double LastParameter() const noexcept override;

	/// @brief Is the ellipse closed
	/// @return Always true
	[[nodiscard]] AMCAX_API bool IsClosed() const noexcept override;

	/// @brief Is the ellipse periodic
	/// @return Always true
	[[nodiscard]] AMCAX_API bool IsPeriodic() const noexcept override;

	AMCAX_API void D0(double u, Point3& p) const noexcept override;
	AMCAX_API void D1(double u, Point3& p, Vector3& v1) const noexcept override;
	AMCAX_API void D2(double u, Point3& p, Vector3& v1, Vector3& v2) const noexcept override;
	AMCAX_API void D3(double u, Point3& p, Vector3& v1, Vector3& v2, Vector3& v3) const noexcept override;
	[[nodiscard]] AMCAX_API Vector3 DN(double u, int n) const override;
	AMCAX_API void Transform(const Transformation3& tr) noexcept override;
	[[nodiscard]] AMCAX_API std::shared_ptr<Geom3Geometry> Copy() const override;
	AMCAX_API std::ostream& Write(std::ostream& os) const override;
	AMCAX_API std::istream& Read(std::istream& is) override;

	/// @brief Get the type of curve, an ellipse
	/// @return Type ellipse
	[[nodiscard]] AMCAX_API CurveType Type() const noexcept override;

private:
	void CheckValidity() const;

	/// @brief Major radius of ellipse
	double majorRadius = std::numeric_limits<double>::max();

	/// @brief Minor radius of ellipse
	double minorRadius = std::numeric_limits<double>::min();
};
} // namespace AMCAX
