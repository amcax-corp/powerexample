/// @file      BRepAdaptorCompCurve3.hpp
/// @brief     Class of adaptor of 3D composite curves in B-Rep
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <geometry/Adaptor3Curve.hpp>
#include <topology/TopoWire.hpp>

namespace AMCAX
{
class BRepAdaptorCurve3;
class TopoEdge;

/// @brief Class of adaptor of 3D composite curves in B-Rep
class AMCAX_CLASS_API BRepAdaptorCompCurve3 : public Adaptor3Curve
{
public:
	/// @brief Default constructor
	BRepAdaptorCompCurve3() noexcept = default;

	/// @brief Construct from a wire
	/// @param w The wire
	/// @param knotByCurvilinearAbscissa Determine whether the knot is computed by curvilinear abscissa
	AMCAX_API explicit BRepAdaptorCompCurve3(const TopoWire& w, bool knotByCurvilinearAbscissa = false);

	/// @brief Construct from a wire and a range of parameter
	/// @param w The wire
	/// @param knotByCurvilinearAbscissa Determine whether the knot is computed by curvilinear abscissa
	/// @param first The first parameter
	/// @param last The last parameter
	/// @param tol The tolerance for point confusion
	AMCAX_API BRepAdaptorCompCurve3(const TopoWire& w, bool knotByCurvilinearAbscissa, double first, double last, double tol);

	[[nodiscard]] AMCAX_API std::shared_ptr<Adaptor3Curve> ShallowCopy() const override;

	/// @brief Initialize from a wire
	/// @param w The wire
	/// @param knotByCurvilinearAbscissa Determine whether the knot is computed by curvilinear abscissa
	AMCAX_API void Initialize(const TopoWire& w, bool knotByCurvilinearAbscissa);

	/// @brief Construct from a wire and a range of parameter
	/// @param w The wire
	/// @param knotByCurvilinearAbscissa Determine whether the knot is computed by curvilinear abscissa
	/// @param first The first parameter
	/// @param last The last parameter
	/// @param tol The tolerance for point confusion
	AMCAX_API void Initialize(const TopoWire& w, bool knotByCurvilinearAbscissa, double first, double last, double tol);

	/// @brief Get the wire
	/// @return The wire
	[[nodiscard]] AMCAX_API const TopoWire& Wire() const noexcept;

	/// @brief Get the edge from a given parameter and the parameter on that edge
	/// @param[in] u The parameter
	/// @param[out] e The edge
	/// @param[out] uOnE The parameter on the edge
	AMCAX_API void Edge(double u, TopoEdge& e, double& uOnE) const;

	[[nodiscard]] AMCAX_API double FirstParameter() const noexcept override;
	[[nodiscard]] AMCAX_API double LastParameter() const noexcept override;
	[[nodiscard]] AMCAX_API ContinuityType Continuity() const override;
	[[nodiscard]] AMCAX_API int NIntervals(ContinuityType c) const override;
	AMCAX_API void Intervals(std::vector<double>& t, ContinuityType c) const override;
	[[nodiscard]] AMCAX_API std::shared_ptr<Adaptor3Curve> Trim(double first, double last, double tol) const override;
	[[nodiscard]] AMCAX_API bool IsClosed() const noexcept override;
	[[nodiscard]] AMCAX_API bool IsPeriodic() const noexcept override;
	[[nodiscard]] AMCAX_API double Period() const noexcept override;
	[[nodiscard]] AMCAX_API Point3 Value(double U) const override;
	AMCAX_API void D0(double u, Point3& p) const override;
	AMCAX_API void D1(double u, Point3& p, Vector3& v) const override;
	AMCAX_API void D2(double u, Point3& p, Vector3& v1, Vector3& v2) const override;
	AMCAX_API void D3(double u, Point3& p, Vector3& v1, Vector3& v2, Vector3& v3) const override;
	[[nodiscard]] AMCAX_API Vector3 DN(double u, int n) const override;
	[[nodiscard]] AMCAX_API double Resolution(double r3d) const override;
	[[nodiscard]] AMCAX_API CurveType Type() const noexcept override;
	[[nodiscard]] AMCAX_API Line3 Line() const override;
	[[nodiscard]] AMCAX_API Circle3 Circle() const override;
	[[nodiscard]] AMCAX_API Ellipse3 Ellipse() const override;
	[[nodiscard]] AMCAX_API Hyperbola3 Hyperbola() const override;
	[[nodiscard]] AMCAX_API Parabola3 Parabola() const override;
	[[nodiscard]] AMCAX_API int Degree() const override;
	[[nodiscard]] AMCAX_API bool IsRational() const override;
	[[nodiscard]] AMCAX_API int NPoles() const override;
	[[nodiscard]] AMCAX_API int NKnots() const override;
	[[nodiscard]] AMCAX_API std::shared_ptr<Geom3BezierCurve> Bezier() const override;
	[[nodiscard]] AMCAX_API std::shared_ptr<Geom3BSplineCurve> BSpline() const override;
	[[nodiscard]] AMCAX_API std::shared_ptr<Geom3OffsetCurve> OffsetCurve() const override;

private:
	void Prepare(double& w, double& d, int& ind) const;
	void InvPrepare(int ind, double& f, double& d) const;

	/// @brief The wire containing curves
	TopoWire wire;

	/// @brief Start parameter
	double tFirst = 0.0;

	/// @brief End parameter
	double tLast = 0.0;

	/// @brief Tolerance
	double pTol = 0.0;

	/// @brief Vector of curves
	std::vector<BRepAdaptorCurve3> curves;

	/// @brief Knot vector
	std::vector<double> knots;

	/// @brief Current index
	int currentIndex = -1;

	/// @brief Is forward or reverse
	bool forward = false;

	/// @brief Is by curvilinear abscissa
	bool isbyAC = false;
};
} // namespace AMCAX
