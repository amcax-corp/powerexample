/// @file      Geom2Parabola.hpp
/// @brief     Class of 2D parabola
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <geometry/Geom2Conic.hpp>
#include <math/ParabolaT.hpp>

namespace AMCAX
{
/// @brief Class of 2D parabola
class AMCAX_CLASS_API Geom2Parabola : public Geom2Conic
{
public:
	/// @brief Default constructor
	constexpr Geom2Parabola() noexcept = default;

	/// @brief Construct from a parabola
	/// @param p The parabola
	AMCAX_API explicit Geom2Parabola(const Parabola2& p) noexcept;

	/// @brief Construct from an axis and a focal length
	/// @param axis The axis
	/// @param focal The focal length
	/// @param isRight Is the local frame right-handed
	AMCAX_API Geom2Parabola(const Axis2& axis, double focal, bool isRight = true);

	/// @brief Construct from a local frame and a focal length
	/// @param frame The local frame
	/// @param focal The focal length
	AMCAX_API Geom2Parabola(const Frame2& frame, double focal);

	/// @brief Construct from a directrix and a focus
	/// @param directrix The directrix
	/// @param focus The focus
	/// @param isRight Is the local frame right-handed
	AMCAX_API Geom2Parabola(const Axis2& directrix, const Point2& focus, bool isRight = true);

	/// @brief Set the focal length
	/// @param focal The focal length
	AMCAX_API void SetFocal(double focal);

	/// @brief Set the parabola
	/// @param p The parabola
	AMCAX_API void SetParabola(const Parabola2& p) noexcept;

	/// @brief Get the parabola
	/// @return The parabola
	[[nodiscard]] AMCAX_API Parabola2 Parabola() const noexcept;

	[[nodiscard]] AMCAX_API double ReversedParameter(double u) const noexcept override;

	/// @brief Get the first parameter
	/// @details For a parabola, the first parameter is negative infinity
	/// @return The first parameter
	[[nodiscard]] AMCAX_API double FirstParameter() const noexcept override;

	/// @brief Get the last parameter
	/// @details For a parabola, the last parameter is positive infinity
	/// @return The last parameter
	[[nodiscard]] AMCAX_API double LastParameter() const noexcept override;

	/// @brief Is the parabola closed
	/// @return Always false
	[[nodiscard]] AMCAX_API bool IsClosed() const noexcept override;

	/// @brief Is the parabola periodic
	/// @return Always false
	[[nodiscard]] AMCAX_API bool IsPeriodic() const noexcept override;

	/// @brief Get the directrix
	/// @return The directrix
	[[nodiscard]] AMCAX_API Axis2 Directrix() const noexcept;

	/// @brief Get the eccentricity of the parabola
	/// @details For a parabola, the eccentricity is 1
	/// @return The eccentricity
	[[nodiscard]] AMCAX_API double Eccentricity() const noexcept override;

	/// @brief Get the focus point
	/// @return The focus point
	[[nodiscard]] AMCAX_API Point2 Focus() const noexcept;

	/// @brief Get the focal length
	/// @return The focal length
	[[nodiscard]] AMCAX_API double Focal() const noexcept;

	/// @brief Get the focal parameter of the parabola
	/// @details The focal parameter of parabola is the distance from the focus to the directrix.
	///          Focal parameter = 2 * focalLength.
	/// @return The focal parameter
	[[nodiscard]] AMCAX_API double FocalParameter() const noexcept;

	/// @brief Get the semilatus rectum of the parabola
	/// @details The semilatus rectum of parabola is half of the length of the chord through a focus parallel to the directrix.
	///          Semilatus rectum = 2 * focalLength
	/// @return The semilatus rectum
	[[nodiscard]] AMCAX_API double SemilatusRectum() const noexcept;

	AMCAX_API void D0(double u, Point2& p) const noexcept override;
	AMCAX_API void D1(double u, Point2& p, Vector2& v1) const noexcept override;
	AMCAX_API void D2(double u, Point2& p, Vector2& v1, Vector2& v2) const noexcept override;
	AMCAX_API void D3(double u, Point2& p, Vector2& v1, Vector2& v2, Vector2& v3) const noexcept override;
	[[nodiscard]] AMCAX_API Vector2 DN(double u, int n) const override;
	AMCAX_API void Transform(const Transformation2& tr) noexcept override;
	[[nodiscard]] AMCAX_API double TransformedParameter(double u, const Transformation2& tr) const noexcept override;
	[[nodiscard]] AMCAX_API double ParametricTransformation(const Transformation2& tr) const noexcept override;
	[[nodiscard]] AMCAX_API std::shared_ptr<Geom2Geometry> Copy() const override;
	AMCAX_API std::ostream& Write(std::ostream& os) const override;
	AMCAX_API std::istream& Read(std::istream& is) override;

	/// @brief Get the type of curve, a parabola
	/// @return Type parabola
	[[nodiscard]] AMCAX_API CurveType Type() const noexcept override;

private:
	void CheckValidity() const;

	/// @brief Focal length of parabola
	double focalLength = std::numeric_limits<double>::max();
};
} // namespace AMCAX
