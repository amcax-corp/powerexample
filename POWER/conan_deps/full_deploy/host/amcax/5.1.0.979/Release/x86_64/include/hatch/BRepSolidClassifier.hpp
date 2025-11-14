/// @file      BRepSolidClassifier.hpp
/// @brief     Class for classifying geometric points with a solid
/// @copyright Copyright (c) 2024 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <common/DirectionT.hpp>
#include <common/PointT.hpp>
#include <topology/TopoFace.hpp>
#include <topology/TopoSolid.hpp>

namespace AMCAX
{
#ifndef DOXYGEN_SKIP
class SolidClassifierImp;
#endif

/// @brief Class for classifying geometric points with a solid
class BRepSolidClassifier
{
public:
	/// @brief Construct from the solid to be processed
	/// @param s The input solid
	AMCAX_API explicit BRepSolidClassifier(const TopoSolid& s);

	/// @brief Classify a point on solid with tolerance
	/// @param p The point
	/// @param tol The tolerance
	AMCAX_API void Perform(const Point3& p, double tol);

	/// @brief Get the state type of the classification result
	/// @return The state type of the classification result
	[[nodiscard]] AMCAX_API StateType State() const;

	/// @brief Can only be used when the state type is on. Obtain the information of the face where the point on
	/// @param[out] facePoint The point on the face
	/// @param[out] normal The normal of the face surface at point
	/// @return The face where the point on
	AMCAX_API TopoFace OnFaceInfo(Point3& facePoint, Direction3& normal) const;

private:
	BRepSolidClassifier(const BRepSolidClassifier&) = delete;
	BRepSolidClassifier& operator=(const BRepSolidClassifier&) = delete;

	std::shared_ptr<SolidClassifierImp> sClassifier;
};
} // namespace AMCAX
