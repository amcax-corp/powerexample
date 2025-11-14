/// @file      MakeFillet.hpp
/// @brief     The class of fillet
/// @details   This class performs fillet on a given shape.
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <unordered_set>

#include <common/PointT.hpp>
#include <fillet/ChamferFilletMacros.hpp>
#include <fillet/MakeChamferFilletBase.hpp>
#include <math/GeometryMacros.hpp>

namespace AMCAX
{
#ifndef DOXYGEN_SKIP
class ChFi3dFilletBuilder;
class Geom3Surface;
class LawFunction;
class TopOpBRepBuildHBuilder;
#endif

/// @brief The class of fillet
class AMCAX_CLASS_API MakeFillet : public MakeChamferFilletBase
{
public:
	/// @brief Initialize the algorithm by setting a given shape and the type of fillet
	/// @param s The given shape
	/// @param fiShape Type of fillet shape
	AMCAX_API explicit MakeFillet(const TopoShape& s, FilletShapeType fiShape = FilletShapeType::Rational);

	/// @brief Set the tolerance parameters
	/// @param tolang Angle tolerance
	/// @param tolesp 3d tolerance
	/// @param tol2d 2d tolerance
	/// @param tolApp3d 3d tolerance in approximation
	/// @param tolApp2d 2d tolerance in approximation
	/// @param fleche
	AMCAX_API void SetParams(double tolang, double tolesp, double tol2d, double tolApp3d, double tolApp2d, double fleche);

	/// @brief Set the continuity and tolerace
	/// @param internalContinuity The continuity of fillet
	/// @param angularTolerance The tolerance used for G1 continuity
	AMCAX_API void SetContinuity(ContinuityType internalContinuity, double angularTolerance);

	/// @brief Add an edge to the fillet
	/// @details The radius must be set later
	/// @param e The edge
	AMCAX_API void Add(const TopoEdge& e) override;

	/// @brief Add an edge with a radius to the fillet
	/// @param r The radius
	/// @param e The edge
	AMCAX_API void Add(double r, const TopoEdge& e);

	/// @brief Add an edge with a linear varying radius
	/// @param r1 The start radius
	/// @param r2 The end radius
	/// @param e The edge to be fillet
	AMCAX_API void Add(double r1, double r2, const TopoEdge& e);

#ifndef DOXYGEN_SKIP

	void Add(const std::shared_ptr<LawFunction>& L, const TopoEdge& E);

#endif

	/// @brief Add an edge with a varying radius control by the parameter-radius pairs
	/// @param UandR The pair values of parameter and radius
	/// @param e The edge
	AMCAX_API void Add(const std::vector<Point2>& UandR, const TopoEdge& e);

	/// @brief Set the radius of the contour at given index
	/// @param r The radius
	/// @param ic The index of contour
	/// @param idxInSpine The index of edge in the contour
	AMCAX_API void SetRadius(double r, int ic, int idxInSpine);

	/// @brief Set the linear varying radius of the contour at given index
	/// @param r1 The start radius
	/// @param r2 The end radius
	/// @param ic The index of contour
	/// @param idxInSpine The index of edge in the contour
	AMCAX_API void SetRadius(double r1, double r2, int ic, int idxInSpine);

#ifndef DOXYGEN_SKIP

	void SetRadius(const std::shared_ptr<LawFunction>& L, int IC, int IinC);

#endif

	/// @brief Set the radius of the contour at a given index with parameter-radius pairs
	/// @param UandR The pair values of parameter and radius
	/// @param ic The index of contour
	/// @param idxInSpine The index of edge in the contour
	AMCAX_API void SetRadius(const std::vector<Point2>& UandR, int ic, int idxInSpine);

	/// @brief Reset the contour at a given index
	/// @param ic The index of contour
	AMCAX_API void ResetContour(int ic) override;

	/// @brief Is the contour has a constant radius
	/// @param ic The index of contour
	/// @return True if the contour has a constant radius
	[[nodiscard]] AMCAX_API bool IsConstant(int ic);

	/// @brief Get the radius of the contour at a given index
	/// @param ic The index of contour
	/// @return The radius
	[[nodiscard]] AMCAX_API double Radius(int ic);

	/// @brief Is the edge in a contour has a constant radius
	/// @param ic The index of contour
	/// @param e The edge
	/// @return True if the edge is in the contour and has a constant radius
	[[nodiscard]] AMCAX_API bool IsConstant(int ic, const TopoEdge& e);

	/// @brief Get the radius of edge in the contour of given index
	/// @param ic The index of contour
	/// @param e The edge
	/// @return The radius
	[[nodiscard]] AMCAX_API double Radius(int ic, const TopoEdge& e);

	/// @brief Set the radius of edge in the contour of given index
	/// @param radius the radius
	/// @param ic The index of contour
	/// @param e The edge
	AMCAX_API void SetRadius(double radius, int ic, const TopoEdge& e);

	/// @brief Set the radius of a vertex in the contour of given index
	/// @param radius The radius
	/// @param ic The index of contour
	/// @param v The vertex
	AMCAX_API void SetRadius(double radius, int ic, const TopoVertex& v);

	/// @brief Get the radius bounds of the radius of an edge in a contour
	/// @param ic The index of contour
	/// @param e The edge
	/// @param f The first radius
	/// @param l The last radius
	/// @return True if the edge has a radius bound
	AMCAX_API bool GetBounds(int ic, const TopoEdge& e, double& f, double& l);

#ifndef DOXYGEN_SKIP

	[[nodiscard]] std::shared_ptr<LawFunction> GetLaw(int IC, const TopoEdge& E);

	void SetLaw(int IC, const TopoEdge& E, const std::shared_ptr<LawFunction>& L);

#endif

	/// @brief Set the type of fillet shape
	/// @param fShape Type of fillet shape
	AMCAX_API void SetFilletShape(FilletShapeType fShape);

	/// @brief Get the type of fillet shape
	/// @return Type of fillet shape
	[[nodiscard]] AMCAX_API FilletShapeType GetFilletShape() const;

	[[nodiscard]] AMCAX_API int NContours() const override;
	[[nodiscard]] AMCAX_API int Contour(const TopoEdge& e) const override;
	[[nodiscard]] AMCAX_API int NEdges(int i) const override;
	[[nodiscard]] AMCAX_API const TopoEdge& Edge(int i, int j) const override;
	AMCAX_API void Remove(const TopoEdge& e) override;
	[[nodiscard]] AMCAX_API double Length(int ic) const override;
	[[nodiscard]] AMCAX_API TopoVertex FirstVertex(int ic) const override;
	[[nodiscard]] AMCAX_API TopoVertex LastVertex(int ic) const override;
	[[nodiscard]] AMCAX_API double Abscissa(int ic, const TopoVertex& v) const override;
	[[nodiscard]] AMCAX_API double RelativeAbscissa(int ic, const TopoVertex& v) const override;
	[[nodiscard]] AMCAX_API bool ClosedAndTangent(int ic) const override;
	[[nodiscard]] AMCAX_API bool Closed(int ic) const override;
	AMCAX_API void Build() override;
	AMCAX_API void Reset() override;

#ifndef DOXYGEN_SKIP

	[[nodiscard]] std::shared_ptr<TopOpBRepBuildHBuilder> Builder() const;

#endif

	[[nodiscard]] AMCAX_API const std::list<TopoShape>& Generated(const TopoShape& s) override;
	[[nodiscard]] AMCAX_API const std::list<TopoShape>& Modified(const TopoShape& s) override;
	[[nodiscard]] AMCAX_API bool IsDeleted(const TopoShape& s) override;

	/// @brief Get the number of generated surfaces of the fillet
	/// @return The number of generated surfaces
	[[nodiscard]] AMCAX_API int NSurfaces() const;

	/// @brief Get the faces for the surface of a given index
	/// @param i The index of surface
	/// @return The list of face
	[[nodiscard]] AMCAX_API const std::list<TopoShape>& NewFaces(int i);

	AMCAX_API void Simulate(int ic) override;
	[[nodiscard]] AMCAX_API int NSurf(int ic) const override;

	/// @brief Get the number of contours failed to perform fillet
	/// @return The number of failed contours
	[[nodiscard]] AMCAX_API int NFaultyContours() const;

	/// @brief Get the contour failed to perform fillet at a given index
	/// @param i The index of failed contour
	/// @return The index of contour
	[[nodiscard]] AMCAX_API int FaultyContour(int i) const;

	/// @brief Get the number of computed surfaces on the given index of contour
	/// @param ic The index of contour
	/// @return The number of computed surfaces
	[[nodiscard]] AMCAX_API int NComputedSurfaces(int ic) const;

	/// @brief Get the computed surface of given index
	/// @param ic The index of contour
	/// @param isurf The index of surface in the contour
	/// @return The computed surface
	[[nodiscard]] AMCAX_API std::shared_ptr<Geom3Surface> ComputedSurface(int ic, int isurf) const;

	/// @brief Get the number of vertices failed to perform fillet
	/// @return The number of failed vertices
	[[nodiscard]] AMCAX_API int NFaultyVertices() const;

	/// @brief Get the vertex failed to perform fillet of a given index
	/// @param iv The index of failed vertex
	/// @return The failed vertex
	[[nodiscard]] AMCAX_API TopoVertex FaultyVertex(int iv) const;

	/// @brief Are some partial results generated
	/// @return True if the algorithm has some intermediate result
	[[nodiscard]] AMCAX_API bool HasResult() const;

	/// @brief Get the bad partial result
	/// @return The partial result
	[[nodiscard]] AMCAX_API TopoShape BadShape() const;

	/// @brief Get the error status of the contour of given index
	/// @param ic The index of contour
	/// @return The error status
	[[nodiscard]] AMCAX_API ChamferFilletErrorStatus StripeStatus(int ic) const;

private:
	std::shared_ptr<ChFi3dFilletBuilder> builder;
	std::unordered_set<TopoShape> myMap;
};
} // namespace AMCAX
