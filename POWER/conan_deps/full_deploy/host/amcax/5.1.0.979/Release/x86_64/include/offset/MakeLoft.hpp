/// @file      MakeLoft.hpp
/// @brief     Class of making a lofting shape
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <unordered_map>
#include <vector>

#include <approx/ApproxParameterizationType.hpp>
#include <math/GeometryMacros.hpp>
#include <modeling/MakeShape.hpp>
#include <topology/TopoVertex.hpp>
#include <topology/TopoFace.hpp>

namespace AMCAX
{
#ifndef DOXYGEN_SKIP
class BRepFillGenerator;
class Geom3BSplineSurface;
class TopoWire;
class TopoVertex;
class TopoShape;
#endif

/// @brief Class of making a lofting shape
/// @details Create a shell or solid to go through the sequential input shapes.
///          Only the first and the last shapes can be degenerated (vertex).
///          The others must be a wire which is not required to lie on a plane or have same number of edges.
///          The steps are:
///          1. MakeLoft(): Set params
///          2. AddWire() or AddVertex(): Add input shapes
///          3. Build(): Perform
class AMCAX_CLASS_API MakeLoft : public MakeShape
{
public:
	/// @brief Construct from parameters
	/// @param isSolid The result is shell or solid
	/// @param ruled If true, smoothness and section normals are not considered when constructing surfaces,
	///              which makes the result be developable.
	///              If not, smoothness and segment normals are considered. Meanwhile approximation is applied to smooth the result,
	///              which might make the result shape do not strictly go through the sections.
	/// @param pres3d approximation tol
	AMCAX_API explicit MakeLoft(bool isSolid = false, bool ruled = false, double pres3d = 1.0e-06);

	/// @brief Initialize loft parameters
	/// @param isSolid The result is shell or solid
	/// @param ruled If true, smoothness and section normals are not considered when constructing surfaces,
	///              which makes the result be developable.
	///              If not, smoothness and segment normals are considered. Meanwhile approximation is applied to smooth the result,
	///              which might make the result shape do not strictly go through the sections.
	/// @param pres3d approximation tol
	AMCAX_API void Init(bool isSolid = false, bool ruled = false, double pres3d = 1.0e-06);

	/// @brief Add a wire
	/// @param wire The wire
	AMCAX_API void AddWire(const TopoWire& wire);

	#ifndef DOXYGEN_SKIP
	/// @brief Add a vector of specified points
	/// @details The number and order of the specified points should be consistent with the number and order of the wires,
	///			 and each specified point should lie on its corresponding wire.
	/// @param vector of the specified points
	AMCAX_TEST_API void AddMapVertex(const std::vector<TopoVertex>& userVertices = std::vector<TopoVertex>());
	#endif

	/// @brief Add a vertex
	/// @param v The vertex
	AMCAX_API void AddVertex(const TopoVertex& v);

	/// @brief Set whether to check compatibility or not
	/// @details Making the number of edges of each wire to be the same and
	///          computing origin (only closed) and orientation to make result avoid twisted results
	AMCAX_API void CheckCompatibility(bool check = true);

	/// @brief Set the algorithm whether to use smoothing or not during the approximation
	/// @param useSmoothing Whether to use smoothing
	AMCAX_API void SetSmoothing(bool useSmoothing);

	/// @brief Set the parameterization type
	/// @param parType Type of parameterzation used in approximation
	AMCAX_API void SetParType(ApproxParameterizationType parType);

	/// @brief Set the continuity of approximation
	/// @param c The type of continuity
	AMCAX_API void SetContinuity(ContinuityType c);

	/// @brief Set the weights in optimization
	/// @param w1 The weight of length
	/// @param w2 The weight of curvature
	/// @param w3 The weight of torsion
	AMCAX_API void SetCriterionWeight(double w1, double w2, double w3);

	/// @brief Set the maximum u degree of the lofting surface
	/// @param maxDeg The maximum u degree of the lofting surface
	AMCAX_API void SetMaxDegree(int maxDeg);

	/// @brief Get the parameterization type
	[[nodiscard]] AMCAX_API ApproxParameterizationType ParType() const;

	/// @brief Get the continuity of approximation
	[[nodiscard]] AMCAX_API ContinuityType Continuity() const;

	/// @brief Get the maximum u degree of the lofting surface
	[[nodiscard]] AMCAX_API int MaxDegree() const;

	/// @brief Get the flag of whether to use smooth or not
	[[nodiscard]] AMCAX_API bool UseSmoothing() const;

	/// @brief Get the weights in approx optimization
	/// @param[out] w1 The weight of length
	/// @param[out] w2 The weight of curvature
	/// @param[out] w3 The weight of torsion
	AMCAX_API void CriteriumWeight(double& w1, double& w2, double& w3) const;

	AMCAX_API void Build() override;

	/// @brief Get the bottom shape of solid
	[[nodiscard]] AMCAX_API const TopoShape& FirstShape() const;

	/// @brief Get the top shape of solid
	[[nodiscard]] AMCAX_API const TopoShape& LastShape() const;

	/// @brief If ruled, returns the face generated by the edge
	[[nodiscard]] AMCAX_API TopoShape GeneratedFace(const TopoShape& Edge) const;

	/// @brief Set if the input shape can be modified
	/// @param isMutableInput Whether the shape can be modified
	AMCAX_API void SetMutableInput(bool isMutableInput);

	[[nodiscard]] AMCAX_API const std::list<TopoShape>& Generated(const TopoShape& S) override;

	/// @brief Get the input shapes
	[[nodiscard]] AMCAX_API const std::list<TopoShape>& Wires() const;

private:
	void CreateRuled();
	void CreateSmoothed();
	std::shared_ptr<Geom3BSplineSurface> TotalSurf(const std::vector<TopoShape>& shapes, int NbSect, int NbEdges, bool w1Point, bool w2Point, bool vClosed) const;

	std::list<TopoShape> inputWires;
	std::vector<TopoShape> wires;
	std::vector<std::vector<TopoVertex>> myMapVertex;
	std::unordered_map<TopoShape, std::list<int>> edgeNewIndices;
	std::unordered_map<TopoShape, int> vertexIndex;
	int nEdgesInSection = 0;
	int degreeMax = 9;
	bool isSolid;
	bool isRuled;
	bool isDegen1 = false;
	bool isDegen2 = false;
	bool wCheck = true;
	bool useSmoothing = false;
	bool isMutableInput = true;
	double pres3d;
	TopoFace first;
	TopoFace last;
	std::unordered_map<TopoShape, TopoShape> edgeFaceMap;
	ContinuityType continuity = ContinuityType::C2;
	ApproxParameterizationType paramType = ApproxParameterizationType::ChordLength;
	double critWeights[3] = {0.4, 0.2, 0.4};
	std::shared_ptr<BRepFillGenerator> brepfillGenerator;
};
} // namespace AMCAX
