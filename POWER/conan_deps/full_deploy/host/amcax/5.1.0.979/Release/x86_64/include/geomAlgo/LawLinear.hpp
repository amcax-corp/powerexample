/// @file      LawLinear.hpp
/// @brief     The class of linear law function
/// @details   This class defines the linear law function
/// @copyright Copyright (c) 2024 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <geomAlgo/LawFunction.hpp>

namespace AMCAX
{
/// @brief The linear function
class AMCAX_CLASS_API LawLinear : public LawFunction
{
public:
	/// @brief Set the two points to define the linear function
	/// @param paraFirst The parameter of the first point
	/// @param valueFirst The value of the first point
	/// @param paraLast The parameter of the second point
	/// @param valueLast The value of the second point
	AMCAX_API void Set(double paraFirst, double valueFirst, double paraLast, double valueLast);

	/// @brief Get the function continuity, always CN
	/// @return The continuity
	[[nodiscard]] AMCAX_API ContinuityType Continuity() const noexcept override;

	/// @brief Get the number of intervals divided by parameters at which the curve continuity is lower than the given continuity, always 1
	/// @param s The given continuity
	/// @return The number of intervals
	[[nodiscard]] AMCAX_API int NIntervals(ContinuityType s) const noexcept override;

	/// @brief Get the bounding parameters of the intervals of the given continuity, always the first parameter and the last parameter
	/// @param[out] t The array to store the parameters
	/// @param[in] s The given continuity
	AMCAX_API void Intervals(std::vector<double>& t, ContinuityType s) const noexcept override;

	/// @brief Get the function value at the given parameter
	/// @param x The given parameter
	/// @return The function value
	[[nodiscard]] AMCAX_API double Value(double x) const noexcept override;

	/// @brief Get the function value and the first derivative at the given parameter
	/// @param[in] x The given parameter
	/// @param[out] f The function value
	/// @param[out] d The function first derivative
	AMCAX_API void D1(double x, double& f, double& d) const noexcept override;

	/// @brief Get the function value and the first, second derivative at the given parameter
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
	/// @param[out] fp The first parameter
	/// @param[out] lp The second parameter
	AMCAX_API void Bounds(double& fp, double& lp) const noexcept override;

	/// @brief Turn the law function to a curve
	/// @return The 3d curve
	[[nodiscard]] AMCAX_API std::shared_ptr<Geom3Curve> ToCurve() const override;

private:
	double valueFirst = 0.0;
	double valueLast = 0.0;
	double paraFirst = 0.0;
	double paraLast = 0.0;
};
} // namespace AMCAX
