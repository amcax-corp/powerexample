/// @file      BRepExtremaProximityTool.hpp
/// @brief     Tool class for detecting the proximity of two shapes
/// @copyright Copyright (c) 2024 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <vector>

#include <common/Precision.hpp>
#include <topology/TopoShape.hpp>

namespace AMCAX
{
/// @brief Tool class for detecting the proximity of two shapes. Note that the discretization algorithm is used internally, and the results are approximate
/// @details This method is used for quick judgment and filtering, and if the result returns false, indicating that there must be no intersection or overlap
class BRepExtremaProximityTool
{
public:
	/// @brief Empty constructor for proximity tool
	AMCAX_API BRepExtremaProximityTool();

	/// @brief Construct proximity tool from two shapes
	/// @param shape1 The first shape
	/// @param shape2 The second shape
	AMCAX_API BRepExtremaProximityTool(const TopoShape& shape1, const TopoShape& shape2) noexcept;

	/// @brief Load the shape of proximity tool
	/// @param shape1 The first shape
	/// @param shape2 The second shape
	AMCAX_API void LoadShapes(const TopoShape& shape1, const TopoShape& shape2) noexcept;

public:
	/// @brief Performs find faces of shape with finite overlapping areas
	/// @param[out] facesInShape The couples of faces with overlapping areas
	/// @param[in] tolerance The horizontal tolerance used for check overlaping
	/// @param[in] isOpposite The flag only keep faces with opposite normal directions
	/// @return true if two shape have overlapping faces
	AMCAX_API bool PerformOverlapFaces(std::vector<std::pair<TopoShape, TopoShape>>& facesInShape,
		double tolerance = Precision::Confusion(), bool isOpposite = false);

	/// @brief Performs find faces of shape with finite overlapping areas when the basic geometric overlap
	/// @param[out] facesInShape The couples of faces with overlapping areas
	/// @param[in] tolerance The confusion tolerance used for check overlaping
	/// @param[in] toleranceAngel The angular tolerance used for check overlaping
	/// @param[in] isOpposite The flag only keep faces with opposite normal directions
	/// @return true if two shape have overlapping faces
	AMCAX_API bool PerformOverlapFacesWithGeomCheck(std::vector<std::pair<TopoShape, TopoShape>>& facesInShape,
		double tolerance = Precision::Confusion(), double toleranceAngel = Precision::Angular(), bool isOpposite = false);

	/// @brief Performs find intersecting faces of shape
	/// @param[out] facesInShape The couple of faces which intersect with each other
	/// @param[in] tolerance The tolerance used for check intersection
	/// @return true if two shape have intersecting faces
	AMCAX_API bool PerformIntersectionFaces(std::vector<std::pair<TopoShape, TopoShape>>& facesInShape, double tolerance = Precision::Confusion());

	/// @brief Compute the approximate hausdorff distance with two shape
	/// @details The hausdorff distance H(S1, S2) = max(maxmin||S1 - S2||, maxmin||S2 - S1||);
	/// @param[out] hdProxDistance The result approximate hausdorff distance
	/// @return true if perform successfully
	AMCAX_API bool PerformProximityValue(double& hdProxDistance);

private:
	bool CheckInputShape() const;

	TopoShape mInputShape1;
	TopoShape mInputShape2;
	std::vector<TopoShape> mShapeVector1;
	std::vector<TopoShape> mShapeVector2;
};
} // namespace AMCAX
