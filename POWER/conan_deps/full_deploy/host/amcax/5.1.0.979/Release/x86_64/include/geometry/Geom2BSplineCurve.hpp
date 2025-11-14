/// @file      Geom2BSplineCurve.hpp
/// @brief     Class of 2D B spline curve
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <vector>

#include <common/Precision.hpp>
#include <geometry/Geom2BoundedCurve.hpp>

namespace AMCAX
{
/// @brief Class of 2D B spline curve
class AMCAX_CLASS_API Geom2BSplineCurve : public Geom2BoundedCurve
{
public:
	/// @brief Default constructor
	/// @details A default curve is a line from the origin towards x-axis with length 1.
	AMCAX_API Geom2BSplineCurve();

	/// @brief Construct a B spline curve from points, knots and multiplicities with a given degree
	/// @param pts The points
	/// @param knots The knots
	/// @param multiplicities The multiplicities
	/// @param degree The degree of curve
	/// @param isPeriodic Set the curve is periodic or not
	AMCAX_API Geom2BSplineCurve(const std::vector<Point2>& pts, const std::vector<double>& knots, const std::vector<int>& multiplicities, int degree, bool isPeriodic = false);

	/// @brief Construct a rational B spline curve from point, weights, knots and multiplicities with a given degree
	/// @param pts The points
	/// @param weights The weights
	/// @param knots The knots
	/// @param multiplicities The multiplicities
	/// @param degree The degree of curve
	/// @param isPeriodic Set the curve is periodic or not
	AMCAX_API Geom2BSplineCurve(const std::vector<Point2>& pts, const std::vector<double>& weights, const std::vector<double>& knots, const std::vector<int>& multiplicities, int degree, bool isPeriodic = false);

	/// @brief Increase the degree of the curve
	/// @param newDegree The new degree
	AMCAX_API void IncreaseDegree(int newDegree);

	/// @brief Increase the multiplicity of the knot at a given index
	/// @param i The index of knot
	/// @param m The new multiplicity
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
	AMCAX_API void InsertKnot(double u, int m = 1, double parametricTolerance = 0.0);

	/// @brief Insert knots
	/// @param newKnots The knots to be inserted
	/// @param newMults The multiplicites of knots to be inserted
	/// @param parametricTolerance The tolerance of parameters
	/// @param add If true, the multiplicities are incremental values. If false the multiplicities are the final values
	AMCAX_API void InsertKnots(const std::vector<double>& newKnots, const std::vector<int>& newMults, double parametricTolerance = 0.0, bool add = false);

	/// @brief Reduce the multiplicity to a given value m. If m = 0, then remove the knot
	/// @param i The index of knot
	/// @param m The target multiplicity
	/// @param tolerance The tolerance between the old and new curves
	/// @return True if the knot removal or multiplicity decrease is succeed
	AMCAX_API bool RemoveKnot(int i, int m, double tolerance);

	AMCAX_API void Reverse() override;
	AMCAX_API double ReversedParameter(double u) const noexcept override;

	/// @brief Segment the B spline curve to a given range
	/// @param u1 The first parameter
	/// @param u2 The last parameter
	/// @param tolerance The parametric tolerance
	AMCAX_API void Segment(double u1, double u2, double tolerance = Precision::PConfusion());

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
	/// @details If the curve is not periodic, the parameter will not be modified
	/// @param[in,out] u The parameter to be normalized
	AMCAX_API void PeriodicNormalization(double& u) const noexcept;

	/// @brief Change the curve into a periodic curve
	AMCAX_API void SetPeriodic();

	/// @brief Set the knot at a given index to be the start point for a periodic curve
	/// @param i The given index
	AMCAX_API void SetOrigin(int i);

	/// @brief Set the knot u to be the start point for a periodic curve
	/// @details If u is not a knot, then insert a knot
	/// @param u The parameter
	/// @param tol Parametric tolerance
	AMCAX_API void SetOrigin(double u, double tol);

	/// @brief Change the curve into a non-periodic curve
	AMCAX_API void SetNotPeriodic();

	/// @brief Set the pole at a given index
	/// @param i The given index
	/// @param p The new pole
	AMCAX_API void SetPole(int i, const Point2& p);

	/// @brief Set the pole and weight at a given index
	/// @param i The given index
	/// @param p The new pole
	/// @param weight The new weight
	AMCAX_API void SetPole(int i, const Point2& p, double weight);

	/// @brief Set the weight at a given index
	/// @param i The given index
	/// @param w The new weight
	AMCAX_API void SetWeight(int i, double w);

	/// @brief Move a point at a given parameter to a new position.
	/// @param[in] u The parameter
	/// @param[in] p The new position
	/// @param[in] i1 The index of the first pole to be moved
	/// @param[in] i2 The index of the last pole to be moved
	/// @param[out] firstModifiedPole The index of the first modified pole
	/// @param[out] lastModifiedPole The index of the last modified pole
	AMCAX_API void MovePoint(double u, const Point2& p, int i1, int i2, int& firstModifiedPole, int& lastModifiedPole);

	AMCAX_API Point2 StartPoint() const override;
	AMCAX_API Point2 EndPoint() const override;
	AMCAX_API double FirstParameter() const noexcept override;
	AMCAX_API double LastParameter() const noexcept override;
	AMCAX_API bool IsClosed() const override;
	AMCAX_API bool IsPeriodic() const noexcept override;
	AMCAX_API ContinuityType Continuity() const noexcept override;
	AMCAX_API bool IsCN(int n) const override;

	/// @brief Check if the curve has G1 continuity in the given interval
	/// @param tf The left parameter of the interval
	/// @param tl The right parameter of the interval
	/// @param angTol The angle tolerance
	/// @return True if the curve has G1 continuity
	AMCAX_API bool IsG1(double tf, double tl, double angTol) const;

	/// @brief Is the B spline curve rational
	/// @return True if the B spline curve is rational
	AMCAX_API bool IsRational() const noexcept;

	/// @brief Get the degree of the B spline curve
	/// @return The degree of the B spline curve
	AMCAX_API int Degree() const noexcept;

	AMCAX_API void D0(double u, Point2& p) const noexcept override;
	AMCAX_API void D1(double u, Point2& p, Vector2& v1) const noexcept override;
	AMCAX_API void D2(double u, Point2& p, Vector2& v1, Vector2& v2) const noexcept override;
	AMCAX_API void D3(double u, Point2& p, Vector2& v1, Vector2& v2, Vector2& v3) const noexcept override;
	AMCAX_API Vector2 DN(double u, int n) const noexcept override;

	/// @brief Compute the point at a given parameter in a local interval
	/// @param u The parameter
	/// @param fromK1 The index of the start knot
	/// @param toK2 The index of the end knot
	/// @return The point
	AMCAX_API Point2 LocalValue(double u, int fromK1, int toK2) const;

	/// @brief Compute the point at a given parameter in a local interval
	/// @param[in] u The parameter
	/// @param[in] fromK1 The index of the start knot
	/// @param[in] toK2 The index of the end knot
	/// @param[out] p The point
	AMCAX_API void LocalD0(double u, int fromK1, int toK2, Point2& p) const;

	/// @brief Compute the point and the first derivative at a given parameter in a local interval
	/// @param[in] u The parameter
	/// @param[in] fromK1 The index of the start knot
	/// @param[in] toK2 The index of the end knot
	/// @param[out] p The point
	/// @param[out] v1 The first derivative
	AMCAX_API void LocalD1(double u, int fromK1, int toK2, Point2& p, Vector2& v1) const;

	/// @brief Compute the point, the first and second derivatives at a given parameter in a local interval
	/// @param[in] u The parameter
	/// @param[in] fromK1 The index of the start knot
	/// @param[in] toK2 The index of the end knot
	/// @param[out] p The point
	/// @param[out] v1 The first derivative
	/// @param[out] v2 The second derivative
	AMCAX_API void LocalD2(double u, int fromK1, int toK2, Point2& p, Vector2& v1, Vector2& v2) const;

	/// @brief Compute the point, the first, second and third derivative at a given parameter in a local interval
	/// @param[in] u The parameter
	/// @param[in] fromK1 The index of the start knot
	/// @param[in] toK2 The index of the end knot
	/// @param[out] p The point
	/// @param[out] v1 The first derivative
	/// @param[out] v2 The second derivative
	/// @param[out] v3 The third derivative
	AMCAX_API void LocalD3(double u, int fromK1, int toK2, Point2& p, Vector2& v1, Vector2& v2, Vector2& v3) const;

	/// @brief Compute the n-th derivative at a given parameter in a local interval
	/// @param u The parameter
	/// @param fromK1 The index of the start knot
	/// @param toK2 The index of the end knot
	/// @param n The order of derivative
	/// @return The n-th derivative
	AMCAX_API Vector2 LocalDN(double u, int fromK1, int toK2, int n) const;

	/// @brief Get the index of the first knot
	/// @return The index of the first knot
	AMCAX_API int FirstUKnotIndex() const noexcept;

	/// @brief Get the index of the last knot
	/// @return The index of the last knot
	AMCAX_API int LastUKnotIndex() const noexcept;

	/// @brief Get the knot at a given index
	/// @param i The given index
	/// @return The knot at a given index
	AMCAX_API double Knot(int i) const;

	/// @brief Get the knots
	/// @return The knots
	AMCAX_API const std::vector<double>& Knots() const noexcept;

	/// @brief Get the flat knot sequence with multiplicity
	/// @return The flat knot sequence
	AMCAX_API const std::vector<double>& KnotSequence() const noexcept;

	/// @brief Get the type of the knot distribution
	/// @return The type of the knot distribution
	AMCAX_API BSplineKnotDistribution KnotDistribution() const noexcept;

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
	AMCAX_API int Multiplicity(int i) const;

	/// @brief Get the multiplicities
	/// @return The multiplicities
	AMCAX_API const std::vector<int>& Multiplicities() const noexcept;

	/// @brief Get the number of knots
	/// @return The number of knots
	AMCAX_API int NKnots() const noexcept;

	/// @brief Get the number of poles
	/// @return The number of poles
	AMCAX_API int NPoles() const noexcept;

	/// @brief Get the pole of the given index
	/// @param i The given index
	/// @return The pole of the given index
	AMCAX_API const Point2& Pole(int i) const;

	/// @brief Get the poles
	/// @return The poles
	AMCAX_API const std::vector<Point2>& Poles() const noexcept;

	/// @brief Get the weight of the given index
	/// @param i The given index
	/// @return The weight of the given index
	AMCAX_API double Weight(int i) const;

	/// @brief Get the weights
	/// @return The weights
	AMCAX_API const std::vector<double>& Weights() const noexcept;

	AMCAX_API void Transform(const Transformation2& tr) noexcept override;

	/// @brief Get the maximum degree of a B spline curve
	/// @return The maximum degree of a B spline curve
	AMCAX_API static int MaxDegree() noexcept;

	/// @brief Compute the parametric tolerance from a 2D tolerance
	/// @param[in] toleranceUV The 2D tolerance
	/// @param[out] uTolerance The parametric tolerance
	AMCAX_API void Resolution(double toleranceUV, double& uTolerance);

	AMCAX_API std::shared_ptr<Geom2Geometry> Copy() const override;
	AMCAX_API std::ostream& Write(std::ostream& os) const override;
	AMCAX_API std::istream& Read(std::istream& is) override;

	/// @brief Get the type of curve, a B spline curve
	/// @return Type B spline curve
	AMCAX_API CurveType Type() const noexcept override;

private:
	void UpdateKnots();
	static void CheckCurveData(const std::vector<Point2>& poles, const std::vector<double>& knots, const std::vector<int>& mults, int degree, bool periodic);
	static bool IsRational(const std::vector<double>& w) noexcept;

	/// @brief Control points
	std::vector<Point2> poles;

	/// @brief Weights for rational curve
	std::vector<double> weights;

	/// @brief Knots with multiplicities
	std::vector<double> flatknots;

	/// @brief Knots
	std::vector<double> knots;

	/// @brief Multiplicities of knots
	std::vector<int> multiplicities;

	/// @brief Inverse of maximal derivative
	double maxderivinv = 0.0;

	/// @brief Degree
	int degree = 0;

	/// @brief Knot distribution type
	BSplineKnotDistribution knotSet = BSplineKnotDistribution::NonUniform;

	/// @brief Overall continuity
	ContinuityType continuity = ContinuityType::C0;

	/// @brief Is the inverse of maximal derivative computed
	bool maxderivinvok = false;

	/// @brief Is periodic
	bool periodic = false;
};
} // namespace AMCAX
