/// @file      MakeChamfer.hpp
/// @brief     The class of chamfer
/// @details   This class performs chamfer on a given shape.
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <unordered_set>

#include <fillet/ChamferFilletMacros.hpp>
#include <fillet/MakeChamferFilletBase.hpp>

namespace AMCAX
{
#ifndef DOXYGEN_SKIP
class ChFi3dChamferBuilder;
class TopOpBRepBuildHBuilder;
class TopoFace;
#endif

/// @brief The class of chamfer
class AMCAX_CLASS_API MakeChamfer : public MakeChamferFilletBase
{
public:
	/// @brief Initialize the algorithm by setting the given shape
	/// @param s The given shape
	AMCAX_API explicit MakeChamfer(const TopoShape& s);

	/// @brief Add an edge used to build chamfers, parameters should be set later
	/// @param e The edge used to build chamfers
	AMCAX_API void Add(const TopoEdge& e) override;

	/// @brief Add an edge used to build chamfers with the same distance to both sides of the edge (symmetric chamfer)
	/// @param dist The distance parameter
	/// @param e The edge used to build chamfers
	AMCAX_API void Add(double dist, const TopoEdge& e);

	/// @brief Set the distance from the edge on a face in the i-th contour
	/// @param dist The distance parameter
	/// @param i The index of contour
	/// @param f The face where the chamfer distance set
	AMCAX_API void SetDist(double dist, int i, const TopoFace& f);

	/// @brief Get the distance parameter in the i-th contour
	/// @param[in] i The index of contour
	/// @param[out] dist The distance parameter
	AMCAX_API void GetDist(int i, double& dist) const;

	/// @brief Add an edge used to build chamfers with two distance parameters on the given face and the face of opposite side
	/// @param dist1 The distance parameter on the given face
	/// @param dist2 The distance parameter on the face of opposite side
	/// @param e The edge used to build chamfers
	/// @param f The face for the first distance parameter
	AMCAX_API void Add(double dist1, double dist2, const TopoEdge& e, const TopoFace& f);

	/// @brief Set the distance parameters for the i-th contour
	/// @param dist1 The distance parameter on the given face
	/// @param dist2 The distance parameter on the face of opposite side
	/// @param i The index of contour
	/// @param f The face for the first distance parameter
	AMCAX_API void SetDists(double dist1, double dist2, int i, const TopoFace& f);

	/// @brief Get the distance parameters of the i-th contour
	/// @param[in] i The index of contour
	/// @param[out] dist1 The first distance parameter
	/// @param[out] dist2 The second distance parameter
	AMCAX_API void GetDists(int i, double& dist1, double& dist2) const;

	/// @brief Add an edge used to build chamfers with a distance parameter and an angle parameter corresponding to a face
	/// @param dist The distance parameter on the given face
	/// @param angle The angle parameter on the given face
	/// @param e The edge used to build chamfers
	/// @param f The reference face for the dist and angle
	AMCAX_API void AddDistAngle(double dist, double angle, const TopoEdge& e, const TopoFace& f);

	/// @brief Set the distance and angle parameters for the i-th contour
	/// @param dist The distance parameter on the given face
	/// @param angle The angle parameter on the given face
	/// @param i The index of contour
	/// @param f The reference face for the dist and angle
	AMCAX_API void SetDistAngle(double dist, double angle, int i, const TopoFace& f);

	/// @brief Get the distance and angle paramter for the i-th contour
	/// @param[in] i The index of contour
	/// @param[out] dist The distance parameter
	/// @param[out] angle The angle parameter
	AMCAX_API void GetDistAngle(int i, double& dist, double& angle) const;

	/// @brief Set the mode of chamfer
	/// @param mode The mode of chamfer
	AMCAX_API void SetMode(ChamferMode mode);

	/// @brief Get the status that whether the i-th contour is symmetric
	/// @param i The index of contour
	/// @return True if the contour is symmetric
	[[nodiscard]] AMCAX_API bool IsSymetric(int i) const;

	/// @brief Get the status that whether the i-th contour is built with two distance
	/// @param i The index of contour
	/// @return True if the contour is built with two distance
	[[nodiscard]] AMCAX_API bool IsTwoDistances(int i) const;

	/// @brief Get the status that whether the i-th contour is build with distance and angle
	/// @param i The index of contour
	/// @return True if the contour is built with distance and angle
	[[nodiscard]] AMCAX_API bool IsDistanceAngle(int i) const;

	/// @brief Reset the parameters of the i-th contour
	/// @param i The index of contour
	AMCAX_API void ResetContour(int i) override;

	/// @brief Get the number of contours
	/// @return The number of contours
	[[nodiscard]] AMCAX_API int NContours() const override;

	/// @brief Get the index of contour that contains the given edge. If the edge is not contained by any contours, returns -1
	/// @param e The given edge
	/// @return The index of contour that contains the given edge
	[[nodiscard]] AMCAX_API int Contour(const TopoEdge& e) const override;

	/// @brief Get the number of edges in the i-th contour
	/// @param i The index of contour
	/// @return The number of edges
	[[nodiscard]] AMCAX_API int NEdges(int i) const override;

	/// @brief Get the j-th edge in the i-th contour
	/// @param i The index of edge
	/// @param j The index of contour
	/// @return The j-th edge in the i-th contour
	[[nodiscard]] AMCAX_API const TopoEdge& Edge(int i, int j) const override;

	/// @brief Remove the contour containing a given edge
	/// @param e The given edge
	AMCAX_API void Remove(const TopoEdge& e) override;

	/// @brief Get the length of the i-th contour
	/// @param i The index of contour
	/// @return The length of contour
	[[nodiscard]] AMCAX_API double Length(int i) const override;

	/// @brief Get the first vertex of the i-th contour
	/// @param i The index of contour
	/// @return The first vertex of contour
	[[nodiscard]] AMCAX_API TopoVertex FirstVertex(int i) const override;

	/// @brief Get the last vertex of the i-th contour
	/// @param i The index of contour
	/// @return The last vertex of contour
	[[nodiscard]] AMCAX_API TopoVertex LastVertex(int i) const override;

	/// @brief Get the abscissa of a vertex on the i-th contour
	/// @param i The index of contour
	/// @param v The given vertex
	/// @return The abscissa of vertex
	[[nodiscard]] AMCAX_API double Abscissa(int i, const TopoVertex& v) const override;

	/// @brief Get the relative abscissa of a vertex on the i-th contour, range in [0, 1]
	/// @param i The index of contour
	/// @param v The given vertex
	/// @return The relative abscissa of vertex
	[[nodiscard]] AMCAX_API double RelativeAbscissa(int i, const TopoVertex& v) const override;

	/// @brief Get the status that whether the i-th contour is closed and tangent
	/// @param i The index of contour
	/// @return Whether the contour is closed and tangent
	[[nodiscard]] AMCAX_API bool ClosedAndTangent(int i) const override;

	/// @brief Get the status that whether the i-th contour is closed
	/// @param i The index of contour
	/// @return Whether the contour is closed
	[[nodiscard]] AMCAX_API bool Closed(int i) const override;

	/// @brief Perform the chamfer algorithm
	AMCAX_API void Build() override;

	/// @brief Reset the building state
	AMCAX_API void Reset() override;

#ifndef DOXYGEN_SKIP

	[[nodiscard]] std::shared_ptr<TopOpBRepBuildHBuilder> Builder() const;

#endif

	[[nodiscard]] AMCAX_API const std::list<TopoShape>& Generated(const TopoShape& s) override;
	[[nodiscard]] AMCAX_API const std::list<TopoShape>& Modified(const TopoShape& s) override;
	[[nodiscard]] AMCAX_API bool IsDeleted(const TopoShape& f) override;

	/// @brief Simulate the i-th contour computation for fast preview
	/// @param i The index of contour
	AMCAX_API void Simulate(int i) override;

	/// @brief Get the number of surfaces in the i-th contour
	/// @param i The index of contour
	/// @return The number of surfaces
	[[nodiscard]] AMCAX_API int NSurf(int i) const override;

private:
	std::shared_ptr<ChFi3dChamferBuilder> builder;
	std::unordered_set<TopoShape> shapes;
};
} // namespace AMCAX
