/// @file      NURBSAPIInterpolate.hpp
/// @brief     Class of NURBS interpolation
/// @copyright Copyright (c) 2024 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <memory>
#include <vector>

#include <approx/ApproxParameterizationType.hpp>
#include <common/PointT.hpp>
#include <common/VectorT.hpp>
#include <nurbs/NURBSMacros.hpp>

namespace AMCAX
{
class Geom3BSplineCurve;
class Geom3BSplineSurface;

/// @brief Struct of data node for interpolation including position and first and second derivatives
struct InterpolationNode
{
	/// @brief The point position
	Point3 pos;

	/// @brief Whether or not to include the constraint of the first derivative
	bool isWithD1 = false;

	/// @brief The target first derivative
	Vector3 deriv1;

	/// @brief Whether or not to include the constraint of the second derivative
	bool isWithD2 = false;

	/// @brief The target second derivative
	Vector3 deriv2;
};

/// @brief Class of interpolating points by a curve
/// @details This class computes the resulting curve by interpolating points
class NURBSAPIInterpolate
{
public:
	/// @brief The curve which interpolate the points is constructed
	/// @param points Data points
	/// @param degree Curve degree
	/// @param isClosed Is the curve closed
	/// @param ptype Parameterization type
	/// @return The curve
	[[nodiscard]] AMCAX_API static std::shared_ptr<Geom3BSplineCurve> InterpolatePoints(const std::vector<Point3>& points, int degree = 3, bool isClosed = false, ApproxParameterizationType ptype = ApproxParameterizationType::ChordLength);

	/// @brief The curve which interpolate the points with gradients is constructed
	/// @param nodes Data nodes
	/// @param isClosed Is the curve closed
	/// @param ptype Parameterization type
	/// @return The curve
	[[nodiscard]] AMCAX_API static std::shared_ptr<Geom3BSplineCurve> InterpolateNodes(const std::vector<InterpolationNode>& nodes, bool isClosed = false, ApproxParameterizationType ptype = ApproxParameterizationType::ChordLength);

	/// @brief The curve which interpolate the points with gradients is constructed with Thin Plate Energy
	/// @param nodes Data nodes
	/// @param isClosed Is the curve closed
	/// @param ptype Parameterization type
	/// @param alpha The weight of D1 Thin Plate Energy
	/// @param beta The weight of D2 Thin Plate Energy
	/// @return The curve
	[[nodiscard]] AMCAX_API static std::shared_ptr<Geom3BSplineCurve> InterpolateNodesThinPlate(const std::vector<InterpolationNode>& nodes, bool isClosed = false, ApproxParameterizationType ptype = ApproxParameterizationType::ChordLength, double alpha = 1e-3, double beta = 1e-3);

	/// @brief The curve which interpolate the points with gradients is constructed with Thin Plate Energy
	/// @param nodes Data nodes
	/// @param parameterization The parameterization of the points
	/// @param isClosed Is the curve closed
	/// @param alpha The weight of D1 Thin Plate Energy
	/// @param beta The weight of D2 Thin Plate Energy
	/// @return The curve
	[[nodiscard]] AMCAX_API static std::shared_ptr<Geom3BSplineCurve> InterpolateNodesThinPlate(const std::vector<InterpolationNode>& nodes, const std::vector<double>& parameterization, const bool isClosed, double alpha, double beta);

#ifndef DOXYGEN_SKIP
	/// @brief The surface which interpolate the curves is constructed
	/// @param curves Data curves
	/// @param isClosed Is the surface closed
	/// @param ptype Parameterization type
	/// @return The surface
	[[nodiscard]] AMCAX_TEST_API static std::shared_ptr<Geom3BSplineSurface> InterpolateCurves(const std::vector<std::shared_ptr<Geom3BSplineCurve>>& curves, bool isClosed = false, ApproxParameterizationType ptype = ApproxParameterizationType::ChordLength);
#endif

	/// @brief Interpolate points to make a BSpline curve with Thin Plate Energy
	/// @param points Data points
	/// @param isClosed Is closed interpolation
	/// @param ptype Parameterization type
	/// @param alpha The weight of D1 Thin Plate Energy
	/// @param beta The weight of D2 Thin Plate Energy
	/// @return The result curve
	[[nodiscard]] AMCAX_API static std::shared_ptr<Geom3BSplineCurve> InterpolatePointsThinPlate(const std::vector<Point3>& points, bool isClosed, ApproxParameterizationType ptype, double alpha, double beta);

	/// @brief Interpolate points to make a BSpline curve with Thin Plate Energy
	/// @param points Data points
	/// @param parameterization The parameterization of the points
	/// @param isClosed Is closed interpolation
	/// @param alpha The weight of D1 Thin Plate Energy
	/// @param beta The weight of D2 Thin Plate Energy
	/// @return The result curve
	[[nodiscard]] AMCAX_API static std::shared_ptr<Geom3BSplineCurve> InterpolatePointsThinPlate(const std::vector<Point3>& points, const std::vector<double>& parameterization, bool isClosed, double alpha, double beta);

#ifndef DOXYGEN_SKIP
	/// @brief Interpolate points to make a BSpline curve
	/// @param points Data points
	/// @param parameterization The parameterization of the points
	/// @param isClosed Is closed interpolation
	/// @param deg The degree
	/// @param knots The knots
	/// @param mults The multiplicities
	/// @return The result curve
	[[nodiscard]] static std::shared_ptr<Geom3BSplineCurve> InterpolatePointsKernel(const std::vector<Point3>& points, const std::vector<double>& parameterization, const bool isClosed, const int deg, const std::vector<double>& knots, const std::vector<int>& mults);

	/// @brief Interpolate nodes to make a BSpline curve
	/// @param nodes Data nodes with positions and derivatives
	/// @param parameterization The parameterization of the BSpline nodes
	/// @param isClosed Is closed interpolation
	/// @return The result curve
	[[nodiscard]] static std::shared_ptr<Geom3BSplineCurve> InterpolateNodesKernel(const std::vector<InterpolationNode>& nodes, const std::vector<double>& parameterization, const bool isClosed);

	/// @brief Interpolate nodes to make a BSpline curve with given degree, knots and multiplicities
	/// @param nodes Data nodes with positions and derivatives
	/// @param parameterization The parameterization of the BSpline nodes
	/// @param isClosed Is closed interpolation
	/// @param deg The degree
	/// @param knots The knots
	/// @param mults The multiplicities
	/// @return The result curve
	[[nodiscard]] static std::shared_ptr<Geom3BSplineCurve> InterpolateNodesKernel(const std::vector<InterpolationNode>& nodes, const std::vector<double>& parameterization, const bool isClosed, const int deg, const std::vector<double>& knots, const std::vector<int>& mults);

	/// @brief Interpolate non-rational BSpline curves to make a BSpline surface
	/// @param curves The non-rational BSpline curves
	/// @param parameterization The parameterization of the BSpline curves
	/// @param isClosed Is the result surface closed
	/// @param deg The degree
	/// @param knots The knots
	/// @param mults The multiplicities
	/// @return The result surface
	[[nodiscard]] static std::shared_ptr<Geom3BSplineSurface> InterpolateCurvesKernel(const std::vector<std::shared_ptr<Geom3BSplineCurve>>& curves, const std::vector<double>& parameterization, const bool isClosed, const int deg, const std::vector<double>& knots, const std::vector<int>& mults);

	/// @brief Interpolate nodes to make a BSpline curve with Thin Plate Energy by giving degree, knots and multiplicities
	/// @param nodes Data nodes with positions and derivatives
	/// @param parameterization The parameterization of the BSpline nodes
	/// @param isClosed Is closed interpolation
	/// @param deg The degree
	/// @param knots The knots
	/// @param mults The multiplicities
	/// @param alpha The weight of D1 Thin Plate Energy
	/// @param beta The weight of D2 Thin Plate Energy
	/// @return The result curve
	[[nodiscard]] static std::shared_ptr<Geom3BSplineCurve> InterpolateNodesKernelThinPlate(const std::vector<InterpolationNode>& nodes, const std::vector<double>& parameterization, const bool isClosed, const int deg, const std::vector<double>& knots, const std::vector<int>& mults, double alpha, double beta);

#endif
};
} // namespace AMCAX
