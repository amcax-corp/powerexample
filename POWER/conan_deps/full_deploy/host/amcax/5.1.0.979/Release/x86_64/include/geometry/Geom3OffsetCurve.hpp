/// @file      Geom3OffsetCurve.hpp
/// @brief     Class of 3D offset curve
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <geometry/Geom3Curve.hpp>

namespace AMCAX
{
#ifndef DOXYGEN_SKIP
class Geom3EvaluatorOffsetCurve;
#endif

/// @brief Class of 3D offset curve
/// @details The offset direction is a reference direction.
///          The point on the offset curve is obtained by translating the point on the basis curve
///          along the direction perpendicular to the reference direction and the tangent direction.
///          If the reference direction is parallel to the tangent direction, the point is undefined
///          and an exception will be thrown when computing the value at this point.
class AMCAX_CLASS_API Geom3OffsetCurve : public Geom3Curve
{
public:
	/// @brief Default constructor
	/// @details A default curve is a line along z-axis
	AMCAX_API Geom3OffsetCurve();

	/// @brief Construct from a curve, an offset value and an offset direction
	/// @param c The basis curve
	/// @param offset The offset value
	/// @param d The offset direction
	/// @param isNotCheckC0 Is the checking of C0 continuity not performed
	AMCAX_API Geom3OffsetCurve(const std::shared_ptr<Geom3Curve>& c, double offset, const Direction3& d, bool isNotCheckC0 = false);

	AMCAX_API void Reverse() override;
	[[nodiscard]] AMCAX_API double ReversedParameter(double u) const noexcept override;

	/// @brief Set the basis curve
	/// @param c The basis curve
	/// @param isNotCheckC0 Is the checking of C0 continuity not performed
	AMCAX_API void SetBasisCurve(const std::shared_ptr<Geom3Curve>& c, bool isNotCheckC0 = false);

	/// @brief Set the offset direction
	/// @param d The offset direction
	AMCAX_API void SetDirection(const Direction3& d) noexcept;

	/// @brief Set the offset value
	/// @param offset The offset value
	AMCAX_API void SetOffsetValue(double offset) noexcept;

	/// @brief Get the basis curve
	/// @return The basis curve
	[[nodiscard]] AMCAX_API const std::shared_ptr<Geom3Curve>& BasisCurve() const noexcept;

	/// @brief Get the first parameter
	/// @details The first parameter is the same as the first parameter of the basis curve
	/// @return The first parameter
	[[nodiscard]] AMCAX_API double FirstParameter() const noexcept override;

	/// @brief Get the last parameter
	/// @details The last parameter is the same as the last parameter of the basis curve
	/// @return The last parameter
	[[nodiscard]] AMCAX_API double LastParameter() const noexcept override;

	/// @brief Get the offset value
	/// @return The offset value
	[[nodiscard]] AMCAX_API double Offset() const noexcept;

	/// @brief Get the continuity of the basis curve
	/// @return The continuity of the basis curve
	[[nodiscard]] AMCAX_API ContinuityType BasisCurveContinuity() const noexcept;

	/// @brief Is the offset curve closed
	/// @return True if the curve is closed
	[[nodiscard]] AMCAX_API bool IsClosed() const override;

	/// @brief Is the offset curve periodic
	/// @return True if the basis curve is periodic
	[[nodiscard]] AMCAX_API bool IsPeriodic() const noexcept override;

	/// @brief Get the period
	/// @return The period
	[[nodiscard]] AMCAX_API double Period() const override;

	/// @brief Get the continuity of the offset curve
	/// @details The continuity of the offset curve is not higher than the basis curve
	/// @return The continuity of the offset curve
	[[nodiscard]] AMCAX_API ContinuityType Continuity() const noexcept override;

	/// @brief Is the offset curve has an order n of continuity
	/// @param n The order of continuity
	/// @return True if the basis curve has an order of n + 1 continuity
	[[nodiscard]] AMCAX_API bool IsCN(int n) const override;

	/// @brief Get the offset direction
	/// @return The offset direction
	[[nodiscard]] AMCAX_API const Direction3& Direction() const noexcept;

	AMCAX_API void D0(double u, Point3& p) const override;
	AMCAX_API void D1(double u, Point3& p, Vector3& v1) const override;
	AMCAX_API void D2(double u, Point3& p, Vector3& v1, Vector3& v2) const override;
	AMCAX_API void D3(double u, Point3& p, Vector3& v1, Vector3& v2, Vector3& v3) const override;
	[[nodiscard]] AMCAX_API Vector3 DN(double u, int n) const override;
	AMCAX_API void Transform(const Transformation3& tr) override;
	[[nodiscard]] AMCAX_API double TransformedParameter(double u, const Transformation3& tr) const noexcept override;
	[[nodiscard]] AMCAX_API double ParametricTransformation(const Transformation3& tr) const noexcept override;
	[[nodiscard]] AMCAX_API std::shared_ptr<Geom3Geometry> Copy() const override;
	AMCAX_API std::ostream& Write(std::ostream& os) const override;
	AMCAX_API std::istream& Read(std::istream& is) override;

	/// @brief Get the type of curve, an offset curve
	/// @return Type offset curve
	[[nodiscard]] AMCAX_API CurveType Type() const noexcept override;

private:
	/// @brief Basis curve
	std::shared_ptr<Geom3Curve> basisCurve;

	/// @brief Offset direction
	Direction3 direction;

	/// @brief Value of offset
	double offsetValue = 0.0;

	/// @brief Continuity of basis curve
	ContinuityType basisCurveContinuity = ContinuityType::C0;

	/// @brief Evaluator for offset curve
	std::shared_ptr<Geom3EvaluatorOffsetCurve> evaluator;
};
} // namespace AMCAX
