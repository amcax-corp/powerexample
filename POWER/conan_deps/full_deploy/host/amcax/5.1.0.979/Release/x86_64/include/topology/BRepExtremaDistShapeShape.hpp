/// @file      BRepExtremaDistShapeShape.hpp
/// @brief     Class of computing extremal distance between two shapes
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <vector>

#include <common/BoundingBox3.hpp>
#include <common/IndexSet.hpp>
#include <topology/BRepExtremaMacros.hpp>
#include <topology/TopoShape.hpp>

namespace AMCAX
{
#ifndef DOXYGEN_SKIP
class BRepExtremaSolution;
class BRepClassSolidClassifier;
class BRepExtremaDistContext;
#endif

/// @brief Class of computing extremal distance between two shapes
class BRepExtremaDistShapeShape
{
public:
	/// @brief Default constructor
	AMCAX_API BRepExtremaDistShapeShape();

	/// @brief Construct from two shapes
	/// @param shape1 The first shape
	/// @param shape2 The second shape
	AMCAX_API BRepExtremaDistShapeShape(const TopoShape& shape1, const TopoShape& shape2);

	/// @brief Construct from two shapes
	/// @param shape1 The first shape
	/// @param shape2 The second shape
	/// @param deflection The deflection tolerance
	AMCAX_API BRepExtremaDistShapeShape(const TopoShape& shape1, const TopoShape& shape2, double deflection);

	/// @brief Set the deflection tolerance
	/// @param deflection The deflection
	AMCAX_API void SetDeflection(double deflection) noexcept;

	/// @brief Load the first shape
	/// @param shape1 The first shape
	AMCAX_API void LoadS1(const TopoShape& shape1);

	/// @brief Load the second shape
	/// @param shape2 The second shape
	AMCAX_API void LoadS2(const TopoShape& shape2);

	/// @brief Perform the algorithm
	/// @return True if the algorithm succeed
	AMCAX_API bool Perform();

	/// @brief Is the algorithm done
	/// @return True if the algorithm is done
	[[nodiscard]] AMCAX_API bool IsDone() const noexcept;

	/// @brief Get the number of solutions
	/// @return The number of solutions
	[[nodiscard]] AMCAX_API int NSolution() const noexcept;

	/// @brief Get the extrema distance
	/// @return The distance
	[[nodiscard]] AMCAX_API double Value() const;

	/// @brief Is one shape in the other shape
	/// @return True if one shape is in the other shape
	[[nodiscard]] AMCAX_API bool InnerSolution() const noexcept;

	/// @brief Get the extrema point on the first shape at a given index
	/// @param n The index
	/// @return The extrema point
	[[nodiscard]] AMCAX_API const Point3& PointOnShape1(int n) const;

	/// @brief Get the extrema point on the second shape at a given index
	/// @param n The index
	/// @return The extrema point
	[[nodiscard]] AMCAX_API const Point3& PointOnShape2(int n) const;

	/// @brief Get the type of support of the first shape at a given index
	/// @param n The index
	/// @return The type of support
	[[nodiscard]] AMCAX_API BRepExtremaSupportType SupportTypeShape1(int n) const;

	/// @brief Get the type of support of the second shape at a given index
	/// @param n The index
	/// @return The type of support
	[[nodiscard]] AMCAX_API BRepExtremaSupportType SupportTypeShape2(int n) const;

	/// @brief Get the support shape of the first shape at a given index
	/// @param n The index
	/// @return The support shape
	[[nodiscard]] AMCAX_API TopoShape SupportOnShape1(int n) const;

	/// @brief Get the support shape of the second shape at a given index
	/// @param n The index
	/// @return The support shape
	[[nodiscard]] AMCAX_API TopoShape SupportOnShape2(int n) const;

	/// @brief Get the parameter of extrema on the edge of the first shape at a given index
	/// @param[in] n The index
	/// @param[out] t The parameter
	AMCAX_API void ParOnEdgeS1(int n, double& t) const;

	/// @brief Get the parameter of extrema on the edge of the second shape at a given index
	/// @param[in] n The index
	/// @param[out] t The parameter
	AMCAX_API void ParOnEdgeS2(int n, double& t) const;

	/// @brief Get the parameter of extrema on the face of the first shape at a given index
	/// @param[in] n The index
	/// @param[out] u The u parameter
	/// @param[out] v The v parameter
	AMCAX_API void ParOnFaceS1(int n, double& u, double& v) const;

	/// @brief Get the parameter of extrema on the face of the second shape at a given index
	/// @param[in] n The index
	/// @param[out] u The u parameter
	/// @param[out] v The v parameter
	AMCAX_API void ParOnFaceS2(int n, double& u, double& v) const;

private:
	bool DistanceMapMap(const IndexSet<TopoShape>& Set1, const IndexSet<TopoShape>& Set2, const std::vector<BoundingBox3>& Lbox1, const std::vector<BoundingBox3>& Lbox2, 
		std::shared_ptr<BRepExtremaDistContext>& context);
	bool DistanceVertVert(const IndexSet<TopoShape>& Set1, const IndexSet<TopoShape>& Set2);
	bool SolidTreatment(std::shared_ptr<BRepClassSolidClassifier> solidTool, const IndexSet<TopoShape>& shapeSet);

	double mDistRef;
	double mEps;
	bool isDone = false;
	bool isInnerSol = false;
	TopoShape mShape1;
	TopoShape mShape2;
	std::shared_ptr<std::vector<BRepExtremaSolution>> solutionsShape1;
	std::shared_ptr<std::vector<BRepExtremaSolution>> solutionsShape2;
	IndexSet<TopoShape> mSetV1;
	IndexSet<TopoShape> mSetV2;
	IndexSet<TopoShape> mSetE1;
	IndexSet<TopoShape> mSetE2;
	IndexSet<TopoShape> mSetF1;
	IndexSet<TopoShape> mSetF2;
	std::vector<BoundingBox3> boxV1;
	std::vector<BoundingBox3> boxV2;
	std::vector<BoundingBox3> boxE1;
	std::vector<BoundingBox3> boxE2;
	std::vector<BoundingBox3> boxF1;
	std::vector<BoundingBox3> boxF2;
	std::shared_ptr<BRepClassSolidClassifier> solidTool1 = nullptr;
	std::shared_ptr<BRepClassSolidClassifier> solidTool2 = nullptr;
};
} // namespace AMCAX
