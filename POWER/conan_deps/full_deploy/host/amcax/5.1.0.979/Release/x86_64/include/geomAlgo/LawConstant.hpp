/// @file      LawConstant.hpp
/// @brief     Class of constant law function
/// @copyright Copyright (c) 2024 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <geomAlgo/LawFunction.hpp>

namespace AMCAX
{
/// @brief Class of constant law function
class AMCAX_CLASS_API LawConstant : public LawFunction
{
public:
	/// @brief Set the parameters
	/// @param r The radius
	/// @param pf The first parameter
	/// @param pl The last parameter
	AMCAX_API void Set(double r, double pf, double pl);

	/// @brief Get the continuity, always CN
	/// @return The continuity
	[[nodiscard]] AMCAX_API ContinuityType Continuity() const noexcept override;

	/// @brief Get the numer of intervals, always 1
	/// @param s The given continuity
	/// @return The number of intervals
	[[nodiscard]] AMCAX_API int NIntervals(ContinuityType s) const noexcept override;

	/// @brief Get the bounding parameters of the intervals of the given continuity, always the first parameter and the last parameter
	/// @param[out] t The array to store the parameters
	/// @param[in] s The given continuity
	AMCAX_API void Intervals(std::vector<double>& t, ContinuityType s) const noexcept override;

	/// @brief Get the function value at the given parameter, always return radius
	/// @param x The given parameter
	/// @return The function value
	[[nodiscard]] AMCAX_API double Value(double x) const noexcept override;

	/// @brief Get the function value and the first derivative at the given parameter, always 0.0
	/// @param[in] x The given parameter
	/// @param[out] f The function value
	/// @param[out] d The function first derivative
	AMCAX_API void D1(double x, double& f, double& d) const noexcept override;

	/// @brief Get the function value and the first and second derivative at the given parameter, always 0.0
	/// @param[in] x The given parameter
	/// @param[out] f The function value
	/// @param[out] d The function first derivative
	/// @param[out] d2 The function second derivative
	AMCAX_API void D2(double x, double& f, double& d, double& d2) const noexcept override;

	/// @brief Get the trimmed law function
	/// @param fp The first parameter
	/// @param lp The second parameter
	/// @param tol The given tolerance, not all laws use this parameter
	/// @return The new law function
	[[nodiscard]] AMCAX_API std::shared_ptr<LawFunction> Trim(double fp, double lp, double tol) const override;

	/// @brief Get the parametric bounds
	/// @param fp The first parameter
	/// @param lp The second parameter
	AMCAX_API void Bounds(double& fp, double& lp) const noexcept override;

	/// @brief Turn the law function to a curve
	/// @return The 3d curve
	[[nodiscard]] AMCAX_API std::shared_ptr<Geom3Curve> ToCurve() const override;

private:
	double radius = 0.0;
	double first = 0.0;
	double last = 0.0;
};
} // namespace AMCAX
