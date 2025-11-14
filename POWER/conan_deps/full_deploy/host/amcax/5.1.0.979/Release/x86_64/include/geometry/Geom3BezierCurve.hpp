/// @file      Geom3BezierCurve.hpp
/// @brief     Class of 3D bezier curve
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <vector>

#include <geometry/Geom3BoundedCurve.hpp>

namespace AMCAX
{
/// @brief Class of 3D bezier curve
class AMCAX_CLASS_API Geom3BezierCurve : public Geom3BoundedCurve
{
public:
	/// @brief Default constructor
	/// @details A default curve is a line from the origin towards x-axis with length 1.
	AMCAX_API Geom3BezierCurve();

	/// @brief Construct a bezier curve from poles
	/// @param pts The poles
	AMCAX_API explicit Geom3BezierCurve(const std::vector<Point3>& pts);

	/// @brief Construct a rational bezier curve from poles and weights
	/// @param pts The poles
	/// @param w The weights
	AMCAX_API Geom3BezierCurve(const std::vector<Point3>& pts, const std::vector<double>& w);

	/// @brief Increase the degree of the curve
	/// @param degree The new degree
	AMCAX_API void Increase(int degree);

	/// @brief Insert a pole before a given index
	/// @param index The index to be insert
	/// @param p The pole
	/// @param weight The weight
	AMCAX_API void InsertPole(int index, const Point3& p, double weight = 1.0);

	/// @brief Remove a pole at a given index
	/// @param index The index of the pole
	AMCAX_API void RemovePole(int index);

	AMCAX_API void Reverse() override;
	AMCAX_API double ReversedParameter(double u) const noexcept override;

	/// @brief Segment the bezier curve to a given range
	/// @param u1 The first parameter
	/// @param u2 The last parameter
	AMCAX_API void Segment(double u1, double u2);

	/// @brief Set the pole at a given index
	/// @param index The given index
	/// @param p The pole
	AMCAX_API void SetPole(int index, const Point3& p);

	/// @brief Set the pole and weight at a given index
	/// @param index The given index
	/// @param p The pole
	/// @param weight The weight
	AMCAX_API void SetPole(int index, const Point3& p, double weight);

	/// @brief Set the weight at a given index
	/// @param index The given index
	/// @param weight The new weight
	AMCAX_API void SetWeight(int index, double weight);

	AMCAX_API Point3 StartPoint() const noexcept override;
	AMCAX_API Point3 EndPoint() const noexcept override;

	/// @brief Get the first parameter
	/// @details For a bezier curve, the first parameter is 0
	/// @return The first parameter
	AMCAX_API double FirstParameter() const noexcept override;

	/// @brief Get the last parameter
	/// @details For a bezier curve, the last parameter is 1
	/// @return The last parameter
	AMCAX_API double LastParameter() const noexcept override;

	/// @brief Is the bezier curve closed
	/// @return True if the bezier curve is closed
	AMCAX_API bool IsClosed() const noexcept override;

	/// @brief Is the bezier curve periodic
	/// @return Always false
	AMCAX_API bool IsPeriodic() const noexcept override;

	/// @brief Get the type of continuity of the bezier curve
	/// @return CN infinite continuity
	AMCAX_API ContinuityType Continuity() const noexcept override;

	/// @brief Is the curve has an order n of continuity
	/// @param n The order of continuity
	/// @return Always true
	AMCAX_API bool IsCN(int n) const noexcept override;

	/// @brief Check whether the bezier curve is rational or not
	/// @return True if the bezier curve is rational
	AMCAX_API bool IsRational() const noexcept;

	/// @brief Get the degree of the bezier curve
	/// @return The degree of the bezier curve
	AMCAX_API int Degree() const noexcept;

	AMCAX_API void D0(double u, Point3& p) const noexcept override;
	AMCAX_API void D1(double u, Point3& p, Vector3& v1) const noexcept override;
	AMCAX_API void D2(double u, Point3& p, Vector3& v1, Vector3& v2) const noexcept override;
	AMCAX_API void D3(double u, Point3& p, Vector3& v1, Vector3& v2, Vector3& v3) const noexcept override;
	AMCAX_API Vector3 DN(double u, int n) const noexcept override;

	/// @brief Get the number of poles
	/// @return The number of poles
	AMCAX_API int NPoles() const noexcept;

	/// @brief Get the pole of the given index
	/// @param index The given index
	/// @return The pole of the given index
	AMCAX_API const Point3& Pole(int index) const;

	/// @brief Get the poles
	/// @return The poles
	AMCAX_API const std::vector<Point3>& Poles() const noexcept;

	/// @brief Get the weight of the given index
	/// @param index The given index
	/// @return The weight of the given index
	AMCAX_API double Weight(int index) const;

	/// @brief Get the weights
	/// @return The weights
	AMCAX_API const std::vector<double>& Weights() const noexcept;

	AMCAX_API void Transform(const Transformation3& tr) noexcept override;

	/// @brief Get the maximum degree of a bezier curve
	/// @return The maximum degree of a bezier curve
	AMCAX_API static int MaxDegree() noexcept;

	/// @brief Compute the parametric tolerance from a 3D tolerance
	/// @param[in] tolerance3D The 3D tolerance
	/// @param[out] uTolerance The parametric tolerance
	AMCAX_API void Resolution(double tolerance3D, double& uTolerance);

	AMCAX_API std::shared_ptr<Geom3Geometry> Copy() const override;
	AMCAX_API std::ostream& Write(std::ostream& os) const override;
	AMCAX_API std::istream& Read(std::istream& is) override;

	/// @brief Get the type of curve, a bezier curve
	/// @return Type bezier curve
	AMCAX_API CurveType Type() const noexcept override;

private:
	void Init(const std::vector<Point3>& pts, const std::vector<double>& ws);
	static bool IsRational(const std::vector<double>& w) noexcept;
	static bool IsClosed(const std::vector<Point3>& pts) noexcept;

	/// @brief Control points
	std::vector<Point3> poles;

	/// @brief Weights for rational curve
	std::vector<double> weights;

	/// @brief Inverse of maximal derivative
	double maxderivinv = 0.0;

	/// @brief Is the inverse of maximal derivative computed
	bool maxderivinvok = false;

	/// @brief Is closed curve
	bool closed = false;
};
} // namespace AMCAX
