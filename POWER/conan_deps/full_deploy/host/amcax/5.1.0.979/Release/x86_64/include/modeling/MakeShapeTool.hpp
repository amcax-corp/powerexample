/// @file      MakeShapeTool.hpp
/// @brief     Class of tools for making shapes
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <list>

#include <common/PointT.hpp>
#include <math/GeometryMacros.hpp>
#include <topology/TopoEdge.hpp>

namespace AMCAX
{
#ifndef DOXYGEN_SKIP
class Adaptor3Curve;
class Geom2Curve;
class Geom3Plane;
class TopoFace;
class TopoShape;
class TopoSolid;
class ReShape;
#endif

/// @brief Class of tools for making shapes
/// @note Some of the function are for internal use only
class MakeShapeTool
{
public:
	/// @brief Build 3d curves for all the edges in a shape
	/// @param s The shape
	/// @return True if the computation succeed
	AMCAX_API static bool BuildCurves3d(const TopoShape& s);

	/// @brief Ensure the consistency of normal in the triangular meshes of a shape
	/// @param s The shape
	/// @param angTol The angular tolerance for checking normal direction
	/// @param forceComputeNormals Whether recompute the normal for the meshes
	/// @return True if the correction is done
	AMCAX_API static bool EnsureNormalConsistency(const TopoShape& s, double angTol = 0.001, bool forceComputeNormals = false);

	/// @brief Extend a face by a given length and extension directions
	/// @param[in] f The face to be extended
	/// @param[in] extVal The extension length
	/// @param[in] extUMin Set whether extending along the reversed U direction
	/// @param[in] extUMax Set whether extending along the forward U direction
	/// @param[in] extVMin Set whether extending along the reversed V direction
	/// @param[in] extVMax Set whether extending along the forward V direction
	/// @param[out] fExt The extended face
	AMCAX_API static void ExtendFace(const TopoFace& f, double extVal, bool extUMin, bool extUMax, bool extVMin, bool extVMax, TopoFace& fExt);

	/// @brief Sew faces to a shell
	/// @details The border edges are merged to common edges under a given tolerance.
	///          If some edges do not coincide, the related faces remain unsewed.
	/// @param shapes The shapes to be sewed
	/// @param tolerance The tolerance
	/// @return The sewed shape
	[[nodiscard]] AMCAX_API static TopoShape SewShape(const std::list<TopoShape>& shapes, double tolerance);

	/// @brief Update all the tolerances in a shape
	/// @details The tolerances of vertices will be not smaller than tolerances of their connected edges.
	///          The tolerances of edges will be not smaller than tolerances of their connected faces.
	/// @param s The shape
	/// @param verifyFaceTolerance Whether to verify face tolerance
	AMCAX_API static void UpdateTolerances(const TopoShape& s, bool verifyFaceTolerance = false);

#ifndef DOXYGEN_SKIP

	static void Precision(double p) noexcept;
	static double Precision() noexcept;
	static bool CheckSameRange(const TopoEdge& e, double tolerance = 1.0e-12) noexcept;
	static void SameRange(const TopoEdge& e, double tolerance = 1.0e-5);
	static bool BuildCurve3d(const TopoEdge& e, double tolerance = 1.0e-5, ContinuityType continuity = ContinuityType::C1, int maxDegree = 14, int maxSegment = 0);
	static bool BuildCurves3d(const TopoShape& s, double tolerance, ContinuityType continuity = ContinuityType::C1, int maxDegree = 14, int maxSegment = 0);
	static void BuildPCurveForEdgeOnPlane(const TopoEdge& e, const TopoFace& f);
	static void BuildPCurveForEdgeOnPlane(const TopoEdge& e, const TopoFace& f, std::shared_ptr<Geom2Curve>& c2d, bool& toUpdate);
	static void BuildPCurveForEdgesOnPlane(const std::list<TopoShape>& edgelist, const TopoFace& f);
	static bool UpdateEdgeTol(const TopoEdge& e, double minToleranceRequest, double maxToleranceToCheck);
	static bool UpdateEdgeTolerance(const TopoShape& s, double minToleranceRequest, double maxToleranceToCheck);
	static void SameParameter(const TopoEdge& e, double tol = 1.0e-5);
	static TopoEdge SameParameter(const TopoEdge& e, double tol, double& newTol, bool isUseOldEdge);
	static void SameParameter(const TopoShape& s, double tol = 1.0e-5, bool forced = false);
	static void SameParameter(const TopoShape& s, ReShape& reshaper, double tolerance = 1.0e-5, bool forced = false);
	static void UpdateTolerances(const TopoShape& s, ReShape& reshaper, bool verifyFaceTolerance = false);
	static void UpdateInnerTolerances(const TopoShape& s);
	static ContinuityType ContinuityOfFaces(const TopoEdge& edge, const TopoFace& face1, const TopoFace& face2, double angTol);
	static void EncodeRegularity(const TopoShape& s, double tolAng = 1.0e-10);
	static void EncodeRegularity(const TopoShape& s, const std::list<TopoShape>& edgelist, double tolAng = 1.0e-10);
	static void EncodeRegularity(const TopoEdge& e, const TopoFace& f1, const TopoFace& f2, double tolAng = 1.0e-10);
	static void SortFaces(const TopoShape& s, std::list<TopoShape>& facelist);
	static void ReverseSortFaces(const TopoShape& s, std::list<TopoShape>& facelist);
	static void UpdateDeflection(const TopoShape& s);
	static void BoundingVertex(const std::list<TopoShape>& vertexlist, Point3& newCenter, double& newTol);
	static bool FindValidRange(const Adaptor3Curve& curve, double tolE, double parV1, const Point3& ptV1, double tolV1, double parV2, const Point3& ptV2, double tolV2, double& first, double& last);
	static bool FindValidRange(const TopoEdge& e, double& first, double& last);

#endif

private:
	static double precision;
};
} // namespace AMCAX
