/// @file      Geom3TrimmedCurve.hpp
/// @brief     Class of 3D trimmed curve
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <geometry/Geom3BoundedCurve.hpp>

namespace AMCAX
{
/// @brief Class of 3D trimmed curve
class AMCAX_CLASS_API Geom3TrimmedCurve : public Geom3BoundedCurve
{
public:
	/// @brief Default constructor
	/// @details A default curve is a line from the origin towards z-axis with length 1
	AMCAX_API Geom3TrimmedCurve();

	/// @brief Construct from a curve with bounds
	/// @param c The basis curve
	/// @param u1 The lower bound of the parameter
	/// @param u2 The upper bound of the parameter
	/// @param sense Whether the orientation is the same with the basis curve
	/// @param adjustPeriodic Whether adjust the bounds into a period
	AMCAX_API Geom3TrimmedCurve(const std::shared_ptr<Geom3Curve>& c, double u1, double u2, bool sense = true, bool adjustPeriodic = true);

	AMCAX_API void Reverse() override;
	[[nodiscard]] AMCAX_API double ReversedParameter(double u) const noexcept override;

	/// @brief Reset new parameter bounds for the basis curve
	/// @param u1 The new lower bound of the parameter
	/// @param u2 The new upper bound of the parameter
	/// @param sense Whether the orientation is the same with the basis curve
	/// @param adjustPeriodic Whether adjust the bounds into a period
	AMCAX_API void SetTrim(double u1, double u2, bool sense = true, bool adjustPeriodic = true);

	/// @brief Get the basis curve
	/// @return The basis curve
	[[nodiscard]] AMCAX_API const std::shared_ptr<Geom3Curve>& BasisCurve() const noexcept;

	/// @brief Get the continuity of the trimmed curve
	/// @return The continuity of the basis curve
	[[nodiscard]] AMCAX_API ContinuityType Continuity() const noexcept override;

	/// @brief Is the trimmed curve has an order n of continuity
	/// @param n The order of continuity
	/// @return True if the basis curve has an order n of continuity
	[[nodiscard]] AMCAX_API bool IsCN(int n) const override;

	/// @brief Is the trimmed curve closed
	/// @return True if the start point and the end point coincide
	[[nodiscard]] AMCAX_API bool IsClosed() const override;

	/// @brief Is the trimmed curve periodic
	/// @return Always false
	[[nodiscard]] AMCAX_API bool IsPeriodic() const noexcept override;

	/// @brief Get the period of the basis curve
	/// @return The period of the basis curve
	[[nodiscard]] AMCAX_API double Period() const override;

	[[nodiscard]] AMCAX_API double FirstParameter() const noexcept override;
	[[nodiscard]] AMCAX_API double LastParameter() const noexcept override;
	[[nodiscard]] AMCAX_API Point3 StartPoint() const override;
	[[nodiscard]] AMCAX_API Point3 EndPoint() const override;
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

	/// @brief Get the type of curve, a trimmed curve
	/// @return Type trimmed curve
	[[nodiscard]] AMCAX_API CurveType Type() const noexcept override;

private:
	/// @brief Basis curve of the trimmed curve
	std::shared_ptr<Geom3Curve> basisCurve;

	/// @brief Start parameter
	double uStart = -std::numeric_limits<double>::max();

	/// @brief End parameter
	double uEnd = std::numeric_limits<double>::max();
};
} // namespace AMCAX
