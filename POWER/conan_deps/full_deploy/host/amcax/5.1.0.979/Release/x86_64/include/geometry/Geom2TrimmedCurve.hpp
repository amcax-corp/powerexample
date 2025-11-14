/// @file      Geom2TrimmedCurve.hpp
/// @brief     Class of 2D trimmed curve
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <geometry/Geom2BoundedCurve.hpp>

namespace AMCAX
{
/// @brief Class of 2D trimmed curve
class AMCAX_CLASS_API Geom2TrimmedCurve : public Geom2BoundedCurve
{
public:
	/// @brief Default constructor
	/// @details A default curve is a line segment from the origin towards x-axis with length 1.
	AMCAX_API Geom2TrimmedCurve();

	/// @brief Construct from a curve with bounds
	/// @param c The basis curve
	/// @param u1 The lower bound of the parameter
	/// @param u2 The upper bound of the parameter
	/// @param sense Whether the orientation is the same with the basis curve
	/// @param adjustPeriodic Whether adjust the bounds into a period
	AMCAX_API Geom2TrimmedCurve(const std::shared_ptr<Geom2Curve>& c, double u1, double u2, bool sense = true, bool adjustPeriodic = true);

	AMCAX_API void Reverse() override;
	AMCAX_API double ReversedParameter(double u) const noexcept override;

	/// @brief Reset new parameter bounds for the basis curve
	/// @param u1 The new lower bound of the parameter
	/// @param u2 The new upper bound of the parameter
	/// @param sense Whether the orientation is the same with the basis curve
	/// @param adjustPeriodic Whether adjust the bounds into a period
	AMCAX_API void SetTrim(double u1, double u2, bool sense = true, bool adjustPeriodic = true);

	/// @brief Get the basis curve
	/// @return The basis curve
	AMCAX_API const std::shared_ptr<Geom2Curve>& BasisCurve() const noexcept;

	/// @brief Get the continuity of the basis curve
	/// @return The continuity of the basis curve
	AMCAX_API ContinuityType Continuity() const noexcept override;

	/// @brief Is the basis curve has an order n of continuity
	/// @param n The order of continuity
	/// @return True if the basis curve has an order n of continuity
	AMCAX_API bool IsCN(int n) const override;

	/// @brief Is the trimmed curve closed
	/// @return True if the start point and the end point coincide
	AMCAX_API bool IsClosed() const override;

	/// @brief Is the trimmed curve periodic
	/// @return Always false
	AMCAX_API bool IsPeriodic() const noexcept override;

	/// @brief Get the period of the basis curve
	/// @return The period of the basis curve
	AMCAX_API double Period() const override;

	AMCAX_API double FirstParameter() const noexcept override;
	AMCAX_API double LastParameter() const noexcept override;
	AMCAX_API Point2 StartPoint() const override;
	AMCAX_API Point2 EndPoint() const override;
	AMCAX_API void D0(double u, Point2& p) const override;
	AMCAX_API void D1(double u, Point2& p, Vector2& v1) const override;
	AMCAX_API void D2(double u, Point2& p, Vector2& v1, Vector2& v2) const override;
	AMCAX_API void D3(double u, Point2& p, Vector2& v1, Vector2& v2, Vector2& v3) const override;
	AMCAX_API Vector2 DN(double u, int n) const override;
	AMCAX_API void Transform(const Transformation2& tr) override;
	AMCAX_API double TransformedParameter(double u, const Transformation2& tr) const noexcept override;
	AMCAX_API double ParametricTransformation(const Transformation2& tr) const noexcept override;
	AMCAX_API std::shared_ptr<Geom2Geometry> Copy() const override;
	AMCAX_API std::ostream& Write(std::ostream& os) const override;
	AMCAX_API std::istream& Read(std::istream& is) override;

	/// @brief Get the type of curve, a trimmed curve
	/// @return Type trimmed curve
	AMCAX_API CurveType Type() const noexcept override;

private:
	/// @brief Basis curve of the trimmed curve
	std::shared_ptr<Geom2Curve> basisCurve;

	/// @brief Start parameter
	double uStart = -std::numeric_limits<double>::max();

	/// @brief End parameter
	double uEnd = std::numeric_limits<double>::max();
};
} // namespace AMCAX
