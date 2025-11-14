/// @file      LawBSpline.hpp
/// @brief     Class of B spline law function
/// @details   This class defines the law function for 1D B spline curves.
/// @copyright Copyright (c) 2024 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <memory>
#include <vector>

#include <common/Macros.hpp>
#include <math/GeometryMacros.hpp>

namespace AMCAX
{
/// @brief Class of B spline law function
class LawBSpline
{
public:
	/// @brief Construct a non-rational BSpline function
	/// @param poles The control points
	/// @param knots The knots
	/// @param multiplicities The multiplicities
	/// @param degree The degree
	/// @param periodic Is Periodic
	AMCAX_API LawBSpline(const std::vector<double>& poles, const std::vector<double>& knots, const std::vector<int>& multiplicities, int degree, bool periodic = false);

	/// @brief Construct a rational BSpline function
	/// @param poles The control points
	/// @param weights The weights
	/// @param knots The knots
	/// @param multiplicities The multiplicities
	/// @param degree The degree
	/// @param periodic Is Periodic
	AMCAX_API LawBSpline(const std::vector<double>& poles, const std::vector<double>& weights, const std::vector<double>& knots, const std::vector<int>& multiplicities, int degree, bool periodic = false);

	/// @brief Increase BSpline degree
	/// @param degree The target degree
	AMCAX_API void IncreaseDegree(int degree);

	/// @brief Increase the multiplicity of the given knot ID to the given multiplicity
	/// @param i The given knot ID
	/// @param m The target multiplicity
	AMCAX_API void IncreaseMultiplicity(int i, int m);

	/// @brief Increase the multiplicities of the knots from i1 to i2
	/// @param i1 The start index
	/// @param i2 The end index
	/// @param m The new multiplicity
	AMCAX_API void IncreaseMultiplicity(int i1, int i2, int m);

	/// @brief Increase the multiplicities of the knots from i1 to i2 by a specific number
	/// @param i1 The start index
	/// @param i2 The end index
	/// @param m The incremental number of multiplicity
	AMCAX_API void IncrementMultiplicity(int i1, int i2, int m);

	/// @brief Insert a knot
	/// @param u The knot to be inserted
	/// @param m The multiplicity of the knot to be inserted
	/// @param parametricTolerance The tolerance of parameters
	/// @param add If true, the multiplicity is an incremental value; if false, the multiplicity is a final value
	AMCAX_API void InsertKnot(double u, int m = 1, double parametricTolerance = 0.0, bool add = true);

	/// @brief Insert knots
	/// @param knots The knots to be inserted
	/// @param mults The multiplicites of knots to be inserted
	/// @param parametricTolerance The tolerance of parameters
	/// @param add If true, the multiplicities are incremental values. If false the multiplicities are final values
	AMCAX_API void InsertKnots(const std::vector<double>& knots, const std::vector<int>& mults, double parametricTolerance = 0.0, bool add = false);

	/// @brief Reduce the multiplicity to a given value m. If m = 0, then remove the knot
	/// @param i The index of knot
	/// @param m The target multiplicity
	/// @param tolerance The tolerance between the old and new curves
	/// @return True if the knot removal or multiplicity decrease is succeed
	AMCAX_API bool RemoveKnot(int i, int m, double tolerance);

	/// @brief Reverse the parameter domain
	AMCAX_API void Reverse();

	/// @brief Compute the reversed parameter from a parameter
	/// @param u The parameter
	/// @return The reversed parameter
	[[nodiscard]] AMCAX_API double ReversedParameter(double u) const noexcept;

	/// @brief Segment the B spline function to a given range
	/// @param u1 The first parameter
	/// @param u2 The last parameter
	AMCAX_API void Segment(double u1, double u2);

	/// @brief Set the knot at a given index
	/// @param i The given index
	/// @param k The new knot
	AMCAX_API void SetKnot(int i, double k);

	/// @brief Set the knots
	/// @param k The knots
	AMCAX_API void SetKnots(const std::vector<double>& k);

	/// @brief Set the knot with multiplicity at a given index
	/// @param i The given index
	/// @param k The new knot
	/// @param m The new multiplicity
	AMCAX_API void SetKnot(int i, double k, int m);

	/// @brief Compute the parameter normalized within the first period
	/// @details If the function is not periodic, the parameter will not be modified
	/// @param[in,out] u The parameter to be normalized
	AMCAX_API void PeriodicNormalization(double& u) const noexcept;

	/// @brief Set the BSpline function to be periodic.
	AMCAX_API void SetPeriodic();

	/// @brief Set the knot at a given index to be the start point for a periodic curve
	/// @param i The given index
	AMCAX_API void SetOrigin(int i);

	/// @brief Change the function into a non-periodic function
	AMCAX_API void SetNotPeriodic();

	/// @brief Set the pole at a given index
	/// @param i The given index
	/// @param p The new pole
	AMCAX_API void SetPole(int i, double p);

	/// @brief Set the pole and weight at a given index
	/// @param i The given index
	/// @param p The new pole
	/// @param w The new weight
	AMCAX_API void SetPole(int i, double p, double w);

	/// @brief Set the weight at a given index
	/// @param i The given index
	/// @param w The new weight
	AMCAX_API void SetWeight(int i, double w);

	/// @brief Is the function has an order n of continuity
	/// @param n The order of continuity
	/// @return True if the function has a continuity of order n
	[[nodiscard]] AMCAX_API bool IsCN(int n) const;

	/// @brief Is the B spline function closed
	/// @return True if the B spline function is closed
	[[nodiscard]] AMCAX_API bool IsClosed() const;

	/// @brief Is the B spline function periodic
	/// @return True of the B spline function is periodic
	[[nodiscard]] AMCAX_API bool IsPeriodic() const noexcept;

	/// @brief Is the BSpline function rational
	/// @return True if the BSpline function is rational
	[[nodiscard]] AMCAX_API bool IsRational() const noexcept;

	/// @brief Get the type of continuity of the BSpline function
	/// @return The continuity
	[[nodiscard]] AMCAX_API ContinuityType Continuity() const noexcept;

	/// @brief Get the degree of the BSpline function
	/// @return The degree of the BSpline function
	[[nodiscard]] AMCAX_API int Degree() const noexcept;

	/// @brief Compute the point at a parameter
	/// @param u The parameter
	/// @return The point
	[[nodiscard]] AMCAX_API double Value(double u) const noexcept;

	/// @brief Compute the point at a parameter
	/// @param[in] u The parameter
	/// @param[out] p The point
	AMCAX_API void D0(double u, double& p) const noexcept;

	/// @brief Compute the point and the first derivative at a parameter
	/// @param[in] u The parameter
	/// @param[out] p The point
	/// @param[out] v1 The first derivative
	AMCAX_API void D1(double u, double& p, double& v1) const noexcept;

	/// @brief Compute the point and the first and second derivatives at a parameter
	/// @param[in] u The parameter
	/// @param[out] p The point
	/// @param[out] v1 The first derivative
	/// @param[out] v2 The second derivative
	AMCAX_API void D2(double u, double& p, double& v1, double& v2) const noexcept;

	/// @brief Compute the point and the first, second and third derivatives at a parameter
	/// @param[in] u The parameter
	/// @param[out] p The point
	/// @param[out] v1 The first derivative
	/// @param[out] v2 The second derivative
	/// @param[out] v3 The third derivative
	AMCAX_API void D3(double u, double& p, double& v1, double& v2, double& v3) const noexcept;

	/// @brief Compute the n-th derivative at a point
	/// @param u The parameter
	/// @param n The order of derivative
	/// @return The n-th derivative
	[[nodiscard]] AMCAX_API double DN(double u, int n) const noexcept;

	/// @brief Compute the point in a local interval
	/// @param u The parameter
	/// @param fromK1 The index of the start knot
	/// @param toK2 The index of the end knot
	/// @return The point
	[[nodiscard]] AMCAX_API double LocalValue(double u, int fromK1, int toK2) const;

	/// @brief Compute the point in a local interval
	/// @param[in] u The parameter
	/// @param[in] fromK1 The index of the start knot
	/// @param[in] toK2 The index of the end knot
	/// @param[out] p The point
	AMCAX_API void LocalD0(double u, int fromK1, int toK2, double& p) const;

	/// @brief Compute the point and the first derivative in a local interval
	/// @param[in] u The parameter
	/// @param[in] fromK1 The index of the start knot
	/// @param[in] toK2 The index of the end knot
	/// @param[out] p The point
	/// @param[out] v1 The first derivative
	AMCAX_API void LocalD1(double u, int fromK1, int toK2, double& p, double& v1) const;

	/// @brief Compute the point, the first and second derivatives in a local interval
	/// @param[in] u The parameter
	/// @param[in] fromK1 The index of the start knot
	/// @param[in] toK2 The index of the end knot
	/// @param[out] p The point
	/// @param[out] v1 The first derivative
	/// @param[out] v2 The second derivative
	AMCAX_API void LocalD2(double u, int fromK1, int toK2, double& p, double& v1, double& v2) const;

	/// @brief Compute the point, the first, second and third derivative in a local interval
	/// @param[in] u The parameter
	/// @param[in] fromK1 The index of the start knot
	/// @param[in] toK2 The index of the end knot
	/// @param[out] p The point
	/// @param[out] v1 The first derivative
	/// @param[out] v2 The second derivative
	/// @param[out] v3 The third derivative
	AMCAX_API void LocalD3(double u, int fromK1, int toK2, double& p, double& v1, double& v2, double& v3) const;

	/// @brief Compute the n-th derivative in a local interval
	/// @param u The parameter
	/// @param fromK1 The index of the start knot
	/// @param toK2 The index of the end knot
	/// @param n The order of derivative
	/// @return The n-th derivative
	[[nodiscard]] AMCAX_API double LocalDN(double u, int fromK1, int toK2, int n) const;

	/// @brief Get the end point
	/// @return The end point
	[[nodiscard]] AMCAX_API double EndPoint() const;

	/// @brief Get the index of the first knot
	/// @return The index of the first knot
	[[nodiscard]] AMCAX_API int FirstUKnotIndex() const noexcept;

	/// @brief Get the first parameter
	/// @return The first parameter
	[[nodiscard]] AMCAX_API double FirstParameter() const noexcept;

	/// @brief Get the knot at a given index
	/// @param i The given index
	/// @return The knot at a given index
	[[nodiscard]] AMCAX_API double Knot(int i) const;

	/// @brief Get the knots
	/// @param[out] k The knots
	AMCAX_API void Knots(std::vector<double>& k) const;

	/// @brief Get the flat knot sequence with multiplicity
	/// @param[out] k The flat knot sequence
	AMCAX_API void KnotSequence(std::vector<double>& k) const;

	/// @brief Get the type of the knot distribution
	/// @return The type of the knot distribution
	[[nodiscard]] AMCAX_API BSplineKnotDistribution KnotDistribution() const noexcept;

	/// @brief Get the index of the last knot
	/// @return The index of the last knot
	[[nodiscard]] AMCAX_API int LastUKnotIndex() const noexcept;

	/// @brief Get the last parameter
	/// @return The last parameter
	[[nodiscard]] AMCAX_API double LastParameter() const noexcept;

	/// @brief Locate the parameter
	/// @param[in] u The parameter
	/// @param[in] parametricTolerance The parametric tolerance
	/// @param[out] i1 The start index of knot
	/// @param[out] i2 The end index of knot
	/// @param[in] withKnotRepetition Is the knot with repetition with respect to the multiplicities
	AMCAX_API void LocateU(double u, double parametricTolerance, int& i1, int& i2, bool withKnotRepetition = false) const noexcept;

	/// @brief Get the multiplicity of the knot at a given index
	/// @param i The given index
	/// @return The multiplicity of the knot at a given index
	[[nodiscard]] AMCAX_API int Multiplicity(int i) const;

	/// @brief Get the multiplicities
	/// @param[out] m The multiplicities
	AMCAX_API void Multiplicities(std::vector<int>& m) const;

	/// @brief Get the number of knots
	/// @return The number of knots
	[[nodiscard]] AMCAX_API int NKnots() const noexcept;

	/// @brief Get the number of poles
	/// @return The number of poles
	[[nodiscard]] AMCAX_API int NPoles() const noexcept;

	/// @brief Get the pole of the given index
	/// @param i The given index
	/// @return The pole of the given index
	[[nodiscard]] AMCAX_API double Pole(int i) const;

	/// @brief Get the poles
	/// @param[out] p The poles
	AMCAX_API void Poles(std::vector<double>& p) const;

	/// @brief Get the start point
	/// @return The start point
	[[nodiscard]] AMCAX_API double StartPoint() const;

	/// @brief Get the weight of the given index
	/// @param i The given index
	/// @return The weight of the given index
	[[nodiscard]] AMCAX_API double Weight(int i) const;

	/// @brief Get the weights
	/// @param[out] w The weights
	AMCAX_API void Weights(std::vector<double>& w) const;

	/// @brief Get the maximum degree of a BSpline function
	/// @return The maximum degree of a BSpline function
	[[nodiscard]] AMCAX_API static int MaxDegree() noexcept;

	/// @brief Compute the parametric tolerance from a 3D tolerance
	/// @param[in] tolerance3D The 3D tolerance
	/// @param[out] uTolerance The parametric tolerance
	AMCAX_API void Resolution(double tolerance3D, double& uTolerance) const noexcept;

	/// @brief Get the copied BSpline function
	/// @return The copied BSpline function
	[[nodiscard]] AMCAX_API std::shared_ptr<LawBSpline> Copy() const;

private:
	void UpdateKnots();

	std::vector<double> poles;
	std::vector<double> weights;
	std::vector<double> flatknots;
	std::vector<double> knots;
	std::vector<int> mults;
	int deg;
	BSplineKnotDistribution knotSet;
	ContinuityType smooth;
	bool rational;
	bool periodic;
};
} // namespace AMCAX
