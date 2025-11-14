/// @file      Geom3Circle.hpp
/// @brief     Class of 3D circle
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <geometry/Geom3Conic.hpp>
#include <math/CircleT.hpp>

namespace AMCAX
{
/// @brief Class of 3D circle
class AMCAX_CLASS_API Geom3Circle : public Geom3Conic
{
public:
	/// @brief Default constructor
	constexpr Geom3Circle() noexcept = default;

	/// @brief Construct from a circle
	/// @param c The circle
	AMCAX_API explicit Geom3Circle(const Circle3& c) noexcept;

	/// @brief Construct from a local frame and a radius
	/// @param frame The local frame
	/// @param r The radius
	AMCAX_API Geom3Circle(const Frame3& frame, double r);

	/// @brief Set the circle
	/// @param c The circle
	AMCAX_API void SetCircle(const Circle3& c) noexcept;

	/// @brief Set the radius
	/// @param r The radius
	AMCAX_API void SetRadius(double r);

	/// @brief Get the circle
	/// @return The circle
	[[nodiscard]] AMCAX_API Circle3 Circle() const noexcept;

	/// @brief Get the radius
	/// @return The radius
	[[nodiscard]] AMCAX_API double Radius() const noexcept;

	[[nodiscard]] AMCAX_API double ReversedParameter(double u) const noexcept override;

	/// @brief Get the eccentricity
	/// @details For a circle, the eccentricity is 0
	/// @return The eccentricity
	[[nodiscard]] AMCAX_API double Eccentricity() const noexcept override;

	/// @brief Get the first parameter
	/// @details For a circle, the first parameter is 0
	/// @return The first parameter
	[[nodiscard]] AMCAX_API double FirstParameter() const noexcept override;

	/// @brief Get the last parameter
	/// @details For a circle, the last parameter is 2pi
	/// @return The last parameter
	[[nodiscard]] AMCAX_API double LastParameter() const noexcept override;

	/// @brief Is the circle closed
	/// @return Always true
	[[nodiscard]] AMCAX_API bool IsClosed() const noexcept override;

	/// @brief Is the circle periodic
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

	/// @brief Get the type of curve, a circle
	/// @return Type circle
	[[nodiscard]] AMCAX_API CurveType Type() const noexcept override;

private:
	void CheckValidity() const;

	/// @brief Radius of circle
	double radius = std::numeric_limits<double>::max();
};
} // namespace AMCAX
