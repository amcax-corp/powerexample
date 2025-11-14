/// @file      Geom3BSplineSurface.hpp
/// @brief     Class of 3D B spline surface
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <common/Array2.hpp>
#include <geometry/Geom3BoundedSurface.hpp>

namespace AMCAX
{
/// @brief Class of 3D B spline surface
class AMCAX_CLASS_API Geom3BSplineSurface : public Geom3BoundedSurface
{
public:
	/// @brief Default constructor
	/// @details A default surface is a unit square
	AMCAX_API Geom3BSplineSurface();

	/// @brief Construct a B spline surface from poles, knots and multiplicities
	/// @param pts The poles
	/// @param uKnots The u knots
	/// @param vKnots The v knots
	/// @param uMults The u multiplicities
	/// @param vMults The v multiplicities
	/// @param uDegree The u degree
	/// @param vDegree The v degree
	/// @param uPeriodic Set whether the surface is periodic along the u direction
	/// @param vPeriodic Set whether the surface is periodic along the v direction
	AMCAX_API Geom3BSplineSurface(const Array2<Point3>& pts, const std::vector<double>& uKnots, const std::vector<double>& vKnots, const std::vector<int>& uMults, const std::vector<int>& vMults, int uDegree, int vDegree, bool uPeriodic = false, bool vPeriodic = false);

	/// @brief Construct a rational B spline surface from poles, knots and multiplicities
	/// @param pts The poles
	/// @param weights The weights
	/// @param uKnots The u knots
	/// @param vKnots The v knots
	/// @param uMults The u multiplicities
	/// @param vMults The v multiplicities
	/// @param uDegree The u degree
	/// @param vDegree The v degree
	/// @param uPeriodic Set whether the surface is periodic along the u direction
	/// @param vPeriodic Set whether the surface is periodic along the v direction
	AMCAX_API Geom3BSplineSurface(const Array2<Point3>& pts, const Array2<double>& weights, const std::vector<double>& uKnots, const std::vector<double>& vKnots, const std::vector<int>& uMults, const std::vector<int>& vMults, int uDegree, int vDegree, bool uPeriodic = false, bool vPeriodic = false);

	/// @brief Exchange the uv directions
	AMCAX_API void ExchangeUV();

	/// @brief Change the surface into a periodic surface along the u direction
	AMCAX_API void SetUPeriodic();

	/// @brief Change the surface into a periodic surface along the v direction
	AMCAX_API void SetVPeriodic();

	/// @brief Compute the parameter normalized within the first period
	/// @param[in,out] u The u parameter to be normalized
	/// @param[in,out] v The v parameter to be normalized
	AMCAX_API void PeriodicNormalization(double& u, double& v) const;

	/// @brief Set the u knot at a given index to be the start point for a periodic surface
	/// @param i The given index
	AMCAX_API void SetUOrigin(int i);

	/// @brief Set the knot u to be the start parameter for a u-periodic surface
	/// @param u The given start parameter
	/// @param tol Parametric tolerance
	AMCAX_API void SetUOrigin(double u, double tol);

	/// @brief Set the v knot at a given index to be the start point for a periodic surface
	/// @param j The given index
	AMCAX_API void SetVOrigin(int j);

	/// @brief Set the knot v to be the start parameter for a v-periodic surface
	/// @param v The given start parameter
	/// @param tol Parametric tolerance
	AMCAX_API void SetVOrigin(double v, double tol);

	/// @brief Change the surface into a non-periodic surface along the u direction
	AMCAX_API void SetUNotPeriodic();

	/// @brief Change the surface into a non-periodic surface along the v direction
	AMCAX_API void SetVNotPeriodic();

	AMCAX_API void UReverse() override;
	AMCAX_API void VReverse() override;
	AMCAX_API double UReversedParameter(double u) const noexcept override;
	AMCAX_API double VReversedParameter(double v) const noexcept override;

	/// @brief Increase the degrees of the B spline surface
	/// @param newUDegree The new u degree
	/// @param newVDegree The new v degree
	AMCAX_API void IncreaseDegree(int newUDegree, int newVDegree);

	/// @brief Insert u knots
	/// @param knots The new knots
	/// @param mults The new multiplicities of the knots
	/// @param parametricTolerance The tolerance of parameters
	/// @param add If true, the multiplicities are incremental values. If false, the multiplicities are final calues
	AMCAX_API void InsertUKnots(const std::vector<double>& knots, const std::vector<int>& mults, double parametricTolerance = 0.0, bool add = true);

	/// @brief Insert v knots
	/// @param knots The new knots
	/// @param mults The new multiplicities of the knots
	/// @param parametricTolerance The tolerance of parameters
	/// @param add If true, the multiplicities are incremental values. If false, the multiplicities are final calues
	AMCAX_API void InsertVKnots(const std::vector<double>& knots, const std::vector<int>& mults, double parametricTolerance = 0.0, bool add = true);

	/// @brief Reduce the u multiplicity to a given value m. If m = 0, then remove the knot
	/// @param index The index of u knot
	/// @param m The target multiplicity
	/// @param tolerance The tolerance between the old and new surfaces
	/// @return True if the knot removal or multiplicity decrease is succeed.
	AMCAX_API bool RemoveUKnot(int index, int m, double tolerance);

	/// @brief Reduce the v multiplicity to a given value m. If m = 0, then remove the knot
	/// @param index The index of v knot
	/// @param m The target multiplicity
	/// @param tolerance The tolerance between the old and new surfaces
	/// @return True if the knot removal or multiplicity decrease is succeed.
	AMCAX_API bool RemoveVKnot(int index, int m, double tolerance);

	/// @brief Increase the u multiplicity of the u knot at a given index
	/// @param i The index of the u knot
	/// @param m The target multiplicity
	AMCAX_API void IncreaseUMultiplicity(int i, int m);

	/// @brief Increase the u multiplicities of the u knots from i1 to i2
	/// @param i1 The start index of the u knot
	/// @param i2 The end index of the u knot
	/// @param m The target multiplicity
	AMCAX_API void IncreaseUMultiplicity(int i1, int i2, int m);

	/// @brief Increase the u multiplicities of the u knots from i1 to i2 by a specific number
	/// @param i1 The start index of the u knot
	/// @param i2 The end index of the u knot
	/// @param step The incremental number of multiplicity
	AMCAX_API void IncrementUMultiplicity(int i1, int i2, int step);

	/// @brief Increase the v multiplicity of the v knot at a given index
	/// @param j The index of the v knot
	/// @param m The target multiplicity
	AMCAX_API void IncreaseVMultiplicity(int j, int m);

	/// @brief Increase the v multiplicities of the v knots from i1 to i2
	/// @param i1 The start index of the v knot
	/// @param i2 The end index of the v knot
	/// @param m The target multiplicity
	AMCAX_API void IncreaseVMultiplicity(int i1, int i2, int m);

	/// @brief Increase the v multiplicities of the v knots from i1 to i2 by a specific number
	/// @param i1 The start index of the v knot
	/// @param i2 The end index of the v knot
	/// @param step The incremental number of multiplicity
	AMCAX_API void IncrementVMultiplicity(int i1, int i2, int step);

	/// @brief Insert a u knot
	/// @param u The knot to be inserted
	/// @param m The multiplicity of the knot to be inserted
	/// @param parametricTolerance The tolerance of parameters
	/// @param add If true, the multiplicity is an incremental value; if false, the multiplicity is a final value
	AMCAX_API void InsertUKnot(double u, int m, double parametricTolerance, bool add = true);

	/// @brief Insert a v knot
	/// @param v The knot to be inserted
	/// @param m The multiplicity of the knot to be inserted
	/// @param parametricTolerance The tolerance of parameters
	/// @param add If true, the multiplicity is an incremental value; if false, the multiplicity is a final value
	AMCAX_API void InsertVKnot(double v, int m, double parametricTolerance, bool add = true);

	/// @brief Segment the B spline surface by given bounds
	/// @param u1 The lower bound of u direction
	/// @param u2 The upper bound of u direction
	/// @param v1 The lower bound of v direction
	/// @param v2 The upper bound of v direction
	/// @param uTolerance The tolerance along the u direction
	/// @param vTolerance The tolerance along the v direction
	AMCAX_API void Segment(double u1, double u2, double v1, double v2, double uTolerance = Precision::PConfusion(), double vTolerance = Precision::PConfusion());

	/// @brief Segment the B spline surface by given bounds, with check on the changes of bound.
	/// @details If the bounds are not changed, the periodicity will not be changed.
	/// @param u1 The lower bound of u direction
	/// @param u2 The upper bound of u direction
	/// @param v1 The lower bound of v direction
	/// @param v2 The upper bound of v direction
	/// @param uTolerance The tolerance along the u direction
	/// @param vTolerance The tolerance along the v direction
	AMCAX_API void CheckAndSegment(double u1, double u2, double v1, double v2, double uTolerance = Precision::PConfusion(), double vTolerance = Precision::PConfusion());

	/// @brief Set the u knot at a given index
	/// @param i The given index
	/// @param k The new knot
	AMCAX_API void SetUKnot(int i, double k);

	/// @brief Set the u knots
	/// @param knots The u knots
	AMCAX_API void SetUKnots(const std::vector<double>& knots);

	/// @brief Set the u knots
	/// @param knots The u knots
	AMCAX_API void SetUKnots(std::vector<double>&& knots);

	/// @brief Set the u knot and multiplicity at a given index
	/// @param i The given index
	/// @param k The new knot
	/// @param m The new multiplicity
	AMCAX_API void SetUKnot(int i, double k, int m);

	/// @brief Set the v knot at a given index
	/// @param j The given index
	/// @param k The new knot
	AMCAX_API void SetVKnot(int j, double k);

	/// @brief Set the v knots
	/// @param knots The v knots
	AMCAX_API void SetVKnots(const std::vector<double>& knots);

	/// @brief Set the v knots
	/// @param knots The v knots
	AMCAX_API void SetVKnots(std::vector<double>&& knots);

	/// @brief Set the v knot and multiplicity at a given index
	/// @param j The given index
	/// @param k The new knot
	/// @param m The new multiplicity
	AMCAX_API void SetVKnot(int j, double k, int m);

	/// @brief Locate the u parameter
	/// @param[in] u The u parameter
	/// @param[in] parametricTolerance The parametric tolerance
	/// @param[out] i1 The start index of u knot
	/// @param[out] i2 The end index of u knot
	/// @param[in] withKnotRepetition Is the knot with repetition with respect to the multplicities
	AMCAX_API void LocateU(double u, double parametricTolerance, int& i1, int& i2, bool withKnotRepetition = false) const;

	/// @brief Locate the v parameter
	/// @param[in] v The v parameter
	/// @param[in] parametricTolerance The parametric tolerance
	/// @param[out] i1 The start index of v knot
	/// @param[out] i2 The end index of v knot
	/// @param[in] withKnotRepetition Is the knot with repetition with respect to the multplicities
	AMCAX_API void LocateV(double v, double parametricTolerance, int& i1, int& i2, bool withKnotRepetition = false) const;

	/// @brief Set the pole at given indices
	/// @param i The index along the u direction
	/// @param j The index along the v direction
	/// @param p The pole
	AMCAX_API void SetPole(int i, int j, const Point3& p);

	/// @brief Set the pole and weight at given indices
	/// @param i The index along the u direction
	/// @param j The index along the v direction
	/// @param p The pole
	/// @param weight The weight
	AMCAX_API void SetPole(int i, int j, const Point3& p, double weight);

	/// @brief Set the weight at given indices
	/// @param i The index along the u direction
	/// @param j The index along the v direction
	/// @param weight The weight
	AMCAX_API void SetWeight(int i, int j, double weight);

	/// @brief Move a point at given parameters to a new position
	/// @param[in] u The u parameter
	/// @param[in] v The v parameter
	/// @param[in] p The new position
	/// @param[in] i1 The index of the first pole to be moved along the u direction
	/// @param[in] i2 The index of the last pole to be moved along the u direction
	/// @param[in] j1 The index of the first pole to be moved along the v direction
	/// @param[in] j2 The index of the last pole to be moved along the v direction
	/// @param[out] uFirstIndex The index of the first modified pole along the u direction
	/// @param[out] uLastIndex The index of the last modified pole along the u direction
	/// @param[out] vFirstIndex The index of the first modified pole along the v direction
	/// @param[out] vLastIndex The index of the last modified pole along the v direction
	AMCAX_API void MovePoint(double u, double v, const Point3& p, int i1, int i2, int j1, int j2, int& uFirstIndex, int& uLastIndex, int& vFirstIndex, int& vLastIndex);

	AMCAX_API bool IsUClosed() const override;
	AMCAX_API bool IsVClosed() const override;
	AMCAX_API bool IsCNu(int n) const override;
	AMCAX_API bool IsCNv(int n) const override;
	AMCAX_API bool IsUPeriodic() const noexcept override;

	/// @brief Is the B spline surface rational along the u direction
	/// @return True if the B spline surface is rational along the u direction
	AMCAX_API bool IsURational() const noexcept;

	AMCAX_API bool IsVPeriodic() const noexcept override;

	/// @brief Is the B spline surface rational along the v direction
	/// @return True if the B spline surface is rational along the v direction
	AMCAX_API bool IsVRational() const noexcept;

	AMCAX_API void Bounds(double& u1, double& u2, double& v1, double& v2) const noexcept override;
	[[nodiscard]] AMCAX_API double FirstUParameter() const noexcept override;
	[[nodiscard]] AMCAX_API double LastUParameter() const noexcept override;
	[[nodiscard]] AMCAX_API double FirstVParameter() const noexcept override;
	[[nodiscard]] AMCAX_API double LastVParameter() const noexcept override;
	AMCAX_API ContinuityType Continuity() const noexcept override;

	/// @brief Get the index of the first u knot
	/// @return The index of the first u knot
	AMCAX_API int FirstUKnotIndex() const noexcept;

	/// @brief Get the index of the first v knot
	/// @return The index of the first v knot
	AMCAX_API int FirstVKnotIndex() const noexcept;

	/// @brief Get the index of the last u knot
	/// @return The index of the last u knot
	AMCAX_API int LastUKnotIndex() const noexcept;

	/// @brief Get the index of the last v knot
	/// @return The index of the last v knot
	AMCAX_API int LastVKnotIndex() const noexcept;

	/// @brief Get the number of u knots
	/// @return The number of u knots
	AMCAX_API int NUKnots() const noexcept;

	/// @brief Get the number of poles along the u direction
	/// @return The number of poles along the u direction
	AMCAX_API int NUPoles() const noexcept;

	/// @brief Get the number of v knots
	/// @return The number of v knots
	AMCAX_API int NVKnots() const noexcept;

	/// @brief Get the number of poles along the v direction
	/// @return The number of poles along the v direction
	AMCAX_API int NVPoles() const noexcept;

	/// @brief Get the pole at given indices
	/// @param i The index along the u direction
	/// @param j The index along the v direction
	/// @return The pole at indince (i, j)
	AMCAX_API const Point3& Pole(int i, int j) const;

	/// @brief Get the poles
	/// @return The poles
	AMCAX_API const Array2<Point3>& Poles() const noexcept;

	/// @brief Get the degree along the u direction
	/// @return The degree along the u direction
	AMCAX_API int UDegree() const noexcept;

	/// @brief Get the u knot at a given index
	/// @param i The given index
	/// @return The u knot
	AMCAX_API double UKnot(int i) const;

	/// @brief Get the type of the u knot distribution
	/// @return The type of the u knot distribution
	AMCAX_API BSplineKnotDistribution UKnotDistribution() const noexcept;

	/// @brief Get the u knots
	/// @return The u knots
	AMCAX_API const std::vector<double>& UKnots() const noexcept;

	/// @brief Get the u flat knot sequence with multiplicity
	/// @return The u flat knot sequence
	AMCAX_API const std::vector<double>& UKnotSequence() const noexcept;

	/// @brief Get the multiplicity of a u knot at a given index
	/// @param i The given index
	/// @return The multiplicity of a u knot
	AMCAX_API int UMultiplicity(int i) const;

	/// @brief Get the u multiplicities
	/// @return The u multiplicities
	AMCAX_API const std::vector<int>& UMultiplicities() const noexcept;

	/// @brief Get the degree along the v direction
	/// @return The degree along the v direction
	AMCAX_API int VDegree() const noexcept;

	/// @brief Get the v knot at a given index
	/// @param j The given index
	/// @return The v knot
	AMCAX_API double VKnot(int j) const;

	/// @brief Get the type of the v knot distribution
	/// @return The type of the v knot distribution
	AMCAX_API BSplineKnotDistribution VKnotDistribution() const noexcept;

	/// @brief Get the v knots
	/// @return The v knots
	AMCAX_API const std::vector<double>& VKnots() const noexcept;

	/// @brief Get the v flat knot sequence with multiplicity
	/// @return The v flat knot sequence
	AMCAX_API const std::vector<double>& VKnotSequence() const noexcept;

	/// @brief Get the multiplicity of a v knot at a given index
	/// @param j The given index
	/// @return The multiplicity of a v knot
	AMCAX_API int VMultiplicity(int j) const;

	/// @brief Get the v multiplicities
	/// @return The v multiplicities
	AMCAX_API const std::vector<int>& VMultiplicities() const noexcept;

	/// @brief Get the weight at given indices
	/// @param i The index along the u direction
	/// @param j The index along the v direction
	/// @return The weight at indince (i, j)
	AMCAX_API double Weight(int i, int j) const;

	/// @brief Get the weights
	/// @return The weights
	AMCAX_API const Array2<double>& Weights() const noexcept;

	AMCAX_API void D0(double u, double v, Point3& p) const override;
	AMCAX_API void D1(double u, double v, Point3& p, Vector3& d1u, Vector3& d1v) const override;
	AMCAX_API void D2(double u, double v, Point3& p, Vector3& d1u, Vector3& d1v, Vector3& d2uu, Vector3& d2uv, Vector3& d2vv) const override;
	AMCAX_API void D3(double u, double v, Point3& p, Vector3& d1u, Vector3& d1v, Vector3& d2uu, Vector3& d2uv, Vector3& d2vv, Vector3& d3uuu, Vector3& d3uuv, Vector3& d3uvv, Vector3& d3vvv) const override;
	AMCAX_API Vector3 DN(double u, double v, int nu, int nv) const override;

	/// @brief Compute the point at given parameters in a local rectangular domain
	/// @param[in] u The u parameter
	/// @param[in] v The v parameter
	/// @param[in] fromUK1 The index of the start u knot
	/// @param[in] toUK2 The index of the end u knot
	/// @param[in] fromVK1 The index of the start v knot
	/// @param[in] toVK2 The index of the end v knot
	/// @param[out] p The point
	AMCAX_API void LocalD0(double u, double v, int fromUK1, int toUK2, int fromVK1, int toVK2, Point3& p) const;

	/// @brief Compute the point and the first partial derivatives at given parameters in a local rectangular domain
	/// @param[in] u The u parameter
	/// @param[in] v The v parameter
	/// @param[in] fromUK1 The index of the start u knot
	/// @param[in] toUK2 The index of the end u knot
	/// @param[in] fromVK1 The index of the start v knot
	/// @param[in] toVK2 The index of the end v knot
	/// @param[out] p The point
	/// @param[out] d1u The partial derivative du
	/// @param[out] d1v The partial derivative dv
	AMCAX_API void LocalD1(double u, double v, int fromUK1, int toUK2, int fromVK1, int toVK2, Point3& p, Vector3& d1u, Vector3& d1v) const;

	/// @brief Compute the point, the first and second partial derivatives at given parameters in a local rectangular domain
	/// @param[in] u The u parameter
	/// @param[in] v The v parameter
	/// @param[in] fromUK1 The index of the start u knot
	/// @param[in] toUK2 The index of the end u knot
	/// @param[in] fromVK1 The index of the start v knot
	/// @param[in] toVK2 The index of the end v knot
	/// @param[out] p The point
	/// @param[out] d1u The partial derivative du
	/// @param[out] d1v The partial derivative dv
	/// @param[out] d2uu The partial derivative du^2
	/// @param[out] d2uv The partial derivative duv
	/// @param[out] d2vv The partial derivative dv^2
	AMCAX_API void LocalD2(double u, double v, int fromUK1, int toUK2, int fromVK1, int toVK2, Point3& p, Vector3& d1u, Vector3& d1v, Vector3& d2uu, Vector3& d2uv, Vector3& d2vv) const;

	/// @brief Compute the point, the first, second and third partial derivatives at given parameters in a local rectangular domain
	/// @param[in] u The u parameter
	/// @param[in] v The v parameter
	/// @param[in] fromUK1 The index of the start u knot
	/// @param[in] toUK2 The index of the end u knot
	/// @param[in] fromVK1 The index of the start v knot
	/// @param[in] toVK2 The index of the end v knot
	/// @param[out] p The point
	/// @param[out] d1u The partial derivative du
	/// @param[out] d1v The partial derivative dv
	/// @param[out] d2uu The partial derivative du^2
	/// @param[out] d2uv The partial derivative duv
	/// @param[out] d2vv The partial derivative dv^2
	/// @param[out] d3uuu The partial derivative du^3
	/// @param[out] d3uuv The partial derivative du^2v
	/// @param[out] d3uvv The partial derivative duv^2
	/// @param[out] d3vvv The partial derivative dv^3
	AMCAX_API void LocalD3(double u, double v, int fromUK1, int toUK2, int fromVK1, int toVK2, Point3& p, Vector3& d1u, Vector3& d1v, Vector3& d2uu, Vector3& d2uv, Vector3& d2vv, Vector3& d3uuu, Vector3& d3uuv, Vector3& d3uvv, Vector3& d3vvv) const;

	/// @brief Compute the partial derivative of given orders at given parameters in a local rectangular domain
	/// @param u The u parameter
	/// @param v The v parameter
	/// @param fromUK1 The index of the start u knot
	/// @param toUK2 The index of the end u knot
	/// @param fromVK1 The index of the start v knot
	/// @param toVK2 The index of the end v knot
	/// @param nu The order of derivative along the u direction
	/// @param nv The order of derivative along the v direction
	/// @return The partial derivative
	AMCAX_API Vector3 LocalDN(double u, double v, int fromUK1, int toUK2, int fromVK1, int toVK2, int nu, int nv) const;

	/// @brief Compute the point at given parameters in a local rectangular domain
	/// @param u The u parameter
	/// @param v The v parameter
	/// @param fromUK1 The index of the start u knot
	/// @param toUK2 The index of the end u knot
	/// @param fromVK1 The index of the start v knot
	/// @param toVK2 The index of the end v knot
	/// @return The point
	AMCAX_API Point3 LocalValue(double u, double v, int fromUK1, int toUK2, int fromVK1, int toVK2) const;

	/// @brief Get the u isoparametric curve at a u parameter
	/// @details For a B spline surface, the u isoparametric curve is a B spline curve
	/// @param u The u parameter
	/// @return The u isoparametric curve
	AMCAX_API std::shared_ptr<Geom3Curve> UIso(double u) const override;

	/// @brief Get the v isoparametric curve at a v parameter
	/// @details For a B spline surface, the v isoparametric curve is a B spline curve
	/// @param v The v parameter
	/// @return The v isoparametric curve
	AMCAX_API std::shared_ptr<Geom3Curve> VIso(double v) const override;

	/// @brief Get the u isoparametric curve at a u parameter
	/// @details For a B spline surface, the u isoparametric curve is a B spline curve
	/// @param u The u parameter
	/// @param checkRational Check the rationality of the weights
	/// @return The u isoparametric curve
	AMCAX_API std::shared_ptr<Geom3Curve> UIso(double u, bool checkRational) const;

	/// @brief Get the v isoparametric curve at a v parameter
	/// @details For a B spline surface, the v isoparametric curve is a B spline curve
	/// @param v The v parameter
	/// @param checkRational Check the rationality of the weights
	/// @return The v isoparametric curve
	AMCAX_API std::shared_ptr<Geom3Curve> VIso(double v, bool checkRational) const;

	AMCAX_API void Transform(const Transformation3& tr) noexcept override;

	/// @brief Get the maximum degree
	/// @return The maximum degree
	AMCAX_API static int MaxDegree() noexcept;

	/// @brief Get the tolerances on the parameters from a 3D tolerance
	/// @param tolerance3D The 3D tolerance
	/// @param uTolerance The u tolerance
	/// @param vTolerance The v tolerance
	AMCAX_API void Resolution(double tolerance3D, double& uTolerance, double& vTolerance);

	AMCAX_API std::shared_ptr<Geom3Geometry> Copy() const override;
	AMCAX_API std::ostream& Write(std::ostream& os) const override;
	AMCAX_API std::istream& Read(std::istream& is) override;

	/// @brief Get the type of B spline surface
	/// @return The type B spline surface
	AMCAX_API SurfaceType Type() const noexcept override;

private:
	void Segment(double u1, double u2, double v1, double v2, double epsU, double epsV, bool segmentInU, bool segmentInV);
	void UpdateUKnots();
	void UpdateVKnots();
	static void CheckSurfaceData(const Array2<Point3>& pts, const std::vector<double>& uKnots, const std::vector<double>& vKnots, const std::vector<int>& uMults, const std::vector<int>& vMults, int uDegree, int vDegree, bool uPeriodic, bool vPeriodic);
	static bool SetRational(const Array2<double>& w, bool& uRational, bool& vRational) noexcept;

	/// @brief Control points
	Array2<Point3> poles;

	/// @brief Weights for rational surfaces
	Array2<double> weights;

	/// @brief U knots with multiplicities
	std::vector<double> uFlatKnots;

	/// @brief V knots with multiplicities
	std::vector<double> vFlatKnots;

	/// @brief U knots
	std::vector<double> uKnots;

	/// @brief V knots
	std::vector<double> vKnots;

	/// @brief Multiplicities of u knots
	std::vector<int> uMultiplicities;

	/// @brief Multiplicities of v knots
	std::vector<int> vMultiplicities;

	/// @brief Inverse of maximal U derivative
	double umaxderivinv = 0.0;

	/// @brief Inverse of maximal V derivative
	double vmaxderivinv = 0.0;

	/// @brief U degree
	int uDegree = 0;

	/// @brief V degree
	int vDegree = 0;

	/// @brief U knot distribution type
	BSplineKnotDistribution uKnotSet = BSplineKnotDistribution::NonUniform;

	/// @brief V knot distribution type
	BSplineKnotDistribution vKnotSet = BSplineKnotDistribution::NonUniform;

	/// @brief U continuity type
	ContinuityType uContinuity = ContinuityType::C0;

	/// @brief V continuity type
	ContinuityType vContinuity = ContinuityType::C0;

	/// @brief Is U rational
	bool uRational = false;

	/// @brief Is V rational
	bool vRational = false;

	/// @brief Is U periodic
	bool uPeriodic = false;

	/// @brief Is V periodic
	bool vPeriodic = false;

	/// @brief Is the inverse of maximal derivative computed
	bool maxderivinvok = false;
};
} // namespace AMCAX
