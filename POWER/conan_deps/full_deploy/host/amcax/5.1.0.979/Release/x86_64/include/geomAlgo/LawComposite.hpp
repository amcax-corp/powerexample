/// @file      LawComposite.hpp
/// @brief     Class of composite law function
/// @copyright Copyright (c) 2024 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <list>

#include <geomAlgo/LawFunction.hpp>

namespace AMCAX
{
/// @brief Class of composite law function
class AMCAX_CLASS_API LawComposite : public LawFunction
{
public:
	/// @brief Default constructor
	LawComposite() noexcept = default;

	/// @brief Constructor
	/// @param fp The first parameter
	/// @param lp The last parameter
	/// @param tol The tolerance
	AMCAX_API LawComposite(double fp, double lp, double tol);

	/// @brief Get the continuity type
	/// @details Not implemented yet
	/// @return The continuity
	[[nodiscard]] AMCAX_API ContinuityType Continuity() const override;

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

	/// @brief Get the function used to compute the value at the given parameter
	/// @param w The given parameter
	/// @return The function
	[[nodiscard]] AMCAX_API std::shared_ptr<LawFunction>& ChangeElementaryLaw(double w);

	/// @brief Get the law functions
	/// @return The law functions
	[[nodiscard]] AMCAX_API std::list<std::shared_ptr<LawFunction>>& ChangeLaws() noexcept;

	/// @brief Get if the function is periodic or not
	/// @return Is the function periodic
	[[nodiscard]] AMCAX_API bool IsPeriodic() const noexcept;

	/// @brief Set the function periodic
	AMCAX_API void SetPeriodic() noexcept;

	/// @brief Turn the law function to a curve
	/// @return The 3d curve
	[[nodiscard]] AMCAX_API std::shared_ptr<Geom3Curve> ToCurve() const override;

private:
	void Prepare(double& W) const;

	mutable double first = -1e100;
	mutable double last = 1e100;
	mutable std::shared_ptr<LawFunction> curfunc;
	std::list<std::shared_ptr<LawFunction>> funclist;
	bool periodic = false;
	double tFirst = -1e100;
	double tLast = 1e100;
	double pTol = 0.0;
};
} // namespace AMCAX
