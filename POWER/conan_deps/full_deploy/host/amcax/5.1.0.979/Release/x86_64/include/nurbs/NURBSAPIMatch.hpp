/// @file      NURBSAPIMatch.hpp
/// @brief     The class of NURBS matching
/// @copyright Copyright (c) 2024 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <vector>

#include <common/VectorT.hpp>
#include <math/GeometryMacros.hpp>
#include <nurbs/NURBSMatchSurfConfig.hpp>
#include <topology/TopoEdge.hpp>
#include <topology/TopoFace.hpp>

namespace AMCAX
{
class Geom3BSplineCurve;
class Geom3BSplineSurface;

/// @brief Class of matching a curve/surface to connect the other curve/surface
/// @details This class computes the result surface of modifing a surface boundary to connect with another surface or face boundary within given geometric continuity tolerance
class NURBSAPIMatch
{
public:
	/// @brief Match a curve to connect the other curve
	/// @param cont Connect geometric continuity of curves
	/// @param curve The source curve
	/// @param isFront The front or back end of the source curve
	/// @param targetCurve The target curve
	/// @param isTargetFront The front or back end of the target curve
	/// @param otherEndCont Keep the source non-connection end continuity when modifying the curve
	/// @return The modified source curve
	[[nodiscard]] AMCAX_API static std::shared_ptr<Geom3BSplineCurve> MatchCurve(
		ContinuityType cont,
		const std::shared_ptr<Geom3BSplineCurve>& curve, bool isFront,
		const std::shared_ptr<Geom3BSplineCurve>& targetCurve, bool isTargetFront,
		int otherEndCont);

	/// @brief Match a curve to connect the other curve
	/// @param[in] cont Connection geometric continuity of curves
	/// @param[in] curve The source curve
	/// @param[in] isFront The front or back end of the source curve
	/// @param[in] targetCurve The target curve
	/// @param[in] isTargetFront The front or back end of the target curve
	/// @param[in] otherEndCont Keep the source non-connection end continuity when modifying the curve
	/// @param[in,out] params The desired continuity parameter
	/// @return The modified source curve
	[[nodiscard]] AMCAX_API static std::shared_ptr<Geom3BSplineCurve> MatchCurve(
		ContinuityType cont,
		const std::shared_ptr<Geom3BSplineCurve>& curve, bool isFront,
		const std::shared_ptr<Geom3BSplineCurve>& targetCurve, bool isTargetFront,
		int otherEndCont,
		std::vector<double>& params);

	/// @brief Make two curves from C0 to G1 or G2
	/// @param[in] cont Connection geometric continuity of curves
	/// @param[in] curve The source curve
	/// @param[in] isFront The front or back end of the source curve
	/// @param[in] targetCurve The target curve
	/// @param[in] isTargetFront The front or back end of the target curve
	/// @param[in] tol The tolerance
	/// @return The modified source curve
	[[nodiscard]] AMCAX_API static std::shared_ptr<Geom3BSplineCurve> MakeCurvesFromC0ToGN(
		ContinuityType cont,
		const std::shared_ptr<Geom3BSplineCurve>& curve, bool isFront,
		const std::shared_ptr<Geom3BSplineCurve>& targetCurve, bool isTargetFront,
		double tol);

	/// @brief Match the curve to connect the face boundary
	/// @param[in] cont Connection geometric continuity
	/// @param[in] curve The source curve
	/// @param[in] isFront The front or back end of the source curve
	/// @param[in] face The target face
	/// @param[in] edge The connection edge on the target face
	/// @param[in] connectionParam The connection parameter on the edge of the target face
	/// @param[in] otherEndCont Keep the source non-connection end continuity when modifying the curve
	/// @param[in,out] params The desired continuity parameter
	/// @return The modified source curve
	[[nodiscard]] AMCAX_API static std::shared_ptr<Geom3BSplineCurve> MatchCurveWithFaceBound(
		ContinuityType cont,
		const std::shared_ptr<Geom3BSplineCurve>& curve, bool isFront,
		const TopoFace& face, const TopoEdge& edge, double connectionParam,
		int otherEndCont,
		std::vector<double>& params);

	/// @brief Match curves with each other. Two curves connect on the middle of the curve ends
	/// @param cont Connect geometric continuity of curves
	/// @param curve The curve1
	/// @param isFront The front or back end of the curve1
	/// @param targetCurve The curve2
	/// @param isTargetFront The front or back end of the curve2
	/// @param otherEndCont Keep the source non-connection end continuity when modifying the curve
	/// @return The modified two curves
	[[nodiscard]] AMCAX_API static std::pair<std::shared_ptr<Geom3BSplineCurve>, std::shared_ptr<Geom3BSplineCurve>>
	MatchCurveWithEachOther(
		ContinuityType cont,
		const std::shared_ptr<Geom3BSplineCurve>& curve, bool isFront,
		const std::shared_ptr<Geom3BSplineCurve>& targetCurve, bool isTargetFront,
		int otherEndCont);

	/// @brief Match curves with each other. Two curves connect on the middle of the curve ends
	/// @param[in] cont Connect geometric continuity of curves
	/// @param[in] curve The curve1
	/// @param[in] isFront The front or back end of the curve1
	/// @param[in] targetCurve The curve2
	/// @param[in] isTargetFront The front or back end of the curve2
	/// @param[in] otherEndCont Keep the source non-connection end continuity when modifying the curve
	/// @param[in,out] params The desired continuity parameter
	/// @return The modified two curves
	[[nodiscard]] AMCAX_API static std::pair<std::shared_ptr<Geom3BSplineCurve>, std::shared_ptr<Geom3BSplineCurve>>
	MatchCurveWithEachOther(
		ContinuityType cont,
		const std::shared_ptr<Geom3BSplineCurve>& curve, bool isFront,
		const std::shared_ptr<Geom3BSplineCurve>& targetCurve, bool isTargetFront,
		int otherEndCont,
		std::vector<double>& params);

	/// @brief Match a surface with another surface to reach geometric continuity
	/// @param[in] surf The source surface to modify
	/// @param[in] isModifyU Is modify u isocurve
	/// @param[in] isFront Is modify front isocurve
	/// @param[in] targetSurf The target surface
	/// @param[in] isTargetU Is target u isocurve
	/// @param[in] isTargetFront Is target front isocurve
	/// @param[in] connectCont Connection cont, C0, G1 or G2
	/// @param[in] otherEndCont Keep the other end continuity when modifying source surface
	/// @param[in] isPrecise Is the result required to under tolerance
	/// @param[in] tol If not precise, tol is not used, else the elements int tol are, in order,
	/// C0 position tolerance, G1 normal angular tolerance in radians, G2 curvature relative error tolerance
	/// @param[in,out] params The desired continuity parameter
	/// @param[in] isEachOther Are both surfaces modified
	/// @param[in] surfConfig The surf match config including begin param and isReverse
	/// @param[in] targetSurfConfig The target surf match config including begin param and isReverse
	/// @return If isEachOther = true, return modified surf and targetSurf, else return modified surf
	[[nodiscard]] AMCAX_API static std::vector<std::shared_ptr<Geom3BSplineSurface>> MatchSurf(
		const std::shared_ptr<Geom3BSplineSurface> surf, bool isModifyU, bool isFront,
		const std::shared_ptr<Geom3BSplineSurface>& targetSurf, bool isTargetU, bool isTargetFront,
		ContinuityType connectCont,
		int otherEndCont,
		bool isPrecise,
		const std::vector<double>& tol,
		std::vector<double>& params,
		bool isEachOther,
		const NURBSMatchSurfConfig& surfConfig,
		const NURBSMatchSurfConfig& targetSurfConfig);

	/// @brief Judge whether the edge is a part of the natural boundary of Face
	/// @param face The face which contains the edge
	/// @param edge The edge
	/// @return Is the edge a part of the natural boundary of Face
	[[nodiscard]] AMCAX_API static bool IsNaturalBound(const TopoFace& face, const TopoEdge& edge);

	/// @brief  Match a face with another face to reach geometric continuity
	/// @param[in] face1 The source face to modify
	/// @param[in] edge1 The chosen edge of face1, it should be untrimmed (unmodified) surface boundary
	/// @param[in] face2 The target face to match
	/// @param[in] edge2 The chosen edge of face2, trimmed or untrimmed. When isEachOther = true, it should be untrimmed
	/// @param[in] connectCont Connection cont, C0, G1 or G2
	/// @param[in] otherEndCont Keep the other end continuity when modifying source surface
	/// @param[in] isPrecise Is the result required to under tolerance
	/// @param[in] tol If not precise, tol is not used, else the elements int tol are, in order,
	/// C0 position tolerance, G1 normal angular tolerance in radians, G2 curvature relative error tolerance
	/// @param[in,out] params The desired continuity parameter
	/// @param[in] isEachOther Are both faces modified. Only when both edges are untrimmed it is allowed to be true.
	/// @param[in] surf1Config The surf match config including begin param and isReverse
	/// @param[in] surf2Config The target surf match config including begin param and isReverse
	/// @return If isEachOther = true, return modified face1 and face2, else return modified face1
	[[nodiscard]] AMCAX_API static std::vector<TopoFace> MatchFace(
		const TopoFace& face1, const TopoEdge& edge1,
		const TopoFace& face2, const TopoEdge& edge2,
		ContinuityType connectCont,
		int otherEndCont,
		bool isPrecise,
		const std::vector<double>& tol,
		std::vector<double>& params,
		bool isEachOther,
		const NURBSMatchSurfConfig& surf1Config,
		const NURBSMatchSurfConfig& surf2Config);
};
} // namespace AMCAX
