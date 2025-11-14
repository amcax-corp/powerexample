/// @file      Geom3BezierSurface.hpp
/// @brief     Class of 3D Bezier surface
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <common/Array2.hpp>
#include <geometry/Geom3BoundedSurface.hpp>

namespace AMCAX
{
/// @brief Class of 3D Bezier surface
class AMCAX_CLASS_API Geom3BezierSurface : public Geom3BoundedSurface
{
public:
	/// @brief Default constructor
	/// @details A default surface is a unit square
	AMCAX_API Geom3BezierSurface();

	/// @brief Construct a bezier surface from poles
	/// @param pts The poles
	AMCAX_API explicit Geom3BezierSurface(const Array2<Point3>& pts);

	/// @brief Construct a rational bezier surface from poles and weights
	/// @param pts The poles
	/// @param w The weights
	AMCAX_API Geom3BezierSurface(const Array2<Point3>& pts, const Array2<double>& w);

	/// @brief Construct a rational bezier surface from poles and weights
	/// @param pts The poles
	/// @param w The weights
	/// @param isURational Set if the bezier surface is rational along the u direction
	/// @param isVRational Set if the bezier surface is rational along the v direction
	AMCAX_API Geom3BezierSurface(const Array2<Point3>& pts, const Array2<double>& w, bool isURational, bool isVRational);

	/// @brief Exchange the uv directions
	AMCAX_API void ExchangeUV();

	/// @brief Increase the degrees to given degrees
	/// @param uDegree The given u degree
	/// @param vDegree The given v degree
	AMCAX_API void Increase(int uDegree, int vDegree);

	/// @brief Segment the bezier surface by given bounds
	/// @param u1 The lower bound of u direction
	/// @param u2 The upper bound of u direction
	/// @param v1 The lower bound of v direction
	/// @param v2 The upper bound of v direction
	AMCAX_API void Segment(double u1, double u2, double v1, double v2);

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

	/// @brief Set part of a column of poles
	/// @details The indices of modified poles start from (i, j) to (i + pts.size() - 1, j)
	/// @param i The index of the start row
	/// @param j The index of column
	/// @param pts The poles
	AMCAX_API void SetPoleCol(int i, int j, const std::vector<Point3>& pts);

	/// @brief Set part of a column of poles and weights
	/// @details The indices of modified poles and weights start from (i, j) to (i + pts.size() - 1, j)
	/// @param i The index of the start row
	/// @param j The index of column
	/// @param pts The poles
	/// @param w The weights
	AMCAX_API void SetPoleCol(int i, int j, const std::vector<Point3>& pts, const std::vector<double>& w);

	/// @brief Set part of a row of poles
	/// @details The indices of modified poles start from (i, j) to (i, j + pts.size() - 1)
	/// @param i The index of the row
	/// @param j The index of the start column
	/// @param pts The poles
	AMCAX_API void SetPoleRow(int i, int j, const std::vector<Point3>& pts);

	/// @brief Set part of a row of poles and weights
	/// @details The indices of modified poles and weights start from (i, j) to (i, j + pts.size() - 1)
	/// @param i The index of the row
	/// @param j The index of the start column
	/// @param pts The poles
	/// @param w The weights
	AMCAX_API void SetPoleRow(int i, int j, const std::vector<Point3>& pts, const std::vector<double>& w);

	/// @brief Set the weight at given indices
	/// @param i The index along the u direction
	/// @param j The index along the v direction
	/// @param weight The weight
	AMCAX_API void SetWeight(int i, int j, double weight);

	/// @brief Set part of a column of weights
	/// @details The indices of modified weights start from (i, j) to (i + pts.size() - 1, j)
	/// @param i The index of the start row
	/// @param j The index of the column
	/// @param w The weights
	AMCAX_API void SetWeightCol(int i, int j, const std::vector<double>& w);

	/// @brief Set part of a row of weights
	/// @details The indices of modified weights start from (i, j) to (i, j + pts.size() - 1)
	/// @param i The index of the row
	/// @param j The index of the start column
	/// @param w The weights
	AMCAX_API void SetWeightRow(int i, int j, const std::vector<double>& w);

	AMCAX_API void UReverse() noexcept override;
	AMCAX_API void VReverse() noexcept override;
	AMCAX_API double UReversedParameter(double u) const noexcept override;
	AMCAX_API double VReversedParameter(double v) const noexcept override;

	/// @brief Get the parameter bounds
	/// @details For a bezier surface, the bounds are from 0 to 1
	/// @param[out] u1 The first u parameter
	/// @param[out] u2 The last u parameter
	/// @param[out] v1 The first v parameter
	/// @param[out] v2 The last v parameter
	AMCAX_API void Bounds(double& u1, double& u2, double& v1, double& v2) const noexcept override;

	/// @brief Get the first u parameter
	/// @details For a bezier surface, the first u parameter is 0
	/// @return The first u parameter
	[[nodiscard]] AMCAX_API double FirstUParameter() const noexcept override;

	/// @brief Get the last u parameter
	/// @details For a bezier surface, the last u parameter is 1
	/// @return The last u paramater
	[[nodiscard]] AMCAX_API double LastUParameter() const noexcept override;

	/// @brief Get the first v parameter
	/// @details For a bezier surface, the first v parameter is 0
	/// @return The first v parameter
	[[nodiscard]] AMCAX_API double FirstVParameter() const noexcept override;

	/// @brief Get the last v parameter
	/// @details For a bezier surface, the last v parameter is 1
	/// @return The last v parameter
	[[nodiscard]] AMCAX_API double LastVParameter() const noexcept override;

	/// @brief Get the continuity of the surface
	/// @return The CN continuity
	AMCAX_API ContinuityType Continuity() const noexcept override;

	AMCAX_API void D0(double u, double v, Point3& p) const override;
	AMCAX_API void D1(double u, double v, Point3& p, Vector3& d1u, Vector3& d1v) const override;
	AMCAX_API void D2(double u, double v, Point3& p, Vector3& d1u, Vector3& d1v, Vector3& d2uu, Vector3& d2uv, Vector3& d2vv) const override;
	AMCAX_API void D3(double u, double v, Point3& p, Vector3& d1u, Vector3& d1v, Vector3& d2uu, Vector3& d2uv, Vector3& d2vv, Vector3& d3uuu, Vector3& d3uuv, Vector3& d3uvv, Vector3& d3vvv) const override;
	AMCAX_API Vector3 DN(double u, double v, int nu, int nv) const override;

	/// @brief Get the number of poles along the u direction
	/// @return The number of poles along the u direction
	AMCAX_API int NUPoles() const noexcept;

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

	/// @brief Get the degree along the v direction
	/// @return The degree along the v direction
	AMCAX_API int VDegree() const noexcept;

	/// @brief Get the u isoparametric curve at a u parameter
	/// @details For a bezier surface, the u isoparametric curve is a bezier curve
	/// @param u The u parameter
	/// @return The u isoparametric curve
	AMCAX_API std::shared_ptr<Geom3Curve> UIso(double u) const override;

	/// @brief Get the v isoparametric curve at a v parameter
	/// @details For a bezier surface, the v isoparametric curve is a bezier curve
	/// @param v The v parameter
	/// @return The v isoparametric curve
	AMCAX_API std::shared_ptr<Geom3Curve> VIso(double v) const override;

	/// @brief Get the weight at given indices
	/// @param i The index along the u direction
	/// @param j The index along the v direction
	/// @return The weight at indince (i, j)
	AMCAX_API double Weight(int i, int j) const;

	/// @brief Get the weights
	/// @return The weights
	AMCAX_API const Array2<double>& Weights() const noexcept;

	AMCAX_API bool IsUClosed() const noexcept override;
	AMCAX_API bool IsVClosed() const noexcept override;

	/// @brief Is the bezier surface has an order n of continuity along the u direction
	/// @param n The order of continuity
	/// @return Always true
	AMCAX_API bool IsCNu(int n) const noexcept override;

	/// @brief Is the bezier surface has an order n of continuity along the v direction
	/// @param n The order of continuity
	/// @return Always true
	AMCAX_API bool IsCNv(int n) const noexcept override;

	/// @brief Is the bezier surface periodic along the u direction
	/// @return Always false
	AMCAX_API bool IsUPeriodic() const noexcept override;

	/// @brief Is the bezier surface periodic along the v direction
	/// @return Always false
	AMCAX_API bool IsVPeriodic() const noexcept override;

	/// @brief Is the bezier surface rational along the u direction
	/// @return True if the bezier surface is rational along the u direction
	AMCAX_API bool IsURational() const noexcept;

	/// @brief Is the bezier surface rational along the v direction
	/// @return True if the bezier surface is rational along the v direction
	AMCAX_API bool IsVRational() const noexcept;

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

	/// @brief Get the type of bezier surface
	/// @return The type bezier surface
	AMCAX_API SurfaceType Type() const noexcept override;

private:
	void Init(const Array2<Point3>& pts, const Array2<double>& w);
	bool SetRational(const Array2<double>& w) noexcept;

	/// @brief Control points
	Array2<Point3> poles;

	/// @brief Weight for each control point
	Array2<double> weights;

	/// @brief Inverse of maximal U derivative
	double umaxderivinv = 0.0;

	/// @brief Inverse of maximal V derivative
	double vmaxderivinv = 0.0;

	/// @brief Is the inverse of maximal derivatives computed
	bool maxderivinvok = false;

	/// @brief Is U direction rational
	bool urational = false;

	/// @brief Is V direction rational
	bool vrational = false;
};
} // namespace AMCAX
