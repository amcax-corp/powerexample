/// @file      NURBSAPIBlend.hpp
/// @brief     Class of blending operation
/// @copyright Copyright (c) 2024 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <memory>
#include <vector>

#include <common/Macros.hpp>
#include <math/GeometryMacros.hpp>
#include <nurbs/NURBSMatchSurfConfig.hpp>

namespace AMCAX
{
class TopoEdge;
class TopoFace;
class Geom3BSplineCurve;
class Geom3BSplineSurface;

/// @brief Class of building a blend curve/surface connecting two curves/surfaces
/// @details This class computes the blend object to connect two objects such as curves, surfaces or faces.
class NURBSAPIBlend
{
public:
	/// @brief Given two curves, a curve to connect the two curves is constructed
	/// @param curve1 Curve1
	/// @param isFront1 Is curve1 front end to connect
	/// @param cont1 Connect geometric continuity of curve1
	/// @param curve2 Curve2
	/// @param isFront2 Is curve2 front end to connect
	/// @param cont2 Connect geometric continuity of curve2
	/// @return The blend curve
	[[nodiscard]] AMCAX_API static std::shared_ptr<Geom3BSplineCurve> BlendCurves(
		const std::shared_ptr<Geom3BSplineCurve>& curve1, bool isFront1, ContinuityType cont1,
		const std::shared_ptr<Geom3BSplineCurve>& curve2, bool isFront2, ContinuityType cont2);

	/// @brief Given two curves, a curve to connect the two curves is constructed
	/// @param[in] curve1 Curve1
	/// @param[in] isFront1 Is curve1 front end to connect
	/// @param[in] cont1 Connect geometric continuity of curve1
	/// @param[in,out] parameters1 The ratio of the nth derivative of the blend
	/// curve at the junction to the nth derivative of curve1
	/// at the junction, and the number of continuity requirements is
	/// what the vector length is. The default parameter is used if the
	/// parameters are missing and the parameter is added to the vec
	/// @param[in] curve2 Curve2
	/// @param[in] isFront2 Is curve2 front end to connect
	/// @param[in] cont2 Connect geometric continuity of curve2
	/// @param[in,out] parameters2 Similar to parameters1
	/// @return The blend curve
	[[nodiscard]] AMCAX_API static std::shared_ptr<Geom3BSplineCurve> BlendCurves(
		const std::shared_ptr<Geom3BSplineCurve>& curve1, bool isFront1, ContinuityType cont1, std::vector<double>& parameters1,
		const std::shared_ptr<Geom3BSplineCurve>& curve2, bool isFront2, ContinuityType cont2, std::vector<double>& parameters2);

	/// @brief Given two surfaces, a blend surface to connect the two surfaces is constructed
	/// @param[in] surf1 Surface1
	/// @param[in] isUIso1 Is surface1 connection curve a u isocurve
	/// @param[in] isFront1 Is surface1 connection curve a front isocurve
	/// @param[in] cont1 Connect geometric continuity of surface1
	/// @param[in,out] parameters1 The maximum vector size is nDerivatives,
	/// each parameter means the norm ratio of each derivative.
	/// If no parameter, default parameter is used and the parameter is added to the vec
	/// @param[in] surf2 Surface2
	/// @param[in] isUIso2 Is surface2 connection curve a u isocurve
	/// @param[in] isFront2 Is surface2 connection curve a front isocurve
	/// @param[in] cont2 Connect geometric continuity of surface2
	/// @param[in,out] parameters2 Similar to parameters1
	/// @param[in] autoReverse Whether it is necessary to automatically
	/// reverse the direction of the surface to avoid distortion of the blend surface
	/// @param[in] isPrecise Is the result required to under tolerance
	/// @param[in] tol If not precise, tol is not used,
	/// else the elements int tol are, in order,
	/// C0 position tolerance, G1 normal angular tolerance in radians, G2 curvature relative error tolerance
	/// @return A blend surface
	[[nodiscard]] AMCAX_API static std::shared_ptr<Geom3BSplineSurface> BlendSurfaces(
		const std::shared_ptr<Geom3BSplineSurface>& surf1, bool isUIso1, bool isFront1, ContinuityType cont1, std::vector<double>& parameters1,
		const std::shared_ptr<Geom3BSplineSurface>& surf2, bool isUIso2, bool isFront2, ContinuityType cont2, std::vector<double>& parameters2,
		bool autoReverse, bool isPrecise, const std::vector<double>& tol);

	/// @brief Given two surfaces, a blend surface to connect the two surfaces is constructed
	/// @param[in] surf1 Surface1
	/// @param[in] isUIso1 Is surface1 connection curve a u isocurve
	/// @param[in] isFront1 Is surface1 connection curve a front isocurve
	/// @param[in] cont1 Connect geometric continuity of surface1
	/// @param[in,out] parameters1 The maximum vector size is nDerivatives,
	/// each parameter means the norm ratio of each derivative.
	/// If no parameter, default parameter is used and the parameter is added to the vec
	/// @param[in] surf2 Surface2
	/// @param[in] isUIso2 Is surface2 connection curve a u isocurve
	/// @param[in] isFront2 Is surface2 connection curve a front isocurve
	/// @param[in] cont2 Connect geometric continuity of surface2
	/// @param[in,out] parameters2 Similar to parameters1
	/// @param[in] autoReverse Whether it is necessary to automatically
	/// reverse the direction of the surface to avoid distortion of the blend surface
	/// @param[in] isPrecise Is the result required to under tolerance
	/// @param[in] tol If not precise, tol is not used,
	/// else the elements int tol are, in order,
	/// C0 position tolerance, G1 normal angular tolerance in radians, G2 curvature relative error tolerance
	/// @param[in] config1 The config of surface1, including isocurve orientation and beginning parameter.
	/// The config parameters can be manualy set (isFixed=true) or automatically computed
	/// @param[in] config2 The config of surface2, similar to config1
	/// @return A blend surface
	[[nodiscard]] AMCAX_API static std::shared_ptr<Geom3BSplineSurface> BlendSurfaces(
		const std::shared_ptr<Geom3BSplineSurface>& surf1, bool isUIso1, bool isFront1, ContinuityType cont1, std::vector<double>& parameters1,
		const std::shared_ptr<Geom3BSplineSurface>& surf2, bool isUIso2, bool isFront2, ContinuityType cont2, std::vector<double>& parameters2,
		bool isPrecise, const std::vector<double>& tol, NURBSMatchSurfConfig config1, NURBSMatchSurfConfig config2);

	/// @brief Given two (trimmed or untrimmed) faces, a blend surface to connect the two faces is constructed
	/// @param[in] face1 The given face 1
	/// @param[in] edge1 The given edge 1, the edge is required to own a pcurve of face 1
	/// @param[in] cont1 Connect geometric continuity of face 1
	/// @param[in,out] parameters1 The maximum vector size is nDerivatives,
	/// each parameter means the norm ratio of each derivative.
	/// If no parameter, default parameter is used and the parameter is added to the vec
	/// @param[in] face2 The given face 2
	/// @param[in] edge2 The given edge 2, the edge is required to own a pcurve of face 2
	/// @param[in] cont2 Connect geometric continuity of face 2
	/// @param[in,out] parameters2 Similar to parameters1
	/// @param[in] autoReverse Whether it is necessary to automatically
	/// reverse the direction of the surface to avoid distortion of the blend surface
	/// @param[in] isPrecise Is the result required to under tolerance
	/// @param[in] tol If not precise, tol is not used,
	/// else the elements int tol are, in order,
	/// C0 position tolerance, G1 normal angular tolerance in radians, G2 curvature relative error tolerance
	/// @return A blend surface
	[[nodiscard]] AMCAX_API static std::shared_ptr<Geom3BSplineSurface> BlendFaces(
		const TopoFace& face1, const TopoEdge& edge1, ContinuityType cont1, std::vector<double>& parameters1,
		const TopoFace& face2, const TopoEdge& edge2, ContinuityType cont2, std::vector<double>& parameters2,
		bool autoReverse, bool isPrecise, const std::vector<double>& tol);

	/// @brief Given two (trimmed or untrimmed) faces, a blend surface to connect the two faces is constructed
	/// @param[in] face1 The given face 1
	/// @param[in] edge1 The given edge 1, the edge is required to own a pcurve of face 1
	/// @param[in] cont1 Connect geometric continuity of face 1
	/// @param[in,out] parameters1 The maximum vector size is nDerivatives,
	/// each parameter means the norm ratio of each derivative.
	/// If no parameter, default parameter is used and the parameter is added to the vec
	/// @param[in] face2 The given face 2
	/// @param[in] edge2 The given edge 2, the edge is required to own a pcurve of face 2
	/// @param[in] cont2 Connect geometric continuity of face 2
	/// @param[in,out] parameters2 Similar to parameters1
	/// @param[in] isPrecise Is the result required to under tolerance
	/// @param[in] tol If not precise, tol is not used,
	/// else the elements int tol are, in order,
	/// C0 position tolerance, G1 normal angular tolerance in radians, G2 curvature relative error tolerance
	/// @param[in] config1 The config of edge1, including edge orientation and beginning parameter.
	/// The config parameters can be manualy set (isFixed=true) or automatically computed
	/// @param[in] config2 The config of edge2, similar to config1
	/// @return A blend surface
	[[nodiscard]] AMCAX_API static std::shared_ptr<Geom3BSplineSurface> BlendFaces(
		const TopoFace& face1, const TopoEdge& edge1, ContinuityType cont1, std::vector<double>& parameters1,
		const TopoFace& face2, const TopoEdge& edge2, ContinuityType cont2, std::vector<double>& parameters2,
		bool isPrecise, const std::vector<double>& tol, NURBSMatchSurfConfig config1, NURBSMatchSurfConfig config2);
};
} // namespace AMCAX
