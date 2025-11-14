/// @file      LawBSplineFunction.hpp
/// @brief     Class of B spline law function inherited from LawFunction
/// @copyright Copyright (c) 2024 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <geomAlgo/LawFunction.hpp>

namespace AMCAX
{
class LawBSpline;

/// @brief Class of B spline law function inherited from LawFunction
class AMCAX_CLASS_API LawBSplineFunction : public LawFunction
{
public:
	/// @brief Default constructor
	LawBSplineFunction() noexcept = default;

	/// @brief Constructor
	/// @param c The BSpline function
	/// @param fp The first parameter
	/// @param lp The last parameter
	AMCAX_API LawBSplineFunction(const std::shared_ptr<LawBSpline>& c, double fp, double lp) noexcept;

	/// @brief Set the BSpline function
	/// @param c The BSpline function
	AMCAX_API void SetCurve(const std::shared_ptr<LawBSpline>& c) noexcept;

	/// @brief Get the BSpline function continuity
	/// @return The continuity
	[[nodiscard]] AMCAX_API ContinuityType Continuity() const noexcept override;

	/// @brief Get the number of intervals divided by parameters at which the curve continuity is lower than the given continuity
	/// @param s The given continuity
	/// @return The number of intervals
	[[nodiscard]] AMCAX_API int NIntervals(ContinuityType s) const override;

	/// @brief Get the bounding parameters of the intervals of the given continuity
	/// @param[out] t The array to store the parameters
	/// @param[in] s The given continuity
	AMCAX_API void Intervals(std::vector<double>& t, ContinuityType s) const override;

	/// @brief Get the function value at the given parameter
	/// @param x The given parameter
	/// @return The function value
	[[nodiscard]] AMCAX_API double Value(double x) const override;

	/// @brief Get the function value and the first derivative at the given parameter
	/// @param[in] x The given parameter
	/// @param[out] f The function value
	/// @param[out] d The function first derivative
	AMCAX_API void D1(double x, double& f, double& d) const override;

	/// @brief Get the function value and the first and second derivative at the given parameter
	/// @param[in] x The given parameter
	/// @param[out] f The function value
	/// @param[out] d The function first derivative
	/// @param[out] d2 The function second derivative
	AMCAX_API void D2(double x, double& f, double& d, double& d2) const override;

	/// @brief Get the trimmed law function
	/// @param fp The first parameter
	/// @param lp The second parameter
	/// @param tol The given tolerance, not all laws use this parameter
	/// @return The new law function
	[[nodiscard]] AMCAX_API std::shared_ptr<LawFunction> Trim(double fp, double lp, double tol) const override;

	/// @brief Get the parametric bounds
	/// @param[out] fp The first parameter
	/// @param[out] lp The second parameter
	AMCAX_API void Bounds(double& fp, double& lp) const noexcept override;

	/// @brief Get the BSpline curve
	/// @return The BSpline curve
	[[nodiscard]] AMCAX_API std::shared_ptr<LawBSpline> Curve() const noexcept;

	/// @brief Turn the law function to a curve
	/// @return The 3d curve
	[[nodiscard]] AMCAX_API std::shared_ptr<Geom3Curve> ToCurve() const override;

private:
	std::shared_ptr<LawBSpline> curve;
	double first = 0.0;
	double last = 0.0;
};
} // namespace AMCAX
