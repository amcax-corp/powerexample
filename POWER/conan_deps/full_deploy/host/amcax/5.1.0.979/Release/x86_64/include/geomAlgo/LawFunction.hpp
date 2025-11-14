/// @file      LawFunction.hpp
/// @brief     Base class of law function
/// @copyright Copyright (c) 2024 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <memory>
#include <vector>

#include <common/Macros.hpp>
#include <math/GeometryMacros.hpp>

namespace AMCAX
{
class Geom3Curve;

/// @brief Base class for 1D law functions
class AMCAX_CLASS_API LawFunction
{
public:
	/// @brief Default constructor
	LawFunction() noexcept = default;

	/// @brief Copy constructor
	LawFunction(const LawFunction&) noexcept = default;

	/// @brief Move constructor
	LawFunction(LawFunction&&) noexcept = default;

	/// @brief Destructor
	virtual ~LawFunction() noexcept = default;

	/// @brief Copy assignment operator
	/// @return The reference to self
	LawFunction& operator=(const LawFunction&) noexcept = default;

	/// @brief Move assignment operator
	/// @return The reference to self
	LawFunction& operator=(LawFunction&&) noexcept = default;

	/// @brief Continuity
	[[nodiscard]] AMCAX_API virtual ContinuityType Continuity() const = 0;

	/// @brief Get the number of intervals divided by parameters at which the curve continuity is lower than the given continuity
	/// @param s The given continuity
	/// @return The number of intervals
	[[nodiscard]] AMCAX_API virtual int NIntervals(ContinuityType s) const = 0;

	/// @brief Get the bounding parameters of the intervals of the given continuity
	/// @param[out] t The array to store the parameters
	/// @param[in] s The given continuity
	AMCAX_API virtual void Intervals(std::vector<double>& t, ContinuityType s) const = 0;

	/// @brief Get the function value at the given parameter
	/// @param x The given parameter
	/// @return The function value
	[[nodiscard]] AMCAX_API virtual double Value(double x) const = 0;

	/// @brief Get the function value and the first derivative at the given parameter
	/// @param[in] x The given parameter
	/// @param[out] f The function value
	/// @param[out] d The function first derivative
	AMCAX_API virtual void D1(double x, double& f, double& d) const = 0;

	/// @brief Get the function value and the first and second derivative at the given parameter
	/// @param[in] x The given parameter
	/// @param[out] f The function value
	/// @param[out] d The function first derivative
	/// @param[out] d2 The function second derivative
	AMCAX_API virtual void D2(double x, double& f, double& d, double& d2) const = 0;

	/// @brief Get the trimmed law function
	/// @param fp The first parameter
	/// @param lp The second parameter
	/// @param tol The given tolerance, not all laws use this parameter
	/// @return The new law function
	[[nodiscard]] AMCAX_API virtual std::shared_ptr<LawFunction> Trim(double fp, double lp, double tol) const = 0;

	/// @brief Get the parametric bounds
	/// @param[out] fp The first parameter
	/// @param[out] lp The second parameter
	AMCAX_API virtual void Bounds(double& fp, double& lp) const = 0;

	/// @brief Turn the law function to a curve
	/// @return The 3d curve
	[[nodiscard]] AMCAX_API virtual std::shared_ptr<Geom3Curve> ToCurve() const = 0;
};
} // namespace AMCAX
